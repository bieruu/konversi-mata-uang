#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <string_view>
#include <sstream>
#include <limits>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include "analytics_logger.h"

using namespace std;
using json = nlohmann::json;

// Struktur data mata uang
struct Currency {
    string name;        // Nama lengkap mata uang (contoh: "Indonesian Rupiah")
    string symbol;      // Simbol mata uang (contoh: "IDR")
    string display;     // Simbol tampilan (contoh: "Rp")
    double rate;        // Kurs terhadap USD
};

// Konfigurasi default mata uang - TAMBAHKAN DI SINI UNTUK MATA UANG BARU
// Format: {nama_lengkap, simbol_api, simbol_tampilan, kurs_default}
const vector<Currency> DEFAULT_CURRENCIES = {
    {"Indonesian Rupiah", "IDR", "Rp", 17000.0},
    {"US Dollar", "USD", "$", 1.0},
    {"Malaysian Ringgit", "MYR", "RM", 4.5},
    {"Japanese Yen", "JPY", "¥", 150.0},
    {"Euro", "EUR", "€", 0.92},
    {"British Pound", "GBP", "£", 0.78},
    {"Singapore Dollar", "SGD", "S$", 1.35},
    {"Thai Baht", "THB", "฿", 36.5},
    {"Australian Dollar", "AUD", "A$", 1.5},
    {"Chinese Yuan", "CNY", "¥", 7.2},
    {"Korean Won", "KRW", "₩", 1350.0}
};

// Fungsi clear screen cross-platform yang lebih kuat
void clearScreen() {
    #ifdef _WIN32
        // Windows: gunakan cls + cls untuk double clear
        system("cls");
        system("cls");
    #else
        // Linux: gunakan escape sequence yang kuat untuk clear screen + scrollback buffer
        // \033[2J = clear screen
        // \033[H = move cursor to home
        // \033[3J = clear scrollback buffer (history)
        // \033c = full reset terminal
        cout << "\033[2J\033[H\033[3J\033c";
        
        // Kembalikan cursor ke posisi awal
        cout << "\033[H";
    #endif
}

// Fungsi deklarasi
vector<Currency> loadCurrencies();
bool updateExchangeRates(vector<Currency>& currencies);
void saveCurrenciesToFile(const vector<Currency>& currencies);
vector<Currency> loadCurrenciesFromFile();
bool isCacheExpired();
string getCurrentDate();
string getCurrencyName(const string& symbol);
string getDisplaySymbol(const string& symbol);
void saveHistoryToFile(const vector<string>& history);
vector<string> loadHistoryFromFile();

int main()
{
    vector<Currency> currencies = loadCurrencies();
    vector<string> riwayat = loadHistoryFromFile();  // Load previous history
    bool jalan = true;
    int pilihan;
    int mu1, mu2;
    double input;
    string inputStr;
    
    // Inisialisasi analytics logger
    AnalyticsLogger analytics;
    
    // Update kurs dari API saat program dimulai
    cout << "\n[SISTEM] Memperbarui kurs mata uang dari API saat startup...\n";
    if (updateExchangeRates(currencies)) {
        saveCurrenciesToFile(currencies);
        cout << "[INFO] Kurs berhasil diperbarui dari API!\n";
        
        // Log aktivitas update API
        analytics.logAPIUpdate(currencies.size());
    } else {
        cout << "[INFO] Gagal update dari API, menggunakan cache/data default...\n";
    }

    while (jalan)
    {

        //==== MENU UTAMA ====
        cout << "\n";
        cout << "+======================================+\n";
        cout << "|        PROGRAM KONVERSI MATA UANG    |\n";
        cout << "+======================================+\n";
        cout << "|  [1] Konversi Mata Uang              |\n";
        cout << "|  [2] Lihat Riwayat Konversi          |\n";
        cout << "|  [3] Update Kurs Mata Uang           |\n";
        cout << "|  [4] Dashboard Analitik              |\n";
        cout << "|  [5] Laporan Detail                  |\n";
        cout << "|  [6] Bantuan & Informasi             |\n";
        cout << "|  [7] Keluar Program                  |\n";
        cout << "+======================================+\n";
        cout << "Pilih menu (1-5): ";

        cin >> pilihan;

        if (!cin)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak Valid. Coba lagi.\n";
            continue;
        }

        //==== KONVERSI ====
        if (pilihan == 1)
        {
            clearScreen();
            cout << "\n[SISTEM] Masuk ke opsi konversi mata uang\n";
            cout << "\n+========================================+\n";
            cout << "|            DAFTAR MATA UANG            |\n";
            cout << "+========================================+\n";

            for (int i = 0; i < currencies.size(); i++)
            {
                cout << "|  [" << i + 1 << "] " << currencies[i].name
                     << " (" << currencies[i].display << ")\n";
            }
            cout << "+----------------------------------------+\n";

            // Input mata uang Asal
            cout << "\n+----------------------------------------+\n";
            cout << "|  Masukkan nomor mata uang asal:        |\n";
            cout << "+----------------------------------------+\n";

            while (true)
            {
                cout << ">> ";
                cin >> mu1;

                if (!cin || mu1 < 1 || mu1 > (int)currencies.size())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "\n[!] Pilihan tidak ada. Coba lagi.\n";
                    cout << "\n+========================================+\n";
                    cout << "|            DAFTAR MATA UANG            |\n";
                    cout << "+========================================+\n";

                    for (int i = 0; i < currencies.size(); i++)
                    {
                        cout << "|  [" << i + 1 << "] " << currencies[i].name
                             << " (" << currencies[i].display << ")\n";
                    }
                    cout << "+----------------------------------------+\n";
                }
                else
                {
                    break;
                }
            }

            // Input mata uang Tujuan
            cout << "\n+----------------------------------------+\n";
            cout << "|  Konversi dari: " << currencies[mu1 - 1].name << " (" << currencies[mu1 - 1].symbol << ") |\n";
            cout << "|  Masukkan nomor mata uang tujuan:      |\n";
            cout << "+----------------------------------------+\n";

            while (true)
            {
                cout << ">> ";
                cin >> mu2;

                if (!cin || mu2 < 1 || mu2 > (int)currencies.size())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "\n[!] Pilihan tidak ada. Coba lagi.\n";
                    cout << "\n+========================================+\n";
                    cout << "|            DAFTAR MATA UANG            |\n";
                    cout << "+========================================+\n";

                    for (int i = 0; i < currencies.size(); i++)
                    {
                        cout << "|  [" << i + 1 << "] " << currencies[i].name
                             << " (" << currencies[i].display << ")\n";
                    }
                    cout << "+----------------------------------------+\n";
                }
                else if (mu2 == mu1)
                {
                    cout << "\n[!] Tidak dapat mengonversi mata uang yang sama!\n";
                    cout << "\n+========================================+\n";
                    cout << "|            DAFTAR MATA UANG            |\n";
                    cout << "+========================================+\n";

                    for (int i = 0; i < currencies.size(); i++)
                    {
                        cout << "|  [" << i + 1 << "] " << currencies[i].name
                             << " (" << currencies[i].display << ")\n";
                    }
                    cout << "+----------------------------------------+\n";
                }
                else
                {
                    break;
                }
            }

            // Input jumlah
            cout << "\n+----------------------------------------+\n";
            cout << "|  Masukkan jumlah yang ingin dikonversi |\n";
            cout << "+----------------------------------------+\n";

            string inputStr;
            const double MAX_AMOUNT = 1e15; // Batas maksimum 10^15

            while (true)
            {
                cout << ">> ";
                cin >> inputStr;

                // Validasi input tidak kosong
                if (inputStr.empty()) {
                    cout << "\n[!] Input tidak boleh kosong. Coba lagi.\n";
                    continue;
                }

                // Hapus titik desimal untuk validasi
                string cleanInput = inputStr;
                cleanInput.erase(remove(cleanInput.begin(), cleanInput.end(), '.'), cleanInput.end());

                // Validasi format angka (hanya boleh mengandung digit, titik, dan minus)
                bool validFormat = true;
                bool hasDecimalPoint = false;
                bool hasMinus = false;
                
                for (char c : inputStr) {
                    if (c == '.') {
                        if (hasDecimalPoint) {
                            validFormat = false;
                            break;
                        }
                        hasDecimalPoint = true;
                    } else if (c == '-') {
                        if (hasMinus || inputStr.find('-') != 0) {
                            validFormat = false;
                            break;
                        }
                        hasMinus = true;
                    } else if (!isdigit(c)) {
                        validFormat = false;
                        break;
                    }
                }

                if (!validFormat) {
                    cout << "\n[!] Format input tidak valid. Gunakan angka (contoh: 1000.50). Coba lagi.\n";
                    continue;
                }

                try
                {
                    input = stod(inputStr);

                    // Validasi range nilai
                    if (input < 0) {
                        cout << "\n[!] Jumlah tidak boleh negatif. Coba lagi.\n";
                        continue;
                    }
                    
                    if (input > MAX_AMOUNT) {
                        cout << "\n[!] Jumlah terlalu besar. Maksimum: " << fixed << setprecision(0) << MAX_AMOUNT << ". Coba lagi.\n";
                        continue;
                    }
                    
                    if (isnan(input) || isinf(input)) {
                        cout << "\n[!] Nilai tidak valid. Coba lagi.\n";
                        continue;
                    }

                    break;
                }
                catch (const invalid_argument& e)
                {
                    cout << "\n[!] Input harus berupa angka. Coba lagi.\n";
                }
                catch (const out_of_range& e)
                {
                    cout << "\n[!] Nilai terlalu besar. Maksimum: " << fixed << setprecision(0) << MAX_AMOUNT << ". Coba lagi.\n";
                }
            }

            double output = input / currencies[mu1 - 1].rate * currencies[mu2 - 1].rate;

            //==== Tampilan Hasil ====
            cout << fixed << setprecision(2);
            cout << "\n+========================================+\n";
            cout << "|              HASIL KONVERSI           |\n";
            cout << "+========================================+\n";
            cout << "| Dari    : " << currencies[mu1 - 1].name << " (" << currencies[mu1 - 1].display << ")\n";
            cout << "| Ke      : " << currencies[mu2 - 1].name << " (" << currencies[mu2 - 1].display << ")\n";
            cout << "| Jumlah  : " << currencies[mu1 - 1].display << input << "\n";
            cout << "|----------------------------------------|\n";
            cout << "| Hasil   : " << currencies[mu2 - 1].symbol << output << "\n";
            cout << "+========================================+\n";

            cout << "\nTekan ENTER untuk melanjutkan...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

            // Bersihkan layar sebelum kembali ke menu utama
            clearScreen();

            // Simpan riwayat
            ostringstream oss;
            oss << fixed << setprecision(2)
                << currencies[mu1 - 1].display << input << " (" << currencies[mu1 - 1].name << ")"
                << " = "
                << currencies[mu2 - 1].display << output << " (" << currencies[mu2 - 1].name << ")";
            riwayat.push_back(oss.str());
            
            // Save history to file after each conversion
            saveHistoryToFile(riwayat);
            
            // Log aktivitas konversi
            analytics.logConversion(
                currencies[mu1 - 1].symbol,
                currencies[mu2 - 1].symbol,
                input,
                oss.str()
            );
        }

        //==== RIWAYAT ====
        else if (pilihan == 2)
        {
            clearScreen();
            cout << "\n+============== RIWAYAT KONVERSI ==============+\n";

            if (riwayat.empty())
            {
                cout << "| Belum ada riwayat konversi.                 |\n";
                cout << "+----------------------------------------------+\n";
            }
            else
            {
                for (int i = 0; i < (int)riwayat.size(); i++)
                {
                    cout << "| [" << i + 1 << "] " << riwayat[i] << "\n";
                    cout << "+----------------------------------------------+\n";
                }
            }

            // Log aktivitas melihat riwayat
            analytics.logHistoryView();

            cout << "\nTekan ENTER untuk melanjutkan...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

            // Bersihkan layar sebelum kembali ke menu utama
            clearScreen();
        }

        //==== UPDATE KURS ====
        else if (pilihan == 3)
        {
            clearScreen();
            cout << "\n[SISTEM] Update kurs mata uang\n";
            if (updateExchangeRates(currencies)) {
                saveCurrenciesToFile(currencies);
                cout << "[INFO] Kurs telah diperbarui dari API!\n";
                
                // Log aktivitas update API
                analytics.logAPIUpdate(currencies.size());
            } else {
                cout << "[INFO] Gagal update dari API, menggunakan cache...\n";
            }
            
            cout << "\nTekan ENTER untuk melanjutkan...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

            // Bersihkan layar sebelum kembali ke menu utama
            clearScreen();
        }

        //==== DASHBOARD ANALITIK ====
        else if (pilihan == 4)
        {
            clearScreen();
            cout << "\n[SISTEM] Menampilkan dashboard analitik...\n";
            analytics.generateDashboard();
            
            cout << "\nTekan ENTER untuk melanjutkan...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

            // Bersihkan layar sebelum kembali ke menu utama
            clearScreen();
        }
        
        //==== LAPORAN DETAIL ====
        else if (pilihan == 5)
        {
            clearScreen();
            cout << "\n[SISTEM] Menampilkan laporan analitik detail...\n";
            analytics.generateDetailedReport();
            
            cout << "\nTekan ENTER untuk melanjutkan...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

            // Bersihkan layar sebelum kembali ke menu utama
            clearScreen();
        }

        //==== BANTUAN ====
        else if (pilihan == 6)
        {
            clearScreen();
            cout << "\n+===============================================+\n";
            cout << "|              BANTUAN & INFORMASI              |\n";
            cout << "+===============================================+\n";
            cout << "Program ini digunakan untuk mengonversi mata uang\n";
            cout << "antar negara dengan kurs terupdate dari API.\n";
            cout << "\nFitur Utama:\n";
            cout << "1. Konversi mata uang\n";
            cout << "2. Riwayat konversi\n";
            cout << "3. Update kurs dari API\n";
            cout << "4. Dashboard analitik\n";
            cout << "5. Laporan detail\n";
            cout << "\nTips:\n";
            cout << "- Pastikan koneksi internet stabil\n";
            cout << "- Update kurs secara berkala\n";
            cout << "- Gunakan simbol mata uang yang benar\n";
            cout << "\nMata Uang yang Didukung:\n";
            
            // Tampilkan daftar mata uang yang didukung secara dinamis
            for (int i = 0; i < (int)currencies.size(); i++) {
                cout << "- " << currencies[i].symbol << " (" << currencies[i].name << ") - " << currencies[i].display << "\n";
            }
            cout << "\n+===============================================+\n";

            cout << "\nTekan ENTER untuk melanjutkan...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

            // Bersihkan layar sebelum kembali ke menu utama
            clearScreen();
        }

        //==== KELUAR ====
        else if (pilihan == 7)
        {
            cout << "\nTerima Kasih telah menggunakan program konversi mata uang!\n";
            cout << "Jika mengalami masalah, silakan coba:\n";
            cout << "  - sudo ldconfig (jika error library)\n";
            cout << "  - ./install.sh (untuk install ulang)\n";
            jalan = false;
        }

        else
        {
            clearScreen();
            cout << "[ERROR] Pilihan tidak Valid. Silakan pilih 1-7.\n";
            
            cout << "\nTekan ENTER untuk melanjutkan...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
    
    // Save history before exiting
    saveHistoryToFile(riwayat);
    return 0;
}

// Fungsi untuk menyimpan riwayat ke file
void saveHistoryToFile(const vector<string>& history) {
    ofstream file("conversion_history.txt");
    if (file.is_open()) {
        for (const auto& entry : history) {
            file << entry << endl;
        }
        file.close();
    }
}

// Fungsi untuk memuat riwayat dari file
vector<string> loadHistoryFromFile() {
    vector<string> history;
    ifstream file("conversion_history.txt");
    
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            history.push_back(line);
        }
        file.close();
    }
    
    return history;
}

// Fungsi untuk mendapatkan tanggal saat ini
string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char timestampStr[20];
    strftime(timestampStr, sizeof(timestampStr), "%Y-%m-%d %H:%M:%S", ltm);
    return string(timestampStr);
}

// Fungsi untuk ekspor data analitik
void exportAnalyticsData(AnalyticsLogger& analytics) {
    string filename;
    cout << "\nMasukkan nama file untuk ekspor data (contoh: analytics_export.json): ";
    cin >> filename;
    
    if (filename.empty()) {
        filename = "analytics_export_" + getCurrentDate() + ".json";
    }
    
    analytics.exportAnalytics(filename);
    
    cout << "\nTekan ENTER untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Fungsi untuk memeriksa apakah cache sudah expired (lebih dari 1 jam)
bool isCacheExpired() {
    ifstream file("currency_cache.txt");
    if (!file.is_open()) {
        return true;
    }
    
    string cacheTimestamp;
    getline(file, cacheTimestamp);
    file.close();
    
    // Parse timestamp cache (format: YYYY-MM-DD HH:MM:SS)
    if (cacheTimestamp.length() < 16) {
        return true; // Format tidak valid
    }
    
    try {
        // Ambil jam cache
        int cacheHour = stoi(cacheTimestamp.substr(11, 2));
        int cacheMinute = stoi(cacheTimestamp.substr(14, 2));
        
        // Hitung waktu sekarang
        time_t now = time(0);
        tm *ltm = localtime(&now);
        
        int currentHour = ltm->tm_hour;
        int currentMinute = ltm->tm_min;
        
        // Hitung selisih waktu dalam menit
        int cacheTimeMinutes = cacheHour * 60 + cacheMinute;
        int currentTimeMinutes = currentHour * 60 + currentMinute;
        
        // Hitung selisih (dengan penanganan wrap-around harian)
        int diffMinutes;
        if (currentTimeMinutes >= cacheTimeMinutes) {
            diffMinutes = currentTimeMinutes - cacheTimeMinutes;
        } else {
            diffMinutes = (24 * 60) - cacheTimeMinutes + currentTimeMinutes;
        }
        
        // Cache expired jika lebih dari 60 menit (1 jam)
        return diffMinutes > 60;
        
    } catch (const exception& e) {
        return true; // Jika parsing gagal, anggap expired
    }
}

// Fungsi untuk menyimpan data mata uang ke file
void saveCurrenciesToFile(const vector<Currency>& currencies) {
    ofstream file("currency_cache.txt");
    if (file.is_open()) {
        file << getCurrentDate() << endl; // Simpan timestamp lengkap
        for (const auto& currency : currencies) {
            file << currency.name << "," << currency.symbol << "," << currency.display << "," << currency.rate << endl;
        }
        file.close();
    }
}

// Fungsi untuk memuat data mata uang dari file
vector<Currency> loadCurrenciesFromFile() {
    vector<Currency> currencies;
    ifstream file("currency_cache.txt");
    
    if (file.is_open()) {
        string timestamp;
        getline(file, timestamp); // Baca timestamp cache
        
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, symbol, display;
            double rate;
            
            getline(ss, name, ',');
            getline(ss, symbol, ',');
            getline(ss, display, ',');
            ss >> rate;
            
            currencies.push_back({name, symbol, display, rate});
        }
        file.close();
    }
    
    return currencies;
}

// Fungsi untuk memuat data mata uang (dari cache atau default)
vector<Currency> loadCurrencies() {
    vector<Currency> currencies = loadCurrenciesFromFile();
    
    if (currencies.empty() || isCacheExpired()) {
        // Gunakan konfigurasi default - CUKUP UBAH DI DEFAULT_CURRENCIES DI ATAS
        currencies = DEFAULT_CURRENCIES;
        cout << "[INFO] Menggunakan data default. Jalankan menu [3] untuk update dari API.\n";
    }
    
    return currencies;
}

// Fungsi untuk update kurs dari API
bool updateExchangeRates(vector<Currency>& currencies) {
    try {
        cout << "[INFO] Menghubungi API...\n";
        
        // Request ke API (gunakan base USD)
        cpr::Response r = cpr::Get(cpr::Url{"https://api.exchangerate-api.com/v4/latest/USD"});
        
        if (r.status_code == 200) {
            json data = json::parse(r.text);
            
            if (data.contains("rates")) {
                json rates = data["rates"];
                int updatedCount = 0;
                
                // Update kurs untuk semua mata uang yang ada di konfigurasi
                for (auto& currency : currencies) {
                    string code = currency.symbol; // Gunakan simbol API langsung
                    
                    if (rates.contains(code)) {
                        if (code == "USD") {
                            currency.rate = 1.0; // USD sebagai base
                        } else {
                            currency.rate = rates[code];
                        }
                        updatedCount++;
                    } else {
                        cout << "[WARNING] Kurs untuk " << code << " tidak ditemukan di API\n";
                    }
                }
                
                cout << "[INFO] Kurs berhasil diupdate! (" << updatedCount << "/" << currencies.size() << " mata uang)\n";
                return true;
            }
        }
        
        cout << "[ERROR] Gagal mendapatkan data dari API\n";
        return false;
        
    } catch (const exception& e) {
        cout << "[ERROR] Exception: " << e.what() << "\n";
        return false;
    }
}

// Fungsi untuk menambahkan mata uang baru (untuk developer)
void addNewCurrency(vector<Currency>& currencies, const string& name, const string& symbol, const string& display, double rate = 1.0) {
    // Cek apakah mata uang sudah ada
    for (const auto& currency : currencies) {
        if (currency.symbol == symbol) {
            cout << "[ERROR] Mata uang dengan simbol " << symbol << " sudah ada!\n";
            return;
        }
    }
    
    currencies.push_back({name, symbol, display, rate});
    cout << "[SUCCESS] Mata uang " << name << " (" << symbol << ") berhasil ditambahkan!\n";
}

// Fungsi untuk menghapus mata uang
bool removeCurrency(vector<Currency>& currencies, const string& symbol) {
    auto it = remove_if(currencies.begin(), currencies.end(),
                        [&symbol](const Currency& c) { return c.symbol == symbol; });
    
    if (it != currencies.end()) {
        currencies.erase(it, currencies.end());
        return true;
    }
    return false;
}

// Fungsi untuk menampilkan daftar mata uang
void showCurrencyList(const vector<Currency>& currencies) {
    cout << "\n+===============================================+\n";
    cout << "|              DAFTAR MATA UANG                |\n";
    cout << "+===============================================+\n";
    cout << "| No | Kode | Nama Lengkap              | Tampil |\n";
    cout << "+----+------+---------------------------+--------+\n";
    
    for (int i = 0; i < (int)currencies.size(); i++) {
        cout << "| " << setw(2) << i + 1 << " | "
             << setw(4) << currencies[i].symbol << " | "
             << left << setw(25) << currencies[i].name << " | "
             << setw(6) << currencies[i].display << " |\n";
    }
    cout << "+===============================================+\n";
}