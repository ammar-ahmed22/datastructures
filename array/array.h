#pragma once
#include <sstream>
#include <stdexcept>
#include <string>
#include "../utils/utils.h"

template <typename T> class Array {
private:
  int size;
  int cap;
  T *data;

  void resize(int newCapacity) {
    T *newData = new T[newCapacity];

    for (int i = 0; i < size; i++) {
      newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    cap = newCapacity;
  }

  void swap(int i, int j) {
    T temp = data[i];
    data[i] = data[j];
    data[j] = temp;
  }

  bool in_bounds(const int index) const {
    return index >= 0 && index < size;
  }

  void assert_in_bounds(const int index) const {
    if (!in_bounds(index)) {
      throw std::out_of_range("index out of range");
    }
  }

  bool isEmpty() {
    return size == 0;
  }

public:
  Array(int c) : size(0), cap(utils::min(2, c)) { data = new T[cap]; }
  Array() : size(0), cap(2) { data = new T[cap]; }
  ~Array() { delete[] data; }

  int length() const { return size; }

  int capacity() const { return cap; }

  void append(const T &value) {
    data[size] = value;
    size++;

    if (size == cap) {
      resize(cap * 2);
    }
  }

  void delete_at(const int index) {
    assert_in_bounds(index);

    // Shift left starting from i to the end
    // Removed value is at the end of the data now
    for (int j = index; j < size - 1; j++) {
      swap(j, j + 1);
    }
    size--;

    if (size <= cap / 4) {
      resize(utils::max(2, cap / 2));
    }
  }

  T pop_front() {
    if (isEmpty()) {
      throw std::out_of_range("cannot call pop_front() on empty array!");
    }
    T value = data[size - 1];
    delete_at(size - 1);
    return value;
  }

  T pop_back() {
    if (isEmpty()) {
      throw std::out_of_range("cannot call pop_back() on empty array!");
    }
    T value = data[0];
    delete_at(0);
    return value;
  }

  int find_index(const T& value) const {
    for (int i = 0; i < size; i++) {
      if (data[i] == value) {
        return i;
      }
    }
    return -1;
  }

  T &operator[](const int index) {
    assert_in_bounds(index);
    return data[index];
  }

  const T &operator[](const int index) const {
    assert_in_bounds(index);
    return data[index];
  }

  std::string str() const {
    std::stringstream ss;
    ss << "[";
    for (int i = 0; i < size; i++) {
      ss << data[i];
      if (i < size - 1) {
        ss << ", ";
      }
    }
    ss << "]";
    return ss.str();
  }

  friend std::ostream &operator<<(std::ostream &os, const Array<T> &arr) {
    os << "[";
    for (int i = 0; i < arr.size; i++) {
      os << arr[i];
      if (i < arr.size - 1) {
        os << ", ";
      }
    }
    os << "]";
    return os;
  }
};
