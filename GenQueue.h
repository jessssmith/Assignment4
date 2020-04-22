#include <iostream>
#include "GenDoublyLinked.h"

using namespace std;

template <class T>
class GenQueue {
  public:
    GenQueue();
    ~GenQueue();


    void insert(T d);
    T remove();
    T peekFront();
    T peekBack();
    bool isEmpty();
    int getSize();

  private:
    int numElements;
    GenDoublyLinked<T> *myQueue;
};

//implementation
template<class T>
GenQueue<T>::GenQueue() {
  myQueue = new GenDoublyLinked<T>();
  numElements = 0;
}

template <class T>
GenQueue<T>::~GenQueue() {
  delete myQueue;
}

template <class T>
void GenQueue<T>::insert(T d) {
  myQueue->insertBack(d);
  numElements++;
}

template <class T>
T GenQueue<T>::remove() {
  if(isEmpty())
    cout << "Cannot remove from empty queue" << endl;
  myQueue->removeFront();
  numElements--;
}

template <class T>
T GenQueue<T>::peekFront() {
  return myQueue->front->data;
}

template <class T>
T GenQueue<T>::peekBack() {
  return myQueue->back->data;
}

template <class T>
bool GenQueue<T>::isEmpty() {
  if(numElements <= 0)
    return true;
  else
    return false;
}

template <class T>
int GenQueue<T>::getSize() {
  return numElements;
}
