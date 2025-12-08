#!/bin/bash

# Redirect ke uninstaller di folder scripts
if [ -f "./scripts/uninstall.sh" ]; then
    exec ./scripts/uninstall.sh "$@"
else
    echo "❌ Uninstaller tidak ditemukan di folder scripts/"
    echo "Silakan jalankan: ./scripts/uninstall.sh"
    exit 1
fi