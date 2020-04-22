template <class T>
class ListNode {
  public:
    T data;
    ListNode *prev;
    ListNode *next;

  ListNode();
  ListNode(T d);
  ~ListNode();
};

//listnode implementation
template <class T>
ListNode<T>::ListNode() {
  data = NULL;
  next = NULL;
  prev = NULL;
}

template <class T>
ListNode<T>::ListNode(T d) {
  data = d;
  next = NULL;
  prev = NULL;
}

template <class T>
ListNode<T>::~ListNode() { //figure this one out
  next = NULL;
  prev = NULL;
}
