# 💱 Konversi Mata Uang CLI

Aplikasi antarmuka baris perintah (CLI) sederhana yang dibangun dengan C++ untuk melakukan konversi mata uang secara cepat. Alat ini dirancang agar mudah digunakan, memungkinkan pengguna untuk mengkonversi nilai antara berbagai mata uang yang didukung serta melacak seluruh riwayat transaksi konversi dalam satu sesi.

---

## ✨ Fitur Utama

*   **Konversi Fleksibel**: Lakukan konversi instan antara mata uang yang tersedia.
*   **Riwayat Transaksi**: Lihat kembali semua konversi yang telah Anda lakukan selama sesi aplikasi berlangsung.
*   **Validasi Input Cerdas**: Aplikasi dilengkapi dengan penanganan kesalahan input untuk memastikan proses konversi yang lancar dan bebas masalah.

---

## 🌍 Mata Uang yang Didukung

Aplikasi ini mendukung konversi antara mata uang global berikut:

*   **Rupiah** (Rp) 🇮🇩
*   **Dollar** ($) 🇺🇸
*   **Ringgit** (MYR) 🇲🇾
*   **Yen** (Y) 🇯🇵
*   **Euro** (E) 🇪🇺

---

## 🚀 Instalasi & Penggunaan

Untuk bisa menggunakan aplikasi ini, Anda memerlukan kompiler C++ (seperti `g++`) yang terinstal di sistem Anda.

### ⚙️ Kompilasi Kode Sumber

1.  Buka terminal Anda.
2.  Navigasi ke direktori tempat file `Project.cpp` berada.
3.  Jalankan perintah kompilasi berikut:

    ```bash
    g++ Project.cpp -o konversi
    ```

### ▶️ Menjalankan Aplikasi

Setelah proses kompilasi selesai, Anda dapat menjalankan aplikasi dengan perintah:

```bash
./konversi
```

---

## 👩‍💻 Cara Menggunakan Aplikasi

Setelah aplikasi dijalankan, Anda akan disambut dengan menu utama yang intuitif:

```
+======================================+
|        PROGRAM KONVERSI MATA UANG    |
+======================================+
|  [1] Konversi Mata Uang              |
|  [2] Lihat Riwayat Konversi          |
|  [3] Keluar Program                  |
+======================================+
Pilih menu (1-3):
```

*   🔢 **Pilih `1`**: Masuk ke mode konversi. Ikuti petunjuk untuk memilih mata uang asal, mata uang tujuan, dan jumlah yang ingin Anda konversi.
*   📜 **Pilih `2`**: Akses daftar riwayat konversi Anda, menampilkan semua transaksi yang telah dilakukan di sesi saat ini.
*   🚪 **Pilih `3`**: Tutup dan keluar dari program.

---

## 🤝 Kontribusi

Kami sangat menyambut setiap kontribusi untuk pengembangan proyek ini! Jika Anda tertarik untuk menambahkan fitur baru, memperbaiki bug, atau menyempurnakan kode, silakan baca panduan kontribusi lengkap kami di [Contributing.md](Contributing.md).