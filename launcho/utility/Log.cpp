#include "utility/Log.h"
#include <cassert>
#include <iostream>
#include <sstream>

static std::string getLevelPrefix(const LogLevel level)
{
  switch (level)
  {
  case LogLevel::Verbose:
    return "V";

  case LogLevel::Debug:
    return "D";

  case LogLevel::Info:
    return "I";

  case LogLevel::Warning:
    return "W";

  case LogLevel::Error:
    return "E";
  }

  return "";
}

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
  if (level < outputLevel)
  {
    return;
  }

  va_list args;
  va_start(args, fmt);
  vprintf(level, tag, fmt, args);
  va_end(args);
}

void Log::vprintf(const LogLevel level, const std::string& tag, const char* fmt,
                  va_list args)
{
  if (level < outputLevel)
  {
    return;
  }

  char buffer[BUFFER_SIZE];
  if (vsnprintf(buffer, BUFFER_SIZE, fmt, args) > 0)
  {
    print(getLevelPrefix(level) + " " + tag, buffer);
  }
  else
  {
    std::cerr << "Log file error" << std::endl;
  }
}

void Log::print(const std::string& tag, const std::string& msg)
{
  auto elapsed =
    std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::steady_clock::now() - startTime
      ).count();
  std::stringstream ss;

  ss << "[" << elapsed << "] " << tag << ": " << msg;
  file << ss.str() << std::endl;

  if (consoleOutput)
  {
    std::cerr << ss.str() << std::endl;
  }
}

Log::Log()
: outputLevel(LogLevel::Warning),
  file(FILE_NAME, std::ios::out),
  startTime(std::chrono::steady_clock::now()),
  consoleOutput(false)
{
}
