#!/bin/bash

echo "=========================================="
echo "  Installer Program Konversi Mata Uang    "
echo "=========================================="
echo ""

# Cek apakah user adalah root
if [ "$EUID" -eq 0 ]; then
    SUDO=""
else
    SUDO="sudo"
fi

echo "[INFO] Memeriksa sistem operasi..."

# Deteksi distribusi Linux
if [ -f /etc/debian_version ]; then
    DISTRO="debian"
    echo "[INFO] Ditemukan Debian/Ubuntu"
elif [ -f /etc/redhat-release ]; then
    DISTRO="redhat"
    echo "[INFO] Ditemukan CentOS/RHEL"
elif [ -f /etc/arch-release ]; then
    DISTRO="arch"
    echo "[INFO] Ditemukan Arch Linux"
else
    echo "[ERROR] Sistem operasi tidak didukung"
    echo "Silakan install library secara manual:"
    echo "  - libcpr-dev"
    echo "  - nlohmann-json3-dev"
    exit 1
fi

echo ""
echo "[INFO] Mengupdate package list..."
if [ "$DISTRO" = "debian" ]; then
    $SUDO apt update
elif [ "$DISTRO" = "redhat" ]; then
    $SUDO yum update -y
elif [ "$DISTRO" = "arch" ]; then
    $SUDO pacman -Sy
fi

echo ""
echo "[INFO] Menginstall library yang dibutuhkan..."

# Install CPR library
echo "  - Menginstall CPR library..."
if [ "$DISTRO" = "debian" ]; then
    # Coba beberapa kemungkinan package name untuk CPR
    if $SUDO apt install -y libcpr-dev 2>/dev/null; then
        echo "    ✅ libcpr-dev berhasil diinstall"
    elif $SUDO apt install -y libcurl4-openssl-dev 2>/dev/null; then
        echo "    ✅ libcurl4-openssl-dev berhasil diinstall (alternatif)"
    else
        echo "    ⚠️  libcpr-dev tidak tersedia, mencoba compile manual..."
        # Download dan compile CPR manual
        if command -v git &> /dev/null; then
            git clone https://github.com/libcpr/cpr.git /tmp/cpr 2>/dev/null
            cd /tmp/cpr
            mkdir -p build && cd build
            cmake .. -DCPR_BUILD_TESTS=OFF -DCPR_BUILD_TOOL=OFF
            make -j$(nproc)
            $SUDO make install
            cd -
            rm -rf /tmp/cpr
            echo "    ✅ CPR berhasil diinstall manual"
        else
            echo "    ❌ Git tidak tersedia, CPR tidak bisa diinstall"
        fi
    fi
elif [ "$DISTRO" = "redhat" ]; then
    $SUDO yum install -y cpr-devel
elif [ "$DISTRO" = "arch" ]; then
    $SUDO pacman -S --noconfirm cpr
fi

# Install Nlohmann JSON
echo "  - Menginstall Nlohmann JSON..."
if [ "$DISTRO" = "debian" ]; then
    $SUDO apt install -y nlohmann-json3-dev
elif [ "$DISTRO" = "redhat" ]; then
    $SUDO yum install -y nlohmann-json-devel
elif [ "$DISTRO" = "arch" ]; then
    $SUDO pacman -S --noconfirm nlohmann-json
fi

# Install compiler g++ jika belum ada
echo "  - Memeriksa compiler g++..."
if ! command -v g++ &> /dev/null; then
    echo "  - Menginstall g++..."
    if [ "$DISTRO" = "debian" ]; then
        $SUDO apt install -y build-essential
    elif [ "$DISTRO" = "redhat" ]; then
        $SUDO yum install -y gcc-c++
    elif [ "$DISTRO" = "arch" ]; then
        $SUDO pacman -S --noconfirm base-devel
    fi
else
    echo "  - g++ sudah terinstall"
fi

echo ""
echo "[INFO] Compile program..."

# Cari file Project.cpp di lokasi yang mungkin
if [ -f "./src/Project.cpp" ]; then
    PROJECT_CPP="./src/Project.cpp"
    echo "[INFO] Menemukan Project.cpp di ./src/"
elif [ -f "./Project.cpp" ]; then
    PROJECT_CPP="./Project.cpp"
    echo "[INFO] Menemukan Project.cpp di root folder"
else
    echo "❌ File Project.cpp tidak ditemukan!"
    echo "File yang dicari: ./Project.cpp atau ./src/Project.cpp"
    exit 1
fi

# Coba beberapa opsi compile dengan library yang tersedia
echo "[INFO] Mencoba compile dengan library yang tersedia..."

# Compile dengan semua source files
g++ -o Project.out "$PROJECT_CPP" src/analytics_logger.cpp -std=c++17 -lcpr

# Jika compile gagal, coba tanpa analytics_logger
if [ $? -ne 0 ]; then
    echo "[WARNING] Compile dengan analytics_logger gagal, mencoba tanpa analytics..."
    g++ -o Project.out "$PROJECT_CPP" -std=c++17 -lcpr
fi

if [ $? -eq 0 ]; then
    echo ""
    echo "[INFO] Refreshing library cache..."
    sudo ldconfig
    
    echo ""
    echo "=========================================="
    echo "  ✅ Instalasi berhasil!                   "
    echo "=========================================="
    echo ""
    echo "Program siap digunakan!"
    echo ""
    echo "Cara menjalankan:"
    echo "  ./Project.out"
    echo ""
    echo "File yang dibuat:"
    echo "  - Project (executable)"
    echo "  - currency_cache.txt (cache kurs)"
    echo "  - history/analytics_log.txt (log aktivitas)"
    echo "  - history/conversion_history.txt (riwayat konversi)"
    echo ""
    echo "Catatan penting:"
    echo "  - Jika program tidak bisa dijalankan, coba: sudo ldconfig"
    echo "  - Pastikan koneksi internet untuk update kurs dari API"
    echo ""
    echo "[INFO] Membersihkan file installer sementara..."
        
        # Hanya hapus installer jika file Project.cpp masih ada
        # Ini untuk mencegah penghapusan installer jika program dijalankan dari folder yang salah
        if [ -f "./src/Project.cpp" ] || [ -f "./Project.cpp" ]; then
            # Hapus installer setelah instalasi berhasil
            if [ -f "./scripts/install.sh" ]; then
                rm -f "./scripts/install.sh"
                echo "  ✅ scripts/install.sh dihapus"
            fi
            
            if [ -f "./install.sh" ]; then
                rm -f "./install.sh"
                echo "  ✅ install.sh dihapus"
            fi
        else
            echo "  ⚠️  Project.cpp tidak ditemukan, installer tidak dihapus"
            echo "  ⚠️  Ini untuk mencegah penghapusan installer yang tidak sengaja"
        fi
    
    echo ""
    echo "✅ Instalasi selesai! Sekarang Anda hanya perlu menjalankan:"
    echo "   ./Project.out"
    echo ""
else
    echo ""
    echo "=========================================="
    echo "  ❌ Gagal compile program                 "
    echo "=========================================="
    echo ""
    echo "Silakan cek error di atas dan coba lagi."
    echo "Pastikan semua dependencies sudah terinstall:"
    echo "  - libcpr-dev"
    echo "  - nlohmann-json3-dev"
    echo "  - build-essential (g++)"
    echo ""
    echo "Coba compile manual:"
    echo "  g++ -o Project src/Project.cpp src/analytics_logger.cpp -std=c++17 -lcpr"
    exit 1
fi