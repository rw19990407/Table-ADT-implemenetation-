#ifndef ARRAY_LIST_HPP
#define ARRAY_LIST_HPP

#include "abstract_list.hpp"
#include "abstract_iterator.hpp"

template <typename T> class ArrayList;

template <typename T>
class ArrayListIterator: public AbstractIterator<T>
{
public:

  T& get();
  
  void next();
  
  bool isAtEnd() const;
  
private:

  ArrayListIterator(ArrayList<T> * that);
  
  std::size_t index = 0;
  ArrayList<T> * list = nullptr;

  // give ArrayList access to the private constructor
  friend class ArrayList<T>;
};


template<typename T>
class ArrayList: public AbstractList<T>
{
public:

  // convenience typedefs
  typedef ArrayListIterator<T> Iterator;
  typedef T Value;
  
  // constructor
  ArrayList() = default;

  // constructor to reserve space
  ArrayList(std::size_t size);

  // copy constructor
  ArrayList(const ArrayList<T> & rhs);

  // copy assignment
  ArrayList<T> & operator=(const ArrayList<T> & rhs);

  // move constructor
  ArrayList(ArrayList<T> && rhs);

  // copy assignment
  ArrayList<T> & operator=(ArrayList<T> && rhs);

  // destructor
  ~ArrayList();
  
  // test if a list is empty
  bool isEmpty() const noexcept;

  // return the number of items in the list
  std::size_t getLength() const noexcept;

  // insert an entry at a given position in the list
  // uses 1-based indexing, shifts entries > newPosition up
  // valid positions are [1,Length+1]
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
  ArrayListIterator<T> begin();

private:

  std::size_t m_capacity = 0;
  std::size_t m_size = 0;
  T* m_data = nullptr;
  
  friend class ArrayListIterator<T>;
};

#include "array_list.tpp"

#endif
