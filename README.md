# C++ Logger
Minimal And Simple Logger Implementation In C++

### How to use ?
To use the Logger, you need to include the logger.h into your project.
```C++
#include "logger.h"

int main(int argc, char const *argv[]) {

  woXrooX::Logger log;

  log.success("Success");
  log.info("Information");
  log.warning("Warning");
  log.error("Error");

  return 0;
}
```
### Output
```
[19:50:36 Mar  4 2022][SUCCESS] Success
[19:50:36 Mar  4 2022][INFO] Information
[19:50:36 Mar  4 2022][WARNING] Warning
[19:50:36 Mar  4 2022][ERROR] Error
```
### Log Pattern
```
[HH:mm:ss MMM  d yyyy][type] message
```
