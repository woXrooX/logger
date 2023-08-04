#include "../source/logger.hpp"

#include <iostream>

int main(){

  // Log to file
  woXrooX::Logger::setPath("./examples/logs/");
  woXrooX::Logger::enableLogToFile();
  // woXrooX::Logger::disableLogToFile();

  // Square brackets
  woXrooX::Logger::enableSquareBrackets();
  // woXrooX::Logger::disableSquareBrackets();

  woXrooX::Log::line();

  woXrooX::Log::success("Success");
  woXrooX::Log::info("Information");
  woXrooX::Log::important("Important");
  woXrooX::Log::warning("Warning");
  woXrooX::Log::error("Error");

  woXrooX::Log::newLine();

  woXrooX::Log::custom("CUSTOM", "Message");

  return 0;
}
