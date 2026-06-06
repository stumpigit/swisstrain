# Swisstrain V1 Implementation Brief

## Kurzfassung

Baue **kein großes Zugsimulationsspiel**, sondern einen **editor-first Authoring Slice** in Unreal 5.5:

1. **Terrain + Look**
2. **Track-Authoring**
3. **Simple scenic train run**
4. **Repo / Build / Doku sauberziehen**

## Reihenfolge

### Phase 1 — Terrain Slice (`swisstrain-terrain`)

Erstes Zielbild:

- Terrain aus dem definierten swisstopo-Ausschnitt vorbereitet
- atmosphärische, gemütliche Schweizer Bergszene
- Wasser, Vegetation, Material-Layer, Lichtstimmung
- Review-fähiger Slice im Unreal Editor

Falls nötig, darf diese Phase auch ein **minimales Unreal-5.5-Projektgerüst** anlegen, damit die Landschaft überhaupt authorbar wird.

### Phase 2 — Track Editor (`swisstrain-track`)

Zweites Zielbild:

- angenehm benutzbarer In-Editor-Trassee-Workflow
- Splines, Station-Anker, Brücke/Tunnel/Einschnitt/Damm-Heuristik
- klar sichtbar: man baut eine Bahnlinie auf dieser Landschaft

### Phase 3 — Train Run (`swisstrain-sim`)

Drittes Zielbild:

- ein oder mehrere Züge fahren die gebauten Strecken ab
- Stops funktionieren
- die Fahrt sieht gut aus und macht Spaß

### Phase 4 — Integration (`swisstrain-integrator`)

Abschlussziel:

- Repo sauber strukturiert
- Git LFS aktiv
- minimale Build-/CI-/Setup-Basis gelegt
- Dokumentation für spätere externe Build-Machine vorhanden

## Qualitätsmaßstab

V1 ist erfolgreich, wenn:

- die Landschaft bereits schön wirkt
- der Editor-Workflow Freude macht
- ein Zug sichtbar durch die gebaute Welt fährt
- das Repo nicht chaotisch ist

V1 ist **nicht** daran zu messen, wie vollständig oder realistisch die Simulation ist.

## Technische Leitlinien

- Unreal Engine 5.5
- Windows-first
- Blueprint-first, C++ selektiv
- Git LFS für Binärdaten
- pragmatische Assets erlaubt
- Terraindaten auf swisstopo-Basis
- Remote-Build/Authoring auf separater Windows-Maschine vorbereiten
- dieser Linux-Host ist Orchestrierungs-, Daten- und Prep-Host, nicht der finale Windows-Build-Host

## Übergaberegeln zwischen Phasen

### Phase 1 → 2

Track-Editor startet erst, wenn ein brauchbarer Landschafts-Slice mit klarer Material-/Topografie-Basis vorhanden ist.

### Phase 2 → 3

Simulation startet erst, wenn mindestens eine authorbare und befahrbare Strecke samt einfachen Stops existiert.

### Phase 3 → 4

Integration zieht erst nach, wenn Kernfunktionalität sichtbar vorhanden ist.
