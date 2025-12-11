#include "currency_manager.h"
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <cpr/cpr.h>

CurrencyManager::CurrencyManager(const string& config_path, const string& cache_path) 
    : config_file(config_path), cache_file(cache_path) {
}

bool CurrencyManager::loadCurrencies() {
    // Coba load dari cache dulu
    if (loadFromCache() && !isCacheExpired()) {
        return true;
    }
    
    // Jika cache tidak ada atau expired, load dari config
    if (loadFromConfig()) {
        cout << "[INFO] Menggunakan data dari konfigurasi.\n";
        cout << "[INFO] Jalankan menu [3] untuk update kurs dari API.\n";
        return true;
    }
    
    return false;
}

bool CurrencyManager::loadFromConfig() {
    json config = readJSONFile(config_file);
    if (config.is_null()) {
        return false;
    }
    
    currencies.clear();
    auto currencies_json = config["currencies"];
    
    if (currencies_json.is_array()) {
        for (const auto& curr : currencies_json) {
            Currency currency;
            currency.name = curr["name"];
            currency.symbol = curr["symbol"];
            currency.display = curr["display"];
            currency.rate = curr["default_rate"];
            currencies.push_back(currency);
        }
        return true;
    }
    
    return false;
}

bool CurrencyManager::loadFromCache() {
    ifstream file(cache_file);
    if (!file.is_open()) {
        return false;
    }
    
    string date;
    getline(file, date); // Baca tanggal cache
    
    currencies.clear();
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
    
    return !currencies.empty();
}

bool CurrencyManager::isCacheExpired() const {
    ifstream file(cache_file);
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

string CurrencyManager::getCurrentDate() const {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char timestampStr[20];
    strftime(timestampStr, sizeof(timestampStr), "%Y-%m-%d %H:%M:%S", ltm);
    return string(timestampStr);
}

bool CurrencyManager::updateFromAPI() {
    try {
        cout << "[INFO] Menghubungi API...\n";
        
        cpr::Response r = cpr::Get(cpr::Url{"https://api.exchangerate-api.com/v4/latest/USD"});
        
        if (r.status_code == 200) {
            json data = json::parse(r.text);
            
            if (data.contains("rates")) {
                json rates = data["rates"];
                int updatedCount = 0;
                
                for (auto& currency : currencies) {
                    string code = currency.symbol;
                    
                    if (rates.contains(code)) {
                        if (code == "USD") {
                            currency.rate = 1.0;
                        } else {
                            currency.rate = rates[code];
                        }
                        updatedCount++;
                    } else {
                        cout << "[WARNING] Kurs untuk " << code << " tidak ditemukan di API\n";
                    }
                }
                
                cout << "[INFO] Kurs berhasil diupdate! (" << updatedCount << "/" << currencies.size() << " mata uang)\n";
                
                // Simpan ke cache
                saveToCache();
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

bool CurrencyManager::saveToCache() {
    ofstream file(cache_file);
    if (!file.is_open()) {
        return false;
    }
    
    file << getCurrentDate() << endl; // Simpan timestamp lengkap
    for (const auto& currency : currencies) {
        file << currency.name << "," << currency.symbol << ","
             << currency.display << "," << currency.rate << endl;
    }
    file.close();
    
    return true;
}

bool CurrencyManager::addCurrency(const Currency& currency) {
    // Cek apakah simbol sudah ada
    for (const auto& curr : currencies) {
        if (curr.symbol == currency.symbol) {
            cout << "[ERROR] Mata uang dengan simbol " << currency.symbol << " sudah ada!\n";
            return false;
        }
    }
    
    currencies.push_back(currency);
    
    // Update config file
    json config = readJSONFile(config_file);
    if (!config.is_null()) {
        json newCurrency;
        newCurrency["name"] = currency.name;
        newCurrency["symbol"] = currency.symbol;
        newCurrency["display"] = currency.display;
        newCurrency["default_rate"] = currency.rate;
        newCurrency["description"] = "New currency added by developer";
        
        config["currencies"].push_back(newCurrency);
        writeJSONFile(config, config_file);
    }
    
    cout << "[SUCCESS] Mata uang " << currency.name << " (" << currency.symbol << ") berhasil ditambahkan!\n";
    return true;
}

bool CurrencyManager::removeCurrency(const string& symbol) {
    // Gunakan erase-remove idiom untuk menghindari double free
    auto original_size = currencies.size();
    currencies.erase(
        remove_if(currencies.begin(), currencies.end(),
                 [&symbol](const Currency& c) { return c.symbol == symbol; }),
        currencies.end()
    );
    
    // Cek apakah ada yang dihapus
    if (currencies.size() < original_size) {
        // Update config file
        json config = readJSONFile(config_file);
        if (!config.is_null()) {
            auto& currencies_json = config["currencies"];
            currencies_json.erase(
                remove_if(currencies_json.begin(), currencies_json.end(),
                         [&symbol](const json& curr) {
                             return curr["symbol"] == symbol;
                         }),
                currencies_json.end()
            );
            writeJSONFile(config, config_file);
        }
        
        return true;
    }
    return false;
}

void CurrencyManager::displayCurrencyList() const {
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

double CurrencyManager::convert(double amount, int from_index, int to_index) const {
    if (from_index < 0 || from_index >= currencies.size() || 
        to_index < 0 || to_index >= currencies.size()) {
        return 0.0;
    }
    
    const Currency& from = currencies[from_index];
    const Currency& to = currencies[to_index];
    
    if (from.symbol == to.symbol) {
        return amount;
    }
    
    return amount / from.rate * to.rate;
}

json CurrencyManager::readJSONFile(const string& filename) const {
    ifstream file(filename);
    if (!file.is_open()) {
        return json::value_t::null;
    }
    
    json data;
    try {
        file >> data;
    } catch (const exception& e) {
        cout << "[ERROR] Gagal membaca file " << filename << ": " << e.what() << "\n";
        return json::value_t::null;
    }
    
    file.close();
    return data;
}

bool CurrencyManager::writeJSONFile(const json& data, const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    file << data.dump(2);
    file.close();
    
    return true;
}