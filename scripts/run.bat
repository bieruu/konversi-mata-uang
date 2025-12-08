@echo off
chcp 65001 >nul
echo ==========================================
echo   Menjalankan Program Konversi Mata Uang
echo ==========================================
echo.

REM Cek apakah file executable ada
if not exist "Project.exe" (
    echo [INFO] File executable tidak ditemukan
    echo [INFO] Menjalankan installer...
    echo.
    call install.bat
    
    if %ERRORLEVEL% NEQ 0 (
        echo.
        echo ==========================================
        echo   ❌ Gagal install program
        echo ==========================================
        pause
        exit /b 1
    )
)

echo [INFO] Menjalankan program...
echo.
Project.exe