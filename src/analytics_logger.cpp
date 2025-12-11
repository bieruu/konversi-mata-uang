#include "analytics_logger.h"
#include <fstream>
#include <algorithm>
#include <numeric>
#include <cmath>

AnalyticsLogger::AnalyticsLogger(const string& log_path) : log_file(log_path) {
    loadLogs();
}

AnalyticsLogger::~AnalyticsLogger() {
    // Save any pending logs
}

string AnalyticsLogger::getCurrentTimestamp() const {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", ltm);
    return string(timestamp);
}

bool AnalyticsLogger::loadLogs() {
    ifstream file(log_file);
    if (!file.is_open()) {
        return false;
    }
    
    string line;
    int validLogs = 0;
    int invalidLogs = 0;
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        ActivityLog log;
        stringstream ss(line);
        string temp;
        
        try {
            // Parse log format: timestamp|type|details|amount|from|to
            if (!getline(ss, log.timestamp, '|')) {
                invalidLogs++;
                continue;
            }
            
            if (!getline(ss, log.activity_type, '|')) {
                invalidLogs++;
                continue;
            }
            
            if (!getline(ss, log.details, '|')) {
                invalidLogs++;
                continue;
            }
            
            if (!getline(ss, temp, '|')) {
                invalidLogs++;
                continue;
            }
            
            // Validasi dan parse amount
            try {
                log.amount = stod(temp);
                if (isnan(log.amount) || isinf(log.amount)) {
                    invalidLogs++;
                    continue;
                }
            } catch (const invalid_argument& e) {
                invalidLogs++;
                continue;
            } catch (const out_of_range& e) {
                invalidLogs++;
                continue;
            }
            
            if (!getline(ss, log.from_currency, '|')) {
                invalidLogs++;
                continue;
            }
            
            if (!getline(ss, log.to_currency, '|')) {
                invalidLogs++;
                continue;
            }
            
            // Validasi minimal data
            if (log.timestamp.empty() || log.activity_type.empty()) {
                invalidLogs++;
                continue;
            }
            
            logs.push_back(log);
            updateAnalytics(log);
            validLogs++;
            
        } catch (const exception& e) {
            invalidLogs++;
            continue;
        }
    }
    
    file.close();
    
    // Tampilkan statistik loading
    if (invalidLogs > 0) {
        cout << "[WARNING] " << invalidLogs << " log entries gagal diparsing, "
             << validLogs << " berhasil.\n";
    }
    
    return validLogs > 0;
}

void AnalyticsLogger::saveLogToFile(const ActivityLog& log) {
    ofstream file(log_file, ios::app);
    if (file.is_open()) {
        // Validasi data sebelum disimpan
        if (log.timestamp.empty() || log.activity_type.empty()) {
            cout << "[ERROR] Gagal menyimpan log: data tidak valid\n";
            file.close();
            return;
        }
        
        file << log.timestamp << "|"
             << log.activity_type << "|"
             << log.details << "|"
             << fixed << setprecision(2) << log.amount << "|"
             << log.from_currency << "|"
             << log.to_currency << endl;
        file.close();
    } else {
        cout << "[ERROR] Gagal membuka file log untuk penulisan\n";
    }
}

void AnalyticsLogger::updateAnalytics(const ActivityLog& log) {
    // Validasi log sebelum update analytics
    if (log.activity_type.empty()) {
        return;
    }
    
    if (log.activity_type == "conversion") {
        total_conversions++;
        if (!log.from_currency.empty()) {
            currency_usage[log.from_currency]++;
        }
        if (!log.to_currency.empty()) {
            currency_usage[log.to_currency]++;
        }
        if (!log.from_currency.empty() && !isnan(log.amount) && !isinf(log.amount)) {
            currency_amounts[log.from_currency] += log.amount;
        }
    } else if (log.activity_type == "api_update") {
        total_api_updates++;
    } else if (log.activity_type == "view_history") {
        total_history_views++;
    }
    
    // Update daily activity
    if (log.timestamp.length() >= 10) {
        string date = log.timestamp.substr(0, 10);
        daily_activity[date]++;
    }
}

void AnalyticsLogger::logConversion(const string& from_currency, const string& to_currency, double amount, const string& result) {
    // Validasi input
    if (from_currency.empty() || to_currency.empty()) {
        cout << "[ERROR] Gagal logging konversi: mata uang tidak valid\n";
        return;
    }
    
    if (isnan(amount) || isinf(amount) || amount < 0) {
        cout << "[ERROR] Gagal logging konversi: jumlah tidak valid\n";
        return;
    }
    
    ActivityLog log;
    log.timestamp = getCurrentTimestamp();
    log.activity_type = "conversion";
    log.details = result;
    log.amount = amount;
    log.from_currency = from_currency;
    log.to_currency = to_currency;
    
    logs.push_back(log);
    updateAnalytics(log);
    saveLogToFile(log);
}

void AnalyticsLogger::logAPIUpdate(int updated_count) {
    ActivityLog log;
    log.timestamp = getCurrentTimestamp();
    log.activity_type = "api_update";
    log.details = "Updated " + to_string(updated_count) + " currencies";
    log.amount = 0.0;
    
    logs.push_back(log);
    updateAnalytics(log);
    saveLogToFile(log);
}

void AnalyticsLogger::logHistoryView() {
    ActivityLog log;
    log.timestamp = getCurrentTimestamp();
    log.activity_type = "view_history";
    log.details = "Viewed conversion history";
    log.amount = 0.0;
    
    logs.push_back(log);
    updateAnalytics(log);
    saveLogToFile(log);
}

void AnalyticsLogger::generateDashboard() {
    cout << "\n+===============================================+\n";
    cout << "|           DASHBOARD ANALITIK PENGGUNAAN       |\n";
    cout << "+===============================================+\n";
    cout << "| Statistik Penggunaan Program                  |\n";
    cout << "+-----------------------------------------------+\n";
    
    // Total aktivitas
    cout << "| Total Konversi     : " << setw(15) << total_conversions << " |\n";
    cout << "| Total Update API   : " << setw(15) << total_api_updates << " |\n";
    cout << "| Total Lihat Riwayat: " << setw(15) << total_history_views << " |\n";
    cout << "| Total Aktivitas    : " << setw(15) << logs.size() << " |\n";
    cout << "+-----------------------------------------------+\n";
    
    // Mata uang paling sering digunakan
    string most_used = getMostUsedCurrency();
    cout << "| Mata Uang Terpopuler: " << setw(14) << most_used << " |\n";
    cout << "+-----------------------------------------------+\n";
    
    // Total amount yang dikonversi
    double total_amount = getTotalAmountConverted();
    cout << "| Total Amount (USD)  : " << setw(14) << fixed << setprecision(2) << total_amount << " |\n";
    cout << "+-----------------------------------------------+\n";
    
    // Top 5 mata uang
    cout << "\n| Top 5 Mata Uang yang Sering Digunakan:        |\n";
    cout << "+----+------+---------------------------+--------+\n";
    cout << "| No | Kode | Nama                      | Jumlah |\n";
    cout << "+----+------+---------------------------+--------+\n";
    
    auto top_currencies = getTopCurrencies(5);
    for (size_t i = 0; i < top_currencies.size(); i++) {
        cout << "| " << setw(2) << (i + 1) << " | "
             << setw(4) << top_currencies[i].first << " | "
             << left << setw(25) << top_currencies[i].first << " | "
             << setw(6) << top_currencies[i].second << " |\n";
    }
    cout << "+===============================================+\n";
    
    // Aktivitas harian terakhir
    cout << "\n| Aktivitas Harian (7 hari terakhir):           |\n";
    cout << "+----------+-----------+----------+-------------+\n";
    cout << "| Tanggal  | Konversi  | Update   | Lihat       |\n";
    cout << "|          |           | API      | Riwayat     |\n";
    cout << "+----------+-----------+----------+-------------+\n";
    
    // Dapatkan 7 hari terakhir
    time_t now = time(0);
    for (int i = 6; i >= 0; i--) {
        tm *ltm = localtime(&now);
        ltm->tm_mday -= i;
        mktime(ltm);
        
        char date_str[11];
        strftime(date_str, sizeof(date_str), "%Y-%m-%d", ltm);
        string date(date_str);
        
        int conversions = 0, api_updates = 0, history_views = 0;
        for (const auto& log : logs) {
            if (log.timestamp.substr(0, 10) == date) {
                if (log.activity_type == "conversion") conversions++;
                else if (log.activity_type == "api_update") api_updates++;
                else if (log.activity_type == "view_history") history_views++;
            }
        }
        
        cout << "| " << date << " | "
             << setw(9) << conversions << " | "
             << setw(8) << api_updates << " | "
             << setw(11) << history_views << " |\n";
    }
    cout << "+===============================================+\n";
}

void AnalyticsLogger::generateDetailedReport() {
    cout << "\n+===============================================+\n";
    cout << "|           LAPORAN DETAIL ANALITIK             |\n";
    cout << "+===============================================+\n";
    
    // Semua aktivitas terbaru
    cout << "| Aktivitas Terbaru (10 terakhir):              |\n";
    cout << "+----------+----------------------+--------------+\n";
    cout << "| Waktu    | Aktivitas            | Detail       |\n";
    cout << "+----------+----------------------+--------------+\n";
    
    int count = 0;
    for (auto it = logs.rbegin(); it != logs.rend() && count < 10; ++it) {
        cout << "| " << it->timestamp.substr(0, 19) << " | "
             << left << setw(20) << it->activity_type << " | "
             << left << setw(12) << it->details.substr(0, 12) << " |\n";
        count++;
    }
    cout << "+===============================================+\n";
    
    // Statistik lebih detail
    cout << "\n| Statistik Detail:                              |\n";
    cout << "+-----------------------------------------------+\n";
    cout << "| Rata-rata konversi per hari: " << setw(12)
         << (total_conversions / max(1, (int)daily_activity.size())) << " |\n";
    cout << "| Rata-rata update API per hari: " << setw(11)
         << (total_api_updates / max(1, (int)daily_activity.size())) << " |\n";
    cout << "| Rata-rata lihat riwayat per hari: " << setw(8)
         << (total_history_views / max(1, (int)daily_activity.size())) << " |\n";
    cout << "+-----------------------------------------------+\n";
}

void AnalyticsLogger::exportAnalytics(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << "=== ANALYTICS EXPORT REPORT ===" << endl;
        file << "Export Date: " << getCurrentTimestamp() << endl;
        file << endl;
        
        file << "=== TOTAL STATISTICS ===" << endl;
        file << "Total Conversions: " << total_conversions << endl;
        file << "Total API Updates: " << total_api_updates << endl;
        file << "Total History Views: " << total_history_views << endl;
        file << "Total Activities: " << logs.size() << endl;
        file << "Total Amount Converted: " << getTotalAmountConverted() << endl;
        file << "Most Used Currency: " << getMostUsedCurrency() << endl;
        file << endl;
        
        file << "=== TOP CURRENCIES ===" << endl;
        auto top_currencies = getTopCurrencies(10);
        for (const auto& currency : top_currencies) {
            file << currency.first << ": " << currency.second << endl;
        }
        file << endl;
        
        file << "=== DAILY ACTIVITY ===" << endl;
        for (const auto& day : daily_activity) {
            file << day.first << ": " << day.second << endl;
        }
        file << endl;
        
        file << "=== ALL LOGS ===" << endl;
        for (const auto& log : logs) {
            file << log.timestamp << " | " << log.activity_type << " | "
                 << log.details << " | " << log.amount << " | "
                 << log.from_currency << " | " << log.to_currency << endl;
        }
        
        file.close();
        cout << "[SUCCESS] Data analitik berhasil diekspor ke " << filename << endl;
    } else {
        cout << "[ERROR] Gagal mengekspor data analitik" << endl;
    }
}

int AnalyticsLogger::getTotalSessions() const {
    return logs.size();
}

double AnalyticsLogger::getTotalAmountConverted() const {
    double total = 0.0;
    for (const auto& amount : currency_amounts) {
        total += amount.second;
    }
    return total;
}

string AnalyticsLogger::getMostUsedCurrency() const {
    if (currency_usage.empty()) {
        return "N/A";
    }
    
    auto max_it = max_element(currency_usage.begin(), currency_usage.end(),
                             [](const pair<string, int>& a, const pair<string, int>& b) {
                                 return a.second < b.second;
                             });
    return max_it->first;
}

vector<pair<string, int>> AnalyticsLogger::getTopCurrencies(int limit) const {
    vector<pair<string, int>> result;
    
    for (const auto& currency : currency_usage) {
        result.push_back({currency.first, currency.second});
    }
    
    sort(result.begin(), result.end(),
         [](const pair<string, int>& a, const pair<string, int>& b) {
             return a.second > b.second;
         });
    
    if (result.size() > limit) {
        result.resize(limit);
    }
    
    return result;
}