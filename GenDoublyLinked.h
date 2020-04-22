#include <iostream>
#include "ListNode.h"

using namespace std;

template <class T>
class GenDoublyLinked {

public:
  ListNode<T> *front;
  ListNode<T> *back;
  unsigned int size;

  GenDoublyLinked();
  ~GenDoublyLinked();

  void insertFront(T data);
  void insertBack(T data);
  T removeFront();
  T removeBack();
  T search(T val);
  T removeAtPos(int pos);
  T remove(T value);

  unsigned int getSize();
  bool isEmpty();
  void printList();

};

//constructor
template <class T>
GenDoublyLinked<T>::GenDoublyLinked() {
  size = 0;
  front = NULL;
  back = NULL;
}

//destructor
template <class T>
GenDoublyLinked<T>::~GenDoublyLinked() { //something in here
  ListNode<T> *curr = front;
  while(curr != NULL) {
    ListNode<T> next = curr->next;
    delete curr;
    curr = next;
  }
}

//insert front
template <class T>
void GenDoublyLinked<T>::insertFront(T d) {
  ListNode<T> *node = new ListNode<T>(d);
  if(size == 0)
    back = node;
  else {
    node->next = front;
    front->prev = node;
  }
  front = node;
  size++;
}

//insert back
template <class T>
void GenDoublyLinked<T>::insertBack(T d) { //this probably doesnt work
  ListNode<T> *node = new ListNode<T>(d);
  if(size == 0)
    front = node;
  else {
    back->next = node;
    node->prev = back;
  }
  back = node;
  size++;
}

//remove at front
template <class T>
T GenDoublyLinked<T>::removeFront() {
  T temp = front->data;
  ListNode<T> *ft = front;
  front = front->next;
  ft->next = NULL;
  delete ft;
  size--;
  return temp;
}

//remove at back
template <class T>
T GenDoublyLinked<T>::removeBack() {
  T temp = back->data;
  ListNode<T> *bk = back;
  back = back->prev;
  back->next = NULL;
  bk->prev = NULL;
  delete bk;
  size--;
  return temp;
}

//search, returns index position of value being searched for
template <class T>
T GenDoublyLinked<T>::search(T v) {
  int pos = -1;
  ListNode<T> *curr = front;

  while(curr != NULL) {
    pos++;
    if(curr->data == v)
      break;
    else
      curr = curr->next;
    }

    if(curr == NULL)
      pos = -1;

    return pos;
}

//remove at position
template <class T>
T GenDoublyLinked<T>::removeAtPos(int p) { //not working
  int idx = 0;
  if(p < size) {
    ListNode<T> *curr = front;
    ListNode<T> *prev = front;

    while(idx != p) {
      prev = curr;
      curr = curr->next;
      idx++;
    }
    if(idx == p) {
      prev->next = curr->next;
      curr->next = NULL;
      curr->prev = NULL;
      T temp = curr->data;
      delete curr;
      size--;
      return temp;
    }
  }
}

//get size
template <class T>
unsigned int GenDoublyLinked<T>::getSize() {
  return size;
}

//check if empty
template <class T>
bool GenDoublyLinked<T>::isEmpty() {
  if(size > 0)
    return false;
  else
    return true;
}

//print list
template <class T>
void GenDoublyLinked<T>::printList() {
  ListNode<T> *curr = front;

  while(curr != NULL) {
    cout << curr->data << endl;
    curr = curr->next;
  }
}

template <class T>
T GenDoublyLinked<T>::remove(T value) {
  if(size == 0)
    return -1;

  ListNode<T> *curr = front;

  while(curr->data != value) {
    curr = curr->next;

    if(curr == NULL)
      return -1;
  }
  if(curr == front)
    front = curr->next;
  else if(curr == back)
    back = curr->prev;
  else {
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
  }

  curr->next = NULL;
  curr->prev = NULL;
  size--;
  return curr->data;
}
