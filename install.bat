@echo off
chcp 65001 >nul

REM Redirect ke installer di folder scripts
if exist "scripts\install.bat" (
    call scripts\install.bat %*
) else (
    echo ❌ Installer tidak ditemukan di folder scripts\
    echo Silakan jalankan: scripts\install.bat
    pause
    exit /b 1
)