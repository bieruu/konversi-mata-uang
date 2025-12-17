# 💰 Konversi Mata Uang C++ (CLI)

Program konversi mata uang berbasis command-line menggunakan C++. Mendukung konversi antar 5 mata uang dengan validasi input, riwayat transaksi, dan fitur hapus riwayat.

## 🎯 Fitur

- Konversi antar 5 mata uang (Rupiah, Dollar, Ringgit, Yen, Euro)
- Validasi input angka dan pilihan menu
- Riwayat transaksi dalam sesi
- Hapus seluruh riwayat
- Cross-platform (Windows/Linux/Mac)
- Tampilan ramah dengan simbol

## 🌍 Mata Uang

| Mata Uang | Simbol | Kode | Rasio terhadap Dollar |
|-----------|--------|------|-----------------------|
| Rupiah    | Rp     | IDR  | 17.000                |
| Dollar    | $      | USD  | 1 (acuan)             |
| Ringgit   | RM     | MYR  | 5                     |
| Yen       | Y      | JPY  | 150                   |
| Euro      | E      | EUR  | 0.85                  |

## 🚀 Cara Menjalankan

### Persyaratan
- Kompiler C++ (g++, clang++, dll)

### Kompilasi

**Untuk Linux:**
```bash
g++ Project.cpp -o Project.out
```

**Untuk Windows:**
```bash
g++ Project.cpp -o Project.exe
```

### Eksekusi

**Untuk Linux:**
```bash
./Project.out
```

**Untuk Windows:**
```bash
Project.exe
```

## 📱 Cara Penggunaan

### Menu Utama
Program menampilkan 4 pilihan:
1. **Konversi Mata Uang** - Melakukan konversi
2. **Lihat Riwayat Konversi** - Menampilkan riwayat sesi
3. **Hapus Riwayat Konversi** - Menghapus seluruh riwayat
4. **Keluar Program** - Mengakhiri program

## 🏗️ Struktur Kode

### Fungsi Utama
- [`clearscreen()`](Project.cpp:14-21) - Membersihkan layar sesuai OS
- [`isValidNumber()`](Project.cpp:24-49) - Validasi input angka
- [`main()`](Project.cpp:51-394) - Program utama

### Variabel Global
- [`uang`](Project.cpp:53) - Daftar nama mata uang
- [`symbol`](Project.cpp:54) - Simbol mata uang
- [`rasio`](Project.cpp:55) - Rasio konversi ke Dollar
- [`riwayat`](Project.cpp:57) - Menyimpan riwayat konversi

### Rumus Konversi
Program menggunakan rumus konversi dua tahap melalui Dollar sebagai acuan:

```
output = input / rasio_asal * rasio_tujuan

Rasio antar mata uang:
rasio_tujuan / rasio_asal
```

Contoh: Konversi 100.000 IDR ke USD
- Rasio IDR = 17.000, Rasio USD = 1
- 100.000 / 17.000 × 1 = 5.88 USD

### Alur Program
1. Tampilkan menu utama
2. Proses pilihan pengguna
3. Validasi input (angka, pilihan, nilai positif)
4. Hitung konversi menggunakan rumus di atas
5. Simpan ke riwayat
6. Ulangi atau keluar

## ⚠️ Validasi Input & Exception Handling

Program menerapkan validasi input ketat pada setiap langkah:

### 1. Validasi Pilihan Menu
- **Exception**: `std::ios::failbit` jika input bukan angka
- **Penanganan**: Membersihkan buffer dan meminta input ulang
- **Validasi**: Hanya menerima nilai 1, 2, 3, atau 4

### 2. Validasi Pilihan Mata Uang
- **Exception**: `std::ios::failbit` jika input bukan angka
- **Validasi Rentang**: Hanya menerima nilai 1-5 (sesuai jumlah mata uang)
- **Validasi Logika**: Tidak boleh memilih mata uang asal dan tujuan yang sama

### 3. Validasi Jumlah Konversi
- **Exception**: `std::invalid_argument` atau `std::out_of_range` pada `std::stod()`
- **Validasi Format**: Menggunakan fungsi [`isValidNumber()`](Project.cpp:24-49) untuk memastikan:
  - Hanya mengandung digit dan satu titik desimal
  - Minimal memiliki satu digit
  - Tidak mengandung karakter selain digit dan titik
- **Validasi Nilai**:
  - Tidak boleh negatif
  - Tidak boleh nol
  - Maksimal sesuai batas `double`

### 4. Mekanisme Penanganan Kesalahan
```cpp
// Contoh penanganan exception pada input angka
try {
    input = stod(inputStr);
    if (input <= 0) {
        // Validasi nilai
    }
} catch (...) {
    // Penanganan exception umum
}
```

### 5. Respon Sistem terhadap Error
- **Clear Screen**: Sistem memuat ulang tampilan setiap kali terjadi error
- **Pesan Error**: Menampilkan pesan spesifik sesuai jenis error
- **Looping**: Meminta input ulang tanpa keluar dari program
- **Buffer Cleanup**: Membersihkan input buffer sebelum meminta input baru

## ⚠️ Catatan Teknis

- Rasio konversi menggunakan Dollar sebagai acuan
- Program menggunakan validasi input ketat
- Riwayat hanya tersimpan selama sesi berlangsung
- Mendukung input desimal (contoh: 100.50)
- Mendeteksi sistem operasi secara otomatis untuk perintah clear screen

## 🤝 Kontribusi

Untuk berkontribusi pada proyek ini, silakan ikuti panduan kontribusi yang terdapat di [Contributing.md](Contributing.md).

**Ringkasan proses kontribusi:**
1. Ambil kode terbaru dari branch `main`
2. Buat branch fitur baru dengan format `fitur/nama-fitur`
3. Lakukan perubahan dan komit dengan format pesan `"feat: deskripsi perubahan"`
4. Push ke repository dan buat Pull Request ke branch `main`
5. Tunggu review dan approval dari kontributor lain

## 📄 Lisensi

Proyek ini bersifat open-source untuk pembelajaran.
