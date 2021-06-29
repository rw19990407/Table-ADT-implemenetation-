#include "catch.hpp"

#include "array_list.hpp"

TEST_CASE( "Test basic operations of ArrayList", "[ArrayList]" ) {

  ArrayList<int> list;

  CHECK(list.isEmpty());
  CHECK(list.getLength() == 0);
  CHECK_FALSE(list.insert(0, 10));

  CHECK(list.insert(1, 10));
  CHECK_FALSE(list.isEmpty());
  CHECK(list.getLength() == 1);
  CHECK(list.getEntry(1) == 10);
}

TEST_CASE("Test value semantics on ArrayList", "[ArrayList]") {

  ArrayList<int> list1;

  CHECK(list1.insert(1, 0));
  CHECK(list1.insert(2, 1));
  CHECK(list1.insert(3, 2));
  CHECK(list1.insert(4, 3));

  CHECK(list1.getEntry(1) == 0);
  CHECK(list1.getEntry(2) == 1);
  CHECK(list1.getEntry(3) == 2);
  CHECK(list1.getEntry(4) == 3);

  ArrayList<int> list2 = list1; // invoke the copy constructor

  CHECK(list2.getEntry(1) == 0);
  CHECK(list2.getEntry(2) == 1);
  CHECK(list2.getEntry(3) == 2);
  CHECK(list2.getEntry(4) == 3);

  list1.insert(1, 100);
  CHECK(list1.getEntry(1) == 100);
  CHECK(list2.getEntry(1) == 0);

  ArrayList<int> list3;

  list3.insert(1, 50);
  list3.insert(2, 51);

  list3 = list2; // invoke assignment operator

  CHECK(list3.getEntry(1) == 0);
  CHECK(list3.getEntry(2) == 1);
  CHECK(list3.getEntry(3) == 2);
  CHECK(list3.getEntry(4) == 3);

  list2.insert(1, 1000);
  CHECK(list3.getEntry(1) == 0);
  CHECK(list2.getEntry(1) == 1000);
  
}

TEST_CASE("Test ArrayList move semantics", "[ArrayList]") {

  ArrayList<int> list;

  for(int position = 1; position < 100; ++position){
    list.insert(position, -position);
  }

  REQUIRE(list.getLength() == 99);

  ArrayList<int> newlist = std::move(list);

  REQUIRE(list.getLength() == 0);
  REQUIRE(newlist.getLength() == 99);

  ArrayList<int> anotherlist;

  anotherlist.insert(1, 42);
  REQUIRE(anotherlist.getLength() == 1);

  anotherlist = std::move(newlist);

  REQUIRE(anotherlist.getLength() == 99);
  REQUIRE(newlist.getLength() == 0);
}

TEST_CASE("Test ArrayList::remove", "[ArrayList]") {

  ArrayList<int> list;

  REQUIRE_THROWS_AS(list.getEntry(0), std::invalid_argument);
  REQUIRE_THROWS_AS(list.getEntry(1), std::invalid_argument);
  REQUIRE_FALSE(list.remove(0));
  
  for(int position = 1; position < 100; ++position){
    list.insert(position, -position);
  }

  REQUIRE_THROWS_AS(list.getEntry(0), std::invalid_argument);
  REQUIRE_THROWS_AS(list.getEntry(100), std::invalid_argument);
  REQUIRE_FALSE(list.remove(100));
    
  for(int i = 1; i < 100; ++i){
    list.remove(1);
  }
  REQUIRE(list.isEmpty());

  for(int i = 1; i < 100; ++i){
    list.insert(i, -i);
  }

  for(int i = 1; i < 100; ++i){
    list.remove(list.getLength());
  }
  REQUIRE(list.isEmpty());
  
}

TEST_CASE("Test ArrayList::clear", "[ArrayList]") {

  ArrayList<int> list;

  REQUIRE(list.isEmpty());
  REQUIRE(list.getLength() == 0);
    
  for(int position = 1; position < 200; ++position){
    list.insert(position, -position);
  }

  REQUIRE_FALSE(list.isEmpty());
  REQUIRE(list.getLength() == 199);

  list.clear();
  REQUIRE(list.isEmpty());
  REQUIRE(list.getLength() == 0);
}

TEST_CASE("Test const ArrayList", "[ArrayList]") {

  const ArrayList<char> list1;

  REQUIRE_THROWS_AS(list1.getEntry(0), std::invalid_argument);
  REQUIRE_THROWS_AS(list1.getEntry(1), std::invalid_argument);

  ArrayList<char> list2;
  list2.insert(1,'a');
  list2.insert(2,'b');
  list2.insert(3,'c');
  list2.insert(4,'d');

  const ArrayList<char> list3 = list2;

  REQUIRE(list3.getEntry(1) == 'a');
  REQUIRE(list3.getEntry(2) == 'b');
  REQUIRE(list3.getEntry(3) == 'c');
  REQUIRE(list3.getEntry(4) == 'd');
  REQUIRE_THROWS_AS(list3.getEntry(5), std::invalid_argument);
  
}

