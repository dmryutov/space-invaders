#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <chrono>
#include <iomanip>
#include <stdio.h>
#include "patterns.hpp"

#define RESET   "\033[0m"
#define BLACK   "\033[30m"  // Black
#define RED     "\033[31m"  // Red
#define GREEN   "\033[32m"  // Green
#define YELLOW  "\033[33m"  // Yellow
#define LOG(level) \
  Logger::Instance(level)

enum TLogLevel {LOG_ERROR, LOG_WARNING, LOG_INFO, LOG_DEBUG};

class Logger: public SingletonLogger<Logger>
{
public:
  template <typename T> Logger &operator << (T const & obj)
  {
    std::clog << "- " << NowTime() << " "
              << m_color[m_level] << m_text[m_level] << RESET << ": "
              << obj << std::endl;
    return *this;
  }
private:
  friend class SingletonLogger<Logger>;

  // Constructor
  Logger() = default;

  std::string NowTime()
  {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch())
              - std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
  
    std::stringstream os;
    os << std::put_time(std::localtime(&time), "%Y.%m.%d %H:%M:%S:") << ms.count();
    return os.str();
  }

  int m_level;
  std::unordered_map<int, std::string> m_color
  {
    {LOG_DEBUG, BLACK},
    {LOG_INFO, GREEN},
    {LOG_WARNING, YELLOW},
    {LOG_ERROR, RED}
  };
  std::unordered_map<int, std::string> m_text
  {
    {LOG_DEBUG, "DEBUG"},
    {LOG_INFO, "INFO"},
    {LOG_WARNING, "WARNING"},
    {LOG_ERROR, "ERROR"}
  };
};

template<typename T, template<typename, typename...> class C, typename... Args>
inline std::ostream & operator << (std::ostream & os, C<T, Args...> const & objs)
{
  os << "\n{\n";
  for (auto const & obj : objs)
    os << obj << ",\n";
  os << "}";
  return os;
}