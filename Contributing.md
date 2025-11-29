# 📚 Contributing

---

## 🛠️ Panduan Kontribusi (Wajib Dibaca!)

Untuk berkontribusi pada proyek ini, ikuti langkah-langkah di bawah ini. Pastikan Anda telah menginstal Git di sistem Anda.

### Memulai Kontribusi

1.  **Clone Repository:**
    Mulailah dengan mengkloning repositori proyek ke mesin lokal Anda.
    ```bash
    git clone https://github.com/bieruu/konversi-mata-uang.git
    cd konversi-mata-uang
    ```

2.  **Siapkan Lingkungan Pengembangan:**
    Pastikan Anda memiliki kompiler C++ (misalnya, GCC atau Clang) terinstal. Bergantung pada sistem operasi Anda, Anda mungkin perlu menginstal alat bantu pembangunan lainnya.

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
        Instal MinGW-w64 atau gunakan Windows Subsystem for Linux (WSL) dengan distribusi Linux pilihan Anda. Pastikan GCC/G++ tersedia di PATH Anda.

    Setelah kompiler terinstal, Anda bisa melanjutkan.

3.  **Menjalankan Aplikasi:**
    Untuk menjalankan aplikasi, gunakan kompiler C++ untuk mengkompilasi kode sumber.

    ```bash
    g++ Project.cpp -o konversi
    ./konversi
    ```

    Ini akan mengkompilasi `Project.cpp` dan menghasilkan file bernama `konversi` (atau nama lain sesuai keinginan Anda). Kemudian, jalankan file tersebut untuk memulai aplikasi.

Branch utama (`main`) dilindungi. Kontribusi wajib dilakukan melalui Pull Request (PR).

### Alur Kerja Kontribusi:
Ikuti langkah-langkah ini setiap kali Anda ingin menambahkan fitur/perbaikan:

1.  **Pastikan Anda memiliki versi Git terbaru:**
    ```bash
    git --version
    ```
    Jika belum terinstal atau sudah usang, unduh dan instal [Git](https://git-scm.com/).

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
    Kerjakan kode Anda, lalu komit perubahan Anda:
    ```bash
    git add .
    git commit -m "feat: Menambahkan [Nama Fitur]"
    ```

5.  **Unggah Cabang:**
    Unggah cabang fitur Anda ke GitHub:
    ```bash
    git push origin fitur/nama-fitur-anda
    ```

6.  **Buka Pull Request (PR):**
    *   Buka GitHub.
    *   Klik tombol **"Compare & pull request"** yang muncul di notifikasi.
    *   Pastikan target *branch* adalah **`main`**.
    *   Deskripsikan perubahan Anda dan kirim PR.

7.  **Tunggu Review & Merge:**
    PR Anda akan ditinjau oleh setidaknya satu kontributor lain sebelum dapat digabungkan ke `main`.


> **Catatan:** Pastikan Anda selalu memulai dari langkah "Ambil Kode Terbaru" sebelum membuat cabang fitur baru untuk memastikan Anda bekerja dengan kode terbaru.
> **Tips:** Gunakan nama cabang yang deskriptif dan jelas, misalnya `fitur/tambah-dukungan-euro` atau `perbaikan/bug-uang-kertas`.

### Konvensi Penulisan Kode (Code Style)

Untuk menjaga konsistensi kode, harap ikuti konvensi penulisan kode berikut:

*   **Nama Variabel dan Fungsi:** Gunakan `camelCase` untuk nama variabel dan fungsi (misalnya, `jumlahUang`, `konversiMataUang`).
*   **Nama Kelas:** Gunakan `PascalCase` untuk nama kelas (misalnya, `KonversiMataUang`).
*   **Indentasi:** Gunakan 4 spasi untuk indentasi.
*   **Komentar:** Tambahkan komentar yang jelas dan deskriptif untuk menjelaskan logika kode yang kompleks.
*   **Baris Kosong:** Gunakan baris kosong untuk memisahkan blok kode yang berbeda secara logis.
*   **Panjang Baris:** Coba batasi panjang baris kode hingga 80-100 karakter untuk keterbacaan.
*   **Header File:** Jika Anda membuat file header (`.h`), gunakan `#pragma once` untuk mencegah inklusi ganda.