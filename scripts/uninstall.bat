:: Program Konversi Mata Uang - Uninstaller
:: Batch script untuk uninstall program dan membersihkan file-file yang terkait
:: Termasuk dependencies yang hanya digunakan oleh program ini

@echo off
chcp 65001 >nul
cls

echo ==========================================
echo   Uninstaller Program Konversi Mata Uang  
echo ==========================================
echo.

:: Cek apakah program sedang berjalan
tasklist /FI "IMAGENAME eq Project.exe" 2>NUL | find /I /N "Project.exe">NUL
if "%ERRORLEVEL%"=="0" (
    echo [⚠️ ] Peringatan: Program sedang berjalan!
    echo [INFO] Untuk hasil terbaik, sebaiknya hentikan program terlebih dahulu
    echo [INFO] Melanjutkan proses uninstall...
    echo.
)

echo [INFO] Mendeteksi file-file yang terkait...
echo.

:: Deteksi file yang akan dihapus
set FILES_TO_REMOVE=
set DIRS_TO_REMOVE=

:: Cek file executable
if exist "Project.exe" (
    set FILES_TO_REMOVE=%FILES_TO_REMOVE% Project.exe
)

:: Cek cache kurs
if exist "currency_cache.txt" (
    set FILES_TO_REMOVE=%FILES_TO_REMOVE% currency_cache.txt
)

:: Cek file installer
if exist "install.sh" (
    set FILES_TO_REMOVE=%FILES_TO_REMOVE% install.sh
)
if exist "run.sh" (
    set FILES_TO_REMOVE=%FILES_TO_REMOVE% run.sh
)
if exist "uninstall.sh" (
    set FILES_TO_REMOVE=%FILES_TO_REMOVE% uninstall.sh
)

:: Cek file Windows
if exist "install.bat" (
    set FILES_TO_REMOVE=%FILES_TO_REMOVE% install.bat
)
if exist "run.bat" (
    set FILES_TO_REMOVE=%FILES_TO_REMOVE% run.bat
)
if exist "uninstall.bat" (
    set FILES_TO_REMOVE=%FILES_TO_REMOVE% uninstall.bat
)

:: Cek direktori
if exist "src" (
    set DIRS_TO_REMOVE=%DIRS_TO_REMOVE% src
)
if exist "scripts" (
    set DIRS_TO_REMOVE=%DIRS_TO_REMOVE% scripts
)
if exist "docs" (
    set DIRS_TO_REMOVE=%DIRS_TO_REMOVE% docs
)

:: Tampilkan file yang akan dihapus
echo [📋] File yang akan dihapus:
for %%f in (%FILES_TO_REMOVE%) do (
    echo   - %%f
)
for %%d in (%DIRS_TO_REMOVE%) do (
    echo   - %%d/
)

:: Cek jika tidak ada file yang perlu dihapus
if "%FILES_TO_REMOVE%"=="" if "%DIRS_TO_REMOVE%"=="" (
    echo.
    echo ❌ Tidak ada file yang perlu dihapus!
    echo Program mungkin belum pernah diinstall.
    pause
    exit /b 1
)

echo.
echo ==========================================
echo   Pilihan Uninstall                        
echo ==========================================
echo 1. Uninstall Normal (hapus program saja)
echo 2. Uninstall Masif (hapus semua termasuk cache dan dokumentasi)
echo 3. Batalkan
echo ==========================================
echo.
set /p PILIHAN=Pilih opsi (1/2/3): 

if "%PILIHAN%"=="1" goto UNINSTALL_NORMAL
if "%PILIHAN%"=="2" goto UNINSTALL_MASSIVE
if "%PILIHAN%"=="3" goto BATAL

echo.
echo ❌ Pilihan tidak valid!
echo Uninstall dibatalkan.
pause
exit /b 1

:UNINSTALL_NORMAL
echo.
echo [INFO] Melakukan uninstall normal...
echo [INFO] Hanya menghapus program dan cache...
echo.

:: Hapus file utama
if exist "Project.exe" (
    del "Project.exe"
    if errorlevel 1 (
        echo   ❌ Gagal hapus Project.exe
    ) else (
        echo   ✅ Project.exe dihapus
    )
)

if exist "currency_cache.txt" (
    del "currency_cache.txt"
    if errorlevel 1 (
        echo   ❌ Gagal hapus currency_cache.txt
    ) else (
        echo   ✅ currency_cache.txt dihapus
    )
)

echo.
echo ✅ Uninstall normal selesai!
echo.
echo [INFO] File yang masih tersisa:
echo   - README.md (dokumentasi)
echo   - docs/ (dokumentasi lengkap)
echo   - src/ (source code)
echo   - scripts/ (installer)
echo.
echo Program sudah diuninstall. File dokumentasi masih tersedia.
goto SELESAI

:UNINSTALL_MASSIVE
echo.
echo [INFO] Melakukan uninstall masif...
echo [INFO] Menghapus semua file termasuk cache dan dokumentasi...
echo.

:: Hapus semua file
for %%f in (%FILES_TO_REMOVE%) do (
    if exist "%%f" (
        del "%%f"
        if errorlevel 1 (
            echo   ❌ Gagal hapus %%f
        ) else (
            echo   ✅ %%f dihapus
        )
    ) else (
        echo   ⚠️  %%f tidak ditemukan
    )
)

:: Hapus direktori
for %%d in (%DIRS_TO_REMOVE%) do (
    if exist "%%d" (
        rmdir /s /q "%%d"
        if errorlevel 1 (
            echo   ❌ Gagal hapus %%d
        ) else (
            echo   ✅ %%d dihapus
        )
    ) else (
        echo   ⚠️  %%d tidak ditemukan
    )
)

:: Hapus README.md juga
if exist "README.md" (
    del "README.md"
    if errorlevel 1 (
        echo   ❌ Gagal hapus README.md
    ) else (
        echo   ✅ README.md dihapus
    )
)

echo.
echo [⚠️ ] Peringatan: Opsi ini akan menghapus SELURUH folder project!
echo [⚠️ ] Semua file dan subfolder di dalamnya akan hilang selamanya!
echo.
set /p KONFIRMASI=Apakah Anda yakin ingin menghapus seluruh folder project? (ketik 'YA' untuk melanjutkan): 

if /i "%KONFIRMASI%"=="YA" goto HAPUS_FOLDER

echo.
echo [INFO] Menghapus file program saja (folder project tetap ada)...
echo.
echo ✅ Uninstall masif selesai!
echo.
echo ❌ Semua file program telah dihapus!
echo.
echo [INFO] Program dan semua file terkait sudah dihapus.
echo Folder project masih ada, tapi isinya sudah dibersihkan.
goto SELESAI

:HAPUS_FOLDER
echo.
echo [INFO] Menghapus folder project secara permanen...
echo.

:: Dapatkan path folder project saat ini
for %%I in (.) do set PROJECT_NAME=%%~nI
cd ..
if exist "%PROJECT_NAME%" (
    rmdir /s /q "%PROJECT_NAME%"
    if errorlevel 1 (
        echo   ❌ Gagal menghapus folder project
    ) else (
        echo   ✅ Folder project '%PROJECT_NAME%' dihapus secara permanen
    )
) else (
    echo   ⚠️  Folder project tidak ditemukan
)

echo.
echo ✅ Uninstall masif selesai!
echo.
echo ❌ SEMUA FILE DAN FOLDER PROJECT TELAH DIHAPUS PERMANEN!
echo.
echo [INFO] Semua file program dan folder project sudah dihapus.
echo Program telah dibersihkan sepenuhnya dari sistem Anda.
goto SELESAI

:BATAL
echo.
echo ❌ Uninstall dibatalkan.
echo Program tetap terinstall.
pause
exit /b 0

:SELESAI
echo.
echo ==========================================
echo   Terima kasih!                           
echo ==========================================
echo.
echo Jika ingin install ulang, cukup jalankan:
echo   install.bat
echo.
echo Sampai jumpa! 👋
echo.
pause