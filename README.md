# Program Konversi Mata Uang

Program konversi mata uang profesional dengan fitur penyimpanan riwayat, dan sistem modular yang mudah dikembangkan.

## 📁 Struktur Project
```
konversi-mata-uang/
├── src/                          # Source code utama
│   ├── Project.cpp               # Program utama
│   ├── currency_manager.h        # Header CurrencyManager
│   ├── currency_manager.cpp      # Implementasi CurrencyManager
│   └── currency_config.json      # Konfigurasi mata uang
├── cache/                        # Folder cache kurs
│   └── cache.txt                 # File cache kurs
├── install.sh                    # Installer Linux
├── uninstall.sh                  # Uninstaller Linux
├── install.bat                   # Installer Windows
├── uninstall.bat                 # Uninstaller Windows
└── docs/                         # Dokumentasi dan panduan
    ├── README.md                 # Dokumentasi utama
    ├── INSTALL.md                # Panduan install manual
    ├── UNINSTALL.md              # Panduan uninstall
    └── Contributing.md           # Panduan kontribusi & developer
```

## ✨ Fitur Utama

- ✅ **Cross-Platform**: Support Windows dan Linux
- ✅ **Cache Lokal**: Menyimpan kurs untuk penggunaan offline
- ✅ **Riwayat Konversi**: Menyimpan dan menampilkan riwayat konversi
- ✅ **Modular Architecture**: Sistem modular dengan CurrencyManager
- ✅ **JSON Configuration**: Konfigurasi mata uang terpusat di file JSON
- ✅ **Developer Friendly**: Mudah ditambahkan mata uang baru tanpa ubah kode

## 🚀 Instalasi & Penggunaan
Pastikan program sudah di-compile terlebih dahulu menggunakan:
- Linux: `./install.sh`
- Windows: `install.bat`

#### Untuk Linux (Ubuntu/Debian/CentOS/Arch):
```bash
./Project.out
```

#### Untuk Windows:
```cmd
Project.exe
```


### 🎯 Menu Program

Program ini menyediakan 6 menu utama:

1. **[1] Konversi Mata Uang** - Konversi antar mata uang
2. **[2] Lihat Daftar Mata Uang** - Tampilkan semua mata uang yang tersedia
3. **[3] Update Kurs dari API** - Update kurs secara real-time dari API
4. **[4] Tambah Mata Uang Baru** - Tambahkan mata uang baru ke sistem
5. **[5] Hapus Mata Uang** - Hapus mata uang dari sistem
6. **[6] Lihat Riwayat Konversi** - Tampilkan riwayat konversi terakhir
7. **[0] Keluar** - Keluar dari program

### 📦 Prasyarat Manual
- **Linux**: g++ compiler, libcpr-dev, nlohmann-json3-dev
- **Windows**: MinGW, CPR library, Nlohmann JSON

## 🗑️ Uninstall

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

## 🏗️ Arsitektur Sistem

### Sistem Modular dengan CurrencyManager

Program ini menggunakan arsitektur modular dengan komponen utama:

- **CurrencyManager**: Kelas manajemen mata uang yang terpisah
- **JSON Configuration**: Konfigurasi mata uang terpusat di `currency_config.json`
- **Easy Currency Addition**: Developer bisa tambah/hapus mata uang tanpa ubah kode program
- **Runtime Currency Management**: Tambah/hapus mata uang secara langsung dari program

### Struktur Data
```cpp
struct Currency {
    string name;        // Nama mata uang
    string symbol;      // Simbol mata uang (ISO 4217)
    string display;     // Simbol tampilan ke user
    double rate;        // Kurs terhadap USD
};
```

### API yang Digunakan
- **Endpoint**: `https://api.exchangerate-api.com/v4/latest/USD`
- **Base Currency**: USD
- **Update Frequency**: Harian (cache expired tiap hari)

## 🎯 Keunggulan

### ✨ Fitur Unggulan
- **Cross-Platform**: Support Windows dan Linux
- **Auto-Update**: Kurs selalu update dari API
- **Offline Support**: Bisa digunakan tanpa internet
- **Developer Friendly**: Sistem modular memudahkan pengembangan
- **JSON Configuration**: Konfigurasi fleksibel tanpa ubah kode

### 🔧 Technical Excellence
- **Error Handling**: Penanganan error yang baik
- **Input Validation**: Validasi input ketat
- **Cache Management**: Cache lokal cerdas
- **Modular Design**: Sistem modular dengan CurrencyManager
- **Easy Maintenance**: Konfigurasi terpusat dan mudah dimodifikasi
- **Cross-Platform Clear Screen**: Implementasi robust menggunakan ANSI escape sequence

## 🌍 Platform Support

| Platform | Installer | Compiler | Package Manager |
|----------|-----------|----------|----------------|
| Linux    | ✅        | g++      | apt/yum/pacman |
| Windows  | ⚠️        | MinGW    | Chocolatey     |

**Catatan**: Program telah diuji dan berjalan lancar di Linux. Di Windows, mungkin diperlukan beberapa konfigurasi tambahan. Untuk bantuan atau perbaikan, silakan submit pull request atau issue di repository kontribusi.

## 📚 Dokumentasi

- **[INSTALL.md](docs/INSTALL.md)**: Panduan install manual
- **[UNINSTALL.md](docs/UNINSTALL.md)**: Panduan uninstall
- **[Contributing.md](docs/Contributing.md)**: Panduan kontribusi & developer

## 📊 Analisis Teknis Mendalam

### Arsitektur Sistem yang Cerdas

Program ini menerapkan **prinsip modularitas** dan **separasi concern** yang sangat baik:

1. **Separation of Concerns**:
   - [`Project.cpp`](src/Project.cpp) berfokus pada logika bisnis dan UI
   - [`CurrencyManager`](src/currency_manager.h) mengelola data dan operasi mata uang
   - [`currency_config.json`](src/currency_config.json) menyimpan konfigurasi

2. **Dependency Injection**:
   - CurrencyManager menerima path file sebagai parameter konstruktor
   - Memungkinkan testing dan fleksibilitas konfigurasi

3. **Strategy Pattern**:
   - Sistem cache dan API sebagai strategi berbeda untuk mendapatkan data
   - Bisa dengan mudah ditambahkan strategi baru (file lokal, database, dll)

### Sistem Manajemen Mata Uang yang Fleksibel

#### JSON Configuration System
```json
{
  "currencies": [
    {
      "name": "Indonesian Rupiah",
      "symbol": "IDR",
      "display": "Rp",
      "default_rate": 17000.0,
      "description": "Indonesian Rupiah"
    }
  ]
}
```

**Keunggulan Sistem Konfigurasi:**
- **Type Safety**: Validasi struktur JSON saat runtime
- **Extensibility**: Mudah menambahkan field baru (deskripsi, kategori, dll)
- **Version Control Friendly**: Perubahan konfigurasi tercatat di git
- **Environment Specific**: Bisa punya config berbeda untuk development/production

#### Runtime Currency Management
```cpp
// Tambah mata uang secara dinamis
bool CurrencyManager::addCurrency(const Currency& currency) {
    // Validasi duplikasi
    // Update config file
    // Simpan ke cache
}
```

**Fitur Manajemen Runtime:**
- **Validation**: Cegah duplikasi simbol mata uang
- **Persistence**: Perubahan langsung disimpan ke file
- **Real-time Update**: Langsung bisa digunakan tanpa restart

### Sistem Cache yang Cerdas

#### Cache Strategy
```cpp
bool CurrencyManager::isCacheExpired() const {
    return cacheDate != getCurrentDate();
}
```

**Cache Mechanism:**
1. **Time-based Expiration**: Cache expired harian
2. **Graceful Fallback**: API gagal → gunakan cache
3. **Auto-refresh**: Update cache saat API berhasil
4. **Storage Efficiency**: Format CSV sederhana, mudah dibaca

#### Error Handling yang Komprehensif
```cpp
try {
    cpr::Response r = cpr::Get(cpr::Url{"https://api.exchangerate-api.com/v4/latest/USD"});
    // Proses response
} catch (const exception& e) {
    cout << "[ERROR] Exception: " << e.what() << "\n";
    return false;
}
```

**Error Handling Strategy:**
- **Network Errors**: Timeout, connection refused, dll
- **API Errors**: HTTP status codes, malformed JSON
- **File Errors**: Permission denied, disk full
- **User Errors**: Input invalid, format salah

### Cross-Platform Installation System

#### Linux Installation Strategy
```bash
# Multi-distro support
if [ -f /etc/debian_version ]; then
    DISTRO="debian"
elif [ -f /etc/redhat-release ]; then
    DISTRO="redhat"
elif [ -f /etc/arch-release ]; then
    DISTRO="arch"
fi
```

**Installation Features:**
1. **Distro Detection**: Otomatis deteksi Ubuntu, CentOS, Arch
2. **Package Manager Integration**: apt, yum, pacman
3. **Dependency Resolution**: Install compiler dan library
4. **Auto-compilation**: Compile program setelah install dependencies
5. **Cleanup**: Hapus installer setelah sukses

#### Windows Installation Strategy
```batch
REM Chocolatey integration
where /q choco
if %ERRORLEVEL% NEQ 0 (
    echo [INFO] Menginstall Chocolatey...
    @"%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe" -NoProfile -InputFormat None -ExecutionPolicy Bypass -Command "iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))"
)
```

**Windows Features:**
1. **Package Manager**: Gunakan Chocolatey untuk consistency
2. **Auto-elevation**: Minta admin rights saat dibutuhkan
3. **Environment Setup**: PowerShell execution policy
4. **Dependency Chain**: MinGW → CPR → Nlohmann JSON

### Advanced Uninstall System

#### Smart Dependency Management
```bash
# Cek apakah package masih digunakan
cek_package_usage() {
    if command -v dpkg &> /dev/null; then
        local reverse_deps=$(apt-cache rdepends "$package" 2>/dev/null | grep -c "ii" || echo "0")
        if [ "$reverse_deps" -gt 1 ]; then
            return 1  # Masih digunakan oleh program lain
        fi
    fi
    return 0  # Aman untuk dihapus
}
```

### Performance & Security Considerations

#### Performance Optimizations
1. **Lazy Loading**: Load config hanya saat dibutuhkan
2. **Cache First**: Selalu cek cache sebelum request API
3. **Efficient Data Structures**: Vector untuk akses cepat O(1)
4. **Memory Management**: RAII dan smart pointers

#### Security Measures
1. **Input Validation**: Validasi semua input user
2. **Path Security**: Cek existence file sebelum operasi
3. **Permission Handling**: Auto-elevation privilege
4. **Error Handling**: Jangan expose internal errors ke user

### Developer Experience Excellence

#### Easy Currency Addition
```json
{
  "name": "Nama lengkap mata uang (contoh: 'Canadian Dollar')",
  "symbol": "Kode mata uang sesuai standar ISO 4217 (contoh: 'CAD')",
  "display": "Simbol yang ditampilkan ke user (contoh: 'C$')",
  "default_rate": "Kurs default terhadap USD (contoh: 1.35)",
  "description": "Deskripsi singkat mata uang (opsional)"
}
```

**Developer Features:**
1. **No Code Changes**: Cukup edit JSON untuk tambah mata uang
2. **Validation**: Sistem validasi duplikasi dan format
3. **Documentation**: Inline documentation di JSON
4. **Best Practices**: Panduan penamaan dan struktur

#### Modular Architecture Benefits
1. **Testability**: Setiap modul bisa di-test terpisah
2. **Maintainability**: Perubahan tidak mempengaruhi modul lain
3. **Reusability**: CurrencyManager bisa dipakai di project lain
4. **Scalability**: Mudah tambah fitur baru

### API Integration Strategy

#### Robust API Handling
```cpp
bool CurrencyManager::updateFromAPI() {
    try {
        cout << "[INFO] Menghubungi API...\n";
        cpr::Response r = cpr::Get(cpr::Url{"https://api.exchangerate-api.com/v4/latest/USD"});
        
        if (r.status_code == 200) {
            json data = json::parse(r.text);
            if (data.contains("rates")) {
                // Update semua mata uang
                for (auto& currency : currencies) {
                    if (rates.contains(currency.symbol)) {
                        currency.rate = rates[currency.symbol];
                    }
                }
                saveToCache();
                return true;
            }
        }
    } catch (const exception& e) {
        cout << "[ERROR] Exception: " << e.what() << "\n";
        return false;
    }
}
```

**API Strategy:**
1. **Base Currency**: Gunakan USD sebagai base untuk konsistensi
2. **Error Handling**: Catch semua exception network dan parsing
3. **Partial Update**: Update hanya mata uang yang tersedia di API
4. **Logging**: Informasi progress update
5. **Fallback**: Gunakan cache jika API gagal

### Best Practices Implementation

#### Code Quality
1. **Consistent Naming**: camelCase untuk variabel, PascalCase untuk class
2. **Documentation**: Komentar Javadoc untuk semua fungsi
3. **Error Messages**: Pesan error informatif dan actionable
4. **Resource Management**: RAII dan proper cleanup

#### Project Structure
1. **Separation of Concerns**: UI, Business Logic, Data Management terpisah
2. **Configuration Management**: Centralized configuration
3. **Build System**: CMake support untuk professional build
4. **Documentation**: Comprehensive docs di setiap aspek

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
