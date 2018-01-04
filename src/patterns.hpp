#pragma once

// Singleton for classes with default constructors
template<typename T> class Singleton
{
public:
  static T & Instance()
  {
    static T inst;
    return inst;
  }
protected:
  // Constructor
  Singleton() = default;
  // Destructor
  virtual ~Singleton() = default;
  // Delete copy
  Singleton(Singleton const &) = delete;
  Singleton & operator = (Singleton const &) = delete;
  // Delete move
  Singleton(Singleton &&) = delete;
  Singleton & operator = (Singleton &&) = delete;
};

// Singleton for Logger class
template<typename T> class SingletonLogger
{
public:
  static T & Instance(int level)
  {
    static T inst;
    inst.m_level = level;
    return inst;
  }
protected:
  // Constructor
  SingletonLogger() = default;
  // Destructor
  virtual ~SingletonLogger() = default;
  // Delete copy
  SingletonLogger(SingletonLogger const &) = delete;
  SingletonLogger & operator = (SingletonLogger const &) = delete;
  // Delete move
  SingletonLogger(SingletonLogger &&) = delete;
  SingletonLogger & operator = (SingletonLogger &&) = delete;
};

// Factory for game objects
class Factory
{
public:
  template<typename T, typename... Args> std::unique_ptr<T> Create(Args && ... args)
  {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
  }
};
