/*
 * Ein simpler Wrapper für std::cout, um Fehlermeldungen (z.B. "Syntax Error in
 * Function") farbig oder einheitlich auszugeben.
 */
#include "logger.hpp"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

namespace Axiom {

void Logger::log(LogLevel level, const std::string &message) {
  // Zeitstempel holen
  auto now =
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  auto local_time = *std::localtime(&now);

  std::cout << "[" << std::put_time(&local_time, "%H:%M:%S") << "] ";

  switch (level) {
  case LogLevel::INFO:
    std::cout << "\033[35m[INFO]\033[0m ";
    break;
  case LogLevel::WARNING:
    std::cout << "\033[33m[WARN]\033[0m "; // Gelb
    break;
  case LogLevel::ERROR:
    std::cout << "\033[31m[ERROR]\033[0m "; // Rot
    break;
  }

  std::cout << message << std::endl;
}

} // namespace Axiom
