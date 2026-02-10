#include <cstddef>
#include <iostream>
#include <sstream>
#include "sorted_linked_list.h"
#include "../testing/test.h"

using namespace std;

static void test_insert() {
  SortedLinkedList<int> sl;

  sl.insert(1);
  ASSERT_TRUE(sl.head->data == 1);
  ASSERT_TRUE(sl.head == sl.tail);

  sl.insert(3);
  ASSERT_TRUE(sl.head->data == 1);
  ASSERT_TRUE(sl.tail->data == 3);
  ASSERT_TRUE(sl.head->next == sl.tail);

  sl.insert(2);
  ASSERT_TRUE(sl.head->next->data == 2);
  ASSERT_TRUE(sl.length() == std::size_t(3));
}

static void test_left_shift_operator() {
  SortedLinkedList<int> sl;

  sl.insert(1);
  sl.insert(3);
  sl.insert(2);
  sl.insert(2);

  stringstream ss;

  ss << sl;
  ASSERT_TRUE(ss.str() == "1 -> 2 -> 2 -> 3");
}

static void test_remove_duplicates() {
  SortedLinkedList<int> sl;

  sl.insert(1);
  sl.insert(2);
  sl.insert(2);
  sl.insert(3);

  stringstream ss;
  ss << sl;
  ASSERT_TRUE(ss.str() == "1 -> 2 -> 2 -> 3");

  sl.remove_duplicates();
  ss = stringstream();
  ss << sl;
  ASSERT_TRUE(ss.str() == "1 -> 2 -> 3");
  ASSERT_TRUE(sl.tail->data == 3);
}

int main() {
  test_insert();
  test_remove_duplicates();
  test_left_shift_operator();

  if (test::fails() == 0) {
    cout << "All tests passed" << endl;
    return 0;
  }

  cerr << test::fails() << " test(s) failed" << endl;
  return 1;
}
