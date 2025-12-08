#!/bin/bash

# Redirect ke installer di folder scripts
if [ -f "./scripts/install.sh" ]; then
    exec ./scripts/install.sh "$@"
else
    echo "❌ Installer tidak ditemukan di folder scripts/"
    echo "Silakan jalankan: ./scripts/install.sh"
    exit 1
fi