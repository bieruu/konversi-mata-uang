#!/bin/bash

# Program Konversi Mata Uang - Uninstaller
# Script untuk uninstall program dan membersihkan file-file yang terkait
# Termasuk dependencies yang hanya digunakan oleh program ini

# Setup error logging dengan permission yang lebih aman
ERROR_LOG="/tmp/uninstall_error_$$"
exec 2>> "$ERROR_LOG"

# Fungsi untuk cek apakah script dijalankan sebagai root
cek_root() {
    if [ "$EUID" -eq 0 ]; then
        return 0
    else
        return 1
    fi
}

# Fungsi untuk elevasi privilege otomatis
elevate_privilege() {
    if ! cek_root; then
        echo "[INFO] Memerlukan hak akses administrator untuk melanjutkan..."
        echo "[INFO] Script akan dijalankan ulang dengan sudo..."
        exec sudo "$0" "$@"
        exit $?
    fi
}

# Fungsi untuk cek apakah package terinstall
cek_package() {
    if command -v dpkg &> /dev/null; then
        dpkg -l | grep -q "^ii.*$1"
    elif command -v rpm &> /dev/null; then
        rpm -q "$1" &> /dev/null
    elif command -v pacman &> /dev/null; then
        pacman -Q "$1" &> /dev/null
    else
        return 1
    fi
}

# Fungsi untuk cek apakah package digunakan oleh program lain
cek_package_usage() {
    local package="$1"
    
    # Cek apakah package ini digunakan oleh program lain
    if command -v dpkg &> /dev/null; then
        # Untuk Debian/Ubuntu, cek reverse dependencies
        local reverse_deps=$(apt-cache rdepends "$package" 2>/dev/null | grep -c "ii" || echo "0")
        # Handle multi-line output by taking only the first line
        reverse_deps=$(echo "$reverse_deps" | head -n 1)
        # Ensure it's a valid number
        if ! [[ "$reverse_deps" =~ ^[0-9]+$ ]]; then
            reverse_deps=0
        fi
        if [ "$reverse_deps" -gt 1 ]; then
            return 1  # Masih digunakan oleh program lain
        fi
    fi
    
    return 0  # Aman untuk dihapus
}

# Fungsi untuk uninstall dependencies
uninstall_dependencies() {
    echo ""
    echo "[INFO] Memeriksa dependencies yang terinstall..."
    
    # Deteksi distribusi
    if [ -f /etc/debian_version ]; then
        DISTRO="debian"
    elif [ -f /etc/redhat-release ]; then
        DISTRO="redhat"
    elif [ -f /etc/arch-release ]; then
        DISTRO="arch"
    else
        echo "[INFO] Sistem operasi tidak didukung untuk uninstall dependencies"
        return 1
    fi
    
    # Dependencies yang diinstall oleh program ini
    DEPS_TO_CHECK=()
    if [ "$DISTRO" = "debian" ]; then
        DEPS_TO_CHECK=("libcpr-dev" "nlohmann-json3-dev" "build-essential")
    elif [ "$DISTRO" = "redhat" ]; then
        DEPS_TO_CHECK=("cpr-devel" "nlohmann-json-devel" "gcc-c++")
    elif [ "$DISTRO" = "arch" ]; then
        DEPS_TO_CHECK=("cpr" "nlohmann-json" "base-devel")
    fi
    
    # Cek dependencies yang terinstall
    INSTALLED_DEPS=()
    for dep in "${DEPS_TO_CHECK[@]}"; do
        if cek_package "$dep"; then
            INSTALLED_DEPS+=("$dep")
        fi
    done
    
    if [ ${#INSTALLED_DEPS[@]} -eq 0 ]; then
        echo "[INFO] Tidak ada dependencies yang perlu diuninstall"
        return 0
    fi
    
    echo ""
    echo "[📋] Dependencies yang terdeteksi:"
    for dep in "${INSTALLED_DEPS[@]}"; do
        echo "  - $dep"
    done
    
    echo ""
    echo "[INFO] Memeriksa apakah dependencies masih digunakan oleh program lain..."
    
    # Cek apakah dependencies aman dihapus
    SAFE_TO_REMOVE=()
    for dep in "${INSTALLED_DEPS[@]}"; do
        if cek_package_usage "$dep"; then
            echo "  ✅ $dep - Aman dihapus (hanya digunakan oleh program ini)"
            SAFE_TO_REMOVE+=("$dep")
        else
            echo "  ⚠️  $dep - Masih digunakan oleh program lain"
        fi
    done
    
    if [ ${#SAFE_TO_REMOVE[@]} -eq 0 ]; then
        echo ""
        echo "[INFO] Tidak ada dependencies yang aman dihapus"
        echo "Dependencies ini masih digunakan oleh program lain di sistem Anda"
        return 0
    fi
    
    echo ""
    echo "[⚠️ ] Peringatan: Dependencies berikut akan dihapus:"
    for dep in "${SAFE_TO_REMOVE[@]}"; do
        echo "  - $dep"
    done
    
    echo ""
    echo "[INFO] Dependencies ini aman dihapus karena hanya digunakan oleh program ini"
    echo "[INFO] Menghapus dependencies secara otomatis..."
    
    # Hapus dependencies tanpa memerlukan konfirmasi user
    # Karena sudah dicek aman untuk dihapus
    for dep in "${SAFE_TO_REMOVE[@]}"; do
        echo "  - Menghapus $dep..."
        if [ "$DISTRO" = "debian" ]; then
            apt-get remove -y "$dep" && apt-get autoremove -y
        elif [ "$DISTRO" = "redhat" ]; then
            yum remove -y "$dep"
        elif [ "$DISTRO" = "arch" ]; then
            pacman -R --noconfirm "$dep"
        fi
        
        if [ $? -eq 0 ]; then
            echo "    ✅ $dep berhasil dihapus"
        else
            echo "    ❌ Gagal menghapus $dep"
        fi
    done
    
    echo ""
    echo "[INFO] Update package database..."
    if [ "$DISTRO" = "debian" ]; then
        apt-get update
    elif [ "$DISTRO" = "redhat" ]; then
        yum update -y
    elif [ "$DISTRO" = "arch" ]; then
        pacman -Sy
    fi
    
    echo ""
    echo "✅ Dependencies berhasil diuninstall!"
}

# Cek dan elevasi privilege jika diperlukan
elevate_privilege

echo "=========================================="
echo "  Uninstaller Program Konversi Mata Uang  "
echo "=========================================="
echo ""
echo "[INFO] Error logging diaktifkan: $ERROR_LOG"
echo ""

# Fungsi untuk cek apakah file ada
cek_file() {
    if [ -f "$1" ]; then
        return 0
    else
        return 1
    fi
}

# Fungsi untuk hapus file
hapus_file() {
    if cek_file "$1"; then
        rm -f "$1"
        if [ $? -eq 0 ]; then
            echo "  ✅ $1 dihapus"
        else
            echo "  ❌ Gagal hapus $1"
        fi
    else
        echo "  ⚠️  $1 tidak ditemukan"
    fi
}

# Fungsi untuk hapus direktori
hapus_dir() {
    if [ -d "$1" ]; then
        rm -rf "$1"
        if [ $? -eq 0 ]; then
            echo "  ✅ $1 dihapus"
        else
            echo "  ❌ Gagal hapus $1"
        fi
    else
        echo "  ⚠️  $1 tidak ditemukan"
    fi
}

# Cek apakah program sedang berjalan
if pgrep -f "Project.out" > /dev/null; then
    echo "[⚠️ ] Peringatan: Program sedang berjalan!"
    echo "[INFO] Untuk hasil terbaik, sebaiknya hentikan program terlebih dahulu:"
    echo "  pkill -f 'Project'"
    echo "[INFO] Melanjutkan proses uninstall..."
fi

echo "[INFO] Mendeteksi file-file yang terkait..."

# Deteksi file yang akan dihapus
FILES_TO_REMOVE=()
DIRS_TO_REMOVE=()

# File executable
if cek_file "./Project.out"; then
    FILES_TO_REMOVE+=("./Project.out")
fi

# Cache kurs
if cek_file "./currency_cache.txt"; then
    FILES_TO_REMOVE+=("./currency_cache.txt")
fi

# File installer
if cek_file "./install.sh"; then
    FILES_TO_REMOVE+=("./install.sh")
fi
if cek_file "./run.sh"; then
    FILES_TO_REMOVE+=("./run.sh")
fi
if cek_file "./uninstall.sh"; then
    FILES_TO_REMOVE+=("./uninstall.sh")
fi

# File Windows (jika ada)
if cek_file "./install.bat"; then
    FILES_TO_REMOVE+=("./install.bat")
fi
if cek_file "./run.bat"; then
    FILES_TO_REMOVE+=("./run.bat")
fi
if cek_file "./uninstall.bat"; then
    FILES_TO_REMOVE+=("./uninstall.bat")
fi

# Direktori
if [ -d "./src" ]; then
    DIRS_TO_REMOVE+=("./src")
fi
if [ -d "./scripts" ]; then
    DIRS_TO_REMOVE+=("./scripts")
fi
if [ -d "./docs" ]; then
    DIRS_TO_REMOVE+=("./docs")
fi

# Tampilkan file yang akan dihapus
echo ""
echo "[📋] File yang akan dihapus:"
for file in "${FILES_TO_REMOVE[@]}"; do
    echo "  - $file"
done
for dir in "${DIRS_TO_REMOVE[@]}"; do
    echo "  - $dir/"
done

if [ ${#FILES_TO_REMOVE[@]} -eq 0 ] && [ ${#DIRS_TO_REMOVE[@]} -eq 0 ]; then
    echo ""
    echo "❌ Tidak ada file yang perlu dihapus!"
    echo "Program mungkin belum pernah diinstall."
    exit 1
fi

echo ""
echo "=========================================="
echo "  Pilihan Uninstall                      "
echo "=========================================="
echo "1. Uninstall Normal (hapus program saja)"
echo "2. Uninstall Masif (hapus semua termasuk cache dan dokumentasi)"
echo "3. Uninstall Lengkap (hapus program + dependencies)"
echo "4. Batalkan"
echo "=========================================="
echo ""
read -p "Pilih opsi (1/2/3/4): " PILIHAN 2>/dev/null

case $PILIHAN in
    1)
        echo ""
        echo "[INFO] Melakukan uninstall normal..."
        echo "[INFO] Hanya menghapus program dan cache..."
        
        # Hapus file utama
        hapus_file "./Project.out"
        hapus_file "./currency_cache.txt"
        
        echo ""
        echo "✅ Uninstall normal selesai!"
        echo ""
        echo "[INFO] File yang masih tersisa:"
        echo "  - README.md (dokumentasi)"
        echo "  - docs/ (dokumentasi lengkap)"
        echo "  - src/ (source code)"
        echo "  - scripts/ (installer)"
        echo ""
        echo "Program sudah diuninstall. File dokumentasi masih tersedia."
        ;;
        
    2)
        echo ""
        echo "[INFO] Melakukan uninstall masif..."
        echo "[INFO] Menghapus semua file termasuk cache dan dokumentasi..."
        
        # Hapus semua file
        for file in "${FILES_TO_REMOVE[@]}"; do
            hapus_file "$file"
        done
        
        # Hapus direktori
        for dir in "${DIRS_TO_REMOVE[@]}"; do
            hapus_dir "$dir"
        done
        
        # Hapus README.md juga
        hapus_file "./README.md"
        
        echo ""
        echo "[⚠️ ] Peringatan: Opsi ini akan menghapus SELURUH folder project!"
        echo "[⚠️ ] Semua file dan subfolder di dalamnya akan hilang selamanya!"
        echo ""
        read -p "Apakah Anda yakin ingin menghapus seluruh folder project? (ketik 'YA' untuk melanjutkan): " KONFIRMASI
        
        if [ "$KONFIRMASI" = "YA" ] || [ "$KONFIRMASI" = "ya" ]; then
            echo ""
            echo "[INFO] Menghapus folder project secara permanen..."
            
            # Dapatkan path folder project saat ini
            PROJECT_DIR=$(pwd)
            PARENT_DIR=$(dirname "$PROJECT_DIR")
            PROJECT_NAME=$(basename "$PROJECT_DIR")
            
            # Kembali ke parent directory
            cd "$PARENT_DIR"
            
            # Hapus folder project dengan sudo jika diperlukan
            if [ -d "$PROJECT_NAME" ]; then
                sudo rm -rf "$PROJECT_NAME" 2>/dev/null || rm -rf "$PROJECT_NAME"
                if [ $? -eq 0 ]; then
                    echo "  ✅ Folder project '$PROJECT_NAME' dihapus secara permanen"
                else
                    echo "  ❌ Gagal menghapus folder project"
                fi
            else
                echo "  ⚠️  Folder project tidak ditemukan"
            fi
            
            echo ""
            echo "✅ Uninstall masif selesai!"
            echo ""
            echo "❌ SEMUA FILE DAN FOLDER PROJECT TELAH DIHAPUS PERMANEN!"
            echo ""
            echo "[INFO] Semua file program dan folder project sudah dihapus."
            echo "Program telah dibersihkan sepenuhnya dari sistem Anda."
        else
            echo ""
            echo "[INFO] Menghapus file program saja (folder project tetap ada)..."
            echo ""
            echo "✅ Uninstall masif selesai!"
            echo ""
            echo "❌ Semua file program telah dihapus!"
            echo ""
            echo "[INFO] Program dan semua file terkait sudah dihapus."
            echo "Folder project masih ada, tapi isinya sudah dibersihkan."
        fi
        ;;
        
    3)
        echo ""
        echo "[INFO] Melakukan uninstall lengkap..."
        echo "[INFO] Menghapus program, dependencies, dan file terkait..."
        
        # Uninstall dependencies terlebih dahulu
        uninstall_dependencies
        
        # Hapus semua file program
        for file in "${FILES_TO_REMOVE[@]}"; do
            hapus_file "$file"
        done
        
        # Hapus direktori
        for dir in "${DIRS_TO_REMOVE[@]}"; do
            hapus_dir "$dir"
        done
        
        echo ""
        echo "✅ Uninstall lengkap selesai!"
        echo ""
        echo "[INFO] Program dan dependencies yang tidak digunakan telah dihapus."
        echo "Sistem Anda telah dibersihkan dari sisa-sisa program ini."
        ;;
        
    4)
        echo ""
        echo "❌ Uninstall dibatalkan."
        echo "Program tetap terinstall."
        exit 0
        ;;
        
    *)
        echo ""
        echo "❌ Pilihan tidak valid!"
        echo "Uninstall dibatalkan."
        exit 1
        ;;
esac

echo ""
echo "=========================================="
echo "  Terima kasih!                           "
echo "=========================================="
echo ""

# Tampilkan laporan error jika ada
if [ -s "$ERROR_LOG" ]; then
    echo "[⚠️ ] Beberapa error terjadi selama proses uninstall:"
    echo "=========================================="
    cat "$ERROR_LOG"
    echo "=========================================="
    echo ""
    echo "[INFO] Detail error tersimpan di: $ERROR_LOG"
else
    echo "✅ Proses uninstall selesai tanpa error!"
fi

echo ""
echo "Jika ingin install ulang, cukup jalankan:"
echo "  ./install.sh"
echo ""
echo "Sampai jumpa! 👋"

# Cleanup error log
rm -f "$ERROR_LOG"