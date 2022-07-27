#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
#include <filesystem> // 4 logsAbsolutePath Existance Check
#include <fstream>
#include <string>
#include <iomanip> // for time

// Types
struct Types{
  static inline const std::string SUCCESS = "SUCCESS";
  static inline const std::string INFO = "INFO";
  static inline const std::string WARNING = "WARNING";
  static inline const std::string ERROR = "ERROR";

};

namespace woXrooX{
  class Logger final{
  public:
    ///////// Success
    template<typename T>
    static void success(T message){
      Logger::log(Types::SUCCESS, message);

    }

    ///////// Info
    template<typename T>
    static void info(T message){
      Logger::log(Types::INFO, message);

    }

    ///////// Warning
    template<typename T>
    static void warning(T message){
      Logger::log(Types::WARNING, message);

    }

    ///////// Error
    template<typename T>
    static void error(T message){
      Logger::log(Types::ERROR, message);

    }

    ///////// Custom
    template<typename T1, typename T2>
    static void custom(T1 type, T2 message){
      Logger::log(type, message);

    }

    ///////// Line
    static void line(){
      std::cout << Logger::colorLine << "----------------------------------------------------------------" << Logger::colorEnd << '\n';

      // If Enabled Line For "logToFile"
      if(Logger::logToFileEnabled) Logger::logToFile("\n----------------------------------------------------------------------------------------\n");

    }

    ///////// New Line
    static void newLine(){
      std::cout << '\n';

      //  If Enabled New Line For "logToFile"
      if(Logger::logToFileEnabled) Logger::logToFile("\n");

    }


    ///////// enable & disable LogToFile
    // enable
    static void enableLogToFile(){
      // Check If "logsAbsolutePath" Exists
      if(!std::filesystem::exists(Logger::logsAbsolutePath)){
        Logger::log("WARNING", "Invalid Logs Absolute Path: " + Logger::logsAbsolutePath);
        
        return;

      }

      // Opening Log File On Append Mode
      Logger::file.open(Logger::logsAbsolutePath + "all.log", std::ios_base::app);

      // Check If File Opened Successfully
      if(Logger::file.is_open()){
        // After Successful Openening Enable Log To File
        Logger::logToFileEnabled = true;
        Logger::log(Types::INFO, "Log To File Is Enabled");
        
        Logger::log(Types::SUCCESS, "Log File Opened Successfully: all.log");
        Logger::log(Types::INFO, "Log File Absolute Path: " + Logger::logsAbsolutePath);

      }else{
        Logger::log(Types::WARNING, "Log To File Is Not Enabled");
        
        Logger::log(Types::WARNING, "Could Not Open Log File");
        
        return;

      }

    }
    
    // disable
    static void disableLogToFile(){
      Logger::logToFileEnabled = false;

      Logger::log(Types::INFO, "Log To File Is Disabled");

      Logger::closeLogFile();

    }

    ///////// enable & disable SquareBrackets
    // enable
    static void enableSquareBrackets(){
      Logger::squareBracketsOpen = "[";
      Logger::squareBracketsClose = "] ";

      Logger::log(Types::INFO, "Square Brackets Are Enabled");

    }
    // disable
    static void disableSquareBrackets(){
      Logger::squareBracketsOpen = "";
      Logger::squareBracketsClose = " ";

      Logger::log(Types::INFO, "Square Brackets Are Disabled");

    }

  private:
    /////////// Methods
    ///////// Log
    template<typename T1, typename T2>
    static void log(T1 type, T2 message){
      // setting color depending on the type
      Logger::setColor(type);

      // Getting TimeStamp And Setting To A Variable So It Will Be Same TimeStamp On "logToFile()"
      const std::string timestamp = Logger::timestamp();

      // Out | Log
      std::cout << Logger::squareBracketsOpen << timestamp << Logger::squareBracketsClose << Logger::squareBracketsOpen << Logger::colorStart << type << Logger::colorEnd << Logger::squareBracketsClose << message << '\n';

      // Cosntructing "logToFile" [timestamp] [TYPE] Message
      if(Logger::logToFileEnabled) Logger::logToFile(('[' + timestamp + "] [" + type + "] " + message + '\n'));

    }

    ///////// logToFile
    static void logToFile(const std::string& log){
      // Check If Logger::logToFileEnabled Is True
      if(!Logger::logToFileEnabled) return;

      if(!(Logger::file << log)) std::cout << "ERROR: Could Not Write The Log: " << log << '\n';

    }

    ///////// TimeStamp
    static const std::string timestamp(){
      // Ugly Time Code
      std::stringstream ss;
      std::time_t const dt = time(NULL);
      ss << std::put_time(localtime(&dt), "%T %F");
      std::string datetime = ss.str();

      return datetime;

    }

    ///////// Colors
    static void setColor(const std::string& type){
      // Unix | Linux
      if(__linux__ || __unix__){
        Logger::colorStart = "\033[1;90m";
        if(Types::SUCCESS.compare(type) == 0) Logger::colorStart = "\033[1;32m";
        else if(Types::INFO.compare(type) == 0) Logger::colorStart = "\033[1;34m";
        else if(Types::WARNING.compare(type) == 0) Logger::colorStart = "\033[1;33m";
        else if(Types::ERROR.compare(type) == 0) Logger::colorStart = "\033[1;31m";

      }

    }

    ///////// Close Log File
    static void closeLogFile(){
      Logger::file.close();

      // Check If File Closed Successfully
      if(!Logger::file.is_open()) Logger::log(Types::SUCCESS, "Log File Closed Successfully");
      else Logger::log(Types::ERROR, "Can Not Close The Log File");

    }

    /////////// Variables
    // File
    static std::ofstream file;
    static bool logToFileEnabled;
    static bool logOnlyToFileEnabled;
    static const std::string logsAbsolutePath;

    // Square Brackets
    static std::string squareBracketsOpen;
    static std::string squareBracketsClose;

    // Colors
    static std::string colorStart;
    static std::string colorEnd;
    static std::string colorLine;

  };
  
  std::ofstream Logger::file;
  bool Logger::logToFileEnabled = false;
  
  // Path To Your Logs Folder
  const std::string Logger::logsAbsolutePath = "/path/to/logs/";

  std::string Logger::squareBracketsOpen = "";
  std::string Logger::squareBracketsClose = " ";

  std::string Logger::colorStart = "";
  std::string Logger::colorEnd = "\033[0m";
  std::string Logger::colorLine = "\033[1;90m";

  // Alias Log To OG Logger
  typedef Logger Log;

}
#endif
