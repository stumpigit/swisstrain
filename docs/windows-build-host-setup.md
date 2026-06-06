# Swisstrain Windows Build Host Setup Guide

Stand: 2026-06-06

## Ziel

Diese Anleitung richtet einen **separaten Windows-Rechner** so ein, dass du das aktuelle Swisstrain-Projekt mit **Unreal Engine 5.5** öffnen und den **Editor-Build** lokal erzeugen kannst.

Der Linux-Hermes-Host bleibt für Orchestrierung, Repo und Datenvorverarbeitung zuständig. Der Windows-Rechner ist der **Unreal-Authoring- und Build-Host**.

## Wichtig zum aktuellen Projektstand

Der aktuelle buildbare Basisstand ist bewusst **minimal**:

- aktives Unreal-Projektmodul: `Swisstrain`
- zusätzliche Verzeichnisse `Source/SwisstrainLandscape/` und `Source/SwisstrainRail/` sind derzeit **Scaffolding / Referenzmaterial**
- diese Zusatzmodule sind **noch nicht** in die aktive Projektkonfiguration eingehängt
- damit bleibt der Windows-Build stabil, obwohl spätere Feature-Module noch in Arbeit sind

## Voraussetzungen

- Windows 10 oder Windows 11
- Unreal Engine 5.5
- Visual Studio 2022
- Git for Windows
- Git LFS
- Python 3.11 oder ähnlich

## 1. Visual Studio 2022 installieren

Installiere Visual Studio 2022 und aktiviere mindestens diese Workloads:

- **Desktop development with C++**
- **Game development with C++**
- **.NET desktop development**

Zusätzlich empfohlen:

- aktuelles Windows 10/11 SDK
- C++ profiling tools
- C++ AddressSanitizer

## 2. Unreal Engine 5.5 installieren

1. Epic Games Launcher installieren
2. Im Launcher **Unreal Engine 5.5** installieren
3. Standardpfad merken, typischerweise:

```text
C:\Program Files\Epic Games\UE_5.5
```

Wenn dein Unreal-Pfad anders ist, setzt du später die Umgebungsvariable `UE_PATH`.

## 3. Git, Git LFS und Python installieren

In PowerShell als Administrator:

```powershell
winget install Git.Git
winget install GitHub.GitLFS
winget install Python.Python.3.11
```

Danach neues Terminal öffnen.

## 4. Repository klonen

```powershell
mkdir C:\dev -Force
cd C:\dev
git clone https://github.com/stumpigit/swisstrain.git
cd .\swisstrain
git lfs install
git lfs pull
```

## 5. Python-Umgebung für Terrain-Skripte anlegen

```powershell
cd C:\dev\swisstrain
py -3 -m venv .venv
.\.venv\Scripts\Activate.ps1
python -m pip install --upgrade pip
pip install numpy scipy
```

## 6. Hilfsskripte testen

```powershell
python .\Scripts\process_swisstopo_data.py --help
python .\Scripts\validate_swisstopo_data.py --help
```

## 7. Unreal-Projektdateien generieren und Editor bauen

### Variante A — Standardpfad für Unreal

```powershell
cd C:\dev\swisstrain
.\Scripts\Build\build.bat
```

### Variante B — Unreal liegt an anderem Ort

```powershell
cd C:\dev\swisstrain
$env:UE_PATH = 'D:\Epic\UE_5.5'
.\Scripts\Build\build.bat
```

Das Skript macht zwei Dinge:

1. `Build.bat -projectfiles -project=... -game -rocket -progress`
2. `Build.bat SwisstrainEditor Win64 Development`

## 8. Projekt im Editor öffnen

Nach erfolgreichem Build:

```powershell
& "C:\Program Files\Epic Games\UE_5.5\Engine\Binaries\Win64\UnrealEditor.exe" "C:\dev\swisstrain\Swisstrain.uproject"
```

Oder per Doppelklick auf `Swisstrain.uproject`.

## 9. Terrain-Daten vorbereiten

Wenn du bereits eine swisstopo-ASCII-Grid-Datei hast:

```powershell
mkdir .\Content\Landscape\Heightmaps -Force
python .\Scripts\process_swisstopo_data.py .\input.asc .\Content\Landscape\Heightmaps --width 2017 --height 2017
python .\Scripts\validate_swisstopo_data.py .\Content\Landscape\Heightmaps\processed_heightmap.raw --type raw --size 2017x2017
```

## 10. Terrain importieren

Im Unreal Editor:

1. `Landscape Mode`
2. `Create`
3. `Import from File`
4. RAW-Datei wählen
5. `2017 x 2017` als Importauflösung verwenden
6. Material / Water / Foliage später schrittweise ergänzen

## 11. Häufige Probleme

### Unreal wird nicht gefunden

Wichtig: `UE_PATH` muss auf den **UE-Root** zeigen, also auf den Ordner, der direkt den Unterordner `Engine` enthält.

Beispiele für korrekte Werte:

```powershell
$env:UE_PATH = 'D:\Epic Games\UE_5.5'
# oder
$env:UE_PATH = 'D:\Program Files\Epic Games\UE_5.5'
```

Schnelltest im PowerShell-Fenster:

```powershell
Test-Path "$env:UE_PATH\Engine\Build\BatchFiles\Build.bat"
```

Wenn das `False` ergibt, ist der Pfad falsch. Dann suche den echten UE-Ordner so:

```powershell
Get-ChildItem D:\ -Directory -Recurse -Filter UE_5.5 -ErrorAction SilentlyContinue | Select-Object -ExpandProperty FullName
```

Danach erneut:

```powershell
.\Scripts\Build\build.bat
```

### Git-LFS-Dateien fehlen

```powershell
git lfs install
git lfs pull
```

### Editor-Build schlägt fehl und du willst sauber neu starten

```powershell
Remove-Item .\Binaries -Recurse -Force -ErrorAction SilentlyContinue
Remove-Item .\Intermediate -Recurse -Force -ErrorAction SilentlyContinue
.\Scripts\Build\build.bat
```

## 12. Was dieser Build bewusst noch nicht tut

Der aktuelle Basisschritt stellt sicher, dass:

- die Unreal-Projekthülle gültig ist
- die Visual-Studio-Projektdateien erzeugt werden können
- `SwisstrainEditor` auf Windows buildbar ist

Die späteren Landschafts-, Gleis- und Simulationsmodule werden danach schrittweise wieder sauber eingehängt, sobald sie jeweils verifiziert sind.
