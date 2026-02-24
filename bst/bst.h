#pragma once
#include <iostream>
#include <sstream>
#include <string>

enum class BSTInsertAlgo {
  Pointer,
  Recurse,
  Parent,
};

template <typename T> class BinarySearchTree {
  class Node {
  public:
    T data;
    Node *left;
    Node *right;
    Node(const T &d) : data(d), left(nullptr), right(nullptr) {}
  };

  Node *root;

  // Post-order DFS for destruction
  void destroy(Node *n) {
    if (!n) {
      return;
    }

    destroy(n->left);
    destroy(n->right);
    delete n;
  }

  void stream_preorder(std::stringstream &ss, Node *curr) {
    if (!curr) {
      return;
    }
    ss << curr->data << " ";
    stream_preorder(ss, curr->left);
    stream_preorder(ss, curr->right);
  }

  void stream_inorder(std::stringstream &ss, Node *curr) {
    if (!curr) {
      return;
    }
    stream_inorder(ss, curr->left);
    ss << curr->data << " ";
    stream_inorder(ss, curr->right);
  }

  void stream_postorder(std::stringstream &ss, Node *curr) {
    if (!curr) {
      return;
    }
    stream_postorder(ss, curr->left);
    stream_postorder(ss, curr->right);
    ss << curr->data << " ";
  }

  void stream_tree(std::ostream &os, Node *n, int depth) const {
    if (!n) {
      return;
    }
    stream_tree(os, n->right, depth + 1);
    os << std::string(depth * 4, ' ') << n->data << "\n";
    stream_tree(os, n->left, depth + 1);
  }

  Node *insert(Node *curr, const T &data) {
    if (!curr) {
      Node *n = new Node(data);
      return n;
    }
    if (data < curr->data) {
      curr->left = insert(curr->left, data);
    } else {
      curr->right = insert(curr->right, data);
    }
    return curr;
  }

  void insert_parent(const T &data) {
    Node *curr = root;
    Node *prev = nullptr;

    while (curr) {
      prev = curr;
      if (data < curr->data) {
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }

    // Insert at prev
    Node *n = new Node(data);
    if (data < prev->data) {
      prev->left = n;
    } else {
      prev->right = n;
    }
  }

  void insert_pointer(const T &data) {
    Node **curr = &root;
    while (*curr) {
      if (data < (*curr)->data) {
        curr = &((*curr)->left);
      } else {
        curr = &((*curr)->right);
      }
    }
    *curr = new Node(data);
  }

  Node *two_child_rm(Node *curr, Node *replace) {
    if (!curr->right) {
      replace->data = curr->data;
      Node *temp = curr->left;
      delete curr;
      return temp;
    }
    curr->right = two_child_rm(curr->right, replace);
    return curr;
  }

  Node *remove(Node *curr, const T &data) {
    if (!curr) {
      return nullptr;
    }

    if (curr->data == data) {
      if (!curr->left) {
        Node *r = curr->right;
        delete curr;
        return r;
      }
      if (!curr->right) {
        Node *l = curr->left;
        delete curr;
        return l;
      }

      curr->left = two_child_rm(curr->left, curr);
      return curr;
    } else if (data < curr->data) {
      curr->left = remove(curr->left, data);
    } else {
      curr->right = remove(curr->right, data);
    }
    return curr;
  }

  BSTInsertAlgo insert_algo;

public:
  BinarySearchTree() : root(nullptr), insert_algo(BSTInsertAlgo::Recurse) {}
  BinarySearchTree(BSTInsertAlgo insert_algo)
      : root(nullptr), insert_algo(insert_algo) {}
  ~BinarySearchTree() { destroy(root); }

  void set_insert_algo(BSTInsertAlgo algo) { insert_algo = algo; }

  void insert(const T &data) {
    if (insert_algo == BSTInsertAlgo::Recurse) {
      root = insert(root, data);
      return;
    } else if (insert_algo == BSTInsertAlgo::Parent) {
      insert_parent(data);
      return;
    } else if (insert_algo == BSTInsertAlgo::Pointer) {
      insert_pointer(data);
      return;
    }
  }

  bool contains(const T &data) const {
    Node *curr = root;
    while (curr) {
      if (data == curr->data) {
        return true;
      } else if (data < curr->data) {
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }
    return false;
  }

  void remove(const T &data) { root = remove(root, data); }

  std::string preorder_str() {
    std::stringstream ss;
    stream_preorder(ss, root);
    return ss.str();
  }

  std::string inorder_str() {
    std::stringstream ss;
    stream_inorder(ss, root);
    return ss.str();
  }

  std::string postorder_str() {
    std::stringstream ss;
    stream_postorder(ss, root);
    return ss.str();
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const BinarySearchTree<T> &bst) {
    bst.stream_tree(os, bst.root, 0);
    return os;
  }
};
