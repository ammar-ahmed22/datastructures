#pragma once
#include <cstddef>
#include <sstream>
#include <stdexcept>
template <typename T> class DoublyLinkedList {
private:
  class Node {
  public:
    T data;
    Node *next;
    Node *prev;

    Node(T value) : data(value), next(nullptr), prev(nullptr) {}
  };

  std::size_t size;

public:
  Node *head;
  Node *tail;

  DoublyLinkedList() : size(0), head(nullptr), tail(nullptr) {}

  T front() {
    if (!head) {
      throw std::out_of_range("front() called on empty list");
    }
    return head->data;
  }
  const T front() const {
    if (!head) {
      throw std::out_of_range("front() called on empty list");
    }
    return head->data;
  }

  T back() {
    if (!tail) {
      throw std::out_of_range("back() called on empty list");
    }
    return tail->data;
  }
  const T back() const {
    if (!tail) {
      throw std::out_of_range("back() called on empty list");
    }
    return tail->data;
  }

  // Append a value to the back of the list
  //
  // Time Complexity: O(1)
  void append_back(T value) {
    Node *n = new Node(value);
    if (!head) {
      head = tail = n;
      size++;
      return;
    }

    tail->next = n;
    n->prev = tail;
    tail = n;
    size++;
    return;
  }

  // Append a value to the front of the list
  //
  // Time Complexity: O(1)
  void append_front(T value) {
    Node *n = new Node(value);
    if (!head) {
      head = tail = n;
      size++;
      return;
    }

    Node *next = head;
    head = n;
    head->next = next;
    next->prev = head;
    size++;
    return;
  }

  T remove_back() {
    if (!head) {
      throw std::out_of_range("remove_back() called on empty list");
    }

    Node* old = tail;
    if (head == tail) {
      head = tail = nullptr;
      T value = old->data;
      delete old;
      size--;
      return value;
    }
    tail = tail->prev;
    tail->next = nullptr;
    T value = old->data;
    delete old;
    size--;
    return value;
  }

  T remove_front() {
    if (!tail) {
      throw std::out_of_range("remove_front() called on empty list");
    }

    Node* old = head;
    if (head == tail) {
      head = tail = nullptr;
      T value = old->data;
      delete old;
      size--;
      return value;
    }
    head = head->next;
    head->prev = nullptr;
    T value = old->data;
    delete old;
    size--;
    return value;
  }

  bool insert_at(T target, T value) {
    if (!head) {
      return false;
    }

    Node* curr = head;
    while(curr) {
      if (curr->data == target) {
        Node* n = new Node(value);
        Node* next = nullptr;
        if (curr->next) {
          next = curr->next;
        }
        if (curr == tail) {
          tail = n;
        }
        curr->next = n;
        n->next = next;
        n->prev = curr;
        size++;
        return true;
      }
      curr = curr->next;
    }
    return false;
  }

  std::size_t length() { return size; }

  friend std::ostream &operator<<(std::ostream &os,
                                  const DoublyLinkedList<T> &list) {
    Node *curr = list.head;
    while (curr) {
      os << curr->data;
      if (curr->next) {
        os << " <-> ";
      }
      curr = curr->next;
    }
    return os;
  }
};
