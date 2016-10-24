#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <stdio.h>
#include <sys/time.h>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"  // Black
#define RED     "\033[31m"  // Red
#define GREEN   "\033[32m"  // Green
#define YELLOW  "\033[33m"  // Yellow
#define LOG(level) \
  Logger().Get(level)

enum TLogLevel {LOG_ERROR, LOG_WARNING, LOG_INFO, LOG_DEBUG};

class Logger
{
public:
  // Constructor
  Logger() = default;
  // Destructor
  ~Logger();

  std::ostringstream& Get(TLogLevel level = LOG_INFO);
private:
  // Delete copy constructor and operator
  Logger(Logger const & obj) = delete;
  Logger& operator = (Logger const & obj) = delete;
  std::string NowTime();

  std::ostringstream m_os;
  std::unordered_map<int, char const *> m_color
  {
    {LOG_DEBUG, BLACK},
    {LOG_INFO, GREEN},
    {LOG_WARNING, YELLOW},
    {LOG_ERROR, RED}
  };
  std::unordered_map<int, char const *> m_text
  {
    {LOG_DEBUG, "DEBUG"},
    {LOG_INFO, "INFO"},
    {LOG_WARNING, "WARNING"},
    {LOG_ERROR, "ERROR"}
  };
};

inline Logger::~Logger()
{
  m_os << std::endl;
  std::clog << m_os.str();
  fflush(stdout);
}

inline std::ostringstream & Logger::Get(TLogLevel level)
{
  m_os << "- " << NowTime() << " "
       << m_color[level] << m_text[level]
       << RESET << ": ";
  return m_os;
}

inline std::string Logger::NowTime()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  struct tm *tm = localtime(&tv.tv_sec);
  char time[30];
  strftime(time, sizeof (time), "%d.%m.%Y %H:%M:%S:%%06u", tm);
  char buf[30];
  snprintf(buf, sizeof (buf), time, tv.tv_usec/1000);
  return buf;
}

template<typename T, template<typename, typename...> class C, typename... Args>
inline std::ostream & operator << (std::ostream & os, C<T, Args...> const & objs)
{
  os << "\n{\n";
  for (auto const & obj : objs)
    os << obj << ",\n";
  os << "}";
  return os;
}
