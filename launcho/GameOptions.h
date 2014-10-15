#pragma once

#include "Singleton.h"
#include <string>
#include <unordered_map>

/**
 * Holds settings for the game configuration.
 */
class GameOptions final
  : public Singleton<GameOptions>
{
private:
  static const std::string TAG;

  std::unordered_map<std::string, std::string> options;

public:
  /**
   * Parses game settings from command line options.
   * @param argc Arg count.
   * @param argv Arg strings.
   */
  void parseCommandLine(int argc, char* argv[]);

  /**
   * Load game settings from a config file.
   * @param filename Path of the file to load.
   */
  void loadFromFile(const std::string& filename);

  /**
   * Dumps all current options to the log file.
   */
  void dumpToLog() const;
  
  /**
   * Sets the value of an option.
   * @param key The option to set.
   * @param value The new value.
   */
  void setString(const std::string& key, const std::string& value);

  /**
   * Sets an option to an int value. See setString().
   */
  void setInt(const std::string& key, const int value);

  /**
   * Sets an option to a float value. See setString().
   */
  void setFloat(const std::string& key, const float value);

  /**
   * Gets an option from the settings.
   * @param key The setting to get.
   * @return The string for the option.
   * @throws std::out_of_range key is not a valid option.
   */
  std::string getString(const std::string& key) const;

  /**
   * Returns an option as an int. See getString().
   */
  int getInt(const std::string& key) const;

  /**
   * Returns an option as a float. See getString().
   */
  float getFloat(const std::string& key) const;

private:
  friend class Singleton<GameOptions>;
  GameOptions() = default;
};