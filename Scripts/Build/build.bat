@echo off
setlocal EnableExtensions

set "SCRIPT_DIR=%~dp0"
for %%I in ("%SCRIPT_DIR%..\..") do set "PROJECT_ROOT=%%~fI"
set "PROJECT_FILE=%PROJECT_ROOT%\Swisstrain.uproject"

if not exist "%PROJECT_FILE%" (
  echo ERROR: Project file not found: "%PROJECT_FILE%"
  exit /b 1
)

set "UE_ROOT="

if defined UE_PATH (
  set "UE_ROOT=%UE_PATH%"
  if "%UE_ROOT:~-1%"=="\" set "UE_ROOT=%UE_ROOT:~0,-1%"
  goto :check_root
)

for %%P in (
  "C:\Program Files\Epic Games\UE_5.5"
  "D:\Program Files\Epic Games\UE_5.5"
  "D:\Epic Games\UE_5.5"
  "D:\UE_5.5"
) do (
  if exist "%%~P\Engine\Build\BatchFiles\Build.bat" (
    set "UE_ROOT=%%~P"
    goto :check_root
  )
)

echo ERROR: Unreal Engine 5.5 not found automatically.
echo.
echo Tried common locations:
echo   C:\Program Files\Epic Games\UE_5.5
echo   D:\Program Files\Epic Games\UE_5.5
echo   D:\Epic Games\UE_5.5
echo   D:\UE_5.5
echo.
echo Set UE_PATH to the Unreal root folder that directly contains the Engine directory.
echo Example:
echo   set UE_PATH=D:\Epic Games\UE_5.5
exit /b 1

:check_root
set "BUILD_BAT=%UE_ROOT%\Engine\Build\BatchFiles\Build.bat"

if not exist "%BUILD_BAT%" (
  echo ERROR: Build.bat not found under "%UE_ROOT%"
  echo Expected file:
  echo   %BUILD_BAT%
  exit /b 1
)

echo Using Unreal Engine root: "%UE_ROOT%"
echo [1/2] Generating Visual Studio project files via Build.bat -projectfiles ...
call "%BUILD_BAT%" -projectfiles -project="%PROJECT_FILE%" -game -rocket -progress
if errorlevel 1 exit /b %errorlevel%

echo [2/2] Building SwisstrainEditor Win64 Development...
call "%BUILD_BAT%" SwisstrainEditor Win64 Development "%PROJECT_FILE%" -WaitMutex -NoHotReloadFromIDE
if errorlevel 1 exit /b %errorlevel%

echo Build finished successfully.
exit /b 0
