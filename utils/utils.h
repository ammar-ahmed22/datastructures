#pragma once

namespace utils {
template <typename T> const T &min(const T &a, const T &b) {
  if (a > b) {
    return b;
  }
  return a;
}

template <typename T> const T &max(const T &a, const T &b) {
  if (a > b) {
    return a;
  }
  return b;
}
} // namespace utils
