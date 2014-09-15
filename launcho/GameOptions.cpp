#include "GameOptions.h"
#include "utility/conversions.h"

std::string GameOptions::getString(const std::string& key) const
{
  return options.at(key);
}

int GameOptions::getInt(const std::string& key) const
{
  return fromString<int>(getString(key));
}

float GameOptions::getFloat(const std::string& key) const
{
  return fromString<float>(getString(key));
}

void GameOptions::setValue(const std::string& key, const std::string& value)
{
  options[key] = value;
}

void GameOptions::loadFromFile(const std::string& filename)
{

}

void GameOptions::parseCommandLine(int argc, char* argv[])
{

}
