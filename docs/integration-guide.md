# Swisstrain Project Integration Guide

Stand: 2026-06-06

## Zielbild

Das Repository ist so organisiert, dass der **Linux-Hermes-Host** die Vorbereitung übernimmt und ein **separater Windows-Rechner** die eigentliche Unreal-Editor- und Windows-Build-Arbeit ausführt.

## Host-Rollen

### Linux-Hermes-Host

Verantwortlich für:

- Repo-Verwaltung
- Dokumentation
- swisstopo-Datenbeschaffung
- Terrain-/Heightmap-Vorverarbeitung
- Skripte, Konvertierung und Validierung
- Multi-Agent-Orchestrierung

### Windows Build/Authoring Host

Verantwortlich für:

- Unreal Engine 5.5 Installation
- Visual Studio 2022 Toolchain
- Generierung der Projektdateien
- Build von `SwisstrainEditor`
- Öffnen des Projekts im Unreal Editor
- später Cook/Package für Windows

## Aktiver Build-Stand

Der aktuell stabile Build-Stand ist bewusst konservativ:

- aktives Projektmodul: `Swisstrain`
- aktive Unreal-Dateien:
  - `Swisstrain.uproject`
  - `Source/Swisstrain.Target.cs`
  - `Source/SwisstrainEditor.Target.cs`
  - `Source/Swisstrain/Swisstrain.Build.cs`
  - `Source/Swisstrain/Public/Swisstrain.h`
  - `Source/Swisstrain/Private/Swisstrain.cpp`
  - `Scripts/Build/build.bat`

Zusätzliche Quellbäume wie `Source/SwisstrainLandscape/` und `Source/SwisstrainRail/` bleiben aktuell als **Scaffolding / Referenzmaterial** im Repo, sind aber noch nicht in die aktive Projektkonfiguration eingehängt. Dadurch blockieren halbfertige Feature-Module den Windows-Build nicht.

## Repository-Struktur

```text
swisstrain/
├── Content/
├── Docs/
├── Scripts/
│   ├── Build/
│   │   ├── build.bat
│   │   └── build.sh
│   ├── process_swisstopo_data.py
│   └── validate_swisstopo_data.py
├── Source/
│   ├── Swisstrain/
│   ├── Swisstrain.Target.cs
│   ├── SwisstrainEditor.Target.cs
│   ├── SwisstrainLandscape/   # noch nicht aktiv eingebunden
│   └── SwisstrainRail/        # noch nicht aktiv eingebunden
├── docs/
├── .gitattributes
├── .gitignore
└── Swisstrain.uproject
```

## Git LFS

Git LFS ist aktiv für:

- Texturen
- Meshes
- RAW-Heightmaps
- `.uasset`
- `.umap`
- Audiodateien

Nach jedem Clone/Pull:

```bash
git lfs pull
```

## Windows-Build-Einstieg

Der empfohlene erste Build auf Windows ist:

```powershell
cd C:\dev\swisstrain
.\Scripts\Build\build.bat
```

Details dazu stehen in:

- `docs/windows-build-host-setup.md`

## Nächste Integrationsschritte

Nach dem stabilen Basis-Build werden die Feature-Module kontrolliert wieder aktiviert:

1. Landscape-Modul bereinigen und validieren
2. Rail-/Track-Modul bereinigen und validieren
3. Simulation einkoppeln
4. Packaging-/UAT-Skripte erweitern

Damit bleibt jeder Zwischenschritt auf Windows nachvollziehbar und buildbar.
