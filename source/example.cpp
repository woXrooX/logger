#include "logger.h"

int main() {

  woXrooX::Logger::enableLogToFile();

  woXrooX::Log::success("Success");
  woXrooX::Log::info("Information");
  woXrooX::Log::warning("Warning");
  woXrooX::Log::error("Error");

  return 0;
}
