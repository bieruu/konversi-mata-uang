#!/bin/bash

echo "=========================================="
echo "  Menjalankan Program Konversi Mata Uang  "
echo "=========================================="
echo ""

# Cek apakah file executable ada
if [ ! -f "./Project" ]; then
    echo "[INFO] File executable tidak ditemukan"
        echo "[INFO] Menjalankan installer..."
        echo ""
        
        # Cek apakah file Project.cpp ada sebelum menjalankan installer
        # Cek di beberapa lokasi yang mungkin
        if [ -f "./src/Project.cpp" ]; then
            PROJECT_CPP="./src/Project.cpp"
        elif [ -f "./Project.cpp" ]; then
            PROJECT_CPP="./Project.cpp"
        else
            echo "❌ File Project.cpp tidak ditemukan!"
            echo "Pastikan Anda berada di folder project yang benar."
            echo "File yang dicari: ./Project.cpp atau ./src/Project.cpp"
            exit 1
        fi
        
        # Pastikan installer memiliki permission execute
        chmod +x "./install.sh" 2>/dev/null
        
        ./install.sh
        
        if [ $? -ne 0 ]; then
            echo ""
            echo "=========================================="
            echo "  ❌ Gagal install program                "
            echo "=========================================="
            exit 1
        fi
fi

echo "[INFO] Menjalankan program..."
echo ""

# Pastikan file executable memiliki permission execute
chmod +x "./Project" 2>/dev/null

./Project