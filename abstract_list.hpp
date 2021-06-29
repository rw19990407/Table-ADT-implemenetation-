#ifndef ABSTRACT_LIST_HPP
#define ABSTRACT_LIST_HPP

// for std::size_t
#include <cstddef>

template <typename T>
class AbstractList
{
public:

  // test if a list is empty
  virtual bool isEmpty() const noexcept = 0;

  // return the number of items in the list
  virtual std::size_t getLength() const noexcept = 0;

  // insert an entry at a given position in the list
  // uses 1-based indexing, shifts entries > newPosition up
  // valid positions are [1,Length+1]
  // returns true on success, false on failure
  virtual bool insert(std::size_t position, const T& value) = 0;

  // remove entry at a given position in the list
  // uses 1-based indexing, shifts entries < position down
  // valid positions are [1,Length]
  // returns true on success, false on failure
  virtual bool remove(std::size_t position) = 0;

  // remove all entries from the list
  virtual void clear() = 0;

  // get a copy of the value at position
  // uses 1-based indexing, valid positions are [1,Length]
  // throws std::invalid_argument if position invalid
  virtual const T& getEntry(std::size_t position) const = 0;

  // replace setEntry() with this member
  // get a reference to the value at position
  // uses 1-based indexing, valid positions are [1,Length]
  // throws std::invalid_argument if position invalid
  virtual T & getEntry(std::size_t position) = 0;
};


#endif
