#include "../testing/test.h"
#include "array.h"
#include <iostream>

using namespace std;

static void test_append() {
  Array<int> arr;
  ASSERT_TRUE(arr.capacity() == 2);
  ASSERT_TRUE(arr.length() == 0);
  ASSERT_EQ(arr.str(), "[]");

  arr.append(1);
  ASSERT_TRUE(arr.capacity() == 2);
  ASSERT_TRUE(arr.length() == 1);
  ASSERT_EQ(arr.str(), "[1]");

  arr.append(2);
  ASSERT_TRUE(arr.capacity() == 4);
  ASSERT_TRUE(arr.length() == 2);
  ASSERT_EQ(arr.str(), "[1, 2]");

  arr.append(3);
  ASSERT_TRUE(arr.capacity() == 4);
  ASSERT_TRUE(arr.length() == 3);

  ASSERT_EQ(arr.str(), "[1, 2, 3]");
}

static void test_delete_at() {
  Array<int> arr;
  arr.append(1);
  arr.append(2);
  arr.append(3);
  arr.append(4);
  ASSERT_EQ(arr.str(), "[1, 2, 3, 4]");
  ASSERT_TRUE(arr.capacity() == 8);
  ASSERT_TRUE(arr.length() == 4);

  // Index out of range
  ASSERT_THROW(arr.delete_at(4));

  arr.delete_at(0);
  ASSERT_EQ(arr.str(), "[2, 3, 4]");
  ASSERT_TRUE(arr.capacity() == 8);
  ASSERT_TRUE(arr.length() == 3);

  // Capacity reduction when size <= cap / 4
  arr.delete_at(arr.length() - 1);
  ASSERT_EQ(arr.str(), "[2, 3]");
  ASSERT_TRUE(arr.capacity() == 4);
  ASSERT_TRUE(arr.length() == 2);
}

static void test_indexing() {
  Array<int> arr;
  arr.append(1);
  arr.append(2);
  arr.append(3);
  arr.append(4);

  // Index out of range
  ASSERT_THROW(arr[4]);

  ASSERT_EQ(arr[3], 4);

  arr[3] = 3;
  ASSERT_EQ(arr[3], 3);
}

static void test_find_index() {
  Array<int> arr;
  arr.append(1);
  arr.append(2);
  arr.append(3);
  arr.append(4);

  ASSERT_EQ(arr.find_index(5), -1);
  ASSERT_EQ(arr.find_index(3), 2);
}

static void test_pop_back() {
  Array<int> arr;
  arr.append(1);
  arr.append(2);

  ASSERT_TRUE(arr.pop_back() == 1);
  ASSERT_TRUE(arr.pop_back() == 2);
  ASSERT_THROW(arr.pop_back());
}
static void test_pop_front() {
  Array<int> arr;
  arr.append(1);
  arr.append(2);

  ASSERT_TRUE(arr.pop_front() == 2);
  ASSERT_TRUE(arr.pop_front() == 1);
  ASSERT_THROW(arr.pop_back());
}

int main() {
  test_append();
  test_delete_at();
  test_indexing();
  test_find_index();
  test_pop_back();
  test_pop_front();

  if (test::fails() == 0) {
    cout << "All tests passed" << endl;
    return 0;
  }

  cerr << test::fails() << " test(s) failed" << endl;
  return 1;
}
