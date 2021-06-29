#include "catch.hpp"

#include "array_list.hpp"
#include "linked_list.hpp"

TEST_CASE("Testing Empty ArrayListIterator", "[Iterators]") {
  ArrayList<int> a;
  
  ArrayListIterator<int> it = a.begin();
  REQUIRE(it.isAtEnd());
  it.next();
  REQUIRE(it.isAtEnd());
}

TEST_CASE("Testing Non-Empty ArrayListIterator", "[Iterators]") {
  ArrayList<int> a;
  
  for(int i = -100; i <= 100; ++i){
    a.insert(a.getLength()+1, i);
  }
  
  ArrayListIterator<int> it = a.begin();
  REQUIRE_FALSE(it.isAtEnd());
  
  //example usage
  int testvalue = -100;
  while(!it.isAtEnd()){
    REQUIRE(it.get() == testvalue);
    it.next();
    testvalue++;
  }
  
  REQUIRE(it.isAtEnd());
}

TEST_CASE("Testing Empty LinkedListIterator", "[Iterators]") {
  LinkedList<int> a;
  
  LinkedListIterator<int> it = a.begin();
  REQUIRE(it.isAtEnd());
  it.next();
  REQUIRE(it.isAtEnd());
}

TEST_CASE("Testing Non-Empty LinkedListIterator", "[Iterators]") {
  LinkedList<int> a;
  
  for(int i = -100; i <= 100; ++i){
    a.insert(a.getLength()+1, i);
  }
  
  LinkedListIterator<int> it = a.begin();
  REQUIRE_FALSE(it.isAtEnd());
  
  //example usage
  int testvalue = -100;
  while(!it.isAtEnd()){
    REQUIRE(it.get() == testvalue);
    it.next();
    testvalue++;
  }
  
  REQUIRE(it.isAtEnd());
}
