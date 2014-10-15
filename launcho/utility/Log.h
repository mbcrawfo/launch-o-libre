#pragma once

#include "Singleton.h"
#include <string>
#include <fstream>
#include <cstdarg>
#include <chrono>

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
  // log file output name
  static const std::string FILE_NAME;
  // buffer size used for printf output
  static const std::size_t BUFFER_SIZE = 256;

  LogLevel outputLevel;
  std::ofstream file;
  std::chrono::steady_clock::time_point startTime;
  bool consoleOutput;

public:
  /**
   * Shortcut methods to write to the log at a particular level.
   */
  static void verbose(const std::string& tag, const char* fmt, ...);
  static void debug(const std::string& tag, const char* fmt, ...);
  static void info(const std::string& tag, const char* fmt, ...);
  static void warning(const std::string& tag, const char* fmt, ...);
  static void error(const std::string& tag, const char* fmt, ...);

  // Get and set the output level for the log
  void setLevel(const LogLevel level);
  LogLevel getLevel() const;

  // Enable or disable output to stderr
  void setConsoleOutputEnable(bool status);

  // Write to the log with printf style formatting
  void printf(const LogLevel level, const std::string& tag,
              const char* fmt, ...);
  void vprintf(const LogLevel level, const std::string& tag,
               const char* fmt, va_list args);

  // Write a message to the log that is always printed regardless of 
  // output level.
  void print(const std::string& tag, const std::string& msg);

private:
  friend class Singleton<Log>;
  Log();
};