#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>
#include <iomanip>

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

    ///////// enableLogToFile
    void enableLogToFile(){
      this->log("INFO", "Log To File Enabled. Log File Location: ./log/");
      this->logsToFileEnabled = true;
      this->file.open("./log/logs.log", std::ios_base::app); // Second Argument For Append Mode
    }

  private:

    // TYPES
    std::string SUCCESS = "SUCCESS";
    std::string INFO = "INFO";
    std::string WARNING = "WARNING";
    std::string ERROR = "ERROR";

    std::ofstream file;
    bool logsToFileEnabled = false;

    std::string colorStart = "";
    std::string colorEnd = "\033[0m";
    std::string colorLine = "\033[1;92m";

    ///////// Log
    template<typename T1, typename T2>
    void log(T1 type, T2 message){
      // setting color depending the type
      this->colors(type);

      // Out
      std::cout << this->timestamp() << "[" << this->colorStart << type << this->colorEnd << "] " << message << '\n';

      if(this->logsToFileEnabled) {
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

      const std::string timestamp = std::string("[") + datetime + std::string("]");
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
