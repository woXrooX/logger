#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo> // For typeid
#include <iomanip> // for time

// OS
#ifdef __unix__
#define OPERATINGSYSTEM "unix"
#endif
#ifdef _WIN32
#define OPERATINGSYSTEM "windows"
#endif

namespace woXrooX{
  class Logger{
  public:
    Logger(){}
    ~Logger(){
      this->file.close();
    }

    ///////// Success
    template<typename T>
    Logger& success(T message){
      log(SUCCESS, message);
      return *this;
    }

    ///////// Info
    template<typename T>
    Logger& info(T message){
      log(INFO, message);
      return *this;
    }

    ///////// Warning
    template<typename T>
    Logger& warning(T message){
      log(WARNING, message);
      return *this;
    }

    ///////// Error
    template<typename T>
    Logger& error(T message){
      log(ERROR, message);
      return *this;
    }

    ///////// Custom
    template<typename T1, typename T2>
    Logger& custom(T1 type, T2 message){
      log(type, message);
      return *this;
    }

    ///////// Line / Divider
    Logger& line(){
      std::cout << this->colorLine << "----------------------------------------------------------------" << this->colorEnd << '\n';
      return *this;
    }

    ///////// enable & disable LogToFile
    // enable
    void enableLogToFile(){
      this->log("INFO", "Log To File Enabled. Log File Location: ./log/");
      this->logToFileEnabled = true;
      this->file.open("./log/logs.log", std::ios_base::app); // Second Argument For Append Mode
    }
    // disable
    void disableLogToFile(){
      this->log("INFO", "Log To File Disabled");
      this->logToFileEnabled = false;
      this->file.close();
    }

    ///////// enable & disable SquareBrackets
    // enable
    void enableSquareBrackets(){
      this->squareBracketsOpen = "[";
      this->squareBracketsClose = "] ";
    }
    // disable
    void disableSquareBrackets(){
      this->squareBracketsOpen = "";
      this->squareBracketsClose = " ";
    }

  private:
    // TYPES
    const std::string SUCCESS = "SUCCESS";
    const std::string INFO = "INFO";
    const std::string WARNING = "WARNING";
    const std::string ERROR = "ERROR";

    std::ofstream file;
    bool logToFileEnabled = false;

    std::string squareBracketsOpen = "[";
    std::string squareBracketsClose = "] ";

    std::string colorStart = "";
    std::string colorEnd = "\033[0m";
    std::string colorLine = "\033[1;90m";

    ///////// Log
    template<typename T1, typename T2>
    void log(T1 type, T2 message){
      // setting color depending on the type
      this->colors(type);

      // Out
      std::cout << this->timestamp() << this->squareBracketsOpen << this->colorStart << type << this->colorEnd << this->squareBracketsClose << message << '\n';

      if(this->logToFileEnabled) {
        this->logsToFile(type, message);
      }
    }

    ///////// logsToFile
    template<typename T1, typename T2>
    void logsToFile(T1 type, T2 message){
      this->file << this->timestamp() << "[" << type << "] " << message << "\n";
    }

    ///////// TimeStamp
    const std::string timestamp(){
      // Ugly time
      std::stringstream ss;
      std::time_t const dt = time(NULL);
      ss << std::put_time(localtime(&dt), "%T %F");
      std::string datetime = ss.str();

      const std::string timestamp = this->squareBracketsOpen + datetime + this->squareBracketsClose;
      return timestamp;
    }

    ///////// Colors
    template<typename T>
    void colors(T type){
      // linux
      if(OPERATINGSYSTEM == "unix"){
        this->colorStart = "\033[1;90m";
        if(SUCCESS.compare(type) == 0) this->colorStart = "\033[1;32m";
        else if(INFO.compare(type) == 0) this->colorStart = "\033[1;34m";
        else if(WARNING.compare(type) == 0) this->colorStart = "\033[1;33m";
        else if(ERROR.compare(type) == 0) this->colorStart = "\033[1;31m";
      }
      // }
    }
  };
}
#endif
