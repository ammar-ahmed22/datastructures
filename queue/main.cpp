#include <cstddef>
#include <iostream>
#include "queue.h"
#include "../testing/test.h"

using namespace std;

static void test_enqueue() {
  Queue<int> q;

  q.enqueue(1);
  q.enqueue(2);

  ASSERT_EQ(q.peek(), 1);
  ASSERT_EQ(q.length(), std::size_t(2));
}

static void test_dequeue() {
  Queue<int> q;

  ASSERT_THROW(q.dequeue());

  q.enqueue(1);
  q.enqueue(2);

  ASSERT_EQ(q.dequeue(), 1);
  ASSERT_EQ(q.dequeue(), 2);
}

static void test_peek() {
  Queue<int> q;
  ASSERT_THROW(q.peek());

  q.enqueue(1);
  q.enqueue(2);

  ASSERT_EQ(q.peek(), 1);
  q.dequeue();
  ASSERT_EQ(q.peek(), 2);
}

int main() {
  test_enqueue();
  test_dequeue();
  test_peek();

  if (test::fails() == 0) {
    cout << "All tests passed" << endl;
    return 0;
  }
  
  cerr << test::fails() << " test(s) failed";
  return 1;
}
