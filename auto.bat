@echo off
setlocal enabledelayedexpansion

:menu
cls
echo.
echo Enter Experiment Number (0 to Exit)
echo.
set /p exp=Enter: 

if "%exp%"=="0" (
    cls
    doskey /reinstall >nul 2>&1
    del "%~f0"
    exit
)

if "%exp%"=="" goto menu
if %exp% LSS 0 goto menu
if %exp% GTR 12 goto menu

cls
echo =========================
echo Experiment %exp%
echo =========================
echo.

:: Clean & Reliable fetching using PowerShell
for /f "delims=" %%i in ('powershell -NoProfile -Command ^
    "$files = Invoke-RestMethod \"https://api.github.com/repos/Hkaren90/cns/contents/%exp%\" -UseBasicParsing; ^
     $files.name" 2^>nul') do (

    if not "%%i"=="" (
        echo File: %%i
        echo ================================================
        curl -sL https://raw.githubusercontent.com/Hkaren90/cns/main/%exp%/%%i
        echo.
        echo.
    )
)

echo ========================
pause
goto menu