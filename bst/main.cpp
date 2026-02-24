#include "../testing/test.h"
#include "bst.h"
#include <iostream>

using namespace std;

static BinarySearchTree<int> create_tree(int *values, int n) {
  BinarySearchTree<int> bst;
  for (int i = 0; i < n; i++) {
    bst.insert(values[i]);
  }
  return bst;
}

static void test_insert_recursive() {
  BinarySearchTree<int> bst = create_tree(new int[4]{20, 15, 25, 23}, 4);

  ASSERT_EQ(bst.inorder_str(), "15 20 23 25 ");

  bst.set_insert_algo(BSTInsertAlgo::Recurse);
  bst.insert(26);

  ASSERT_EQ(bst.inorder_str(), "15 20 23 25 26 ");
}

static void test_insert_parent_ptr() {
  BinarySearchTree<int> bst = create_tree(new int[4]{20, 15, 25, 23}, 4);

  ASSERT_EQ(bst.inorder_str(), "15 20 23 25 ");

  bst.set_insert_algo(BSTInsertAlgo::Parent);
  bst.insert(26);

  ASSERT_EQ(bst.inorder_str(), "15 20 23 25 26 ");
}

static void test_insert_ptr_to_ptr() {
  BinarySearchTree<int> bst = create_tree(new int[4]{20, 15, 25, 23}, 4);

  ASSERT_EQ(bst.inorder_str(), "15 20 23 25 ");

  bst.set_insert_algo(BSTInsertAlgo::Pointer);
  bst.insert(26);

  ASSERT_EQ(bst.inorder_str(), "15 20 23 25 26 ");
}

static void test_contains() {
  BinarySearchTree<int> bst = create_tree(new int[4]{20, 15, 25, 23}, 4);

  ASSERT_TRUE(bst.contains(25));
  ASSERT_TRUE(!bst.contains(21));
}

static void test_remove() {
  BinarySearchTree<int> bst = create_tree(new int[4]{20, 15, 25, 23}, 4);
  bst.remove(15);
}

static void test_preorder_str() {
  BinarySearchTree<int> bst = create_tree(new int[4]{20, 15, 25, 23}, 4);
  ASSERT_EQ(bst.preorder_str(), "20 15 25 23 ");
}

static void test_postorder_str() {
  BinarySearchTree<int> bst = create_tree(new int[4]{20, 15, 25, 23}, 4);
  ASSERT_EQ(bst.postorder_str(), "15 23 25 20 ");
}

int main() {
  test_insert_recursive();
  test_insert_parent_ptr();
  test_insert_ptr_to_ptr();
  test_contains();
  test_preorder_str();
  test_postorder_str();
  test_remove();
  if (test::fails() == 0) {
    cout << "All tests passed" << endl;
    return 0;
  }

  cerr << test::fails() << " test(s) failed" << endl;
  return 1;
}
