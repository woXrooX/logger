# C++ Logger
Minimal And Simple Logger Implementation In C++

### How to use ?
First include the logger.h into your project.
```C++
#include "logger.h"

int main(int argc, char const *argv[]){
  //In Case "using namespace woXrooX;" Is Always Here :)
  
  //// Log To File
  //// Currently No Path Setter Method :)
  //// Absolute Path Defined At -> "woXrooX::Logger::logsAbsolutePath"
  
  // To Enable Log To File.
  woXrooX::Logger::enableLogToFile();
  
  // To Disable Log To File.
  woXrooX::Logger::disableLogToFile();

  // Modes
  woXrooX::Log::success("Success");
  woXrooX::Log::info("Information");
  woXrooX::Log::warning("Warning");
  woXrooX::Log::error("Error");
  woXrooX::Log::custom("customType", "Custom");

  // New Line
  woXrooX::Log::newLine();

  // Line
  woXrooX::Log::line();
  
  //// Enable & Disable Square Brackets (By Default Disabled)
  // Enabler
  woXrooX::Logger::enableSquareBrackets();
  
  // Disabler
  woXrooX::Logger::disableSquareBrackets();

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


```
### Log Pattern
```
[HH:mm:ss yyyy-MM-dd][type] message
```
