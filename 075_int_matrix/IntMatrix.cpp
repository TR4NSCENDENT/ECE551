#include "IntMatrix.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {}
IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c), rows(NULL) {
  rows = new IntArray * [r]();
  for (int i = 0; i < r; i++) {
    rows[i] = new IntArray(c);
  }
}
IntMatrix::IntMatrix(const IntMatrix & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns) {
  rows = new IntArray * [rhs.numRows]();
  for (int i = 0; i < rhs.numRows; i++) {
    rows[i] = new IntArray(rhs[i]);
  }
}
IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}
IntMatrix &IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    IntArray ** temp = new IntArray * [rhs.numRows]();
    for (int i = 0; i < rhs.numRows; i++) {
      temp[i] = new IntArray(rhs[i]);
    }
    for (int i = 0; i < numRows; i++) {
      if (rows[i] != NULL) { delete rows[i]; }
    }
    delete[] rows;
    rows = temp;
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
  }
  return *this;
}
int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert(index < numRows && index >= 0);
  return *rows[index];
}
IntArray & IntMatrix::operator[](int index){
  assert(index < numRows && index >= 0);
  return *rows[index];
}



bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (this == &rhs) { return true; }
  if (numRows != rhs.numRows || numColumns != rhs.numColumns) { 
    return false; 
  }
  for (int i = 0; i < numRows; i++) {
    if (*rows[i] != rhs[i]) { return false; }
  }
  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
  IntMatrix ans(numRows, numColumns);
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      ans[i][j] = (*rows[i])[j] + rhs[i][j];
    }
  }
  return ans;
}


std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  int r = rhs.getRows();
  s << "[ ";
  for (int i = 0; i < r; i++) {
    s << rhs[i];
    if (i < r - 1) { s << ",\n"; }
  }
  s << " ]";
  return s;
}
