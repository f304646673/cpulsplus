#include <iostream>
#include <optional>
#include <string>

class AppConfig {
public:
    void setDatabaseUrl(const std::string& url) {
        databaseUrl = url;
    }

    void setLogLevel(const std::string& level) {
        logLevel = level;
    }

    std::optional<std::string> getDatabaseUrl() const {
        return databaseUrl;
    }

    std::optional<std::string> getLogLevel() const {
        return logLevel;
    }

private:
    std::optional<std::string> databaseUrl;
    std::optional<std::string> logLevel;
};

int main() {
    AppConfig config;

    // 设置数据库URL
    config.setDatabaseUrl("mysql://localhost:3306/mydb");

    // 未设置日志级别

    // 获取并处理配置项
    if (auto dbUrl = config.getDatabaseUrl()) {
        std::cout << "Database URL: " << *dbUrl << std::endl;
    } else {
        std::cout << "Database URL not set." << std::endl;
    }

    if (auto logLevel = config.getLogLevel()) {
        std::cout << "Log Level: " << *logLevel << std::endl;
    } else {
        std::cout << "Log Level not set." << std::endl;
    }

    return 0;
}