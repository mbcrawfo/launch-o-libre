#pragma once

#include "Singleton.h"
#include <string>
#include <unordered_map>

class GameOptions
  : public Singleton<GameOptions>
{
private:
  std::unordered_map<std::string, std::string> options;

public:
  std::string getString(const std::string& key) const;
  int getInt(const std::string& key) const;
  float getFloat(const std::string& key) const;

  void setValue(const std::string& key, const std::string& value);
  void loadFromFile(const std::string& filename);
  void parseCommandLine(int argc, char* argv[]);
};