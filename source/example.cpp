#include "logger.h"

int main(int argc, char const *argv[]) {

  woXrooX::Logger log;

  log.success("Success");
  log.info("Information");
  log.warning("Warning");
  log.error("Error");

  return 0;
}
