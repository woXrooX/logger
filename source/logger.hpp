#ifndef LOGGER_HPP
#define LOGGER_HPP
#include <iostream>
#include <filesystem> // 4 logFilesPath Existance Check
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
      // Comment 4 Daemon. Daemon Has No Terminal To "stdout"
      // std::cout << Logger::colorLine << "----------------------------------------------------------------" << Logger::colorEnd << '\n';

      // If enabled line for "logToFile"
      if(Logger::logToFileEnabled) Logger::logToFile("\n----------------------------------------------------------------------------------------\n");
    }

    ///////// New Line
    static void newLine(){
      // Comment 4 Daemon. Daemon Has No Terminal To "stdout"
      // std::cout << '\n';

      //  If enabled new line for "logToFile"
      if(Logger::logToFileEnabled) Logger::logToFile("\n");
    }


    ///////// enable & disable LogToFile
    // enable
    static void enableLogToFile(){
      // Check If "logFilesPath" Exists
      if(!std::filesystem::exists(Logger::logFilesPath)){
        Logger::log("WARNING", "Invalid log files path: " + Logger::logFilesPath);
        return;
      }

      // Opening log file
      // Second argument for append mode
      Logger::file.open(Logger::logFilesPath+"all.log", std::ios_base::app);

      // Check if file opened successfully
      if(Logger::file.is_open()){
        // After successful openening enable log to file
        Logger::logToFileEnabled = true;
        Logger::log(Types::INFO, "Log to file is enabled");
        Logger::log(Types::SUCCESS, "Log file opened successfully: all.log");
        Logger::log(Types::INFO, "Log files path: " + Logger::logFilesPath);

      }else{
        Logger::log(Types::INFO, "Log to file is not enabled");
        Logger::log(Types::WARNING, "Could not open log file");
        return;
      }
    }

    // disable
    static void disableLogToFile(){
      Logger::logToFileEnabled = false;

      Logger::log(Types::INFO, "Log to file is disabled");

      Logger::closeLogFile();
    }

    ///////// enable & disable SquareBrackets
    // enable
    static void enableSquareBrackets(){
      Logger::squareBracketsOpen = "[";
      Logger::squareBracketsClose = "] ";

      Logger::log(Types::INFO, "Square brackets are enabled");
    }

    // disable
    static void disableSquareBrackets(){
      Logger::squareBracketsOpen = "";
      Logger::squareBracketsClose = " ";

      Logger::log(Types::INFO, "Square brackets are disabled");
    }

  private:
    /////////// Methods
    ///////// Log
    template<typename T1, typename T2>
    static void log(T1 type, T2 message){
      // setting color depending on the type
      Logger::setColor(type);

      // Getting timestamp and setting to a variable so it will be same timestamp on "logToFile()"
      const std::string timestamp = Logger::timestamp();

      // Redirects all stdout to a file. #include <stdio.h>
      // freopen((Logger::logFilesPath+"all.log").c_str(), "a", stdout);

      // Out | Log
      // Comment 4 Daemon. Daemon Has No Terminal To "stdout"
      // std::cout
      //   << Logger::squareBracketsOpen
      //   << timestamp
      //   << Logger::squareBracketsClose
      //   << Logger::squareBracketsOpen
      //   << Logger::colorStart
      //   << type
      //   << Logger::colorEnd
      //   << Logger::squareBracketsClose
      //   << message << '\n';

      // Cosntructing "logToFile" [timestamp] [TYPE] Message
      if(Logger::logToFileEnabled) Logger::logToFile(('[' + timestamp + "] [" + type + "] " + message + '\n'));

    }

    ///////// logToFile
    static void logToFile(const std::string& log){
      // Check If Logger::logToFileEnabled Is True
      if(!Logger::logToFileEnabled) return;

      // Flush Is bad For Performance!!!
      // https://softwareengineering.stackexchange.com/questions/386269/why-do-you-want-to-avoid-flushing-stdout
      // if(!(Logger::file << log << std::flush)) std::cout << "ERROR: Could Not Write The Log" << '\n';
      // w/o Flushing Logs Will Be Written When OS Thinks Buffer Is Big Enough To Flush Instead Flushing Small Data.
      if(!(Logger::file << log)){
        // Comment 4 Daemon. Daemon Has No Terminal To "stdout"
        // std::cout << "ERROR: Could Not Write The Log: " << log << '\n';
      }
    }

    ///////// TimeStamp
    static const std::string timestamp(){
      // Ugly time code
      std::stringstream ss;
      std::time_t const dt = time(NULL);
      ss << std::put_time(localtime(&dt), "%T %F");
      std::string datetime = ss.str();

      return datetime;
    }

    ///////// Colors
    // https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
    // template<typename T>
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
      if(!Logger::file.is_open()) Logger::log(Types::SUCCESS, "Log file closed successfully.");
      else Logger::log(Types::ERROR, "Can not close the log file.");
    }

    /////////// Variables
    // File
    static std::ofstream file;
    static bool logToFileEnabled;
    static bool logOnlyToFileEnabled;
    static const std::string logFilesPath;

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
  bool Logger::logOnlyToFileEnabled = false;
  const std::string Logger::logFilesPath = "/home/woxroox/Desktop/woXTools/logs/";

  std::string Logger::squareBracketsOpen = "";
  std::string Logger::squareBracketsClose = " ";

  std::string Logger::colorStart = "";
  std::string Logger::colorEnd = "\033[0m";
  std::string Logger::colorLine = "\033[1;90m";

  // Alias Log To OG Logger
  typedef Logger Log;
}
#endif
