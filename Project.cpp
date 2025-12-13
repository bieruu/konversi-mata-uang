#include <iostream>
#include <string>
#include <iomanip>
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

// Fungsi untuk validasi input angka
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

    while (jalan)
    {
        //==== MENU UTAMA ====
        clearscreen();
        cout << "+======================================+\n";
        cout << "|        PROGRAM KONVERSI MATA UANG    |\n";
        cout << "+======================================+\n";
        cout << "|  [1] Konversi Mata Uang              |\n";
        cout << "|  [2] Lihat Riwayat Konversi          |\n";
        cout << "|  [3] Keluar Program                  |\n";
        cout << "+======================================+\n";
        cout << "Pilih menu (1-3): ";

        cin >> pilihan;

        if (!cin)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n[!] Input tidak valid. Harap masukkan angka (1-3).\n";
            continue;
        }

        //==== KONVERSI ====
        if (pilihan == 1)
        {
            clearscreen();
            cout << "[SISTEM] Masuk ke opsi konversi mata uang\n";
            cout << "\n+========================================+\n";
            cout << "|            DAFTAR MATA UANG            |\n";
            cout << "+========================================+\n";

            for (int i = 0; i < uang.size(); i++)
            {
                cout << "|  [" << i + 1 << "] " << uang[i]
                     << " (" << symbol[i] << ")\n";
            }
            cout << "+----------------------------------------+\n";
            cout << "|  Masukkan nomor mata uang asal:        |\n";
            cout << "+----------------------------------------+\n";

            while (true)
            {
                cout << ">> ";
                cin >> mu1;

                if (!cin)
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "\n[SISTEM] Memuat ulang daftar mata uang...\n";
                    clearscreen();
                    cout << "[SISTEM] Masuk ke opsi konversi mata uang\n";
                    cout << "\n[!] Input tidak valid. Harap masukkan angka.\n";
                    cout << "\n+========================================+\n";
                    cout << "|            DAFTAR MATA UANG            |\n";
                    cout << "+========================================+\n";

                    for (int i = 0; i < uang.size(); i++)
                    {
                        cout << "|  [" << i + 1 << "] " << uang[i]
                             << " (" << symbol[i] << ")\n";
                    }
                    cout << "+----------------------------------------+\n";
                    cout << "|  Masukkan nomor mata uang asal:        |\n";
                    cout << "+----------------------------------------+\n";
                }
                else if (mu1 < 1 || mu1 > (int)uang.size())
                {
                    cout << "\n[SISTEM] Memuat ulang daftar mata uang...\n";
                    clearscreen();
                    cout << "[SISTEM] Masuk ke opsi konversi mata uang\n";
                    cout << "\n+========================================+\n";
                    cout << "|            DAFTAR MATA UANG            |\n";
                    cout << "+========================================+\n";

                    for (int i = 0; i < uang.size(); i++)
                    {
                        cout << "|  [" << i + 1 << "] " << uang[i]
                             << " (" << symbol[i] << ")\n";
                    }
                    cout << "+----------------------------------------+\n";
                    cout << "\n[!] Pilihan tidak ada. Coba lagi.\n";
                    cout << "|  Masukkan nomor mata uang asal:        |\n";
                    cout << "+----------------------------------------+\n";
                }
                else
                {
                    cout << "\n[✓] Anda memilih " << uang[mu1 - 1] << " (" << symbol[mu1 - 1] << ")\n";
                    break;
                }
            }

            // Input mata uang Tujuan
            clearscreen();
            cout << "[SISTEM] Konversi dari: " << uang[mu1 - 1] << " (" << symbol[mu1 - 1] << ")\n";
            cout << "\n+========================================+\n";
            cout << "|            DAFTAR MATA UANG            |\n";
            cout << "+========================================+\n";

            for (int i = 0; i < uang.size(); i++)
            {
                cout << "|  [" << i + 1 << "] " << uang[i]
                     << " (" << symbol[i] << ")\n";
            }
            cout << "+----------------------------------------+\n";
            cout << "|  Masukkan nomor mata uang tujuan:      |\n";
            cout << "+----------------------------------------+\n";

            while (true)
            {
                cout << ">> ";
                cin >> mu2;

                if (!cin)
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "\n[SISTEM] Memuat ulang daftar mata uang...\n";
                    clearscreen();
                    cout << "[SISTEM] Konversi dari: " << uang[mu1 - 1] << " (" << symbol[mu1 - 1] << ")\n";
                    cout << "\n[!] Input tidak valid. Harap masukkan angka.\n";
                    cout << "\n+========================================+\n";
                    cout << "|            DAFTAR MATA UANG            |\n";
                    cout << "+========================================+\n";

                    for (int i = 0; i < uang.size(); i++)
                    {
                        cout << "|  [" << i + 1 << "] " << uang[i]
                             << " (" << symbol[i] << ")\n";
                    }
                    cout << "+----------------------------------------+\n";
                    cout << "|  Masukkan nomor mata uang tujuan:      |\n";
                    cout << "+----------------------------------------+\n";
                }
                else if (mu2 < 1 || mu2 > (int)uang.size())
                {
                    cout << "\n[SISTEM] Memuat ulang daftar mata uang...\n";
                    clearscreen();
                    cout << "[SISTEM] Konversi dari: " << uang[mu1 - 1] << " (" << symbol[mu1 - 1] << ")\n";
                    cout << "\n[!] Pilihan tidak ada. Coba lagi.\n";
                    cout << "\n+========================================+\n";
                    cout << "|            DAFTAR MATA UANG            |\n";
                    cout << "+========================================+\n";

                    for (int i = 0; i < uang.size(); i++)
                    {
                        cout << "|  [" << i + 1 << "] " << uang[i]
                             << " (" << symbol[i] << ")\n";
                    }
                    cout << "+----------------------------------------+\n";
                    cout << "|  Masukkan nomor mata uang tujuan:      |\n";
                    cout << "+----------------------------------------+\n";
                }
                else if (mu2 == mu1)
                {
                    cout << "\n[SISTEM] Memuat ulang daftar mata uang...\n";
                    clearscreen();
                    cout << "[SISTEM] Konversi dari: " << uang[mu1 - 1] << " (" << symbol[mu1 - 1] << ")\n";
                    cout << "\n[!] Tidak dapat mengonversi mata uang yang sama!\n";
                    cout << "\n+========================================+\n";
                    cout << "|            DAFTAR MATA UANG            |\n";
                    cout << "+========================================+\n";

                    for (int i = 0; i < uang.size(); i++)
                    {
                        cout << "|  [" << i + 1 << "] " << uang[i]
                             << " (" << symbol[i] << ")\n";
                    }
                    cout << "+----------------------------------------+\n";
                    cout << "|  Konversi dari: " << uang[mu1 - 1] << " (" << symbol[mu1 - 1] << ") |\n";
                    cout << "|  Masukkan nomor mata uang tujuan:      |\n";
                    cout << "+----------------------------------------+\n";
                }
                else
                {
                    cout << "\n[✓] Anda memilih " << uang[mu2 - 1] << " (" << symbol[mu2 - 1] << ")\n";
                    break;
                }
            }

            // Input jumlah
            clearscreen();
            cout << "[SISTEM] Konversi dari: " << uang[mu1 - 1] << " (" << symbol[mu1 - 1] << ") ke " << uang[mu2 - 1] << " (" << symbol[mu2 - 1] << ")\n";
            cout << "\n+----------------------------------------+\n";
            cout << "|  Masukkan jumlah yang ingin dikonversi |\n";
            cout << "+----------------------------------------+\n";

            string inputStr;

            while (true)
            {
                cout << ">> ";
                cin >> inputStr;

                // Validasi input menggunakan fungsi kustom
                if (!isValidNumber(inputStr))
                {
                    cout << "\n[SISTEM] Memuat ulang form input...\n";
                    clearscreen();
                    cout << "[SISTEM] Konversi dari: " << uang[mu1 - 1] << " (" << symbol[mu1 - 1] << ") ke " << uang[mu2 - 1] << " (" << symbol[mu2 - 1] << ")\n";
                    cout << "\n[!] Input harus berupa angka (contoh: 1000, 100.50).\n";
                    cout << "\n+----------------------------------------+\n";
                    cout << "|  Masukkan jumlah yang ingin dikonversi |\n";
                    cout << "+----------------------------------------+\n";
                    continue;
                }

                // Hapus titik pemisah ribuan
                inputStr.erase(remove(inputStr.begin(), inputStr.end(), '.'), inputStr.end());

                try
                {
                    input = stod(inputStr);

                    if (input < 0)
                    {
                        cout << "\n[SISTEM] Memuat ulang form input...\n";
                        clearscreen();
                        cout << "[SISTEM] Konversi dari: " << uang[mu1 - 1] << " (" << symbol[mu1 - 1] << ") ke " << uang[mu2 - 1] << " (" << symbol[mu2 - 1] << ")\n";
                        cout << "\n[!] Jumlah tidak valid. Harap masukkan angka positif.\n";
                        cout << "\n+----------------------------------------+\n";
                        cout << "|  Masukkan jumlah yang ingin dikonversi |\n";
                        cout << "+----------------------------------------+\n";
                    }
                    else if (input == 0)
                    {
                        cout << "\n[SISTEM] Memuat ulang form input...\n";
                        clearscreen();
                        cout << "[SISTEM] Konversi dari: " << uang[mu1 - 1] << " (" << symbol[mu1 - 1] << ") ke " << uang[mu2 - 1] << " (" << symbol[mu2 - 1] << ")\n";
                        cout << "\n[!] Jumlah tidak boleh nol. Coba lagi.\n";
                        cout << "\n+----------------------------------------+\n";
                        cout << "|  Masukkan jumlah yang ingin dikonversi |\n";
                        cout << "+----------------------------------------+\n";
                    }
                    else
                    {
                        break;
                    }
                }
                catch (...)
                {
                    cout << "\n[SISTEM] Memuat ulang form input...\n";
                    clearscreen();
                    cout << "[SISTEM] Konversi dari: " << uang[mu1 - 1] << " (" << symbol[mu1 - 1] << ") ke " << uang[mu2 - 1] << " (" << symbol[mu2 - 1] << ")\n";
                    cout << "\n[!] Terjadi kesalahan saat memproses angka. Coba lagi.\n";
                    cout << "\n+----------------------------------------+\n";
                    cout << "|  Masukkan jumlah yang ingin dikonversi |\n";
                    cout << "+----------------------------------------+\n";
                }
            }

            // Perhitungan konversi
            clearscreen();
            cout << "\n[SISTEM] Menghitung konversi...\n";
            
            double output = input / rasio[mu1 - 1] * rasio[mu2 - 1];

            //==== Tampilan Hasil ====
            cout << fixed << setprecision(2);
            cout << "\n+========================================+\n";
            cout << "|           [HASIL KONVERSI]            |\n";
            cout << "+========================================+\n";
            cout << "| Dari    : " << uang[mu1 - 1] << " (" << symbol[mu1 - 1] << ")\n";
            cout << "| Ke      : " << uang[mu2 - 1] << " (" << symbol[mu2 - 1] << ")\n";
            cout << "| Jumlah  : " << symbol[mu1 - 1] << input << "\n";
            cout << "|----------------------------------------|\n";
            cout << "| Hasil   : " << symbol[mu2 - 1] << output << "\n";
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

            cout << "\nTekan ENTER untuk melanjutkan...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            
            clearscreen();
        }

        //==== KELUAR ====
        else if (pilihan == 3)
        {
            cout << "\nTerima Kasih telah menggunakan program konversi mata uang!\n";
            jalan = false;
        }

        else
        {
            cout << "Pilihan tidak Valid.\n";
        }
    }
    return 0;
}