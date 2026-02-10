#pragma once
#include "../linked_list/linked_list.h"
#include <cstddef>
#include <sstream>
#include <stdexcept>

template <typename T>
class Stack {
private:
  LinkedList<T> list;

public:
  Stack() {}

  void push(T value) {
    list.append_front(value);
  }

  T pop() {
    if (list.length() == 0) {
      throw std::out_of_range("pop() called on empty stack");
    }
    return list.remove_front();
  }

  T peek() {
    if (list.length() == 0) {
      throw std::out_of_range("peek() called on empty stack");
    }
    return list.front();
  }

  std::size_t length() {
    return list.length();
  }
};
