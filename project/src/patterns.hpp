#pragma once

template<typename T> class Singleton
{
public:
  static T & Instance()
  {
    static T inst;
    return inst;
  }
  static T & Instance(int level)
  {
    static T inst;
    inst.m_level = level;
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


class Factory
{
public:
  template<typename T, typename... Args> std::unique_ptr<T> Create(Args && ... args)
  {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
  }
};