#include "utility/Log.h"
#include <cassert>
#include <iostream>

const std::string Log::FILE_NAME = "launcho.log";

void Log::verbose(const std::string& tag, const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  getInstance().vprintf(LogLevel::Verbose, tag, fmt, args);
  va_end(args);
}

void Log::debug(const std::string& tag, const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  getInstance().vprintf(LogLevel::Debug, tag, fmt, args);
  va_end(args);
}

void Log::info(const std::string& tag, const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  getInstance().vprintf(LogLevel::Info, tag, fmt, args);
  va_end(args);
}

void Log::warning(const std::string& tag, const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  getInstance().vprintf(LogLevel::Warning, tag, fmt, args);
  va_end(args);
}

void Log::error(const std::string& tag, const char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  getInstance().vprintf(LogLevel::Error, tag, fmt, args);
  va_end(args);
}

Log::~Log()
{
  fclose(file);
}

void Log::setLevel(const LogLevel level)
{
  outputLevel = level;
}

LogLevel Log::getLevel() const
{
  return outputLevel;
}

void Log::setConsoleOutputEnable(bool status)
{
  consoleOutput = status;
}

void Log::printf(const LogLevel level, const std::string& tag, const char* fmt,
                 ...)
{
  va_list args;
  va_start(args, fmt);
  vprintf(level, tag, fmt, args);
  va_end(args);
}

void Log::vprintf(const LogLevel level, const std::string& tag, const char* fmt,
                  va_list args)
{
  char buffer[BUFFER_SIZE];

  if (vsnprintf(buffer, BUFFER_SIZE, fmt, args) > 0)
  {
    fputs(buffer, file);
    fputs("\n", file);
    if (consoleOutput)
    {
      std::cerr << buffer << std::endl;
    }
  }
  else
  {
    std::cerr << "Log file error" << std::endl;
  }
}

Log::Log()
: outputLevel(LogLevel::Warning), file(fopen(FILE_NAME.c_str(), "w"))
{
  assert(file != nullptr);
  if (!file)
  {
    std::cerr << "Error opening log file" << std::endl;
  }
}
