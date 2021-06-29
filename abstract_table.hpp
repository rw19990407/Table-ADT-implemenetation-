#ifndef ABSTRACT_TABLE_HPP
#define ABSTRACT_TABLE_HPP

#include <string>
#include <cstddef>

template<typename T>
class AbstractTable{
public:

  // return the number of rows in the Table
  virtual std::size_t numRows() const noexcept = 0;

  // return the number of columns in the Table
  virtual std::size_t numCols() const noexcept = 0;

  // set column header to the string name
  // valid values for col is [1,numCols()]
  // throws std::invalid_argument if invalid column
  virtual void setHeader(std::size_t col, std::string name) = 0;

  // get column header as string
  // valid values for col is [1,numCols()]
  // throws std::invalid_argument if invalid column
  virtual std::string getHeader(std::size_t col) = 0;

  // insert row into table at position set to value 
  // valid values for position is [1,numRows()+1]
  // throws std::invalid_argument if invalid
  virtual void insertRow(std::size_t position, T value) = 0;

  // append row to table set to value 
  virtual void appendRow(T value) = 0;

  // insert column into table at position set to value 
  // valid values for position is [1,numCols()+1]
  // throws std::invalid_argument if invalid
  virtual void insertCol(std::size_t position, std::string name, T value) = 0;

  // append column to table set to value 
  virtual void appendCol(std::string name, T value) = 0;

  // return constant reference to table entry at (row, col)
  // throws std::invalid_argument if invalid row or column
  virtual const T& operator()(std::size_t row, std::size_t col) const = 0;

  // return reference to table entry at (row, col)
  // throws std::invalid_argument if invalid row or column
  virtual T& operator()(std::size_t row, std::size_t col) = 0;

  // stable sort (low to high) of table rows using column col
  // throws std::invalid_argument if invalid column
  virtual void sortBy(std::size_t col) = 0;

  // stable sort (low to high) of table rows using column with name
  // throws std::invalid_argument if invalid column name
  virtual void sortBy(std::string colname) = 0;

  // stable sort (high to low) of table rows using column col
  // throws std::invalid_argument if invalid column
  virtual void reverseSortBy(std::size_t col) = 0;

  // stable sort (high to low) of table rows using column with name
  // throws std::invalid_argument if invalid column name
  virtual void reverseSortBy(std::string colname) = 0;
};

#endif

