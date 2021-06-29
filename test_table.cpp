#include "catch.hpp"
#include "table.hpp"

TEST_CASE("Test basic operations", "[Table]") {

    Table<int> table;
    // append a column named "C2" filled with 2's
    table.appendCol("C2", 2);
    // insert a column at Column 1 named "C1" filled with 1's
    table.insertCol(1, "C1", 1);
    // insert a column at Column 3 named "C3" filled with 3's
    table.insertCol(3, "C3", 3);
    // append a column named "C4" filled with 4's
    table.appendCol("C4", 4);
    // append three row filled with 2's, 3's, and 4's
    table.appendRow(2);
    table.appendRow(3);
    table.appendRow(4);
    // insert a row at 1 filled with 1's
    table.insertRow(1, 1);
    // insert a row at 5 filled with 5's
    table.insertRow(5, 5);
    table.appendCol("C5", 100);
    REQUIRE(table(3, 5) == 100);
    table(3, 5) = 15;
    REQUIRE(table(3, 5) == 15);

    
    REQUIRE(table.numCols() == 5);
    REQUIRE(table.numRows() == 5);
    REQUIRE(table.getHeader(2) == "C2");
    REQUIRE(table(1, 1) == 1);
    REQUIRE(table(5, 4) == 5);
    table.reverseSortBy("C2");
    REQUIRE(table(2, 1) == 4);
    table.sortBy("C2");
    REQUIRE(table(2, 1) == 2);
    table.reverseSortBy(2);
    REQUIRE(table(2, 1) == 4);
    table.sortBy(2);
    REQUIRE(table(2, 1) == 2);
}

TEST_CASE("value semantics", "[Table]") {
    Table<int> table;
    // append a column named "C2" filled with 2's
    table.appendCol("C2", 2);
    // insert a column at Column 1 named "C1" filled with 1's
    table.insertCol(1, "C1", 1);
    // insert a column at Column 3 named "C3" filled with 3's
    table.insertCol(3, "C3", 3);
    // append a column named "C4" filled with 4's
    table.appendCol("C4", 4);
    // append three row filled with 2's, 3's, and 4's
    table.appendRow(2);
    table.appendRow(3);
    table.appendRow(4);
    // insert a row at 1 filled with 1's
    table.insertRow(1, 1);
    // insert a row at 5 filled with 5's
    table.insertRow(5, 5);
    table.appendCol("C5", 100);
    REQUIRE(table.getHeader(2) == "C2");
    REQUIRE(table(1, 1) == 1);
    REQUIRE(table(5, 4) == 5);
    const Table<int> table2 = table;
    Table<int> table3;
    table3 = table;
    
    REQUIRE(table2(1, 1) == 1);
    REQUIRE(table2(5, 4) == 5);
    REQUIRE(table3.getHeader(2) == "C2");
    REQUIRE(table3(1, 1) == 1);
    REQUIRE(table3(5, 4) == 5);

    REQUIRE(table2.numCols() == 5);
    REQUIRE(table2.numRows() == 5);
    REQUIRE(table3.numCols() == 5);
    REQUIRE(table3.numRows() == 5);

}
TEST_CASE("move semantics", "[Table]") {
    Table<int> table;
    // append a column named "C2" filled with 2's
    table.appendCol("C2", 2);
    // insert a column at Column 1 named "C1" filled with 1's
    table.insertCol(1, "C1", 1);
    // insert a column at Column 3 named "C3" filled with 3's
    table.insertCol(3, "C3", 3);
    // append a column named "C4" filled with 4's
    table.appendCol("C4", 4);
    // append three row filled with 2's, 3's, and 4's
    table.appendRow(2);
    table.appendRow(3);
    table.appendRow(4);
    // insert a row at 1 filled with 1's
    table.insertRow(1, 1);
    // insert a row at 5 filled with 5's
    table.insertRow(5, 5);
    table.appendCol("C5", 100);

    Table<int> table1 = std::move(table);
    REQUIRE(table1.numCols() == 5);
    REQUIRE(table1.numRows() == 5);
    REQUIRE(table1.getHeader(2) == "C2");
    REQUIRE(table1(1, 1) == 1);
    REQUIRE(table1(5, 4) == 5);

    REQUIRE(table.numCols() == 0);
    REQUIRE(table.numRows() == 0);

    Table<int> table2;
    table2 = std::move(table1);
    REQUIRE(table2.numCols() == 5);
    REQUIRE(table2.numRows() == 5);
    REQUIRE(table2.getHeader(2) == "C2");
    REQUIRE(table2(1, 1) == 1);
    REQUIRE(table2(5, 4) == 5);

    REQUIRE(table1.numCols() == 0);
    REQUIRE(table1.numRows() == 0);
}