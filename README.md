# Swisstrain

Swisstrain ist ein **editor-first Unreal-5.5-Prototyp** für eine Schweizer Landschafts- und Bahn-Sandbox.

Ziel von V1 ist **nicht** ein kompletter Tycoon, sondern eine saubere Basis für:

- schöne Schweizer Landschaften
- swisstopo-basierte Terrain-Vorbereitung
- späteres Track-/Stations-Authoring
- später einfache Zugbewegung
- Windows-Authoring und Windows-Build auf separater Maschine

## Aktueller Status

Der aktuelle Repo-Stand enthält einen **minimal buildbaren Unreal-Basisstand** für Windows:

- gültige `Swisstrain.uproject`
- gültige Unreal-Targets
- ein aktives Primärmodul `Swisstrain`
- Windows-Build-Wrapper unter `Scripts/Build/build.bat`

Zusätzliche Verzeichnisse wie:

- `Source/SwisstrainLandscape/`
- `Source/SwisstrainRail/`

bleiben aktuell als **Scaffolding / Referenzmaterial** im Repo, sind aber **noch nicht** in die aktive Projektkonfiguration eingehängt. Dadurch bleibt der Editor-Build stabil, während die späteren Feature-Module separat bereinigt werden.

## Voraussetzungen für den Windows-Build

- Windows 10/11
- Unreal Engine 5.5
- Visual Studio 2022
- Git + Git LFS
- Python 3.11

## Schnellstart auf Windows

```powershell
git clone https://github.com/stumpigit/swisstrain.git
cd swisstrain
git lfs install
git lfs pull
.\Scripts\Build\build.bat
```

Eine ausführliche Schritt-für-Schritt-Anleitung steht hier:

- `docs/windows-build-host-setup.md`

## Terrain-/swisstopo-Skripte

Vorhanden und unabhängig vom Unreal-Build nutzbar:

- `Scripts/process_swisstopo_data.py`
- `Scripts/validate_swisstopo_data.py`

Beispiel:

```powershell
python .\Scripts\process_swisstopo_data.py .\input.asc .\Content\Landscape\Heightmaps --width 2017 --height 2017
python .\Scripts\validate_swisstopo_data.py .\Content\Landscape\Heightmaps\processed_heightmap.r16 --type raw --size 2017x2017
```

## Relevante Doku

- `docs/swisstrain-bootstrap.md`
- `docs/swisstrain-v1-spec.md`
- `docs/v1-implementation-brief.md`
- `docs/remote-build-architecture.md`
- `docs/windows-build-host-setup.md`
- `docs/import-runbook.md`

## Architekturhinweis

- **Linux-Hermes-Host**: Orchestrierung, Repo, Doku, Vorverarbeitung
- **Windows-Host**: Unreal Editor, Build, Cook, Package
