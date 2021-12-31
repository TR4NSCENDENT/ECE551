#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>

template <typename T> class Matrix;

template <typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs);

template <typename T>
class Matrix {
private:
  int numRows;
  int numColumns;
  std::vector<T> ** rows;
public:
  Matrix(): numRows(0), numColumns(0), rows(NULL) {}
  Matrix(int r, int c): numRows(r), numColumns(c), rows(NULL) {
    rows = new std::vector<T> * [r]();
    for (int i = 0; i < r; i++) {
      rows[i] = new std::vector<T>(c);
    }
  }
  Matrix(const Matrix & rhs): numRows(rhs.numRows), numColumns(rhs.numColumns) {
    rows = new std::vector<T> * [rhs.numRows]();
    for (int i = 0; i < rhs.numRows; i++) {
      rows[i] = new std::vector<T>(rhs[i]);
    }
  }
  ~Matrix() {
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
  }
  Matrix & operator=(const Matrix & rhs) {
    if (this != &rhs) {
      std::vector<T> ** temp = new std::vector<T> * [rhs.numRows]();
      for (int i = 0; i < rhs.numRows; i++) {
        temp[i] = new std::vector<T>(rhs[i]);
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
  int getRows() const {
    return numRows;
  }
  int getColumns() const {
    return numColumns;
  }
  const std::vector<T> & operator[](int index) const {
    assert(index < numRows && index >= 0);
    return *rows[index];
  }
  std::vector<T> & operator[](int index) {
    assert(index < numRows && index >= 0);
    return *rows[index];
  }
  bool operator==(const Matrix & rhs) const {
    if (this == &rhs) { return true; }
    if (numRows != rhs.numRows || numColumns != rhs.numColumns) { 
      return false; 
    }
    for (int i = 0; i < numRows; i++) {
      if (*rows[i] != rhs[i]) { return false; }
    }
    return true;
  }
  Matrix operator+(const Matrix & rhs) const {
    assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
    Matrix ans(numRows, numColumns);
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        ans[i][j] = (*rows[i])[j] + rhs[i][j];
      }
    }
    return ans;
  }
  friend std::ostream & operator<< <T>(std::ostream & s, const Matrix<T> & rhs);
};

template <typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  int r = rhs.getRows();
  int c = rhs.getColumns();
  s << "[ ";
  for (int i = 0; i < r; i++) {
    s << "{";
    for (int j = 0; j < c; j++) {
      s << rhs[i][j];
      if (j < c - 1) { s << ", "; }
    }
    s << "}";
    if (i < r - 1) { s << ",\n"; }
  }
  s << " ]";
  return s;
}

#endif
