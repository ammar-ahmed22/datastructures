#pragma once
#include <iostream>
#include <sstream>
#include <string>

namespace test {
  inline int& fails() { static int f = 0;  return f; }
  inline int& tests() { static int t = 0; return t; }

  [[noreturn]] inline void die() { std::exit(1); };

  inline void report_fail(const char* expr, const char* file, int line, const char* func, const std::string& msg = "") {
    ++fails();
    std::cerr << file << ":" << line << " in " << func << "\n  FAILED: " << expr;
    if (!msg.empty()) {
      std::cerr << "\n  " << msg;
    }
    std::cerr << "\n\n";
  }
}

#define ASSERT_TRUE(expr) \
  do { \
    if (!(expr)) { \
      ::test::report_fail(#expr, __FILE__, __LINE__, __func__); \
      return; \
    } \
  } while (0)

#define ASSERT_EQ(a, b) \
  do { \
    auto _a = a; \
    auto _b = b; \
    if (!(_a == _b)) { \
      std::stringstream _oss; \
      _oss << "  expected equality\n    left: " << _a << "\n    right: " << _b; \
      ::test::report_fail(#a " == " #b, __FILE__, __LINE__, __func__, _oss.str()); \
      return; \
    } \
  } while (0)

#define ASSERT_THROW(expr) \
  do { \
    try { \
      expr; \
      std::stringstream _oss; \
      _oss << "  expected throw\n"; \
      ::test::report_fail(#expr, __FILE__, __LINE__, __func__, _oss.str()); \
      return; \
    } catch (...) { \
    } \
  } while (0)
