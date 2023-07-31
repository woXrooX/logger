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

  woXrooX::Log::success("Success");
  woXrooX::Log::info("Information");
  woXrooX::Log::warning("Warning");
  woXrooX::Log::error("Error");

  return 0;
}
