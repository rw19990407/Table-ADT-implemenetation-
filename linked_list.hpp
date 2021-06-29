#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "abstract_list.hpp"
#include "abstract_iterator.hpp"

template <typename T> class LinkedList;

template <typename T>
class LinkedListIterator: public AbstractIterator<T>
{
public:

  T& get();
  
  void next();
  
  bool isAtEnd() const;
  
private:

  LinkedListIterator(LinkedList<T> * that);

  // pointer to the list we are iterating over
  LinkedList<T> * list;

  // pointer to the current node in the LinkedList
  typename LinkedList<T>::NodePtr current = nullptr;

  // give LinkedList access to the private constructor
  friend class LinkedList<T>;
};

template <typename T>
class LinkedList: public AbstractList<T>
{
public:

  // convenience typedefs
  typedef LinkedListIterator<T> Iterator;
  typedef T Value;
  
  // default constructor
  LinkedList();

  // constructor to reserve space
  LinkedList(std::size_t size);
  
  // copy constructor
  LinkedList(const LinkedList<T>& x);

  // move constructor
  LinkedList(LinkedList<T>&& x);

  // destructor
  ~LinkedList();

  // copy assignment
  LinkedList& operator=(const LinkedList<T>& x);

  // move assignment
  LinkedList& operator=(LinkedList<T>&& x);

  // test if a list is empty
  bool isEmpty() const noexcept;

  // return the number of items in the list
  std::size_t getLength() const noexcept;

  // insert an entry at a given position in the list
  // uses 1-based indexing, shifts entries > newPosition up
  // valid positions are [1,Length+1]11
  // returns true on success, false on failure
  bool insert(std::size_t position, const T& value);

  // remove entry at a given position in the list
  // uses 1-based indexing, shifts entries < position down
  // valid positions are [1,Length]
  // returns true on success, false on failure
  bool remove(std::size_t position);

  // remove all entries from the list
  void clear();

  // get a copy of the value at position
  // uses 1-based indexing, valid positions are [1,Length]
  // throws std::invalid_argument if position invalid
  const T& getEntry(std::size_t position) const;

  // replace setEntry() with this member
  // get a reference to the value at position
  // uses 1-based indexing, valid positions are [1,Length]
  // throws std::invalid_argument if position invalid
  T & getEntry(std::size_t position);

  // return iterator at first element of the list
  LinkedListIterator<T> begin();
  
private:

  template<typename U>
  struct Node{
    T data;
    Node * next = nullptr;
    Node * prev = nullptr;
  };

  typedef Node<T>* NodePtr;
  
  Node<T> m_guard;
  std::size_t m_size = 0;

  // helper function
  NodePtr find(std::size_t pos) const;

  friend class LinkedListIterator<T>;
};

#include "linked_list.tpp"

#endif
