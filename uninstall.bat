@echo off
chcp 65001 >nul

REM Redirect ke uninstaller di folder scripts
if exist "scripts\uninstall.bat" (
    call scripts\uninstall.bat %*
) else (
    echo ❌ Uninstaller tidak ditemukan di folder scripts\
    echo Silakan jalankan: scripts\uninstall.bat
    pause
    exit /b 1
)