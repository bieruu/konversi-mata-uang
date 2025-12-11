@echo off
chcp 65001 >nul
echo ==========================================
echo   Installer Program Konversi Mata Uang
echo ==========================================
echo.

REM Cek apakah Chocolatey sudah terinstall
where /q choco
if %ERRORLEVEL% NEQ 0 (
    echo [INFO] Chocolatey belum terinstall
    echo [INFO] Menginstall Chocolatey...
    @"%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe" -NoProfile -InputFormat None -ExecutionPolicy Bypass -Command "iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))" && SET "PATH=%PATH%;%ALLUSERSPROFILE%\chocolatey\bin"
    if %ERRORLEVEL% NEQ 0 (
        echo [ERROR] Gagal menginstall Chocolatey
        echo Silakan install manual:
        echo   1. Buka PowerShell sebagai Administrator
        echo   2. Jalankan: iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))
        pause
        exit /b 1
    )
)

echo [INFO] Mengupdate Chocolatey...
choco upgrade chocolatey -y

echo.
echo [INFO] Menginstall library yang dibutuhkan...

REM Install MinGW (compiler)
echo   - Menginstall MinGW...
choco install mingw -y

REM Install CPR library
echo   - Menginstall CPR library...
choco install cpr -y

REM Install Nlohmann JSON
echo   - Menginstall Nlohmann JSON...
choco install nlohmann-json -y

echo.
echo [INFO] Compile program...
g++ -o Project Project.cpp -std=c++11 -lcpr -lnlohmann_json

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ==========================================
    echo   ✅ Instalasi berhasil!
    echo ==========================================
    echo.
    echo Program siap digunakan!
    echo.
    echo Cara menjalankan:
    echo   ./Project
    echo.
    echo File yang dibuat:
    echo   - Project.exe (executable)
    echo   - currency_cache.txt (cache kurs)
    echo.
    echo [INFO] Menghapus installer untuk pengalaman yang lebih bersih...
    echo.
    
    REM Hapus installer setelah instalasi berhasil
    if exist "scripts\install.bat" (
        del "scripts\install.bat"
        echo   ✅ scripts\install.bat dihapus
    )
    
    if exist "install.bat" (
        del "install.bat"
        echo   ✅ install.bat dihapus
    )
    
    echo.
    echo ✅ Instalasi selesai! Sekarang Anda hanya perlu menjalankan:
    echo    ./Project
    echo.
    pause
) else (
    echo.
    echo ==========================================
    echo   ❌ Gagal compile program
    echo ==========================================
    echo.
    echo Silakan cek error di atas dan coba lagi.
    pause
    exit /b 1
)