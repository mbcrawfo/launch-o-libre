#pragma once

/**
  * Implements the singleton design pattern for the template parameter. The
  * inheriting class must provide a default constructor that is accessible to
  * its base classes.
  */
template<typename T>
class Singleton
{
  Singleton() = default;

public:
  /**
    * Returns the singleton instance. Creates the instance if it has not been
    * initialized.
    */
  static T& getInstance();

  Singleton(const Singleton&) = delete;
  Singleton& operator =(const Singleton&) = delete;
};

/****************************************************************************
  * Function definitions
  ****************************************************************************/

template<typename T>
T& Singleton<T>::getInstance()
{
  static T instance;
  return instance;
}

