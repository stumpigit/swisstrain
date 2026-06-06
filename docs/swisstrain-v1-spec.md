# Swisstrain V1 Specification

## 1. Produktdefinition

Swisstrain V1 ist eine **Sandbox zum Gestalten schöner Schweizer Landschaften und Bahntrassen**.

Der Schwerpunkt liegt auf:

- einer attraktiven Berglandschaft
- einem guten Editor-Workflow im Unreal Editor
- einfacher, befriedigender Zugbewegung auf selbst gebauten Strecken

Der Schwerpunkt liegt **nicht** auf Wirtschaft, Missionen oder komplexer Physik.

## 2. Harte Leitplanken

Diese Punkte sind verbindlich:

1. **Unreal Engine 5.5**
2. **Windows** als Zielplattform
3. **Editor-first**: Tools im Unreal Editor, kein vollwertiger Ingame-Editor in V1
4. **stylized-realistic cozy** Look
5. **swisstopo-DHM als 1:1 Basis**, danach künstlerisch bereinigbar
6. **nur normale Bahn** in V1
7. **Blueprint-first**, aber C++ erlaubt für Basisklassen, Utilitys und Performance-kritische Teile
8. **pragmatische Assets** sind erlaubt
9. **Git LFS** ist Pflicht für große Binärdateien
10. **Build-/CI-Gerüst minimal**, aber von Anfang an sauber anlegbar
11. **Remote-Build-Modell**: finale Unreal-Editor-/Windows-Build-Schritte laufen auf einer separaten Windows-Maschine, nicht auf diesem Linux-Hermes-Host

## 3. V1 Nicht-Ziele

Nicht in V1 bauen:

- Zahnradbahn
- Standseilbahn
- Seilbahn
- Wirtschaftssimulation
- Kampagne / Missionen
- realistische Fahrdynamik
- komplexe Signal- und Dispositionslogik
- Multiplayer
- vollwertige Betriebsplanung

## 4. Phase 1 — Landschaft zuerst

### Ziel

Ein erster spielbarer / begehbarer / betrachtbarer Landschafts-Slice mit starkem Schweizer Charakter.

### Muss enthalten

- Import oder Vorbereitung des Zielterrains aus der angegebenen swisstopo-Bounding-Box
- Terrain im Unreal-Landscape-Workflow
- mindestens ein glaubwürdiger See oder Wasserbereich
- Berg-/Talwirkung
- grundlegende Materialschichten für Fels, Wiese, Wald, Schotter/Erde
- Vegetation / Foliage-Grundsetup
- Licht / Atmosphäre / Fog / Post-Process so, dass der Look bereits angenehm wirkt
- Kamera-/Preview-Möglichkeit für Review

### Darf enthalten

- artistisches Glätten, Formen oder Komponieren einzelner Bereiche
- Platzhalter-Assets
- vereinfachte Materialsysteme, solange sie hübsch und ausbaubar sind

### Muss noch nicht enthalten

- Schienenlogik
- Simulation
- finale Performance-Optimierung

## 5. Phase 2 — Streckenbau-Editor

### Ziel

Ein angenehmer In-Editor-Workflow zum Bauen einer Bahntrasse auf der vorhandenen Landschaft.

### Muss enthalten

- Spline-basierte Streckenanlage
- einfache Stations-/Haltepunkte oder Anker
- Höhen- und Verlaufsregeln, die extremes Chaos vermeiden
- sichtbare oder halbautomatische Behandlung von:
  - Damm
  - Einschnitt
  - Brücke
  - Tunnel
- gutes visuelles Feedback beim Platzieren und Bearbeiten

### Muss nicht enthalten

- komplexe Weichenlogik
- mehrere Spurweiten
- realistische Bahnbaunormen
- große Betriebslogik

## 6. Phase 3 — Einfache Zugsimulation

### Ziel

Züge sollen die gebauten Strecken glaubwürdig und befriedigend abfahren.

### Muss enthalten

- Zug folgt Strecke
- Halte an Stationen / Haltepunkten
- einfache Geschwindigkeits- oder Fahrkurvenlogik
- minimale Reservierung / Kollisionsvermeidung, falls mehrere Züge existieren
- kamerataugliche Fahrt durch die Szene

### Muss nicht enthalten

- realistische Physik
- Signaltechnik nach Vorbild
- Rangierlogik
- komplexer Fahrplan

## 7. Build-Host-Modell

### Verbindlicher Grundsatz

- Finale **Windows-Builds** und Unreal-Editor-Arbeit müssen so vorbereitet werden, dass sie auf einer **separaten Windows-Maschine** laufen können.
- Dieser Linux-Host ist für Orchestrierung, Datenvorbereitung, Skripte und Repo-Hygiene gedacht, **nicht** als finaler Unreal-Windows-Build-Host.
- Eine Linux-VPS darf später für CI, Vorverarbeitung und Hilfsjobs genutzt werden, ist aber **nicht** das primäre Ziel für das finale Windows-Packaging in V1.

## 8. Phase 4 — Integration und Repo-Hygiene

### Ziel

Das Projekt soll als sauber strukturiertes Unreal-Repo weiterentwickelbar sein.

### Muss enthalten

- sinnvolle Projekt-/Ordnerstruktur
- `.gitattributes` / Git LFS Setup
- minimale Build-/Automations-Skripte oder dokumentierte Hooks
- Setup-Dokumentation für spätere Build-Machine
- kurze Architektur- und Workflow-Doku

## 9. Assignee-Regeln für das Board

Erlaubte spezialisierten Worker für V1:

- `swisstrain-terrain`
- `swisstrain-track`
- `swisstrain-sim`
- `swisstrain-integrator`
- `swisstrain-orchestrator`

Keine neuen Fantasie-Assignees verwenden.

## 10. Arbeitsmodus

- bevorzugt **kleine, überprüfbare Schritte**
- frühe visuelle Ergebnisse schlagen theoretische Vollständigkeit
- wenn Architekturentscheide nicht den Kurs ändern, lieber pragmatisch entscheiden als blockieren
