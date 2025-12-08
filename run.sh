#!/bin/bash

# Redirect ke runner di folder scripts
if [ -f "./scripts/run.sh" ]; then
    # Pastikan script memiliki permission execute
    chmod +x "./scripts/run.sh" 2>/dev/null
    exec ./scripts/run.sh "$@"
else
    echo "❌ Runner tidak ditemukan di folder scripts/"
    echo "Silakan jalankan: ./scripts/run.sh"
    exit 1
fi