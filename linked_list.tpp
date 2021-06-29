#include "linked_list.hpp"

#include <stdexcept>

// LinkedList implementation

template<typename T>
LinkedList<T>::LinkedList(std::size_t size){

  m_size = size;
  NodePtr curr = &m_guard;
  for(std::size_t i = 0; i < m_size; ++i){
    curr->next = new Node<T>;
    curr->next->next = &m_guard;
    curr->next->prev = curr;
    curr = curr->next;
  }
}

template<typename T>
LinkedList<T>::LinkedList(){
  m_guard.prev = m_guard.next = &m_guard;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& x){

  NodePtr xcurr = x.m_guard.next;
  NodePtr curr = &m_guard;
  while(xcurr != &x.m_guard){
    NodePtr temp = new Node<T>;
    temp->data = xcurr->data;
    temp->prev = curr;
    temp->next = &m_guard;
    
    curr->next = temp;
    m_guard.prev = temp;
    m_size++;
      
    xcurr = xcurr->next;
    curr = temp;
  }
}

template<typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& x){
  std::swap(m_size, x.m_size);

  if(m_size > 0){
    m_guard.next = x.m_guard.next;
    x.m_guard.next = &x.m_guard;
    m_guard.prev = x.m_guard.prev;
    x.m_guard.prev = &x.m_guard;
    m_guard.next->prev = &m_guard;
    m_guard.prev->next = &m_guard;
  }
  else{
    m_guard.prev = m_guard.next = &m_guard;
  }
}


template<typename T>
LinkedList<T>::~LinkedList(){
  clear();
}

// this is the simplest solution and is equivalent to using copy-swap
// possible optimizations include using existing allocated nodes and
// removing any extra
template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& x){

  if(this != &x){
    clear();
    
    // copy from x
    NodePtr xcurr = x.m_guard.next;
    NodePtr curr = &m_guard;
    while(xcurr != &x.m_guard){
      NodePtr temp = new Node<T>;
      temp->data = xcurr->data;
      temp->prev = curr;
      temp->next = &m_guard;
    
      curr->next = temp;
      m_guard.prev = temp;
      m_size++;
      
      xcurr = xcurr->next;
      curr = temp;
    }
  }
  
  return *this;
}

// self (move) assignment is effectively is the same as clear
template<typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& x){

  clear();
  if(this != &x){
    std::swap(m_size, x.m_size);

    if(m_size > 0){
      m_guard.next = x.m_guard.next;
      x.m_guard.next = &x.m_guard;
      m_guard.prev = x.m_guard.prev;
      x.m_guard.prev = &x.m_guard;
      m_guard.next->prev = &m_guard;
      m_guard.prev->next = &m_guard;
    }
  }
  
  return *this;
}

template<typename T>
bool LinkedList<T>::isEmpty() const noexcept{

  return m_size == 0;
}

template<typename T>
std::size_t LinkedList<T>::getLength() const noexcept{

  return m_size;
}

template<typename T>
typename LinkedList<T>::NodePtr LinkedList<T>::find(std::size_t pos) const{

  NodePtr curr = const_cast<NodePtr>(&m_guard);
  for(std::size_t i = 1; i <= pos; ++i){
    curr = curr->next;
  }
  
  return curr;
}

template<typename T>
bool LinkedList<T>::insert(std::size_t position, const T& value){

  if(position == 0 || position > m_size+1){
    return false;
  }

  NodePtr curr = find(position);
  
  NodePtr temp = new Node<T>;
  temp->data = value;
  curr->prev->next = temp;
  temp->prev = curr->prev;
  temp->next = curr;
  curr->prev = temp;

  m_size++;
  
  return true;
}

template<typename T>
bool LinkedList<T>::remove(std::size_t position){

  if(position == 0 || position > m_size){
    return false;
  }

  NodePtr curr = find(position);

  curr->prev->next = curr->next;
  curr->next->prev = curr->prev;
  delete curr;
  m_size--;
  
  return true;
}

template<typename T>
void LinkedList<T>::clear(){

  NodePtr curr = m_guard.next;
  while(curr != &m_guard){
    m_guard.next = curr->next;
    delete curr;
    m_size--;
    curr = m_guard.next;
  }
}

template<typename T>
const T& LinkedList<T>::getEntry(std::size_t position) const{

  if(position == 0 || position > m_size){
    throw std::invalid_argument("invalid position in LinkedList::getEntry");
  }

  NodePtr curr = find(position);
  
  return curr->data;
}

template<typename T>
T& LinkedList<T>::getEntry(std::size_t position){

  if(position == 0 || position > m_size){
    throw std::invalid_argument("invalid position in LinkedList::getEntry");
  }

  NodePtr curr = find(position);
  
  return curr->data;
}

template<typename T>
LinkedListIterator<T> LinkedList<T>::begin(){
    return LinkedListIterator<T>(this);
}


// LinkedListIterator implementation
template <typename T>
T& LinkedListIterator<T>::get(){
  return current->data;
}

template <typename T>
void LinkedListIterator<T>::next() { current = current->next; }

template <typename T>
bool LinkedListIterator<T>::isAtEnd() const {
  return current == &(list->m_guard);
}

template <typename T>
LinkedListIterator<T>::LinkedListIterator(LinkedList<T> * that){
  list = that;
  current = list->m_guard.next;
}
