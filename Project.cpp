#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string_view>
#include <sstream>
#include <limits>
#include <cstdlib>
#include <map>
#include <curl/curl.h>

using namespace std;

// Struktur untuk menyimpan informasi mata uang
struct CurrencyInfo {
    string name;
    string symbol;
    double rate;
};

// Callback function untuk menangani data dari curl
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* userp) {
    size_t totalSize = size * nmemb;
    userp->append((char*)contents, totalSize);
    return totalSize;
}

// Fungsi untuk mengambil data nilai tukar dari API
bool getExchangeRates(map<string, CurrencyInfo>& currencies) {
    CURL* curl;
    CURLcode res;
    string readBuffer;
    
    curl = curl_easy_init();
    if (curl) {
        // API endpoint untuk nilai tukar terhadap USD
        string url = "https://api.exchangerate-api.com/v4/latest/USD";
        
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L); // Timeout 10 detik
        
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        
        if (res != CURLE_OK) {
            return false;
        }
        
        // Parse JSON sederhana untuk mendapatkan nilai tukar
        // Mencari nilai tukar untuk mata uang yang didukung
        if (readBuffer.find("\"rates\":{") != string::npos) {
            // Update nilai tukar untuk mata uang yang didukung
            vector<string> currencyCodes = {"IDR", "MYR", "JPY", "EUR", "CNY"};
            
            for (const string& code : currencyCodes) {
                if (currencies.find(code) != currencies.end()) {
                    size_t pos = readBuffer.find("\"" + code + "\":");
                    if (pos != string::npos) {
                        size_t start = readBuffer.find_first_of("0123456789", pos);
                        size_t end = readBuffer.find_first_not_of("0123456789.", start);
                        if (start != string::npos && end != string::npos) {
                            string rateStr = readBuffer.substr(start, end - start);
                            currencies[code].rate = stod(rateStr);
                        }
                    }
                }
            }
            
            // USD selalu 1 sebagai acuan
            if (currencies.find("USD") != currencies.end()) {
                currencies["USD"].rate = 1.0;
            }
            
            return true;
        }
    }
    
    return false;
}

// Fungsi clearscreen yang mendeteksi sistem operasi secara otomatis
void clearscreen()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Fungsi untuk membuat border dinamis berdasarkan lebar yang diberikan
string generateBorder(int width)
{
    string border = "+";
    for (int i = 0; i < width; i++) {
        border += "=";
    }
    border += "+";
    return border;
}

// Fungsi tampilkan header program dengan teks center
void tampilkanHeader(const string& judul, int width = 50)
{
    string border = generateBorder(width);
    cout << border << "\n";

    int judulLength = judul.length();
    int leftPadding = (width - judulLength) / 2;
    int rightPadding = width - judulLength - leftPadding;

    cout << "|";
    for (int i = 0; i < leftPadding; i++) cout << " ";
    cout << judul;
    for (int i = 0; i < rightPadding; i++) cout << " ";
    cout << "|\n";

    cout << border << "\n";
}

// Fungsi tampilkan header konversi dan kembalikan string
string tampilkanHeaderKonversi(const string& dariMataUang, const string& dariSymbol,
                               const string& keMataUang = "", const string& keSymbol = "")
{
    string header = "[SISTEM] Konversi dari: " + dariMataUang + " (" + dariSymbol + ")";
    if (!keMataUang.empty())
    {
        header += " ke " + keMataUang + " (" + keSymbol + ")";
    }
    header += "\n";
    
    cout << header;
    return header;
}

// Fungsi tampilkan pesan error dan clearscreen
void tampilkanError(const string& pesan, const string& header = "", bool newLine = true)
{
    if (!header.empty())
    {
        cout << header << "\n";
        if (newLine) cout << "\n";
    }
    else if (newLine)
    {
        cout << "\n";
    }
    cout << "[!] " << pesan << "\n";
}

// Fungsi validasi input angka
bool isValidNumber(const string& str)
{
    if (str.empty()) return false;

    bool hasDecimal = false;
    bool hasDigit = false;

    for (char c : str)
    {
        if (c == '.')
        {
            if (hasDecimal) return false;
            hasDecimal = true;
        }
        else if (!isdigit(c))
        {
            return false;
        }
        else
        {
            hasDigit = true;
        }
    }

    return hasDigit;
}

// Fungsi untuk mengonversi angka ke string dengan 2 desimal dan pemisah ribuan
string formatCurrency(double amount)
{
    ostringstream oss;
    oss << fixed << setprecision(2) << amount;
    string result = oss.str();

    // Temukan posisi titik desimal
    size_t dotPos = result.find('.');
    if (dotPos == string::npos) {
        dotPos = result.length();
    }

    // Bagian sebelum titik desimal
    string integerPart = result.substr(0, dotPos);
    string decimalPart = (dotPos < result.length()) ? result.substr(dotPos) : "";

    // Tambahkan pemisah ribuan
    int length = integerPart.length();
    for (int i = length - 3; i > 0; i -= 3) {
        integerPart.insert(i, ",");
    }

    return integerPart + decimalPart;
}

// Helper function to get user input with exit handling
string getUserInput(bool& exitRequested)
{
    string inputStr;
    getline(cin >> ws, inputStr);

    // Cek jika user mengetik 'exit'
    if (inputStr == "exit" || inputStr == "EXIT")
    {
        exitRequested = true;
    }

    return inputStr;
}

// Fungsi untuk mendapatkan pilihan mata uang dari user
int getPilihanMataUang(const vector<string_view>& uang, const vector<string>& symbol,
                       const string& judul, const string& header, bool& exitRequested,
                       const string& selectedCurrency = "", const string& selectedSymbol = "")
{
    exitRequested = false;
    
    while (true)
    {
        cout << "+========================================+\n";
        cout << "|            DAFTAR MATA UANG            |\n";
        cout << "+========================================+\n";
        
        for (int i = 0; i < uang.size(); i++)
        {
            cout << "|   [" << i + 1 << "] " << left << setw(32) << (string(uang[i]) + " (" + symbol[i] + ")") << " |\n";
        }
        cout << "+----------------------------------------+\n";
        cout << "|  " << left << setw(35) << judul << ":  |\n";
        cout << "|  (Ketik 'exit' untuk kembali ke menu)  |\n";
        cout << "+----------------------------------------+\n";
        
        cout << ">> ";
        string inputStr = getUserInput(exitRequested);

        if (exitRequested)
        {
            clearscreen();
            return -1;
        }
        
        // Konversi string ke integer untuk validasi
        try
        {
            int pilihan = stoi(inputStr);

            // Periksa apakah pilihan valid sebelum mengakses array
            if (pilihan >= 1 && pilihan <= (int)uang.size())
            {
                // Selalu tampilkan "anda memilih" terlebih dahulu
                clearscreen();
                cout << "[✓] Anda memilih " << uang[pilihan - 1] << " (" << symbol[pilihan - 1] << ")\n";
                return pilihan;
            }
            else
            {
                // Pilihan tidak valid, tampilkan error
                clearscreen();
                if (!selectedCurrency.empty()) {
                    cout << "[✓] Anda memilih " << selectedCurrency << " (" << selectedSymbol << ")\n";
                }
                tampilkanError("Pilihan tidak ada. Coba lagi.", ""); // Jangan tampilkan header
                // Jangan lanjutkan loop, biarkan user melihat error dan mencoba lagi
            }
        }
        catch (...)
        {
            // Jika input tidak valid (bukan angka), tampilkan error dan lanjutkan loop
            clearscreen();
            if (!selectedCurrency.empty()) {
                cout << "[✓] Anda memilih " << selectedCurrency << " (" << selectedSymbol << ")\n";
            }
            tampilkanError("Input tidak valid. Harap masukkan angka atau 'exit'.", ""); // Jangan tampilkan header
            // Jangan lanjutkan loop, biarkan user melihat error dan mencoba lagi
        }
    }
}

// Fungsi untuk mendapatkan jumlah input dari user
double getJumlahInput(const string& dariMataUang, const string& dariSymbol,
                      const string& keMataUang, const string& keSymbol, bool& exitRequested)
{
    exitRequested = false;
    
    while (true)
    {
        tampilkanHeaderKonversi(dariMataUang, dariSymbol, keMataUang, keSymbol);
        cout << "\n+----------------------------------------+\n";
        cout << "|  Masukkan jumlah yang ingin dikonversi |\n";
        cout << "|  (Ketik 'exit' untuk kembali ke menu)  |\n";
        cout << "+----------------------------------------+\n";
        
        cout << ">> ";
        string inputStr = getUserInput(exitRequested);

        if (exitRequested)
        {
            clearscreen();
            return -1;
        }
        
        // Validasi input menggunakan fungsi kustom
        if (!isValidNumber(inputStr))
        {
            clearscreen();
            tampilkanError("Input harus berupa angka (contoh: 1000, 100.50) atau 'exit'.");
            continue;
        }

        try
        {
            double jumlah = stod(inputStr);
            
            if (jumlah < 0)
            {
                tampilkanError("Jumlah tidak valid. Harap masukkan angka positif.");
            }
            else if (jumlah == 0)
            {
                clearscreen();
                tampilkanError("Jumlah tidak boleh nol. Coba lagi.");
            }
            else
            {
                return jumlah;
            }
        }
        catch (...)
        {
            tampilkanError("Terjadi kesalahan saat memproses angka. Coba lagi.");
        }
    }
}

int main()
{
    // Inisialisasi curl global
    curl_global_init(CURL_GLOBAL_DEFAULT);
    
    // Struktur data untuk mata uang
    map<string, CurrencyInfo> currencies = {
        {"IDR", {"Rupiah", "Rp", 17000.0}},
        {"USD", {"Dollar", "$", 1.0}},
        {"MYR", {"Ringgit", "RM", 5.0}},
        {"JPY", {"Yen", "Y", 150.0}},
        {"EUR", {"Euro", "E", 0.85}},
        {"CNY", {"Yuan", "CNY", 7.05}}
    };
    
    // Coba ambil nilai tukar dari API
    bool apiSuccess = getExchangeRates(currencies);
    
    vector<string> riwayat;
    bool jalan = true;
    int pilihan;
    int mu1, mu2;
    double input;
    string inputStr;
    string mataUangAsalInput, mataUangTujuanInput, jumlahInput;
    
    // Konversi map ke vector untuk tampilan menu
    vector<string> currencyCodes;
    vector<string_view> uang;
    vector<string> symbol;
    vector<double> rasio;
    
    for (const auto& pair : currencies) {
        currencyCodes.push_back(pair.first);
        uang.push_back(pair.second.name);
        symbol.push_back(pair.second.symbol);
        rasio.push_back(pair.second.rate);
    }

    while (jalan)
    {
        //==== MENU UTAMA ====
        tampilkanHeader("PROGRAM KONVERSI MATA UANG");
        cout << "|  [1] Konversi Mata Uang                          |\n";
        cout << "|  [2] Lihat Riwayat Konversi                      |\n";
        cout << "|  [3] Hapus Riwayat Konversi                      |\n";
        cout << "|  [4] Keluar Program                              |\n";
        cout << "+==================================================+\n";
        cout << "Pilih menu (1-4): ";
        
        cin >> pilihan;
        
        if (!cin)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            clearscreen();
            tampilkanError("Input tidak valid. Harap masukkan angka (1-4).");
            continue;
        }

        //==== KONVERSI ====
        if (pilihan == 1)
        {
            clearscreen();
            cout << "[SISTEM] Masuk ke opsi konversi mata uang\n";
            
            bool exitRequested = false;
            
            // Dapatkan mata uang asal
            int mu1 = getPilihanMataUang(uang, symbol, "Masukkan nomor mata uang asal",
                                       "[SISTEM] Masuk ke opsi konversi mata uang", exitRequested, "", "");
            
            if (exitRequested)
            {
                continue;
            }
            
            // Dapatkan mata uang tujuan
            int mu2 = getPilihanMataUang(uang, symbol, "Masukkan nomor mata uang tujuan",
                                       "[SISTEM] Konversi dari: " + string(uang[mu1 - 1]) + " (" + symbol[mu1 - 1] + ")", exitRequested,
                                       string(uang[mu1 - 1]), symbol[mu1 - 1]);
            
            if (exitRequested)
            {
                continue;
            }
            
            // Periksa apakah mata uang sama
            while (mu2 == mu1)
            {
                tampilkanError("Tidak dapat mengonversi mata uang yang sama!",
                              "[SISTEM] Konversi dari: " + string(uang[mu1 - 1]) + " (" + symbol[mu1 - 1] + ")");

                mu2 = getPilihanMataUang(uang, symbol, "Masukkan nomor mata uang tujuan",
                                       "[SISTEM] Konversi dari: " + string(uang[mu1 - 1]) + " (" + symbol[mu1 - 1] + ")", exitRequested,
                                       string(uang[mu1 - 1]), symbol[mu1 - 1]);

                if (exitRequested)
                {
                    break;
                }
            }
            
            if (exitRequested)
            {
                continue;
            }
            
            // Dapatkan jumlah input
            double input = getJumlahInput(string(uang[mu1 - 1]), symbol[mu1 - 1],
                                        string(uang[mu2 - 1]), symbol[mu2 - 1], exitRequested);

            if (exitRequested)
            {
                continue;
            }

            // Perhitungan konversi
            clearscreen();
            tampilkanHeader("HASIL KONVERSI");
            
            // Ambil nilai tukar terbaru dari map currencies
            string code1 = currencyCodes[mu1 - 1];
            string code2 = currencyCodes[mu2 - 1];
            double rate1 = currencies[code1].rate;
            double rate2 = currencies[code2].rate;
            
            double output = input / rate1 * rate2;

            //==== Tampilan Hasil ====
            cout << "| Dari    : " << left << setw(39) << (string(uang[mu1 - 1]) + " (" + symbol[mu1 - 1] + ")") << "|\n";
            cout << "| Ke      : " << left << setw(39) << (string(uang[mu2 - 1]) + " (" + symbol[mu2 - 1] + ")") << "|\n";
            cout << "| Jumlah  : " << left << setw(39) << (symbol[mu1 - 1] + formatCurrency(input)) << "|\n";
            cout << "|--------------------------------------------------|\n";
            cout << "| Hasil   : " << left << setw(39) << (symbol[mu2 - 1] + formatCurrency(output)) << "|\n";
            cout << "+==================================================+\n";
            
            // Tampilkan rasio konversi
            cout << fixed << setprecision(2);
            double conversionRatio = rasio[mu2 - 1] / rasio[mu1 - 1];
            cout << "\n[INFO] Rasio konversi: 1 " << symbol[mu1 - 1] << " = "
                 << formatCurrency(conversionRatio) << " " << symbol[mu2 - 1] << "\n";

            cout << "\nTekan ENTER untuk melanjutkan...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Simpan riwayat
            ostringstream oss;
            oss << symbol[mu1 - 1] << formatCurrency(input) << " (" << uang[mu1 - 1] << ")"
                << " = "
                << symbol[mu2 - 1] << formatCurrency(output) << " (" << uang[mu2 - 1] << ")";
            riwayat.push_back(oss.str());
            
            cout << "\n[SISTEM] Menyimpan riwayat konversi...\n";
            clearscreen();
        }

        //==== RIWAYAT ====
        else if (pilihan == 2)
        {
            clearscreen();

            // Hitung lebar maksimum yang dibutuhkan untuk riwayat
            int maxWidth = 50; // Lebar default
            if (!riwayat.empty())
            {
                // Temukan panjang maksimum dari riwayat
                for (const string& entry : riwayat)
                {
                    int entryLength = entry.length() + 6; // +6 untuk "[X] " dan spasi
                    if (entryLength > maxWidth)
                    {
                        maxWidth = entryLength;
                    }
                }
                // Pastikan lebar minimal 50
                maxWidth = max(maxWidth, 50);
            }

            tampilkanHeader("RIWAYAT KONVERSI", maxWidth);

            if (riwayat.empty())
            {
                string emptyMsg = "Belum ada riwayat konversi.";
                int msgLength = emptyMsg.length();
                int leftPadding = (maxWidth - msgLength) / 2;
                int rightPadding = maxWidth - msgLength - leftPadding;

                cout << "|";
                for (int i = 0; i < leftPadding; i++) cout << " ";
                cout << emptyMsg;
                for (int i = 0; i < rightPadding; i++) cout << " ";
                cout << "|\n";
                cout << generateBorder(maxWidth) << "\n";
            }
            else
            {
                for (int i = 0; i < (int)riwayat.size(); i++)
                {
                    // Hitung padding yang dibutuhkan
                    int contentWidth = maxWidth - 6; // -6 untuk "| [X] " dan " |"
                    cout << "| [" << i + 1 << "] " << left << setw(contentWidth) << riwayat[i] << " |\n";
                }
                cout << generateBorder(maxWidth) << "\n";
            }

            cout << "\nTekan ENTER untuk melanjutkan...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

            clearscreen();
        }

        //==== HAPUS RIWAYAT ====
        else if (pilihan == 3)
        {
            clearscreen();
            cout << "[SISTEM] Masuk ke opsi hapus riwayat konversi\n";
            
            if (riwayat.empty())
            {
                cout << "\n[!] Tidak ada riwayat untuk dihapus.\n";
                cout << "\nTekan ENTER untuk melanjutkan...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                clearscreen();
                continue;
            }
            
            // Tampilkan konfirmasi dialog
            cout << "\n+==================================================+\n";
            cout << "|  Apakah Anda yakin ingin menghapus seluruh       |\n";
            cout << "|  riwayat konversi?                               |\n";
            cout << "|                                                  |\n";
            cout << "|  [1] Ya, hapus seluruh riwayat                   |\n";
            cout << "|  [2] Tidak, batalkan                             |\n";
            cout << "+==================================================+\n";
            
            bool konfirmasiValid = false;
            while (!konfirmasiValid)
            {
                cout << "Pilih (1-2): ";
                
                int konfirmasi;
                cin >> konfirmasi;
                
                if (!cin)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    clearscreen();
                    cout << "[SISTEM] Masuk ke opsi hapus riwayat konversi\n";
                    cout << "\n+==================================================+\n";
                    cout << "|  Apakah Anda yakin ingin menghapus seluruh       |\n";
                    cout << "|  riwayat konversi?                               |\n";
                    cout << "|                                                  |\n";
                    cout << "|  [1] Ya, hapus seluruh riwayat                   |\n";
                    cout << "|  [2] Tidak, batalkan                             |\n";
                    cout << "+==================================================+\n";
                    tampilkanError("Input tidak valid. Harap masukkan angka (1-2).");
                    continue;
                }
                
                if (konfirmasi == 1)
                {
                    konfirmasiValid = true;
                    clearscreen();
                    cout << "[SISTEM] Menghapus seluruh riwayat konversi...\n";
                    
                    // Hapus seluruh riwayat dari penyimpanan lokal (vector)
                    riwayat.clear();
                    
                    cout << "\n[✓] Seluruh riwayat konversi berhasil dihapus.\n";
                    cout << "\nTekan ENTER untuk melanjutkan...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get();
                    clearscreen();
                }
                else if (konfirmasi == 2)
                {
                    konfirmasiValid = true;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    clearscreen();
                }
                else
                {
                    clearscreen();
                    cout << "[SISTEM] Masuk ke opsi hapus riwayat konversi\n";
                    cout << "\n+==================================================+\n";
                    cout << "|  Apakah Anda yakin ingin menghapus seluruh       |\n";
                    cout << "|  riwayat konversi?                               |\n";
                    cout << "|                                                  |\n";
                    cout << "|  [1] Ya, hapus seluruh riwayat                   |\n";
                    cout << "|  [2] Tidak, batalkan                             |\n";
                    cout << "+==================================================+\n";
                    tampilkanError("Pilihan tidak valid. Harap masukkan angka (1-2).");
                }
            }
        }

        //==== KELUAR ====
        else if (pilihan == 4)
        {
            clearscreen();
            cout << "\nTerima Kasih telah menggunakan program konversi mata uang!\n";
            jalan = false;
        }

        else
        {
            clearscreen();
            tampilkanError("Pilihan tidak valid. Harap masukkan angka (1-4).");
        }
    }
    return 0;
}
