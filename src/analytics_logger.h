#ifndef ANALYTICS_LOGGER_H
#define ANALYTICS_LOGGER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <map>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

// Struktur data untuk logging aktivitas
struct ActivityLog {
    string timestamp;
    string activity_type;  // "conversion", "api_update", "view_history"
    string details;
    double amount;         // Jumlah konversi (jika applicable)
    string from_currency;  // Mata uang asal (jika applicable)
    string to_currency;    // Mata uang tujuan (jika applicable)
};

class AnalyticsLogger {
private:
    string log_file;
    vector<ActivityLog> logs;
    
    // Statistik analitik
    map<string, int> currency_usage;
    map<string, double> currency_amounts;
    map<string, int> daily_activity;
    int total_conversions = 0;
    int total_api_updates = 0;
    int total_history_views = 0;
    
    string getCurrentTimestamp() const;
    bool loadLogs();
    void saveLogToFile(const ActivityLog& log);
    void updateAnalytics(const ActivityLog& log);
    
public:
    AnalyticsLogger(const string& log_path = "analytics_log.txt");
    ~AnalyticsLogger();
    
    // Logging functions
    void logConversion(const string& from_currency, const string& to_currency, double amount, const string& result);
    void logAPIUpdate(int updated_count);
    void logHistoryView();
    
    // Analytics functions
    void generateDashboard();
    void generateDetailedReport();
    void exportAnalytics(const string& filename);
    
    // Utility functions
    int getTotalSessions() const;
    double getTotalAmountConverted() const;
    string getMostUsedCurrency() const;
    double getAverageSessionDuration() const;
    vector<pair<string, int>> getTopCurrencies(int limit = 5) const;
};

#endif // ANALYTICS_LOGGER_H