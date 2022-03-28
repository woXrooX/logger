// Logger

// Usage
// woXrooX::Logger log;
// log.success("Message");
// log.info("Message");
// log.warning("Message");
// log.error("Message");
// Log Pattern: [HH:mm:ss MMM  d yyyy][type] message

#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> // for time

// OS
#ifdef linux
#define OPERATINGSYSTEM "linux"
#endif
#ifdef _WIN32
#define OPERATINGSYSTEM "windows"
#endif

// TYPES
#define SUCCESS "SUCCESS"
#define INFO "INFO"
#define WARN "WARNING"
#define ERROR "ERROR"

namespace woXrooX{
  class Logger{
  public:
    Logger(){}
    ~Logger(){
      this->file.close();
    }

    ///////// Success
    void success(const std::string &message = ""){
      log(SUCCESS, message);
    }

    ///////// Info
    void info(const std::string &message = ""){
      log(INFO, message);
    }

    ///////// Warning
    void warning(const std::string &message = ""){
      log(WARN, message);
    }

    ///////// Error
    void error(const std::string &message = ""){
      log(ERROR, message);
    }

    ///////// enableLogToFile
    void enableLogToFile(){
      this->log("INFO", "Log To File Enabled. Log File Location: ./log/");
      this->logsToFileEnabled = true;
      this->file.open("./log/logs.log", std::ios_base::app); // Second Argument For Append Mode
    }

  private:
    std::ofstream file;
    bool logsToFileEnabled = false;

    std::string colorStart = "";
    std::string colorEnd = "";

    ///////// Log
    void log(std::string type, std::string message){
      if(message == ""){
        type = ERROR;
        message = "Log Message Has Not Been Provided";
      }

      // setting color depending the type
      this->colors(type);

      // Out
      std::cout << this->timestamp() << "[" << this->colorStart << type << this->colorEnd << "] " << message << '\n';
      this->logsToFile(type, message);
    }

    ///////// logsToFile
    void logsToFile(std::string type, std::string message){
      if(!this->logsToFileEnabled) return;
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
    void colors(std::string type){
      // linux
      if(OPERATINGSYSTEM == "linux"){
        this->colorEnd = "\033[0m";
        if(type == SUCCESS) this->colorStart = "\033[1;32m";
        if(type == INFO) this->colorStart = "\033[1;34m";
        if(type == WARN) this->colorStart = "\033[1;33m";
        if(type == ERROR) this->colorStart = "\033[1;31m";
      }
    }
  };
}
#endif
