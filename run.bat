@echo off
chcp 65001 >nul

REM Redirect ke runner di folder scripts
if exist "scripts\run.bat" (
    call scripts\run.bat %*
) else (
    echo ❌ Runner tidak ditemukan di folder scripts\
    echo Silakan jalankan: scripts\run.bat
    pause
    exit /b 1
)