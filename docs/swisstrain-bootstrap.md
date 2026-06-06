# Swisstrain Bootstrap

Stand: 2026-06-06

## Ziel

Swisstrain ist eine **editor-first Landschafts- und Streckenbau-Sandbox** für den Eigengebrauch.

Priorisierte Entwicklungsreihenfolge:

1. **Schöne 3D-Landschaft** im stilisierten, gemütlichen Schweizer Bergwelt-Stil
2. **Bahntrassee-Editor** mit Bahnhöfen, Brücken, Tunnels, Einschnitten und Dämmen
3. **Einfache Zugsimulation** auf den gebauten Strecken

## Verbindliche Startentscheide

- **Engine:** Unreal Engine 5.5
- **Authoring-Modus:** Unreal-Editor-Tooling, kein Runtime-Editor in V1
- **Zielplattform:** Windows
- **Stil:** stylized-realistic cozy
- **Terrain-Fidelity:** swisstopo 1:1 Basis, danach künstlerisch bereinigt
- **V1 Schienenarten:** nur normale Bahn / Adhäsionsbahn
- **Assets:** pragmatisch; Marketplace, Megascans und Platzhalter sind erlaubt
- **Tech-Mix:** Blueprint-first, mit gezielten C++-Anteilen
- **Git LFS:** ja
- **Build-Gerüst:** ja, minimal von Anfang an

## Nicht Teil von V1

- Wirtschaft / Tycoon
- Missionen / Kampagne
- aufwendige Fahrphysik
- Bergbahn, Zahnradbahn, Standseilbahn
- komplexe Disposition oder realistische Betriebsregeln
- vollwertiger Runtime-Editor

## Repo / Arbeitsort

- **GitHub:** https://github.com/stumpigit/swisstrain
- **Lokales Repo:** `/root/workspace/swisstrain`

## Build- und Authoring-Architektur

- **Dieser Host ist nicht die Unreal-Build-Maschine.**
- Die eigentliche Unreal-Authoring-/Build-Arbeit soll später auf einer **separaten Windows-Maschine** laufen.
- Dieser Linux-Host dient primär für:
  - Hermes/Kanban-Orchestrierung
  - Repo- und Doku-Arbeit
  - swisstopo-Datenbeschaffung und -Vorverarbeitung
  - Skripte, Konvertierungen und Build-Vorbereitung
- Eine reine Linux-VPS ist für das finale **Windows-Package von Unreal 5.5** nicht der Standardpfad und wird für V1 **nicht** als Ziel-Build-Umgebung vorausgesetzt.

## Terrain-Ausschnitt

DHM-Zielgebiet (EPSG:2056):

- **top-left:** `2673957.58, 1216900.00`
- **bottom-right:** `2689486.72, 1204462.45`

## Multi-Agent-Rollen

- `swisstrain-terrain` → Landschaft, Heightmap, Materialien, Wasser, Vegetation, Stimmung
- `swisstrain-track` → Trassee-Editor, Stationsanker, Splines, Brücken/Tunnels, UX für Streckenbau
- `swisstrain-sim` → einfache Zugbewegung, Stops, Reservierung, Kamerafahrt
- `swisstrain-integrator` → Repo-Struktur, Unreal-Projekt-Hygiene, Git LFS, Doku, Build-/CI-Grundgerüst
- `swisstrain-orchestrator` → Planung, Decomposition, Task-Routing

## Grundsatz für V1

Lieber ein **kleiner, wunderschöner, spaßiger Authoring-Slice** als ein breites, halbfertiges Simulationsspiel.

Die ersten Worker sollen deshalb nicht maximal viele Systeme bauen, sondern zuerst ein belastbares, schönes Kerngefühl erzeugen:

- **landschaftlich glaubwürdig**
- **visuell anmächelig**
- **beim Bauen angenehm**
- **beim Zuschauen befriedigend**
