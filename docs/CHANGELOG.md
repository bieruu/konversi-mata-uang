# Changelog

Semua perubahan pada program konversi mata uang ini tercatat di sini.

## [2.0.0] - 2025-12-08

### ✨ Fitur Baru

#### **Cross-Platform Support**
- **Platform Support**: Support Windows dan Linux secara resmi
- **Installer Otomatis**: Script install otomatis untuk semua platform
- **Runner Otomatis**: Satu command untuk jalankan program
- **Package Manager Integration**:
  - Linux: apt, yum, pacman
  - Windows: Chocolatey
- **Multi-Platform Documentation**: README khusus untuk tiap platform

#### **Modular Architecture**
- **CurrencyManager Class**: Sistem modular terpisah untuk manajemen mata uang
- **JSON Configuration**: Konfigurasi mata uang terpusat di `currency_config.json`
- **Easy Currency Addition**: Developer bisa tambah/hapus mata uang tanpa ubah kode program
- **Runtime Currency Management**: Tambah/hapus mata uang secara langsung dari program
- **ISO 4217 Standard**: Mendukung standar internasional kode mata uang
- **Auto Config Update**: Perubahan config otomatis tersimpan dan terload

#### **Enhanced Installation System**
- **Zero Setup Installation**: User tidak perlu install apa-apa manual
- **One-Click Execution**: Cukup jalankan satu script, semuanya otomatis
- **Non-Root Installation Support**: Installer mencoba install local dulu sebelum minta sudo/admin
- **Enhanced Error Handling**: Error handling lebih baik untuk tiap platform
- **Progress Feedback**: Tambahkan `--no-progress` untuk Chocolatey

#### **Uninstall Feature**
- **Dual Options**: Menyediakan opsi uninstall normal dan uninstall masif
- **Massive Uninstall**: Opsi untuk menghapus seluruh folder project secara permanen
- **Complete Uninstall**: Opsi baru untuk menghapus program + dependencies yang tidak digunakan
- **Safety Features**: Hanya menghapus dependencies yang aman dihapus (tidak digunakan oleh program lain)
- **Double Confirmation**: Konfirmasi tambahan sebelum menghapus folder project
- **Cross-Platform**: Fitur uninstall tersedia untuk Linux dan Windows
- **Auto Privilege Elevation (Linux)**: Script secara otomatis meminta elevasi privilege jika diperlukan
- **Admin Check (Windows)**: Cek otomatis apakah script dijalankan sebagai Administrator

#### **Developer Experience**
- **Developer-Friendly System**: Sistem modular dengan CurrencyManager class
- **JSON Configuration**: Konfigurasi mata uang terpusat di `currency_config.json`
- **Easy Currency Addition**: Developer bisa tambah mata uang tanpa ubah kode program
- **Runtime Currency Management**: Tambah/hapus mata uang secara langsung dari program
- **Developer Menu**: Menu khusus untuk manajemen mata uang (Tambah, Hapus, Lihat Daftar)
- **ISO 4217 Standard**: Mendukung standar internasional kode mata uang
- **Auto Config Update**: Perubahan config otomatis tersimpan dan terload
- **Validation System**: Validasi input dan konfigurasi untuk mencegah error
- **Backup & Restore**: Sistem config memudahkan backup dan restore data mata uang

### 🔧 Perbaikan Besar

#### **Struktur Project Profesional**
```
konversi-mata-uang/
├── src/                          # Source code utama
│   ├── Project.cpp               # Program utama (versi API)
│   ├── currency_manager.h        # Header CurrencyManager
│   ├── currency_manager.cpp      # Implementasi CurrencyManager
│   └── currency_config.json      # Konfigurasi mata uang
├── scripts/                      # Installer dan runner
│   ├── install.sh                # Installer Linux
│   ├── run.sh                    # Runner Linux
│   ├── uninstall.sh              # Uninstaller Linux
│   ├── install.bat               # Installer Windows
│   ├── run.bat                   # Runner Windows
│   └── uninstall.bat             # Uninstaller Windows
└── docs/                         # Dokumentasi dan panduan
    ├── README.md                 # Dokumentasi utama
    ├── INSTALL.md                # Panduan install manual
    ├── UNINSTALL.md              # Panduan uninstall
    ├── Contributing.md           # Panduan kontribusi & developer
    ├── CHANGELOG.md              # Riwayat perubahan
    └── FlowChart.drawio.pdf      # Flowchart program
```

#### **Enhanced Error Handling**
- **Linux**: Cek akses write ke home directory
- **Windows**: Cek apakah bisa install local tanpa admin
- **Better Messages**: Pesan error lebih informatif dan actionable
- **Graceful Fallback**: Gagal local install tidak crash program
- **Better Logging**: Progress install lebih jelas

#### **Improved User Experience**
- **No Surprise Sudo**: User tahu kapan butuh root/admin
- **Clear Instructions**: Panduan jelas cara jalankan sebagai root/admin
- **User Friendly**: Pesan jelas cara jalankan sebagai root/admin
- **Clear Feedback**: Progress install dan error message jelas

### 📦 Dependencies Management
- **Linux**: libcpr-dev, nlohmann-json3-dev, build-essential
- **Windows**: MinGW, CPR library, Nlohmann JSON via Chocolatey
- **Auto-Detection**: Mendeteksi distro/OS dan install package yang sesuai
- **Dependency Safety**: Hanya menghapus dependencies yang tidak digunakan oleh program lain

### 🚀 User Experience
- **Windows User**: Cukup buka Command Prompt, jalankan `run.bat`
- **Linux User**: Cukup buka terminal, jalankan `./run.sh`
- **No Manual Setup**: Tidak perlu install compiler/library manual
- **Clear Feedback**: Progress install dan error message jelas

### 🎯 Target Platform
- **Linux**: Ubuntu 18.04+, Debian 9+, CentOS 7+, Arch Linux
- **Windows**: Windows 7+, Windows 10, Windows 11

---

## [1.0.0] - 2025-12-08

### ✨ Fitur Baru
- **Update Kurs Otomatis**: Mengambil kurs real-time dari API publik
- **Cache Lokal**: Menyimpan kurs untuk penggunaan offline
- **Riwayat Konversi**: Menyimpan dan menampilkan riwayat konversi
- **Menu Update Kurs**: Menu khusus untuk update kurs dari API
- **Error Handling**: Penanganan error yang baik untuk koneksi dan input
- **Validasi Input**: Input lebih aman dan user-friendly

### 🔧 Perbaikan
- **Struktur Kode**: Lebih modular dan mudah dikembangkan
- **Tampilan**: Menu lebih informatif dan user-friendly
- **Performa**: Cache mengurangi request API berulang

### 🐛 Perbaikan Bug
- Validasi input lebih ketat
- Penanganan exception lebih baik
- Error message lebih informatif