# Panduan Instalasi Library untuk Program Konversi Mata Uang

## Instalasi Library yang Dibutuhkan

### 1. CPR (HTTP Library)
```bash
# Untuk Ubuntu/Debian
sudo apt install libcpr-dev

# Untuk CentOS/RHEL
sudo yum install cpr-devel

# Atau compile dari source
git clone https://github.com/libcpr/cpr.git
cd cpr
mkdir build && cd build
cmake ..
make -j4
sudo make install
```

### 2. Nlohmann JSON (JSON Library)
```bash
# Cara termudah - header-only library
git clone https://github.com/nlohmann/json.git
cd json
# Copy header ke system directory
sudo cp -r include/nlohmann /usr/include/

# Atau untuk Ubuntu/Debian
sudo apt install nlohmann-json3-dev

# Atau untuk CentOS/RHEL
sudo yum install nlohmann-json-devel
```

## Compile Program

### Program Standar (tanpa API)
```bash
g++ -o Project Project.cpp -std=c++17
./Project
```

### Program dengan API
```bash
g++ -o Project Project.cpp -std=c++17 -lcpr -lnlohmann_json
./Project
```

### Setelah Compile
```bash
# Refresh library cache (penting untuk menghindari error libcpr.so)
sudo ldconfig

# Jalankan program
./Project
```

### Cara Mudah: Gunakan Installer

Untuk kemudahan, Anda bisa menggunakan installer yang sudah disediakan:

```bash
# Untuk Linux
./install.sh

# Untuk Windows
install.bat
```

**Catatan**: Setelah instalasi berhasil, installer akan secara otomatis terhapus untuk pengalaman yang lebih bersih. Untuk menjalankan program, cukup gunakan:

```bash
# Untuk Linux
./run.sh

# Untuk Windows
run.bat
```

## Alternatif: Compile dengan CMake

Buat file `CMakeLists.txt`:
```cmake
cmake_minimum_required(VERSION 3.10)
project(CurrencyConverter)

set(CMAKE_CXX_STANDARD 17)

# Untuk versi API
add_executable(Project Project.cpp)
find_package(cpr REQUIRED)
find_package(nlohmann_json 3.1.0 REQUIRED)
target_link_libraries(Project cpr::cpr nlohmann_json::nlohmann_json)
```

Compile:
```bash
mkdir build && cd build
cmake ..
make
```

### Setelah Compile dengan CMake
```bash
# Refresh library cache (penting untuk menghindari error libcpr.so)
sudo ldconfig

# Jalankan program
./Project
```

## Troubleshooting

### Error: cannot open source file "cpr/cpr.h"
- Pastikan library CPR terinstall dengan benar
- Cek path include library

### Error: cannot open source file "nlohmann/json.hpp"
- Pastikan header JSON tercopy ke `/usr/include/nlohmann/`
- Atau tambahkan path manual: `g++ -I/path/to/json/include ...`

### Error: libcpr.so.1: cannot open shared object file
- **Penyebab**: Library cache tidak diperbarui setelah install CPR
- **Solusi**: Jalankan `sudo ldconfig` untuk refresh library cache
- **Pencegahan**: Selalu jalankan `sudo ldconfig` setelah install library system-wide

### Error koneksi API
- Pastikan koneksi internet aktif
- Cek firewall/anti-virus
- API yang digunakan: https://api.exchangerate-api.com/v4/latest/USD

### Error compilation C++11 vs C++17
- **Penyebab**: CPR library membutuhkan C++17, bukan C++11
- **Solusi**: Gunakan `-std=c++17` bukan `-std=c++11`
- **Contoh**: `g++ -o Project Project.cpp -std=c++17 -lcpr -lnlohmann_json`

### Program tidak bisa dijalankan
- Pastikan file executable memiliki permission:
  ```bash
  chmod +x Project
  ```
- Pastikan library cache sudah di-refresh:
  ```bash
  sudo ldconfig
  ```
- Cek dependencies:
  ```bash
  ldd Project
  ```

## Fitur yang Ditambahkan

1. **Update Kurs Otomatis**: Mengambil kurs real-time dari API
2. **Cache Lokal**: Menyimpan kurs ke file untuk penggunaan offline
3. **Error Handling**: Penanganan error koneksi dan exception
4. **Menu Update**: Menu khusus untuk update kurs
5. **Validasi Input**: Validasi input lebih ketat
6. **Modular Architecture**: Sistem modular dengan CurrencyManager
7. **JSON Configuration**: Konfigurasi mata uang terpusat di `currency_config.json`
8. **Easy Currency Management**: Tambah/hapus mata uang secara langsung dari program

## Struktur File

```
konversi-mata-uang/
├── src/
│   ├── Project.cpp               # Program utama (dengan API)
│   ├── currency_manager.h        # Header CurrencyManager
│   ├── currency_manager.cpp      # Implementasi CurrencyManager
│   └── currency_config.json      # File config mata uang
├── scripts/
│   ├── install.sh                # Installer Linux
│   ├── run.sh                    # Runner Linux
│   ├── uninstall.sh              # Uninstaller Linux
│   ├── install.bat               # Installer Windows
│   ├── run.bat                   # Runner Windows
│   └── uninstall.bat             # Uninstaller Windows
└── docs/
    ├── README.md                 # Dokumentasi utama
    ├── INSTALL.md                # File ini
    ├── UNINSTALL.md              # Panduan uninstall
    ├── Contributing.md           # Panduan kontribusi
    ├── CHANGELOG.md              # Riwayat perubahan
    └── FlowChart.drawio.pdf      # Flowchart program
```

## Developer Notes

### Menambahkan Mata Uang Baru

Program ini menggunakan sistem modular dengan CurrencyManager yang memudahkan penambahan mata uang baru:

1. **Melalui File Config** (Direkomendasikan):
   - Buka `src/currency_config.json`
   - Tambahkan objek baru ke array `currencies`:
   ```json
   {
     "name": "Nama Mata Uang Lengkap",
     "symbol": "KODE",
     "display": "Simbol Tampilan",
     "default_rate": 1.0,
     "description": "Deskripsi mata uang"
   }
   ```

2. **Melalui Program** (Runtime):
   - Jalankan program
   - Pilih menu [4] Tambah Mata Uang Baru
   - Masukkan data mata uang
   - Mata uang akan otomatis ditambahkan ke config file

### Aturan Penamaan

- **Symbol**: Gunakan standar ISO 4217 (contoh: USD, EUR, IDR, JPY)
- **Display**: Simbol yang ditampilkan ke user (boleh menggunakan simbol khusus)
- **Name**: Nama lengkap mata uang (format: Negara + Currency)
- **Default Rate**: Kurs default terhadap USD (akan diupdate otomatis dari API)