#include <cstddef>
#include <iostream>
#include <sstream>
#include "doubly_linked_list.h"
#include "../testing/test.h"

using namespace std;

static void test_append_back() {
  DoublyLinkedList<int> dl;

  dl.append_back(1);
  dl.append_back(2);

  ASSERT_EQ(dl.head->data, 1);
  ASSERT_EQ(dl.head->next->data, 2);
  ASSERT_EQ(dl.tail->data, 2);
  ASSERT_EQ(dl.tail->prev->data, 1);
}

static void test_append_front() {
  DoublyLinkedList<int> dl;

  dl.append_front(2);
  dl.append_front(1);

  ASSERT_EQ(dl.head->data, 1);
  ASSERT_EQ(dl.head->next->data, 2);
  ASSERT_EQ(dl.tail->data, 2);
  ASSERT_EQ(dl.tail->prev->data, 1);
}

static void test_remove_back() {
  DoublyLinkedList<int> dl;

  dl.append_back(1);
  dl.append_back(2);

  ASSERT_EQ(dl.remove_back(), 2);
  ASSERT_EQ(dl.tail->data, 1);
  ASSERT_EQ(dl.tail->next, nullptr);
  ASSERT_EQ(dl.tail->prev, nullptr);
  ASSERT_EQ(dl.tail, dl.head);
  ASSERT_EQ(dl.length(), std::size_t(1));

  ASSERT_EQ(dl.remove_back(), 1);
  ASSERT_EQ(dl.tail, nullptr);
  ASSERT_EQ(dl.head, nullptr);
  ASSERT_EQ(dl.length(), std::size_t(0));
}

static void test_remove_front() {
  DoublyLinkedList<int> dl;

  dl.append_back(1);
  dl.append_back(2);

  ASSERT_EQ(dl.remove_front(), 1);
  ASSERT_EQ(dl.tail->data, 2);
  ASSERT_EQ(dl.tail->next, nullptr);
  ASSERT_EQ(dl.tail->prev, nullptr);
  ASSERT_EQ(dl.tail, dl.head);
  ASSERT_EQ(dl.length(), std::size_t(1));

  ASSERT_EQ(dl.remove_front(), 2);
  ASSERT_EQ(dl.tail, nullptr);
  ASSERT_EQ(dl.head, nullptr);
  ASSERT_EQ(dl.length(), std::size_t(0));
}

static void test_insert_at() {
  DoublyLinkedList<int> dl;

  dl.append_back(1);
  dl.append_back(2);
  dl.append_back(3);

  ASSERT_EQ(dl.insert_at(2, 2), true);
  stringstream ss;
  ss << dl;
  ASSERT_EQ(ss.str(), "1 <-> 2 <-> 2 <-> 3");

  ASSERT_EQ(dl.insert_at(3, 3), true);
  ss = stringstream();
  ss << dl;
  ASSERT_EQ(ss.str(), "1 <-> 2 <-> 2 <-> 3 <-> 3");
  ASSERT_EQ(dl.tail->data, 3);
  ASSERT_EQ(dl.tail->prev->data, 3);

  ASSERT_EQ(dl.insert_at(4, 4), false);

  dl = DoublyLinkedList<int>();
  dl.append_back(1);
  ASSERT_EQ(dl.insert_at(1, 2), true);
  ASSERT_EQ(dl.tail->data, 2);
  ASSERT_EQ(dl.tail->prev->data, 1);
}

static void test_left_shift_operator() {
  DoublyLinkedList<int> dl;
  dl.append_back(1);
  dl.append_back(2);

  stringstream ss;
  ss << dl;

  ASSERT_EQ(ss.str(), "1 <-> 2");
}

int main() {
  test_append_back();
  test_append_front();
  test_remove_back();
  test_remove_front();
  test_insert_at();
  test_left_shift_operator();

  if (test::fails() == 0) {
    cout << "All tests passed" << endl;
    return 0;
  }

  cerr << test::fails() << " test(s) failed" << endl;
  return 1;
}
