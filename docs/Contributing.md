# 📚 Contributing

---

## 🛠️ Panduan Kontribusi (Wajib Dibaca!)

Untuk berkontribusi pada proyek ini, ikuti langkah-langkah di bawah ini. Pastikan Anda telah menginstal Git di sistem Anda。

### Memulai Kontribusi

1.  **Clone Repository:**
      Mulailah dengan mengkloning repositori proyek ke mesin lokal Anda。
      ```bash
      git clone https://github.com/bieruu/konversi-mata-uang.git
      cd konversi-mata-uang
      ```

2.  **Siapkan Lingkungan Pengembangan:**
      Pastikan Anda memiliki kompiler C++ (misalnya, GCC atau Clang) terinstal。Bergantung pada sistem operasi Anda，Anda mungkin perlu menginstal alat bantu pembangunan lainnya。

      *   **Untuk Debian/Ubuntu:**
          ```bash
          sudo apt update
          sudo apt install build-essential git
          ```
      *   **Untuk Fedora/CentOS:**
          ```bash
          sudo dnf install gcc-c++ make git
          ```
      *   **Untuk macOS dengan Homebrew:**
          ```bash
          brew install gcc git
          ```
      *   **Untuk Windows (misalnya dengan MinGW-w64 atau WSL):**
          Instal MinGW-w64 atau gunakan Windows Subsystem for Linux (WSL) dengan distribusi Linux pilihan Anda。Pastikan GCC/G++ tersedia di PATH Anda。

      Setelah kompiler terinstal，Anda bisa melanjutkan。

3.  **Menjalankan Aplikasi:**
      Untuk menjalankan aplikasi，gunakan kompiler C++ untuk mengkompilasi kode sumber。

      ```bash
      g++ -o Project src/Project.cpp src/currency_manager.cpp -std=c++17 -lcpr -lnlohmann_json
      ./Project
      ```

      Ini akan mengkompilasi `Project.cpp` dan `currency_manager.cpp` dan menghasilkan file bernama `Project` (atau nama lain sesuai keinginan Anda)。Kemudian，jalankan file tersebut untuk memulai aplikasi。

Branch utama (`main`) dilindungi。Kontribusi wajib dilakukan melalui Pull Request (PR)。

### Alur Kerja Kontribusi:
Ikuti langkah-langkah ini setiap kali Anda ingin menambahkan fitur/perbaikan：

1.  **Pastikan Anda memiliki versi Git terbaru:**
      ```bash
      git --version
      ```
      Jika belum terinstal atau sudah usang，unduh dan instal [Git](https://git-scm.com/)。

2.  **Ambil Kode Terbaru:**
      ```bash
      git checkout main
      git pull origin main
      ```

3.  **Buat Cabang Fitur Baru:**
      ```bash
      git checkout -b fitur/nama-fitur-anda
      ```

4.  **Kembangkan & Komit:**
      Kerjakan kode Anda，lalu komit perubahan Anda：
      ```bash
      git add .
      git commit -m "feat: Menambahkan [Nama Fitur]"
      ```

5.  **Unggah Cabang:**
      Unggah cabang fitur Anda ke GitHub：
      ```bash
      git push origin fitur/nama-fitur-anda
      ```

6.  **Buka Pull Request (PR):**
      *   Buka GitHub。
      *   Klik tombol **"Compare & pull request"** yang muncul di notifikasi。
      *   Pastikan target *branch* adalah **`main`**。
      *   Deskripsikan perubahan Anda dan kirim PR。

7.  **Tunggu Review & Merge:**
      PR Anda akan ditinjau oleh setidaknya satu kontributor lain sebelum dapat digabungkan ke `main`。

> **Catatan:** Pastikan Anda selalu memulai dari langkah "Ambil Kode Terbaru" sebelum membuat cabang fitur baru untuk memastikan Anda bekerja dengan kode terbaru。
> **Tips:** Gunakan nama cabang yang deskriptif dan jelas，misalnya `fitur/tambah-dukungan-euro` atau `perbaikan/bug-uang-kertas`。

### Konvensi Penulisan Kode (Code Style)

Untuk menjaga konsistensi kode，harap ikuti konvensi penulisan kode berikut：

*   **Nama Variabel dan Fungsi：** Gunakan `camelCase` untuk nama variabel dan fungsi （misalnya，`jumlahUang`，`konversiMataUang`）。
*   **Nama Kelas：** Gunakan `PascalCase` untuk nama kelas （misalnya，`CurrencyManager`）。
*   **Indentasi：** Gunakan 4 spasi untuk indentasi。
*   **Komentar：** Tambahkan komentar yang jelas dan deskriptif untuk menjelaskan logika kode yang kompleks。
*   **Baris Kosong：** Gunakan baris kosong untuk memisahkan blok kode yang berbeda secara logis。
*   **Panjang Baris：** Coba batasi panjang baris kode hingga 80-100 karakter untuk keterbacaan。
*   **Header File：** Jika Anda membuat file header （`.h`），gunakan `#pragma once` untuk mencegah inklusi ganda。

## 🚀 Panduan Developer: Menambahkan Mata Uang Baru

### 📁 Struktur File Baru

Program konversi mata uang ini sekarang dirancang agar mudah dikembangkan。Developer dapat dengan mudah menambahkan，menghapus，atau mengubah mata uang tanpa perlu menyentuh kode program utama。

```
src/
├── currency_manager.h       # Header CurrencyManager
├── currency_manager.cpp     # Implementasi CurrencyManager
└── currency_config.json     # Konfigurasi mata uang
```

### 🆕 Cara Menambahkan Mata Uang Baru

#### Metode 1: Melalui File Konfigurasi （Direkomendasikan）

1. **Buka file `src/currency_config.json`**

2. **Tambahkan objek baru ke array `currencies`**：

```json
{
  "name": "Nama Mata Uang Lengkap",
  "symbol": "KODE", 
  "display": "Simbol Tampilan",
  "default_rate": 1.0,
  "description": "Deskripsi mata uang"
}
```

**Contoh penambahan mata uang Kanada：**

```json
{
  "name": "Canadian Dollar",
  "symbol": "CAD",
  "display": "C$",
  "default_rate": 1.35,
  "description": "Canadian Dollar"
}
```

3. **Simpan file dan jalankan program**

#### Metode 2: Melalui Program （Runtime）

1. **Jalankan program**
2. **Pilih menu [4] Tambah Mata Uang Baru**
3. **Masukkan data mata uang：**
   - Nama mata uang：`Canadian Dollar`
   - Simbol mata uang：`CAD`
   - Simbol tampilan：`C$`
   - Kurs default：`1.35`

4. **Mata uang akan otomatis ditambahkan ke config file**

### � Aturan Penamaan

#### Symbol （Kode Mata Uang）
- **Gunakan standar ISO 4217** （contoh：USD, EUR, IDR, JPY）
- **3 huruf kapital**
- **Harus unik**，tidak boleh duplikat
- **Wajib** untuk kompatibilitas API

#### Display （Simbol Tampilan）
- Simbol yang ditampilkan ke user
- Boleh menggunakan simbol khusus （€, £, ¥, dll）
- Boleh menggunakan format khusus （C$, A$, S$, dll）
- Tidak harus unik

#### Name （Nama Lengkap）
- Nama lengkap mata uang
- Format：`Negara + Currency` （contoh："US Dollar", "Euro"）
- Harus deskriptif

#### Default Rate
- Kurs default terhadap USD
- Digunakan saat cache expired dan API tidak tersedia
- Harus angka desimal （contoh：1.0, 150.0, 17000.0）

### �🔄 Cara Menghapus Mata Uang

#### Melalui Program：
1. Jalankan program
2. Pilih menu [5] Hapus Mata Uang
3. Pilih nomor mata uang yang ingin dihapus
4. Konfirmasi penghapusan

#### Melalui File Config：
1. Buka `src/currency_config.json`
2. Hapus objek mata uang dari array `currencies`
3. Simpan file

### ⚠️ Peringatan Penting

1. **Jangan gunakan simbol yang sudah ada**
   - Cek terlebih dahulu di file config
   - Simbol harus unik

2. **Pastikan simbol sesuai standar ISO 4217**
   - Untuk kompatibilitas dengan API
   - Cek daftar resmi di [Wikipedia ISO 4217](https://en.wikipedia.org/wiki/ISO_4217)

3. **Default rate harus realistis**
   - Gunakan nilai perkiraan yang mendekati kenyataan
   - Akan diupdate otomatis dari API saat program berjalan

4. **Backup file config sebelum edit**
   - Simpan salinan file config.json
   - Jika terjadi error，bisa dikembalikan

### 🎯 Best Practices

1. **Gunakan format yang konsisten**
2. **Berikan deskripsi yang jelas**
3. **Update default rate secara berkala**
4. **Test setelah menambahkan mata uang baru**
5. **Documentasikan perubahan yang dilakukan**

### 📞 Dukungan

Jika mengalami masalah：
1. Cek log error di console
2. Validasi file JSON
3. Cek koneksi API
4. Buka issue di repository dengan detail error

---

**Selamat mengembangkan！🚀**