#include <cstddef>
#include <iostream>
#include "stack.h"
#include "../testing/test.h"

using namespace std;

static void test_push() {
  Stack<int> s;

  s.push(1);
  ASSERT_TRUE(s.length() == std::size_t(1));
  ASSERT_TRUE(s.peek() == 1);

  s.push(2);
  ASSERT_TRUE(s.length() == std::size_t(2));
  ASSERT_TRUE(s.peek() == 2);
}

static void test_pop() {
  Stack<int> s;

  s.push(1);
  s.push(2);
  s.push(3);

  ASSERT_EQ(s.length(), std::size_t(3));
  ASSERT_EQ(s.pop(), 3);
  ASSERT_EQ(s.length(), std::size_t(2));
  ASSERT_EQ(s.pop(), 2);
  ASSERT_EQ(s.length(), std::size_t(1));
  ASSERT_EQ(s.pop(), 1);
  ASSERT_EQ(s.length(), std::size_t(0));
  ASSERT_THROW(s.pop());
}

static void test_peek() {
  Stack<int> s;

  s.push(1);
  s.push(2);
  s.push(3);

  ASSERT_EQ(s.peek(), 3);
  ASSERT_EQ(s.length(), std::size_t(3));
  s.pop();
  ASSERT_EQ(s.peek(), 2);
  ASSERT_EQ(s.length(), std::size_t(2));
  s.pop();
  ASSERT_EQ(s.peek(), 1);
  ASSERT_EQ(s.length(), std::size_t(1));
  s.pop();
  ASSERT_THROW(s.peek());
}

int main() {
  test_push();
  test_pop();
  test_peek();

  if (test::fails() == 0) {
    cout << "All tests passed" << endl;
    return 0;
  }

  cerr << test::fails() << " test(s) failed" << endl;
  return 1;
}
