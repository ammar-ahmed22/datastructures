#include "../testing/test.h"
#include "../array/array.h"
#include "heap.h"
#include <iostream>

using namespace std;

static void test_max_insert() {
  Heap<int> heap(HeapOrder::MAX);
  heap.append(1);
  ASSERT_TRUE(heap.size() == 1);
  ASSERT_TRUE(heap.peek() == 1);

  heap.append(4);
  ASSERT_TRUE(heap.size() == 2);
  ASSERT_TRUE(heap.peek() == 4);

  heap.append(12);
  heap.append(5);
  heap.append(7);
  ASSERT_TRUE(heap.size() == 5);
  ASSERT_TRUE(heap.peek() == 12);
}

static void test_min_insert() {
  Heap<int> heap(HeapOrder::MIN);
  heap.append(12);
  ASSERT_TRUE(heap.size() == 1);
  ASSERT_TRUE(heap.peek() == 12);

  heap.append(9);
  ASSERT_TRUE(heap.size() == 2);
  ASSERT_TRUE(heap.peek() == 9);

  heap.append(7);
  heap.append(10);
  heap.append(11);
  ASSERT_TRUE(heap.size() == 5);
  ASSERT_TRUE(heap.peek() == 7);
}

static void test_max_pop() {
  Heap<int> heap(HeapOrder::MAX);
  heap.append(2);
  heap.append(4);
  heap.append(3);
  heap.append(6);
  heap.append(8);
  // values = [2, 4, 3, 6, 8]
  ASSERT_TRUE(heap.size() == 5);
  // pop
  ASSERT_TRUE(heap.pop() == 8);
  ASSERT_TRUE(heap.size() == 4);
  // pop
  ASSERT_TRUE(heap.pop() == 6);
  ASSERT_TRUE(heap.size() == 3);
  // pop
  ASSERT_TRUE(heap.pop() == 4);
  ASSERT_TRUE(heap.size() == 2);
  // pop
  ASSERT_TRUE(heap.pop() == 3);
  ASSERT_TRUE(heap.size() == 1);
  // pop
  ASSERT_TRUE(heap.pop() == 2);
  ASSERT_TRUE(heap.size() == 0);
  // pop -> throw
  ASSERT_THROW(heap.pop());
}

static void test_min_pop() {
    Heap<int> heap(HeapOrder::MIN);
  heap.append(2);
  heap.append(4);
  heap.append(3);
  heap.append(6);
  heap.append(8);
  // values = [2, 4, 3, 6, 8]
  ASSERT_TRUE(heap.size() == 5);
  // pop
  ASSERT_TRUE(heap.pop() == 2);
  ASSERT_TRUE(heap.size() == 4);
  // pop
  ASSERT_TRUE(heap.pop() == 3);
  ASSERT_TRUE(heap.size() == 3);
  // pop
  ASSERT_TRUE(heap.pop() == 4);
  ASSERT_TRUE(heap.size() == 2);
  // pop
  ASSERT_TRUE(heap.pop() == 6);
  ASSERT_TRUE(heap.size() == 1);
  // pop
  ASSERT_TRUE(heap.pop() == 8);
  ASSERT_TRUE(heap.size() == 0);
  // pop -> throw
  ASSERT_THROW(heap.pop());
}

static void test_heapify() {
  Array<int> input;
  input.append(3);
  input.append(9);
  input.append(2);
  input.append(1);
  input.append(4);
  input.append(5);
  // values = [3, 9, 2, 1, 4, 5]
  
  Heap<int> max_heap = Heap<int>::heapify(input, HeapOrder::MAX);
  ASSERT_TRUE(max_heap.size() == 6);
  ASSERT_TRUE(max_heap.pop() == 9);
  ASSERT_TRUE(max_heap.pop() == 5);
  ASSERT_TRUE(max_heap.pop() == 4);
  ASSERT_TRUE(max_heap.pop() == 3);
  ASSERT_TRUE(max_heap.pop() == 2);
  ASSERT_TRUE(max_heap.pop() == 1);

  Heap<int> min_heap = Heap<int>::heapify(input, HeapOrder::MIN);
  ASSERT_TRUE(min_heap.size() == 6);
  ASSERT_TRUE(min_heap.pop() == 1);
  ASSERT_TRUE(min_heap.pop() == 2);
  ASSERT_TRUE(min_heap.pop() == 3);
  ASSERT_TRUE(min_heap.pop() == 4);
  ASSERT_TRUE(min_heap.pop() == 5);
  ASSERT_TRUE(min_heap.pop() == 9);
}

int main() {
  test_max_insert();
  test_min_insert();
  test_max_pop();
  test_min_pop();
  test_heapify();

  if (test::fails() == 0) {
    cout << "All tests passed" << endl;
    return 0;
  }

  cerr << test::fails() << " test(s) failed" << endl;
  return 1;
}
