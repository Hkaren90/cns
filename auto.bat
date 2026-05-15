@echo off
setlocal enabledelayedexpansion

:menu
cls
echo.
echo Enter Experiment Number (0 to Exit)
echo.
set /p exp=Enter: 

if "%exp%"=="0" exit

if "%exp%"=="" goto menu
if %exp% LSS 0 goto menu
if %exp% GTR 12 goto menu

cls
echo =========================
echo Experiment %exp%
echo =========================
echo.

:: Get list of files
powershell -NoProfile -Command "Invoke-RestMethod 'https://api.github.com/repos/Hkaren90/cns/contents/%exp%' | Select-Object -ExpandProperty name" > files.txt 2>nul

:: Show files and content
for /f "delims=" %%i in (files.txt) do (
    if not "%%i"=="" (
        echo --- %%i ---
        echo.
        curl -sL https://raw.githubusercontent.com/Hkaren90/cns/main/%exp%/%%i
        echo.
        echo.
    )
)

del files.txt 2>nul
pause
goto menu