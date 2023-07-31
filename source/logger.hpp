#ifndef LOGGER_HPP
#define LOGGER_HPP
#include <iostream>
#include <filesystem> // 4 logsFolderPath Existance Check
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
    ////////////////// APIs | Methods
    ///////// Success
    template<typename T>
    static void success(T&& message){
      Logger::log(Types::SUCCESS, message);
    }

    ///////// Info
    template<typename T>
    static void info(T&& message){
      Logger::log(Types::INFO, message);
    }

    ///////// Warning
    template<typename T>
    static void warning(T&& message){
      Logger::log(Types::WARNING, message);
    }

    ///////// Error
    template<typename T>
    static void error(T&& message){
      Logger::log(Types::ERROR, message);
    }

    ///////// Custom
    template<typename T>
    static void custom(const std::string& type, T&& message){
      Logger::log(type, message);
    }

    ///////// Line
    static void line(){
      if(!Logger::logOnlyToFileEnabled) std::cout << Logger::colorLine << "----------------------------------------------------------------" << Logger::colorEnd << '\n';
      if(Logger::logToFileEnabled) Logger::logToFile("\n----------------------------------------------------------------\n");
    }

    ///////// New Line
    static void newLine(){
      if(!Logger::logOnlyToFileEnabled) std::cout << '\n';
      if(Logger::logToFileEnabled) Logger::logToFile("\n");
    }


    ///////// Log to file
    // Set logs folder path
    static void setPath(const std::string& path){
      // Check if the provided path exists. If not, create it.
      if(!std::filesystem::exists(path)){
        if(std::filesystem::create_directories(path)) Logger::success("Logs folder created successfully.");
        else{
          Logger::error("Could not create logs folder: " + path);
          return;
        }
      }

      Logger::logsFolderPath = path;
      Logger::info("Logs folder ready to use: " + Logger::logsFolderPath);
    }

    // enable
    static void enableLogToFile(){
      // Check if already enabled
      if(Logger::logToFileEnabled) return;

      // Check If "logsFolderPath" Exists
      if(!std::filesystem::exists(Logger::logsFolderPath)){
        Logger::error("Logs folder does not exists. Please set up the directories first using Logger::setPath(\"path/to/logs/\")");
        return;
      }

      // Open the log file in append mode
      Logger::file.open(Logger::logsFolderPath+"all.log", std::ios_base::app);

      // Check if file opened successfully
      if(Logger::file.is_open()) Logger::success("Log file opened successfully: all.log");
      else{
        Logger::warning("Could not open the log file.");
        Logger::info("Log to file is not enabled.");
        return;
      }

      Logger::logToFileEnabled = true;
      Logger::info("Log to file is enabled.");
    }

    // disable
    static void disableLogToFile(){
      // Check if already disabled
      if(!Logger::logToFileEnabled) return;
      Logger::logToFileEnabled = false;
      Logger::info("Log to file is disabled.");
      Logger::closeLogFile();
    }

    ///////// enable & disable SquareBrackets
    // enable
    static void enableSquareBrackets(){
      Logger::squareBracketsOpen = "[";
      Logger::squareBracketsClose = "] ";
      Logger::info("Square brackets are enabled.");
    }

    // disable
    static void disableSquareBrackets(){
      Logger::squareBracketsOpen = "";
      Logger::squareBracketsClose = " ";
      Logger::info("Square brackets are disabled.");
    }

  private:
    ////////////////// Helpers
    ///////// Log
    template<typename T>
    static void log(const std::string& type, T&& message){
      // Setting color depending on the type
      Logger::setColor(type);

      // Getting timestamp and setting to a variable so it will be same timestamp on "logToFile()"
      const std::string timestamp = Logger::timestamp();

      // Redirects all stdout to a file. #include <stdio.h>
      // freopen((Logger::logsFolderPath+"all.log").c_str(), "a", stdout);

      // Out | Log
      if(!Logger::logOnlyToFileEnabled)
        std::cout
          << Logger::squareBracketsOpen << timestamp << Logger::squareBracketsClose
          << Logger::squareBracketsOpen << Logger::colorStart << type << Logger::colorEnd << Logger::squareBracketsClose
          << message << '\n';

      // Log structure: [timestamp] [TYPE] Message
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
      if(!Logger::file.is_open()) Logger::success("Log file closed successfully.");
      else Logger::error("Could not close the log file.");
    }

    /////////// Variables
    // File
    static std::ofstream file;
    static bool logToFileEnabled;
    static bool logOnlyToFileEnabled;
    static std::string logsFolderPath;

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
  std::string Logger::logsFolderPath = "./logs/";

  std::string Logger::squareBracketsOpen = "";
  std::string Logger::squareBracketsClose = " ";

  std::string Logger::colorStart = "";
  std::string Logger::colorEnd = "\033[0m";
  std::string Logger::colorLine = "\033[1;90m";

  // Alias Log To OG Logger
  typedef Logger Log;
}
#endif
