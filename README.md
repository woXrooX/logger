# C++ Logger
Minimal And Simple Logger Implementation In C++

### How to use ?
To use the Logger, you need to include the logger.h into your project.
```C++
#include "logger.h"

int main(int argc, char const *argv[]){

  woXrooX::Logger log;
  //// Log To File
  //// Currently Path And File Are Not Dynamic.
  //// Hard Coded Path And File -> "./log/log.log"
  // To Enable Log To File Call This Method.
  log.enableLogToFile();
  // To Disable Log To File Use This Following Method.
  log.disableLogToFile();

  log.success("Success");
  log.info("Information");
  log.warning("Warning");
  log.error("Error");
  log.custom("customType", "Custom");
  
  // Line
  log.line();
  
  // Chaining
  log.custom("customType", "Line And Chaining").line().info("Chained Info);

  //// Enable & Disable Square Brackets
  // Enabler
  log.enableSquareBrackets();
  log.info("Square Brackets Are Enabled");
  // Disabler
  log.disableSquareBrackets();
  log.info("Square Brackets Are Enabled");
  
  

  return 0;
}
```
### Output
```
[19:50:36 2022-03-19] [SUCCESS] Success
[19:50:36 2022-03-19] [INFO] Information
[19:50:36 2022-03-19] [WARNING] Warning
[19:50:36 2022-03-19] [ERROR] Error
[19:50:36 2022-03-19] [customType] Custom
----------------------------------------------------------------
[19:50:36 2022-03-19] [customType] Line And Chaining
----------------------------------------------------------------
[19:50:36 2022-03-19] [INFO] Chained Info
[12:50:05 2022-05-06] [INFO] Square Brackets Are Enabled
12:50:05 2022-05-06 INFO Square Brackets Are Enabled


```
### Log Pattern
```
[HH:mm:ss yyyy-MM-dd][type] message
```
