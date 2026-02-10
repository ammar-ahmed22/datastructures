#pragma once
#include <cstddef>
#include <iostream>

template <typename T>
class SortedLinkedList {
private:
  class Node {
  public:
    T data;
    Node* next;
    Node(T value) : data(value), next(nullptr) {}
  };

  std::size_t size;
public:
  Node* head;
  Node* tail;

  SortedLinkedList() : size(0), head(nullptr), tail(nullptr) {}

  std::size_t length() {
    return size;
  }

  void insert(T value) {
    Node* n = new Node(value);

    Node** curr = &head;
    while(*curr && (*curr)->data < value) {
      curr = &((*curr)->next);
    }

    n->next = *curr;
    *curr = n;

    if (!n->next) {
      tail = n;
    }

    size++;
    return;
  }

  void remove_duplicates() {
    Node* curr = head;
    while(curr) {
      Node* next = curr->next;
      while(next && next->data == curr->data) {
        Node* old = next;
        next = next->next;
        delete old;
        size--;
      }
      curr->next = next;
      if (!next) {
        tail = curr;
      }
      curr = next;
    }
  }

  friend std::ostream& operator<<(std::ostream& os, const SortedLinkedList<T>& list) {
    Node* curr = list.head;
    while(curr) {
      os << curr->data;
      if (curr->next) {
        os << " -> ";
      }
      curr = curr->next;
    }
    return os;
  }
};
