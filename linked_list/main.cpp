#include <cstddef>
#include <iostream>
#include "linked_list.h"
#include <sstream>
#include "../testing/test.h"

using namespace std;


static void test_left_shift_stream() {
  LinkedList<int> ll;
  stringstream ss;
  ll.append_back(1);
  ll.append_back(2);
  ll.append_back(3);

  ss << ll;

  ASSERT_EQ(ss.str(), "1 -> 2 -> 3");
}

static void test_front() {
  LinkedList<int> ll;
  ll.append_back(1);
  ll.append_back(2);

  ASSERT_EQ(ll.front(), 1);
  ll.remove_front();
  ASSERT_EQ(ll.front(), 2);
  ll.remove_front();
  ASSERT_THROW(ll.front());
}

static void test_back() {
  LinkedList<int> ll;
  ll.append_back(1);
  ll.append_back(2);

  ASSERT_EQ(ll.back(), 2);
  ll.remove_back();
  ASSERT_EQ(ll.back(), 1);
  ll.remove_back();
  ASSERT_THROW(ll.back());
}

static void test_append_back() {
  LinkedList<int> ll;
  ll.append_back(1);
  ASSERT_EQ(ll.length(), std::size_t(1));
  ASSERT_EQ(ll.back(), 1);
}

static void test_append_front() {
  LinkedList<int> ll;
  stringstream ss;

  ll.append_back(1);
  ll.append_back(2);

  ss << ll;
  ASSERT_EQ(ss.str(), "1 -> 2");
  ASSERT_EQ(ll.length(), std::size_t(2));

  ll.append_front(0);
  ss = stringstream();
  ss << ll;
  ASSERT_EQ(ss.str(), "0 -> 1 -> 2");
  ASSERT_EQ(ll.length(), std::size_t(3));
}

static void test_remove_back() {
  LinkedList<int> ll;
  ASSERT_THROW(ll.remove_back());

  stringstream ss;
  ll.append_back(1);
  ll.append_back(2);

  ss << ll;
  ASSERT_EQ(ss.str(), "1 -> 2");
  ASSERT_EQ(ll.length(), std::size_t(2));
  ASSERT_EQ(ll.remove_back(), 2);

  ss = stringstream();
  ss << ll;
  ASSERT_EQ(ll.length(), std::size_t(1));
  ASSERT_EQ(ss.str(), "1");
}

static void test_remove_front() {
  LinkedList<int> ll;
  ASSERT_THROW(ll.remove_front());

  stringstream ss;
  ll.append_back(1);
  ll.append_back(2);

  ss << ll;
  ASSERT_EQ(ss.str(), "1 -> 2");
  ASSERT_EQ(ll.length(), std::size_t(2));
  ASSERT_EQ(ll.remove_front(), 1);

  ss = stringstream();
  ss << ll;
  ASSERT_EQ(ll.length(), std::size_t(1));
  ASSERT_EQ(ss.str(), "2");
}

static void test_contains() {
  LinkedList<int> ll;

  ll.append_back(1);
  ll.append_back(2);
  ll.append_back(3);

  ASSERT_TRUE(ll.contains(3));
  ASSERT_TRUE(!ll.contains(5));
}

static void test_insert_at() {
  LinkedList<int> ll;

  ll.append_back(1);
  ll.append_back(2);
  ll.append_back(3);

  ASSERT_TRUE(ll.insert_at(2, 2));
  stringstream ss;
  ss << ll;
  ASSERT_EQ(ss.str(), "1 -> 2 -> 2 -> 3");

  ASSERT_TRUE(!ll.insert_at(4, 3));
  ss = stringstream();
  ss << ll;
  ASSERT_EQ(ss.str(), "1 -> 2 -> 2 -> 3");
}

static void test_remove() {
  LinkedList<int> ll;

  ll.append_back(1);
  ll.append_back(2);
  ll.append_back(3);

  ASSERT_TRUE(ll.remove(2));
  ASSERT_TRUE(ll.remove(3));
  ASSERT_TRUE(ll.tail->data == 1);
}

static void test_length() {
  LinkedList<int> ll;

  ASSERT_TRUE(ll.length() == std::size_t(0));

  ll.append_back(1);
  ll.append_back(2);

  ASSERT_TRUE(ll.length() == std::size_t(2));

  ll.remove_back();
  ASSERT_TRUE(ll.length() == std::size_t(1));

  ll.remove_front();
  ASSERT_TRUE(ll.length() == std::size_t(0));

  ll.append_front(ll.length() == std::size_t(1));
}

static void test_iterator() {
  LinkedList<int> ll;
  int* arr = new int[2];
  arr[0] = 1;
  arr[1] = 2;
  ll.append_back(arr[0]);
  ll.append_back(arr[1]);

  int i = 0;
  for (int& x : ll) {
    ASSERT_EQ(x, arr[i]);
    i++;
  }

}

int main() {
  test_left_shift_stream();
  test_front();
  test_back();
  test_append_back();
  test_append_front();
  test_remove_back();
  test_remove_front();
  test_contains();
  test_insert_at();
  test_remove();
  test_length();
  test_iterator();

  if (test::fails() == 0) {
    cout << "All tests passed" << endl;
    return 0;
  }

  cout << test::fails() << " test(s) failed" << endl;
  return 1;
}
