@echo off
setlocal

set "SCRIPT_DIR=%~dp0"
for %%I in ("%SCRIPT_DIR%..\..") do set "PROJECT_ROOT=%%~fI"
set "PROJECT_FILE=%PROJECT_ROOT%\Swisstrain.uproject"

if defined UE_PATH (
  set "UE_ROOT=%UE_PATH%"
) else (
  set "UE_ROOT=C:\Program Files\Epic Games\UE_5.5"
)

set "GEN_PROJECTS=%UE_ROOT%\Engine\Build\BatchFiles\GenerateProjectFiles.bat"
set "BUILD_BAT=%UE_ROOT%\Engine\Build\BatchFiles\Build.bat"

if not exist "%PROJECT_FILE%" (
  echo ERROR: Project file not found: "%PROJECT_FILE%"
  exit /b 1
)

if not exist "%GEN_PROJECTS%" (
  echo ERROR: GenerateProjectFiles.bat not found under "%UE_ROOT%"
  echo Set UE_PATH to your Unreal Engine 5.5 install root, e.g.:
  echo   set UE_PATH=C:\Program Files\Epic Games\UE_5.5
  exit /b 1
)

if not exist "%BUILD_BAT%" (
  echo ERROR: Build.bat not found under "%UE_ROOT%"
  exit /b 1
)

echo [1/2] Generating Visual Studio project files...
call "%GEN_PROJECTS%" -project="%PROJECT_FILE%" -game -engine
if errorlevel 1 exit /b %errorlevel%

echo [2/2] Building SwisstrainEditor Win64 Development...
call "%BUILD_BAT%" SwisstrainEditor Win64 Development "%PROJECT_FILE%" -WaitMutex -NoHotReloadFromIDE
if errorlevel 1 exit /b %errorlevel%

echo Build finished successfully.
exit /b 0
