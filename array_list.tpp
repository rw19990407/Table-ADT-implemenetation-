#include "array_list.hpp"

#include <stdexcept>

// ArrayList implementation

template <typename T>
ArrayList<T>::ArrayList(std::size_t size){

  m_capacity = size;
  m_size = size;
  m_data = new T[m_capacity];
}

template <typename T>
ArrayList<T>::~ArrayList() {
  delete [] m_data;
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T> & rhs){

  if(rhs.m_size == 0) return;
  
  m_capacity = rhs.m_capacity;
  m_size = rhs.m_size;
  m_data = new T[m_capacity];
  for(std::size_t i = 0; i < m_size; ++i){
    m_data[i] = rhs.m_data[i];
  }
}

template <typename T>
ArrayList<T>::ArrayList(ArrayList<T> && rhs){
  std::swap(m_capacity, rhs.m_capacity);
  std::swap(m_size, rhs.m_size);
  std::swap(m_data, rhs.m_data);
}

template <typename T>
ArrayList<T> & ArrayList<T>::operator=(const ArrayList<T>& rhs){  

  if(this == &rhs) return *this;

  if(m_capacity < rhs.m_size){
    delete [] m_data;
    m_capacity = rhs.m_capacity;
    m_data = new T[m_capacity];
  }
  m_size = rhs.m_size;
  for(std::size_t i = 0; i < m_size; ++i){
    m_data[i] = rhs.m_data[i];
  }
  
  return *this;
}

template <typename T>
ArrayList<T> & ArrayList<T>::operator=(ArrayList<T>&& rhs){  

  // tear down current instance, return to default
  delete [] m_data;
  m_data = nullptr;
  m_capacity = 0;
  m_size = 0;

  std::swap(m_capacity, rhs.m_capacity);
  std::swap(m_size, rhs.m_size);
  std::swap(m_data, rhs.m_data);
  
  return *this;
}


template <typename T>
bool ArrayList<T>::isEmpty() const noexcept{
  return m_size == 0;
}

template <typename T>
std::size_t ArrayList<T>::getLength() const noexcept{
  return m_size;
}

template <typename T>
bool ArrayList<T>::insert(std::size_t position, const T& entry){

  if(position == 0 || position > m_size + 1){
    return false;
  }

  // switch to 0-based indexing internally
  position--;

  if(m_size + 1 > m_capacity){
    m_capacity = (m_capacity == 0) ? 1 : 2*m_capacity;
    T* temp = new T[m_capacity];
    for(std::size_t i = 0; i < m_size; ++i){
      temp[i] = m_data[i];
    }
    delete [] m_data;
    m_data = temp;
  }

  for(std::size_t i = m_size; i > position; --i){
    m_data[i] = m_data[i-1];
  }
  m_data[position] = entry;
  m_size++;
    
  return true;
}

template <typename T>
bool ArrayList<T>::remove(std::size_t position){
  if(position == 0 || position > m_size){
    return false;
  }

  // switch to 0-based indexing internally
  position--;

  for(std::size_t i = position; i < m_size - 1; ++i){
    m_data[i] = m_data[i+1];
  }
  --m_size;
  return true;
}

template <typename T>
void ArrayList<T>::clear() {
  m_size = 0;
}

template <typename T>
const T& ArrayList<T>::getEntry(std::size_t position) const{
  if(position == 0 || position > m_size){
    throw std::invalid_argument("invalid position in ArrayList<T>::getEntry");
  }
  return m_data[position-1];
}

template <typename T>
T& ArrayList<T>::getEntry(std::size_t position){
  if(position == 0 || position > m_size){
    throw std::invalid_argument("invalid position in ArrayList<T>::getEntry");
  }
  return m_data[position-1];
}

template <typename T>
ArrayListIterator<T> ArrayList<T>::begin(){
    return ArrayListIterator<T>(this);
}

// ArrayListIterator implementation
template <typename T>
T& ArrayListIterator<T>::get(){
  return list->m_data[index];
}

template <typename T>
void ArrayListIterator<T>::next() { index++; }

template <typename T>
bool ArrayListIterator<T>::isAtEnd() const {
  return index >= list->m_size;
}

template <typename T>
ArrayListIterator<T>::ArrayListIterator(ArrayList<T> * that){
  index = 0;
  list = that;
}


