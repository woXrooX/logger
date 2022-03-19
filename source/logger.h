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
#include <string>
#include <chrono>

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
    ~Logger(){}

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

  private:
    std::string colorStart = "";
    std::string colorEnd = "";

    ///////// Log
    void log(std::string type, std::string message){
      if(message == ""){
        type = ERROR;
        message = "Log Message Not Entered.";
      }

      // setting color depending the type
      colors(type);

      // Out
      std::cout << timestamp() << "[" << this->colorStart << type << this->colorEnd << "] " << message << '\n';
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
