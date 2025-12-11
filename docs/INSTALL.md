# Panduan Instalasi Library untuk Program Konversi Mata Uang

## Cara Termudah (Satu Command!)
### Untuk Linux (Ubuntu/Debian/CentOS/Arch):
```bash
./install.sh
```

### Untuk Windows:
```cmd
install.bat
```

**Proses Instalasi:**
- Install package manager (jika belum)
- Install compiler dan library
- Compile program
- Program siap dijalankan

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

## Cara Manual

### Linux:
```bash
# 1. Install library
./install.sh

# 2. Jalankan program
./Project.out
```

### Windows:
```cmd
# 1. Install library (sebagai Administrator)
install.bat

# 2. Jalankan program
Project.exe
```

## Compile Program

### Program Standar (tanpa API)
```bash
g++ -o Project.out Project.cpp -std=c++17
./Project.out
```

### Program dengan API
```bash
g++ -o Project.out Project.cpp -std=c++17 -lcpr -lnlohmann_json
./Project.out
```

### Setelah Compile
```bash
# Refresh library cache (penting untuk menghindari error libcpr.so)
sudo ldconfig

# Jalankan program
./Project.out
```

### Cara Mudah: Gunakan Installer

Untuk kemudahan, Anda bisa menggunakan installer yang sudah disediakan:

```bash
# Untuk Linux
./install.sh

# Untuk Windows
install.bat
```

**Catatan**: Setelah instalasi berhasil, program dapat langsung dijalankan:

```bash
# Untuk Linux
./Project.out

# Untuk Windows
Project.exe
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
./Project.out
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
