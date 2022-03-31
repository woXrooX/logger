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
  log.custom("customType", "Custom");

  return 0;
}
```
### Output
```
[19:50:36 2022-03-19][SUCCESS] Success
[19:50:36 2022-03-19][INFO] Information
[19:50:36 2022-03-19][WARNING] Warning
[19:50:36 2022-03-19][ERROR] Error
[19:50:36 2022-03-19][customType] Custom
```
### Log Pattern
```
[HH:mm:ss yyyy-MM-dd][type] message
```
