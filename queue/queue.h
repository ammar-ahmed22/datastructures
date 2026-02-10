#pragma once
#include "../linked_list/linked_list.h"
#include <cstddef>
#include <stdexcept>

template <typename T>
class Queue {
private:
  LinkedList<T> list;

public:
  void enqueue(T value) {
    list.append_back(value);
  }

  T dequeue() {
    if (list.length() == 0) {
      throw std::out_of_range("dequeue() called on empty queue");
    }
    return list.remove_front();
  }

  T peek() {
    if (list.length() == 0) {
      throw std::out_of_range("peek() called on empty queue");
    }
    return list.front();
  }

  std::size_t length() {
    return list.length();
  }
};
