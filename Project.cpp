#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string_view>
#include <sstream>
#include <limits>
#include <algorithm>
#include <cstdlib>

using namespace std;

// Fungsi clearscreen yang mendeteksi sistem operasi secara otomatis
void clearscreen()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Fungsi tampilkan header program dengan teks center
void tampilkanHeader(const string& judul)
{
    string border = "+==================================================+";
    cout << border << "\n";
    
    int totalWidth = 50; // Lebar dalam border
    int judulLength = judul.length();
    int leftPadding = (totalWidth - judulLength) / 2;
    int rightPadding = totalWidth - judulLength - leftPadding;
    
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

// Fungsi untuk mengonversi angka ke string dengan 2 desimal
string formatCurrency(double amount)
{
    ostringstream oss;
    oss << fixed << setprecision(2) << amount;
    return oss.str();
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
            cout << "   [" << i + 1 << "] " << left << setw(10) << (string(uang[i]) + " (" + symbol[i] + ")") << "\n";
        }
        cout << "+----------------------------------------+\n";
        cout << "|  " << left << setw(35) << judul << ":  |\n";
        cout << "|  (Ketik 'exit' untuk kembali ke menu)  |\n";
        cout << "+----------------------------------------+\n";
        
        cout << ">> ";
        string inputStr;
        cin >> inputStr;
        
        // Cek jika user mengetik 'exit'
        if (inputStr == "exit" || inputStr == "EXIT")
        {
            exitRequested = true;
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
        string inputStr;
        cin >> inputStr;
        
        // Cek jika user mengetik 'exit'
        if (inputStr == "exit" || inputStr == "EXIT")
        {
            exitRequested = true;
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
        
        // Hapus titik pemisah ribuan
        inputStr.erase(remove(inputStr.begin(), inputStr.end(), '.'), inputStr.end());
        
        try
        {
            double jumlah = stod(inputStr);
            
            if (jumlah < 0)
            {
                tampilkanError("Jumlah tidak valid. Harap masukkan angka positif.");
            }
            else if (jumlah == 0)
            {
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
    // Bisa Ditambahkan Mata Uang Lagi Sesuai Kebutuhan
    vector<string_view> uang{"Rupiah", "Dollar", "Ringgit", "Yen", "Euro"};
    vector<string> symbol{"Rp", "$", "MYR", "Y", "E"};
    vector<double> rasio{17000, 1, 5, 150, 1.15};

    vector<string> riwayat;
    bool jalan = true;
    int pilihan;
    int mu1, mu2;
    double input;
    string inputStr;
    string mataUangAsalInput, mataUangTujuanInput, jumlahInput;

    while (jalan)
    {
        //==== MENU UTAMA ====
        tampilkanHeader("PROGRAM KONVERSI MATA UANG");
        cout << "|  [1] Konversi Mata Uang                          |\n";
        cout << "|  [2] Lihat Riwayat Konversi                      |\n";
        cout << "|  [3] Keluar Program                              |\n";
        cout << "+==================================================+\n";
        cout << "Pilih menu (1-3): ";
        
        cin >> pilihan;
        
        if (!cin)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            clearscreen();
            tampilkanError("Input tidak valid. Harap masukkan angka (1-3).");
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
                cout << "[DEBUG] Mata uang sama terdeteksi: mu1=" << mu1 << ", mu2=" << mu2 << endl;
                tampilkanError("Tidak dapat mengonversi mata uang yang sama!",
                              "[SISTEM] Konversi dari: " + string(uang[mu1 - 1]) + " (" + symbol[mu1 - 1] + ")");

                cout << "[DEBUG] Memanggil getPilihanMataUang untuk mata uang tujuan..." << endl;
                mu2 = getPilihanMataUang(uang, symbol, "Masukkan nomor mata uang tujuan",
                                       "[SISTEM] Konversi dari: " + string(uang[mu1 - 1]) + " (" + symbol[mu1 - 1] + ")", exitRequested,
                                       string(uang[mu1 - 1]), symbol[mu1 - 1]);
                
                cout << "[DEBUG] Setelah getPilihanMataUang, mu2=" << mu2 << ", exitRequested=" << exitRequested << endl;
                
                if (exitRequested)
                {
                    cout << "[DEBUG] exitRequested = true, keluar dari loop mata uang sama" << endl;
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
            
            // DEBUG: Tambahkan log untuk memastikan exitRequested bekerja
            cout << "[DEBUG] exitRequested setelah getJumlahInput: " << exitRequested << endl;
            
            if (exitRequested)
            {
                cout << "[DEBUG] Melanjutkan karena exitRequested = true" << endl;
                continue;
            }

            // Perhitungan konversi
            clearscreen();
            tampilkanHeader("HASIL KONVERSI");
            cout << "\n[SISTEM] Menghitung konversi...\n";
            
            double output = input / rasio[mu1 - 1] * rasio[mu2 - 1];

            //==== Tampilan Hasil ====
            cout << "\n+========================================+\n";
            cout << "| Dari    : " << left << setw(29) << (string(uang[mu1 - 1]) + " (" + symbol[mu1 - 1] + ")") << "|\n";
            cout << "| Ke      : " << left << setw(29) << (string(uang[mu2 - 1]) + " (" + symbol[mu2 - 1] + ")") << "|\n";
            cout << "| Jumlah  : " << left << setw(29) << (symbol[mu1 - 1] + formatCurrency(input)) << "|\n";
            cout << "|----------------------------------------|\n";
            cout << "| Hasil   : " << left << setw(29) << (symbol[mu2 - 1] + formatCurrency(output)) << "|\n";
            cout << "+========================================+\n";
            
            // Tampilkan rasio konversi
            cout << "\n[INFO] Rasio konversi: 1 " << symbol[mu1 - 1] << " = "
                 << rasio[mu2 - 1]/rasio[mu1 - 1] << " " << symbol[mu2 - 1] << "\n";

            cout << "\nTekan ENTER untuk melanjutkan...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

            // Simpan riwayat
            ostringstream oss;
            oss << fixed << setprecision(2)
                << symbol[mu1 - 1] << input << " (" << uang[mu1 - 1] << ")"
                << " = "
                << symbol[mu2 - 1] << output << " (" << uang[mu2 - 1] << ")";
            riwayat.push_back(oss.str());
            
            cout << "\n[SISTEM] Menyimpan riwayat konversi...\n";
            clearscreen();
        }

        //==== RIWAYAT ====
        else if (pilihan == 2)
        {
            clearscreen();
            tampilkanHeader("RIWAYAT KONVERSI");

            if (riwayat.empty())
            {
                cout << "|";
                string emptyMsg = "Belum ada riwayat konversi.";
                int totalWidth = 50;
                int msgLength = emptyMsg.length();
                int leftPadding = (totalWidth - msgLength) / 2;
                int rightPadding = totalWidth - msgLength - leftPadding;
                for (int i = 0; i < leftPadding; i++) cout << " ";
                cout << emptyMsg;
                for (int i = 0; i < rightPadding; i++) cout << " ";
                cout << "|\n";
                cout << "+==================================================+\n";
            }
            else
            {
                for (int i = 0; i < (int)riwayat.size(); i++)
                {
                    cout << "| [" << i + 1 << "] " << left << setw(45) << riwayat[i] << "|\n";
                }
                cout << "+==================================================+\n";
            }

            cout << "\nTekan ENTER untuk melanjutkan...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

            clearscreen();
        }

        //==== KELUAR ====
        else if (pilihan == 3)
        {
            clearscreen();
            cout << "\nTerima Kasih telah menggunakan program konversi mata uang!\n";
            jalan = false;
        }

        else
        {
            clearscreen();
            tampilkanError("Pilihan tidak valid. Harap masukkan angka (1-3).");
        }
    }
    return 0;
}
