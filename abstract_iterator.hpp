#ifndef ABSTRACT_ITERATOR_HPP
#define ABSTRACT_ITERATOR_HPP

template<typename T>
class AbstractIterator{
public:
  // get a reference to the value a the current
  // iterator place
  virtual T& get() = 0;

  // increment to the next value in the sequence
  virtual void next() = 0;

  // is the iterator at the end (one past last value)
  virtual bool isAtEnd() const = 0;  
};

#endif
