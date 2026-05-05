#pragma once

#include <string>

namespace Axiom {

enum class LogLevel {
    INFO,
    WARNING,
    ERROR
};

class Logger {
public:
    // static, damit wir Logger::log() ohne Instanz aufrufen können
    static void log(LogLevel level, const std::string& message);

    static void info(const std::string& msg) { log(LogLevel::INFO, msg); }
    static void warn(const std::string& msg) { log(LogLevel::WARNING, msg); }
    static void err(const std::string& msg) { log(LogLevel::ERROR, msg); }

private:
    // Privater Konstruktor verhindert, dass jemand "Logger l;" schreibt
    Logger() = default;
};

} // namespace Axiom
