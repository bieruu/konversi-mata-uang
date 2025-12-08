# Panduan Uninstall Program Konversi Mata Uang

## 🗑️ Overview

Program ini menyediakan fitur uninstall yang lengkap untuk membersihkan file-file yang terkait dengan program. Anda memiliki tiga pilihan: uninstall normal, uninstall masif, atau uninstall lengkap (termasuk dependencies).

## 📋 Opsi Uninstall

### 1. Uninstall Normal
- **Deskripsi**: Hanya menghapus program dan cache
- **File yang dihapus**:
  - `Project` (executable Linux) atau `Project.exe` (Windows)
  - `currency_cache.txt` (file cache kurs)
- **File yang tetap ada**:
  - Dokumentasi (`README.md`, `docs/`)
  - Source code (`src/`)
  - Installer (`scripts/`, `install.sh`, `install.bat`, dll)

### 2. Uninstall Masif
- **Deskripsi**: Menghapus semua file termasuk cache dan dokumentasi
- **Peringatan**: Opsi ini akan menghapus seluruh folder project secara permanen
- **Proses**:
  1. Menghapus semua file program
  2. Menghapus semua direktori (src/, docs/, scripts/)
  3. Menghapus README.md
  4. **Meminta konfirmasi tambahan** sebelum menghapus folder project
  5. Jika dikonfirmasi, menghapus seluruh folder project

### 3. Uninstall Lengkap (Baru!)
- **Deskripsi**: Menghapus program, dependencies, dan file terkait
- **Fitur baru**: Secara otomatis mendeteksi dan menghapus dependencies yang hanya digunakan oleh program ini
- **Keamanan**: Hanya menghapus dependencies yang aman dihapus (tidak digunakan oleh program lain)
- **Dependencies yang diperiksa**:
  - `libcpr-dev` / `cpr-devel` / `cpr` (tergantung distro)
  - `nlohmann-json3-dev` / `nlohmann-json-devel` / `nlohmann-json`
  - `build-essential` / `gcc-c++` / `base-devel`
- **Proses**:
  1. Memeriksa dependencies yang terinstall
  2. Mengecek apakah dependencies masih digunakan oleh program lain
  3. Hanya menghapus dependencies yang aman dihapus
  4. Meminta konfirmasi sebelum menghapus
  5. Menghapus dependencies dan file program

## 🚀 Cara Menggunakan

### Untuk Linux:
```bash
./uninstall.sh
```

### Untuk Windows:
```cmd
uninstall.bat
```

### Pilihan Uninstall (Versi Terbaru)
```
==========================================
  Pilihan Uninstall
==========================================
1. Uninstall Normal (hapus program saja)
2. Uninstall Masif (hapus semua termasuk cache dan dokumentasi)
3. Uninstall Lengkap (hapus program + dependencies)
4. Batalkan
==========================================

Pilih opsi (1/2/3/4):
```

## ⚠️ Peringatan Penting

### Uninstall Masif
- **Hati-hati**: Opsi ini akan menghapus SEMUA file dan folder project
- **Tidak bisa dikembalikan**: Proses penghapusan permanen
- **Konfirmasi ganda**: Anda akan diminta konfirmasi dua kali:
  1. Konfirmasi memilih opsi uninstall masif
  2. Konfirmasi tambahan sebelum folder project dihapus

### Uninstall Lengkap
- **Keamanan**: Hanya menghapus dependencies yang tidak digunakan oleh program lain
- **Konfirmasi**: Akan meminta konfirmasi sebelum menghapus dependencies
- **Sistem tetap aman**: Tidak akan merusak file system atau program lain
- **Contoh proses**:
  ```
  [📋] Dependencies yang terdeteksi:
    - libcpr-dev
    - nlohmann-json3-dev
    - build-essential

  [INFO] Memeriksa apakah dependencies masih digunakan oleh program lain...
    ✅ libcpr-dev - Aman dihapus (hanya digunakan oleh program ini)
    ⚠️  build-essential - Masih digunakan oleh program lain

  [⚠️ ] Peringatan: Dependencies berikut akan dihapus:
    - libcpr-dev
    - nlohmann-json3-dev

  Apakah Anda yakin ingin menghapus dependencies ini? (y/N): y
  ```

### Contoh Proses Uninstall Masif
```
==========================================
  Uninstaller Program Konversi Mata Uang  
==========================================

[INFO] Mendeteksi file-file yang terkait...

[📋] File yang akan dihapus:
  - Project
  - currency_cache.txt
  - install.sh
  - run.sh
  - uninstall.sh
  - install.bat
  - run.bat
  - uninstall.bat
  - src/
  - scripts/
  - docs/

==========================================
  Pilihan Uninstall                      
==========================================
1. Uninstall Normal (hapus program saja)
2. Uninstall Masif (hapus semua termasuk cache dan dokumentasi)
3. Batalkan
==========================================

Pilih opsi (1/2/3): 2

[INFO] Melakukan uninstall masif...
[INFO] Menghapus semua file termasuk cache dan dokumentasi...

[⚠️ ] Peringatan: Opsi ini akan menghapus SELURUH folder project!
[⚠️ ] Semua file dan subfolder di dalamnya akan hilang selamanya!

Apakah Anda yakin ingin menghapus seluruh folder project? (ketik 'YA' untuk melanjutkan): YA

[INFO] Menghapus folder project secara permanen...
  ✅ Folder project 'konversi-mata-uang' dihapus secara permanen

✅ Uninstall masif selesai!

❌ SEMUA FILE DAN FOLDER PROJECT TELAH DIHAPUS PERMANEN!

[INFO] Semua file program dan folder project sudah dihapus。
Program telah dibersihkan sepenuhnya dari sistem Anda。
```

### Elevasi Privilege Otomatis (Linux)
Jika script dijalankan tanpa hak akses root, script akan secara otomatis meminta elevasi privilege:

```
[INFO] Memerlukan hak akses administrator untuk melanjutkan...
[INFO] Script akan dijalankan ulang dengan sudo...
[sudo] password for user: [masukkan password]
```

Setelah elevasi privilege berhasil, script akan melanjutkan proses uninstall secara otomatis tanpa perlu input tambahan dari user.

## 🛠️ Troubleshooting

### Error Uninstall
Jika uninstall gagal, coba solusi berikut：

#### Untuk Linux:
- Pastikan tidak ada program yang sedang berjalan：
  ```bash
  pkill -f "Project"
  ```
- Jalankan uninstall sebagai root jika diperlukan：
  ```bash
  sudo ./uninstall.sh
  ```

**Catatan**: Script uninstall.sh akan secara otomatis meminta elevasi privilege jika diperlukan, sehingga Anda tidak perlu menjalankan perintah sudo secara manual。

#### Untuk Windows:
- Pastikan program tidak sedang berjalan：
  - Buka Task Manager (Ctrl+Shift+Esc)
  - Cari `Project.exe` dan hentikan
- Jalankan uninstall.bat sebagai Administrator：
  - Klik kanan pada `uninstall.bat`
  - Pilih "Run as Administrator"

### Dependencies Tidak Bisa Dihapus
Jika uninstall dependencies gagal：

#### Penyebab Umum:
1. **Dependencies masih digunakan oleh program lain** - Ini adalah hal yang baik, sistem akan melindungi dependencies yang masih dibutuhkan
2. **Akses tidak cukup** - Pastikan Anda menjalankan sebagai root/administrator
3. **Package manager error** - Coba update package manager terlebih dahulu

#### Solusi：
```bash
# Untuk Debian/Ubuntu:
sudo apt-get update
sudo apt-get autoremove

# Untuk CentOS/RHEL:
sudo yum update
sudo yum autoremove

# Untuk Arch Linux:
sudo pacman -Sy
sudo pacman -Sc
```

### File Masih Tersisa
Jika setelah uninstall masih ada file yang tersisa：

#### Uninstall Normal：
File yang seharusnya masih ada：
- `README.md`
- `docs/` (semua dokumentasi)
- `src/` (source code)
- `scripts/` (installer)

#### Uninstall Masif：
Jika Anda memilih uninstall masif tapi folder project masih ada, berarti Anda membatalkan konfirmasi terakhir。Hanya file program yang dihapus，folder project tetap ada。

#### Uninstall Lengkap：
Jika dependencies masih ada setelah uninstall lengkap，kemungkinan：
1. Dependencies masih digunakan oleh program lain (aman，tidak dihapus)
2. Anda membatalkan konfirmasi penghapusan
3. Ada error saat proses uninstall

## 🔄 Install Ulang

Jika Anda ingin install ulang setelah uninstall：

### Setelah Uninstall Normal：
```bash
# Untuk Linux
./install.sh
./run.sh

# Untuk Windows
install.bat
run.bat
```

### Setelah Uninstall Masif：
Anda perlu mendownload ulang project dari repository，karena semua file telah dihapus。

### Setelah Uninstall Lengkap：
Jika Anda ingin install ulang dan dependencies telah dihapus：
```bash
# Install dependencies terlebih dahulu
sudo apt-get install libcpr-dev nlohmann-json3-dev build-essential  # Debian/Ubuntu
# atau
sudo yum install cpr-devel nlohmann-json-devel gcc-c++              # CentOS/RHEL
# atau
sudo pacman -S cpr nlohmann-json base-devel                         # Arch Linux

# Kemudian install program
./install.sh
```

## 📞 Dukungan

Jika Anda mengalami masalah dengan proses uninstall：

1. Buka issue di repository GitHub
2. Sertakan：
   - Sistem operasi yang digunakan
   - Opsi uninstall yang dipilih
   - Pesan error yang muncul
   - Langkah-langkah yang telah dicoba

## ⚡ Tips

1. **Backup terlebih dahulu**：Jika Anda ingin menyimpan dokumentasi atau source code，lakukan backup sebelum uninstall masif
2. **Pastikan tidak ada program berjalan**：Selalu hentikan program sebelum uninstall
3. **Baca konfirmasi dengan teliti**：Terutama pada uninstall masif，pastikan Anda benar-benar yakin sebelum mengetik 'YA'