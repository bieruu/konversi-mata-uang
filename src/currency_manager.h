#ifndef CURRENCY_MANAGER_H
#define CURRENCY_MANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

// Struktur data mata uang
struct Currency {
    string name;        // Nama lengkap mata uang (contoh: "Indonesian Rupiah")
    string symbol;      // Simbol mata uang (contoh: "IDR")
    string display;     // Simbol tampilan (contoh: "Rp")
    double rate;        // Kurs terhadap USD
};

class CurrencyManager {
private:
    vector<Currency> currencies;
    string config_file;
    string cache_file;

public:
    CurrencyManager(const string& config_path = "src/currency_config.json", 
                   const string& cache_path = "currency_cache.txt");
    
    // Load currencies dari config atau cache
    bool loadCurrencies();
    
    // Update kurs dari API
    bool updateFromAPI();
    
    // Simpan ke cache
    bool saveToCache();
    
    // Tambah mata uang baru
    bool addCurrency(const Currency& currency);
    
    // Hapus mata uang
    bool removeCurrency(const string& symbol);
    
    // Dapatkan daftar mata uang
    vector<Currency> getCurrencies() const { return currencies; }
    
    // Dapatkan mata uang berdasarkan index
    Currency getCurrency(int index) const { return currencies[index]; }
    
    // Dapatkan jumlah mata uang
    int size() const { return currencies.size(); }
    
    // Tampilkan daftar mata uang
    void displayCurrencyList() const;
    
    // Konversi mata uang
    double convert(double amount, int from_index, int to_index) const;
    
private:
    // Load dari config JSON
    bool loadFromConfig();
    
    // Load dari cache file
    bool loadFromCache();
    
    // Cek apakah cache expired
    bool isCacheExpired() const;
    
    // Dapatkan tanggal saat ini
    string getCurrentDate() const;
    
    // Baca file JSON
    json readJSONFile(const string& filename) const;
    
    // Tulis file JSON
    bool writeJSONFile(const json& data, const string& filename) const;
};

#endif // CURRENCY_MANAGER_H