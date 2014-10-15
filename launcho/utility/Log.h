#pragma once

#include "Singleton.h"
#include <string>
#include <cstdio>
#include <cstdarg>

enum class LogLevel
{
  Verbose,
  Debug,
  Info,
  Warning,
  Error
};

class Log
  : public Singleton<Log>
{
private:
  static const std::string FILE_NAME;
  static const std::size_t BUFFER_SIZE = 256;

  LogLevel outputLevel;
  FILE* file;
  bool consoleOutput;

public:
  static void verbose(const std::string& tag, const char* fmt, ...);
  static void debug(const std::string& tag, const char* fmt, ...);
  static void info(const std::string& tag, const char* fmt, ...);
  static void warning(const std::string& tag, const char* fmt, ...);
  static void error(const std::string& tag, const char* fmt, ...);

  ~Log();

  void setLevel(const LogLevel level);
  LogLevel getLevel() const;

  void setConsoleOutputEnable(bool status);

  void printf(const LogLevel level, const std::string& tag,
              const char* fmt, ...);
  void vprintf(const LogLevel level, const std::string& tag,
               const char* fmt, va_list args);

private:
  friend class Singleton<Log>;
  Log();
};