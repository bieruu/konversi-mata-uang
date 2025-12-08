# Program Konversi Mata Uang

<div align="center">
  <p>
    <a href="#instalasi">
      <img src="https://img.shields.io/badge/Install-Auto-brightgreen?style=for-the-badge&logo=appveyor" alt="Auto Install">
    </a>
    <a href="#fitur-utama">
      <img src="https://img.shields.io/badge/Platform-Cross--Platform-blue?style=for-the-badge&logo=appveyor" alt="Cross Platform">
    </a>
    <a href="#versi">
      <img src="https://img.shields.io/badge/Version-2.0.0-orange?style=for-the-badge&logo=appveyor" alt="Version">
    </a>
    <a href="#lisensi">
      <img src="https://img.shields.io/badge/License-MIT-brightgreen?style=for-the-badge&logo=appveyor" alt="License">
    </a>
  </p>
</div>

Program konversi mata uang dengan fitur update kurs otomatis dari API, penyimpanan riwayat, dan sistem modular yang mudah dikembangkan.

## 🎯 Versi Saat Ini
**v2.0.0** - Cross-Platform Release

## 📁 Struktur Project
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

## ✨ Fitur Utama

- ✅ **Cross-Platform**: Support Windows dan Linux
- ✅ **Zero Setup**: Install otomatis
- ✅ **Update Kurs Otomatis**: Mengambil kurs real-time dari API
- ✅ **Cache Lokal**: Menyimpan kurs untuk penggunaan offline
- ✅ **Riwayat Konversi**: Menyimpan dan menampilkan riwayat konversi
- ✅ **Error Handling**: Penanganan error yang baik
- ✅ **Validasi Input**: Input lebih aman dan user-friendly
- ✅ **One-Click Execution**: Cukup satu command untuk jalankan program
- ✅ **Developer Friendly**: Mudah ditambahkan mata uang baru tanpa ubah kode
- ✅ **Modular Architecture**: Sistem modular dengan CurrencyManager
- ✅ **JSON Configuration**: Konfigurasi mata uang terpusat di file JSON
- ✅ **Easy Currency Management**: Tambah/hapus mata uang secara langsung dari program

## 🚀 Instalasi & Penggunaan

### ⚡ Cara Termudah (Satu Command!)

#### Untuk Linux (Ubuntu/Debian/CentOS/Arch):
```bash
./run.sh
```

#### Untuk Windows:
```cmd
run.bat
```

**Hanya itu!** Semuanya otomatis:
- Install package manager (jika belum)
- Install compiler dan library
- Compile program
- Langsung jalan!

### 🛠️ Cara Manual

#### Linux:
```bash
# 1. Install library
./install.sh

# 2. Jalankan program
./src/Project
```

#### Windows:
```cmd
# 1. Install library (sebagai Administrator)
install.bat

# 2. Jalankan program
src\Project.exe
```

### 📦 Prasyarat Manual
- **Linux**: g++ compiler, libcpr-dev, nlohmann-json3-dev
- **Windows**: MinGW, CPR library, Nlohmann JSON

## 🗑️ Uninstall

Program ini menyediakan fitur uninstall untuk membersihkan file-file yang terkait。

### Untuk Linux:
```bash
./uninstall.sh
```

### Untuk Windows:
```cmd
uninstall.bat
```

### Opsi Uninstall

Program uninstall menyediakan 3 pilihan：

1. **Uninstall Normal**: Hanya menghapus program dan cache
2. **Uninstall Masif**: Menghapus semua file termasuk cache dan dokumentasi
   - **Peringatan**: Opsi ini akan menghapus seluruh folder project secara permanen
   - Anda akan diminta konfirmasi tambahan sebelum folder dihapus
3. **Uninstall Lengkap**: Menghapus program, dependencies, dan file terkait
   - **Fitur baru**: Secara otomatis mendeteksi dan menghapus dependencies yang hanya digunakan oleh program ini
   - **Keamanan**: Hanya menghapus dependencies yang aman dihapus (tidak digunakan oleh program lain)
   - **Auto Privilege Elevation**: Script secara otomatis meminta elevasi privilege jika diperlukan

## 🏗️ Arsitektur Program

### Sistem Modular dengan CurrencyManager

Program ini menggunakan arsitektur modular dengan komponen utama:

- **CurrencyManager**: Kelas manajemen mata uang yang terpisah
- **JSON Configuration**: Konfigurasi mata uang terpusat di `currency_config.json`
- **Easy Currency Addition**: Developer bisa tambah/hapus mata uang tanpa ubah kode program
- **Runtime Currency Management**: Tambah/hapus mata uang secara langsung dari program

### Source Code (`src/`)
- **`Project.cpp`**: Program utama dengan fitur API
- **`currency_manager.h`**: Header CurrencyManager
- **`currency_manager.cpp`**: Implementasi CurrencyManager
- **`currency_config.json`**: Konfigurasi mata uang

### Struktur Data
```cpp
struct Currency {
    string name;        // Nama mata uang
    string symbol;      // Simbol mata uang (ISO 4217)
    string display;     // Simbol tampilan ke user
    double rate;        // Kurs terhadap USD
};
```

### Scripts (`scripts/`)
- **`install.sh`**: Installer Linux (Ubuntu/Debian/CentOS/Arch)
- **`run.sh`**: Runner Linux
- **`uninstall.sh`**: Uninstaller Linux
- **`install.bat`**: Installer Windows (Chocolatey)
- **`run.bat`**: Runner Windows
- **`uninstall.bat`**: Uninstaller Windows

### API yang Digunakan
- **Endpoint**: `https://api.exchangerate-api.com/v4/latest/USD`
- **Base Currency**: USD
- **Update Frequency**: Harian (cache expired tiap hari)

## 🎯 Keunggulan

### ✨ Fitur Unggulan
- **Cross-Platform**: Support Windows dan Linux
- **Zero Setup**: Tidak perlu install manual
- **One-Click Execution**: Cukup satu command
- **Auto-Update**: Kurs selalu update dari API
- **Offline Support**: Bisa digunakan tanpa internet
- **Professional Structure**: Struktur project rapi dan terorganisir
- **Developer Friendly**: Sistem modular memudahkan pengembangan
- **JSON Configuration**: Konfigurasi fleksibel tanpa ubah kode

### 🔧 Technical Excellence
- **Error Handling**: Penanganan error yang baik
- **Input Validation**: Validasi input ketat
- **Cache Management**: Cache lokal cerdas
- **User Friendly**: Tampilan dan pesan informatif
- **Modular Design**: Sistem modular dengan CurrencyManager
- **Easy Maintenance**: Konfigurasi terpusat dan mudah dimodifikasi

## 🌍 Platform Support

| Platform | Installer | Compiler | Package Manager |
|----------|-----------|----------|----------------|
| Linux    | ✅        | g++      | apt/yum/pacman |
| Windows  | ✅        | MinGW    | Chocolatey     |

## 📚 Dokumentasi

- **[README.md](docs/README.md)**: Dokumentasi utama
- **[INSTALL.md](docs/INSTALL.md)**: Panduan install manual
- **[UNINSTALL.md](docs/UNINSTALL.md)**: Panduan uninstall
- **[Contributing.md](docs/Contributing.md)**: Panduan kontribusi & developer
- **[CHANGELOG.md](docs/CHANGELOG.md)**: Riwayat perubahan
- **[FlowChart.drawio.pdf](docs/FlowChart.drawio.pdf)**: Flowchart program

## Troubleshooting

### Untuk Linux
**Program Tidak Bisa Dijalankan:**
- Pastikan library terinstall dengan benar
- Cek path compiler dan library
- Jalankan `./install.sh` untuk install ulang

**Error Koneksi API:**
- Pastikan koneksi internet aktif
- Cek firewall/anti-virus
- API mungkin sedang down, program akan menggunakan cache

**Error Compile:**
- Pastikan versi compiler mendukung C++17+
- Cek path include library
- Ikuti petunjuk di INSTALL.md

**Error Uninstall:**
- Pastikan tidak ada program yang sedang berjalan
- Jalankan uninstall sebagai root jika diperlukan
- Script uninstall.sh akan secara otomatis meminta elevasi privilege jika diperlukan

### Untuk Windows
**Program Tidak Bisa Dijalankan:**
- Pastikan MinGW terinstall
- Jalankan `install.bat` sebagai Administrator
- Cek apakah file `Project.exe` terbuat

**Error "choco is not recognized":**
- Buka Command Prompt sebagai Administrator
- Jalankan: `@"%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe" -NoProfile -InputFormat None -ExecutionPolicy Bypass -Command "iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))"`
- Restart Command Prompt

**Error Compile:**
- Pastikan MinGW ada di PATH
- Cek apakah library CPR dan Nlohmann JSON terinstall
- Buka Command Prompt sebagai Administrator saat install

**Error Uninstall:**
- Pastikan program tidak sedang berjalan
- Jalankan uninstall.bat sebagai Administrator

## 🤝 Kontribusi

1. Fork repository ini
2. Buat branch fitur (`git checkout -b fitur-baru`)
3. Commit perubahan (`git commit -m 'Tambah fitur baru'`)
4. Push ke branch (`git push origin fitur-baru`)
5. Buka Pull Request

## 📄 Lisensi

Program ini bebas digunakan untuk pembelajaran dan pengembangan pribadi.

## 📞 Kontak

Untuk pertanyaan dan saran, silakan buka issue di repository ini.
