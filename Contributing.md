# 📚 Contributing

## 🛠️ Panduan Kontribusi

Kontribusi wajib melalui Pull Request ke branch `main`.

### Alur Kerja:

1.  **Ambil Kode Terbaru:**
    ```bash
    git checkout main
    git pull origin main
    ```

2.  **Buat Cabang Fitur:**
    ```bash
    git checkout -b fitur/nama-fitur
    ```

3.  **Kembangkan & Komit:**
    ```bash
    git add .
    git commit -m "feat: Menambahkan [Nama Fitur]"
    ```

4.  **Unggah & PR:**
    ```bash
    git push origin fitur/nama-fitur
    ```
    Buka GitHub, buat Pull Request ke branch `main`.

5.  **Review & Merge:**
    PR ditinjau sebelum digabung.

## 💱 Menambahkan Mata Uang Baru

### 1. Tambahkan ke Struktur Data
Di fungsi [`main()`](Project.cpp:352-361), tambahkan ke `currencies`:
```cpp
{"KODE", {"Nama", "Simbol", nilai_default}}
```

### 2. Tambahkan ke API
Di fungsi [`getExchangeRates()`](Project.cpp:30-82), tambahkan ke `currencyCodes`:
```cpp
vector<string> currencyCodes = {"IDR", "MYR", "JPY", "EUR", "KODE"};
```

### 3. Uji Coba
Kompilasi dan jalankan program untuk memastikan mata uang baru muncul dan nilai tukar diambil dari API.
