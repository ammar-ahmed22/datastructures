#pragma once
#include <stdexcept>
#include <iostream>


template <typename T> 
class LinkedList {
private:
 class Node {
    public:
      T data;
      Node* next;

      Node(T value) : data(value), next(nullptr) {}
  };

  class Iter {
  public:
    Node* n;
    Iter(Node* c): n(c) {}
    T& operator*() const { return n->data; }
    Iter& operator++() { n = n->next; return *this; }
    bool operator!=(const Iter& o) const { return n != o.n; }
  };

  std::size_t size;

  void destroy(Node* n) {
    if (n->next) {
      destroy(n->next);
    }
    delete n;
  }
public:
  Node* head;
  Node* tail;
  LinkedList() : size(0), head(nullptr), tail(nullptr) {}
  ~LinkedList() {
    if (head) {
      destroy(head);
    }
  }

  std::size_t length() {
    return size;
  }

  T& front() {
    if (!head) {
      throw std::out_of_range("front() called on empty list");
    }
    return head->data;
  }

  const T& front() const {
    if (!head) {
      throw std::out_of_range("front() called on empty list");
    }
    return head->data;
  }

  T& back() {
    if (!tail) {
      throw std::out_of_range("back() called on empty list");
    }
    return tail->data;
  }

  const T& back() const {
    if (!tail) {
      throw std::out_of_range("back() called on empty list");
    }
    return tail->data;
  }

  // Appends a value to the back of the list
  // 
  // Time Complexity: O(1)
  void append_back(T value) {
    Node* n = new Node(value);
    if (!head) {
      head = tail = n;
      size++;
      return;
    }

    tail->next = n;
    tail = tail->next;
    size++;
    return;
  }

  // Appends a value to the front of the list
  //
  // Time Complexity: O(1)
  void append_front(T value) {
    Node* n = new Node(value);
    if (!head) {
      head = tail = n;
      size++;
      return;
    }

    Node* next = head;
    head = n;
    head->next = next;
    size++;
    return;
  }

  // Removes a value from the back of the list
  // If there is no values, will throw an out_of_range error
  // Time Complexity: O(n)
  T remove_back() {
    if (!head) {
      throw std::out_of_range("Cannot remove from empty list");
    }

    if (head == tail) {
      T removed = head->data;
      delete head;
      head = tail = nullptr;
      size--;
      return removed;
    }

    Node* current = head;
    while(current->next != tail) {
      current = current->next;
    }

    T removed = tail->data;
    delete tail;
    tail = current;
    tail->next = nullptr;
    size--;
    return removed;
  }

  // Removes a value from the front of the list
  // If there is no values, will throw an out_of_range error
  // Time Complexity: O(1)
  T remove_front() {
    if (!head) {
      throw std::out_of_range("Cannot remove from empty list");
    }

    Node* to_remove = head;
    head = head->next;
    T removed = to_remove->data;
    delete to_remove;
    size--;

    if (!head) {
      tail = nullptr;
    }
    return removed;
  }

  // Checks if a list contains a value
  // Time Complexity: O(n)
  bool contains(T value) {
    Node* curr = head;
    while(curr) {
      if (curr->data == value) {
        return true;
      }
      curr = curr->next;
    }
    return false;
  }

  // Inserts a value at the node that has the specified value
  // If the value does not exist, returns false
  // If inserted successfully, returns true
  // Time Complexity: O(n)
  bool insert_at(T target, T value) {
    Node* curr = head;
    while(curr) {
      if (curr->data == target) {
        Node* next = curr->next;
        Node* n = new Node(value);
        n->next = next;
        curr->next = n;
        if (!next) {
          tail = n;
        }
        size++;
        return true;
      }
      curr = curr->next;
    }
    return false;
  }

  // Removes a node with a specified value
  // If the value does not exist, returns false
  // If removed successfully, returns true;
  bool remove(T value) {
    Node* curr = head;
    Node* prev = nullptr;
    while(curr) {
      if (curr->data == value) {
        if (prev) {
          prev->next = curr->next;
        } else {
          head = curr->next;
        }

        if (curr == tail) {
          tail = prev;
        }
        delete curr;
        size--;
        return true;
      }
      prev = curr;
      curr = curr->next;
    }
    return false;
  }

  Iter begin() {
    return Iter(head);
  }

  Iter end() {
    return Iter(nullptr);
  }

  friend std::ostream & operator<<(std::ostream & os, const LinkedList<T>& ll) {
    Node* curr = ll.head;
    while (curr) {
      os << curr->data;
      if (curr->next) {
        os << " -> ";
      }
      curr = curr->next;
    }
    return os;
  }
};
