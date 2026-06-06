# Swisstrain Remote Build Architecture

Stand: 2026-06-06

## Zielbild

Swisstrain wird so vorbereitet, dass die eigentliche Unreal-Editor- und Windows-Build-Arbeit **nicht auf diesem Linux-Hermes-Host**, sondern auf einer **separaten Windows-Maschine** laufen kann.

## Rollen der Maschinen

### Linux-Hermes-Host

Verantwortlich für:

- Hermes/Kanban-Orchestrierung
- Repo-Verwaltung
- Dokumentation
- swisstopo-Datenbeschaffung
- Terrain-/Heightmap-/GIS-Vorverarbeitung
- Skripte, Konvertierungen und Validierung
- Vorbereitung eines sauberen Unreal-Projekts für Übergabe an Windows

Nicht verantwortlich für:

- finale Unreal-Editor-Authoring-Sessions
- finales Windows-Packaging
- lokale Unreal-5.5-Installation als Projektvoraussetzung auf diesem Host

### Remote Windows Build/Authoring Host

Verantwortlich für:

- Unreal Engine 5.5 Installation
- Öffnen und Bearbeiten des Unreal-Projekts
- Import von Landscape-/Material-/Foliage-Assets
- Lookdev im Editor
- Build/Cook/Package für Windows
- ggf. spätere Automatisierung via UAT/BuildCookRun

## Konsequenzen für Phase 1

Phase 1 darf auf dem Linux-Host nicht pauschal mit "UE 5.5 fehlt lokal" enden, solange noch konkrete Vorarbeit möglich ist.

Erwartete vorbereitende Outputs:

- saubere swisstopo-Import-Pipeline für die festgelegte Bounding Box
- Heightmap-/Konvertierungsskripte
- Import-/Lookdev-Runbook für die Windows-Maschine
- sauberes Unreal-Projektgerüst, soweit ohne installierte Engine authorbar
- klare Liste, welche Schritte zwingend erst auf dem Windows-Host passieren

## Konsequenzen für Phase 4

Phase 4 soll explizit vorbereiten:

- Repo-Struktur für Übergabe auf Windows
- Git LFS für große Unreal-Artefakte
- Build-Skripte oder Runbooks für spätere UAT-Nutzung
- Setup-Dokumentation für den Windows-Host
- klare Trennung zwischen Prep-Host und Build-Host

## V1-Entscheid

Für V1 wird **kein Linux-only Unreal-Windows-Build-Pfad** vorausgesetzt.
Experimentelle Wege wie Wine-basierte Windows-Builds unter Linux sind nicht Teil der Basisarchitektur.
