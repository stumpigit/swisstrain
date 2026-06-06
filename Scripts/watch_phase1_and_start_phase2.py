#!/usr/bin/env python3
import json
import os
import re
import subprocess
from pathlib import Path

BOARD = "swisstrain"
PHASE1 = "t_3b2918af"
PHASE2 = "t_de5eb3a6"
STATE_PATH = Path("/root/workspace/swisstrain/.watch_phase_state.json")


def run(cmd):
    res = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    return res.returncode, res.stdout, res.stderr


def show(task_id):
    code, out, err = run(f"hermes kanban --board {BOARD} show {task_id}")
    if code != 0:
        raise SystemExit(f"show failed for {task_id}: {err or out}")
    return out


def parse_status(show_output):
    m = re.search(r"^  status:\s+(\w+)", show_output, re.MULTILINE)
    return m.group(1) if m else "unknown"


def latest_summary(show_output):
    marker = "Latest summary:"
    if marker not in show_output:
        return ""
    after = show_output.split(marker, 1)[1]
    return after.strip().split("\n\n", 1)[0].strip()


def load_state():
    if STATE_PATH.exists():
        try:
            return json.loads(STATE_PATH.read_text())
        except Exception:
            return {}
    return {}


def save_state(state):
    STATE_PATH.write_text(json.dumps(state, indent=2, sort_keys=True))


def main():
    state = load_state()
    p1_show = show(PHASE1)
    p2_show = show(PHASE2)
    p1 = parse_status(p1_show)
    p2 = parse_status(p2_show)
    key = f"{p1}:{p2}"

    # Stay silent while Phase 1 is still running normally.
    if p1 in {"todo", "ready", "running"}:
        if state.get("last_key") != key:
            state["last_key"] = key
            save_state(state)
        return

    # If Phase 1 blocks, notify once per unique summary.
    if p1 == "blocked":
        summary = latest_summary(p1_show)
        block_key = f"blocked::{summary}"
        if state.get("last_notice") != block_key:
            state["last_key"] = key
            state["last_notice"] = block_key
            save_state(state)
            print("Swisstrain-Update: Phase 1 ist blockiert.\n")
            if summary:
                print(f"Grund: {summary}\n")
            print("Ich habe Phase 2 deshalb noch nicht gestartet.")
        return

    # Once Phase 1 is done, dispatch Phase 2 if needed.
    if p1 == "done":
        if p2 in {"todo", "ready"}:
            run(f"hermes kanban --board {BOARD} dispatch")
            p2_show = show(PHASE2)
            p2 = parse_status(p2_show)
            key = f"{p1}:{p2}"
        notice = None
        if p2 == "running":
            notice = "Swisstrain-Update: Phase 1 ist abgeschlossen und Phase 2 (Track-Editor) wurde automatisch gestartet."
        elif p2 == "done":
            notice = "Swisstrain-Update: Phase 1 war bereits abgeschlossen; Phase 2 ist ebenfalls bereits abgeschlossen."
        elif p2 in {"todo", "ready"}:
            notice = "Swisstrain-Update: Phase 1 ist abgeschlossen, aber Phase 2 konnte noch nicht gestartet werden. Bitte Board-Status prüfen."
        else:
            notice = f"Swisstrain-Update: Phase 1 ist abgeschlossen. Aktueller Phase-2-Status: {p2}."
        if state.get("last_notice") != notice:
            state["last_key"] = key
            state["last_notice"] = notice
            save_state(state)
            print(notice)
        return

    # Fallback: report unknown state changes once.
    notice = f"Swisstrain-Update: Unerwarteter Status — Phase 1: {p1}, Phase 2: {p2}."
    if state.get("last_notice") != notice:
        state["last_key"] = key
        state["last_notice"] = notice
        save_state(state)
        print(notice)


if __name__ == "__main__":
    main()
