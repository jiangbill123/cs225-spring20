/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}


/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode* curr = head_;
  ListNode *temp;
  while (curr != NULL){
    temp = curr;  
    curr=curr->next;
    delete temp;
  }
  head_ = NULL;
  tail_ = NULL;
  length_=0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  //emty list
  if (length_ == 0){
    tail_ = newNode;
    head_ = newNode;
    length_ = 1;
    return;
  }

  else
  {
    newNode -> next = head_;
    newNode -> prev = NULL;
    head_ -> prev = newNode;
    head_ = newNode;
  }
  
  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode* newNode = new ListNode(ndata);
  if (length_==0){
    head_=newNode;
    tail_=newNode;
    length_=1;
  }
  else{
    tail_->next = newNode;
    newNode->prev = tail_;
    tail_= tail_->next;
    length_++;
  }
  
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  //base
  if (start==NULL) {return NULL; }
  if (splitPoint == 0) { return start; }
  if (splitPoint >= length_) { return NULL; }

  ListNode * curr = start;
  ListNode *temp;

  for (int i = 0; i < splitPoint; i++) {
    curr = curr->next;
  }
  tail_ = curr->prev;
  tail_->next = NULL;
  curr->prev= NULL;
  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  ListNode* iter = head_; 
  //first 3, start pointing to 1
  if (length_<3){
    return;
  }
  ListNode *one = iter;
  ListNode *two = iter->next;
  ListNode *three = two->next;
  one->next = three->next;
  two->prev = one->prev;
  if (one->prev != NULL){
    one->prev->next = two;
  }
  if (three->next != NULL){
    three->next->prev=one;
  }
  three->next = one;
  one->prev = three;
  head_ = two;
  iter = one->next;
  if (length_<6){
    return;
  }

  for (int i = 2; i<=length_/3; i++){
    one = iter;
    two = iter->next;
    three = two->next;
    one->next = three->next;
    two->prev = one->prev;
    if (one->prev != NULL){
      one->prev->next = two;
    }
    if (three->next != NULL){
      three->next->prev=one;
    }
    three->next = one;
    one->prev = three;
    iter = one->next;
  }
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  //base
  if (startPoint == endPoint) { return; }
  
  ListNode* curr = startPoint;
  ListNode* right = endPoint->next;
  ListNode* left = startPoint->prev;
  ListNode* temp;

  while(curr != endPoint){ 
    temp = curr->prev;
    curr->prev = curr->next;
    curr->next = temp;
    curr = curr->prev;
  } //finish when curr==endPoint
  curr->next = curr->prev;
  curr->prev = left;
  startPoint->next = right;
  if (left != NULL){
    left->next = endPoint;
  }
  else
  {
    head_ = endPoint;
  }
  if (right != NULL){
    right->prev = startPoint;
  }
  else
  {
    tail_ = startPoint;
  }
  temp = startPoint;
  startPoint = endPoint;
  endPoint = temp;
  return;
  
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if (head_ == NULL || n<2) { return; }
  ListNode* start = head_;
  ListNode* end = start;
  while(start!=NULL){

    for (int j = 0; j<n-1; j++){
      if (end->next != NULL){
        end = end->next;
      }
    }
    reverse(start, end);
    start = end->next;
    end = start;
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  //base:
  if (second == NULL) { return first; }
  if (first == NULL) { return second; }

  ListNode* one = first;
  ListNode* two = second;
  ListNode* new_head = NULL;
  ListNode* curr = NULL;
  ListNode* temp;

  if (one!=NULL && two!=NULL){
    if (one->data < two->data){
      curr = one;
      one = curr->next;
    }
    else
    {
      curr = two;
      two = curr->next;
    }
    
  }
  new_head = curr;

  while (one!=NULL && two!=NULL){
    if (one->data < two->data){
      temp = one;
      curr->next = temp;
      temp->prev = curr;
      curr = one;
      one = curr->next;
    } 
    else{
      temp = two;
      curr->next = temp;
      temp->prev = curr;
      curr = two;
      two = curr->next;
    }
  }

  if (one == NULL){
    temp = two;
    curr->next = temp;
    temp->prev = curr;
  }
  if (two == NULL){
    temp = one;
    curr->next = temp;
    temp->prev = curr;
  }

  return new_head;

}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (chainLength == 1){
    start->next = NULL;
    start->prev = NULL;
    return start;
  }
  int pivot = chainLength/2;
  ListNode* start2 = split(start, pivot);
  return merge(mergesort(start, pivot), mergesort(start2, chainLength-pivot));
}
