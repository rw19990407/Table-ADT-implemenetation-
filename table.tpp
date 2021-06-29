#include "table.hpp"
#include <stdexcept>

template<typename T>
bool Table<T>::checkheader(std::string name) {
	bool check = false;
	for (std::size_t i = 1; i <= header.getLength(); ++i) {
		if (header.getEntry(i) == name) {
			check = true;
			break;
		}
	}
	return check;
}
template<typename T>
// return the number of rows in the Table
std::size_t Table<T>::numRows() const noexcept {
	return m_row.getLength(); 
}

template<typename T>
// return the number of columns in the Table
std::size_t Table<T>::numCols() const noexcept {
	return header.getLength();
}

template<typename T>
// set column header to the string name
// valid values for col is [1,numCols()]
// throws std::invalid_argument if invalid column
void Table<T>::setHeader(std::size_t col, std::string name) {
	if (col <= 0 || col > header.getLength()) {
		throw std::invalid_argument("invalid Set Header in Table");
	}
	header.getEntry(col) = name;
	
}

template<typename T>
// get column header as string
// valid values for col is [1,numCols()]
// throws std::invalid_argument if invalid column
std::string Table<T>::getHeader(std::size_t col) {
	if (col <= 0 || col > header.getLength()) {
		throw std::invalid_argument("invalid Get Column in Table");
	}
	return header.getEntry(col);

}

template<typename T>
// insert row into table at position set to value 
// valid values for position is [1,numRows()+1]
// throws std::invalid_argument if invalid
void Table<T>::insertRow(std::size_t position, T value) {
	if (position <= 0 || position > m_row.getLength() + 1 ) {
		throw std::invalid_argument("invalid Insert Row in Table");
	}
	ArrayList<T> Rui_row(header.getLength());
	for (std::size_t i = 1; i <= header.getLength(); ++i) {
		Rui_row.getEntry(i) = value;
	}
	m_row.insert(position,Rui_row);

}

template<typename T>
// append row to table set to value 
void Table<T>::appendRow(T value) {
	ArrayList<T> Rui_row(header.getLength());
	for (std::size_t i = 1; i <= header.getLength(); ++i) {
		Rui_row.getEntry(i) = value;
	}
	m_row.insert(m_row.getLength()+1,Rui_row);
}

template<typename T>
// insert column into table at position set to value 
// valid values for position is [1,numCols()+1]
// throws std::invalid_argument if invalid

void Table<T>::insertCol(std::size_t position, std::string name, T value) {
	if (position <= 0 || position > header.getLength() + 1||checkheader(name)) {
		throw std::invalid_argument("invalid insertCol to insert a col");
	}
	header.insert(position,name);
	for (LinkedListIterator<ArrayList<T>> it = m_row.begin();
		!it.isAtEnd();
		it.next()) {
		it.get().insert(position,value);
	}
}

template<typename T>
// append column to table set to value 
void Table<T>::appendCol(std::string name, T value) {
	if (checkheader(name)) {
		throw std::invalid_argument("invalid index");
	}
	header.insert(header.getLength() + 1, name);
	for (LinkedListIterator<ArrayList<T>> it = m_row.begin();
		!it.isAtEnd();
		it.next()) {
		it.get().insert(header.getLength(), value);
	}
}

template<typename T>
// return constant reference to table entry at (row, col)
// throws std::invalid_argument if invalid row or column
const T& Table<T>:: operator()(std::size_t row, std::size_t col) const {
	if ((col <= 0 || col > header.getLength())||(row <= 0 || row > m_row.getLength())) {
		throw std::invalid_argument("invalid position in Table::operator");
	}	
	return m_row.getEntry(row).getEntry(col);
}

template<typename T>
// return reference to table entry at (row, col)
// throws std::invalid_argument if invalid row or column
T& Table<T>::operator()(std::size_t row, std::size_t col) {
	if ((col <= 0 || col > header.getLength())|| (row <= 0 || row > m_row.getLength())) {
		throw std::invalid_argument("invalid position in Table::operator");
	}
	return m_row.getEntry(row).getEntry(col);
}

template<typename T>
// stable sort (low to high) of table rows using column col
// throws std::invalid_argument if invalid column
void Table<T>::sortBy(std::size_t col) {
	if (col <= 0 || col > header.getLength()) {
		throw std::invalid_argument("invalid stable sort (low to high) in Table");
	}
	for (std::size_t j = 1; j < m_row.getLength(); ++j) {
		for (std::size_t i = 1; i < m_row.getLength(); ++i) {
			if (m_row.getEntry(i).getEntry(col) > m_row.getEntry(i + 1).getEntry(col)) {
				std::swap(m_row.getEntry(i), m_row.getEntry(i + 1));
			}
		}
	}
}

template<typename T>
// stable sort (low to high) of table rows using column with name
// throws std::invalid_argument if invalid column name
void Table<T>::sortBy(std::string colname) {
	if (!checkheader(colname)) {
		throw std::invalid_argument("Invalid header in colname");
	}
	std::size_t col = 0;
	for (std::size_t k = 1; k <= header.getLength(); k++) {
		if (header.getEntry(k) == colname) {
			col = k;
			break;
		}
	}
	for (std::size_t j = 1; j < m_row.getLength(); ++j) {
		for (std::size_t i = 1; i < m_row.getLength(); ++i) {
			if (m_row.getEntry(i).getEntry(col) > m_row.getEntry(i + 1).getEntry(col)) {
				std::swap(m_row.getEntry(i), m_row.getEntry(i + 1));
			}
		}
	}
}

template<typename T>
// stable sort (high to low) of table rows using column col
// throws std::invalid_argument if invalid column
void Table<T>::reverseSortBy(std::size_t col) {
	if (col <= 0 || col > header.getLength()) {
		throw std::invalid_argument("invalid stable sort (low to high) in Table");
	}
	for (std::size_t j = 1; j < m_row.getLength(); ++j) {
		for (std::size_t i = 1; i < m_row.getLength(); ++i) {
			if (m_row.getEntry(i).getEntry(col) < m_row.getEntry(i + 1).getEntry(col)) {
				std::swap(m_row.getEntry(i), m_row.getEntry(i + 1));
			}
		}
	}
}

template<typename T>
// stable sort (high to low) of table rows using column with name
// throws std::invalid_argument if invalid column name
void Table<T>::reverseSortBy(std::string colname) {
	if (!checkheader(colname)) {
		throw std::invalid_argument("Invalid header in colname");
	}
	std::size_t col = 0;
	for (std::size_t k = 1; k <= header.getLength(); k++) {
		if (header.getEntry(k) == colname) {
			col = k;
			break;
		}
	}
	for (std::size_t j = 1; j < m_row.getLength(); ++j) {
		for (std::size_t i = 1; i < m_row.getLength(); ++i) {
			if (m_row.getEntry(i).getEntry(col) < m_row.getEntry(i + 1).getEntry(col)) {
				std::swap(m_row.getEntry(i), m_row.getEntry(i + 1));
			}
		}
	}
}

// TODO
