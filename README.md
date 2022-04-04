# C++ Logger
Minimal And Simple Logger Implementation In C++

### How to use ?
To use the Logger, you need to include the logger.h into your project.
```C++
#include "logger.h"

int main(int argc, char const *argv[]) {

  woXrooX::Logger log;
  // To Enable Log To File Call This Method.
  // Currently Path And File Are Not Dynamic.
  // Hard Coded Path And File -> "./log/log.log"
  log.enableLogToFile();

  log.success("Success");
  log.info("Information");
  log.warning("Warning");
  log.error("Error");
  log.custom("customType", "Custom");
  
  // Line
  log.line();
  
  // Chaining
  log.custom("customType", "Line And Chaining").line().info("Chained Info);

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
----------------------------------------------------------------
[19:50:36 2022-03-19][customType] Line And Chaining
----------------------------------------------------------------
[19:50:36 2022-03-19][INFO] Chained Info


```
### Log Pattern
```
[HH:mm:ss yyyy-MM-dd][type] message
```
