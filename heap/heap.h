#pragma once
#include "../array/array.h"
#include <stdexcept>


enum class HeapOrder {
  MAX,
  MIN
};

template <typename T>
class Heap {
private:
  Array<T> data;
  HeapOrder heap_order;

  int parent(int index) {
    return (index - 1) / 2;
  }

  int left(int index) {
    return 2 * index + 1;
  }

  int right(int index) {
    return 2 * index + 2;
  }

  bool isEmpty() {
    return data.length() == 0;
  }

  void swap(int i, int j) {
    T temp = data[i];
    data[i] = data[j];
    data[j] = temp;
  }

  void bubbleUp(int index) {
    int p = parent(index);
    if (p < 0) {
      return;
    }
    if (heap_order == HeapOrder::MIN && data[index] < data[p]) {
      swap(index, p);
      bubbleUp(p);
    }
    if (heap_order == HeapOrder::MAX && data[index] > data[p]) {
      swap(index, p);
      bubbleUp(p);
    }
  }

  void bubbleDown(int index) {
    int l = left(index);
    int r = right(index);
    int extreme = index;
    int n = data.length() - 1;

    if (heap_order == HeapOrder::MIN) {
      if (l <= n && data[l] < data[extreme]) extreme = l;
      if (r <= n && data[r] < data[extreme]) extreme = r;
    } else if (heap_order == HeapOrder::MAX) {
      if (l <= n && data[l] > data[extreme]) extreme = l;
      if (r <= n && data[r] > data[extreme]) extreme = r;
    }

    if (index != extreme) {
      swap(index, extreme);
      bubbleDown(extreme);
    }
  }

public:
  Heap() : heap_order(HeapOrder::MIN) {}
  Heap(HeapOrder order) : heap_order(order) {}

  static Heap<T> heapify(const Array<T>& arr, HeapOrder order) {
    Heap<T> heap(order);
    // Add all values to the heap without checking anything
    for (int i = 0; i < arr.length(); i++) {
      heap.data.append(arr[i]);
    }

    int n = arr.length() - 1;
    int last_internal = n / 2;
    for (int i = last_internal; i >= 0; i--) {
      heap.bubbleDown(i);
    }

    return heap;
  }

  void append(const T& value) {
    data.append(value);
    bubbleUp(data.length() - 1);
  }
  T pop() {
    if (isEmpty()) {
      throw std::out_of_range("cannot call pop() on empty heap!");
    }
    T value = data.pop_back();
    if (!isEmpty()) {
      bubbleDown(0);
    }
    return value;
  }
  T peek() {
    if (isEmpty()) {
      throw std::out_of_range("cannot call peek() on empty heap!");
    }
    return data[0];
  }
  int size() {
    return data.length();
  }

};
