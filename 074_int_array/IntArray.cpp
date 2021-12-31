#include "IntArray.h"
#include <assert.h>
#include <ostream>

IntArray::IntArray() : data(NULL), numElements(0) {}
IntArray::IntArray(int n) : numElements(n) {
  if (n < 1) { data = NULL; }
  else {
    data = new int[n];
    for (int i = 0; i < n; i++) {
      data[i] = 0;
    }
  }
}

IntArray::IntArray(const IntArray & rhs)  {
  numElements = rhs.numElements;
  if (rhs.data == NULL) { data = NULL; }
  else {
    data = new int[numElements];
    for (int i = 0; i < numElements; i++) {
      data[i] = rhs.data[i];
    }
  }
}

IntArray::~IntArray() {
  if (data != NULL) {
    delete[] data;
  }
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    numElements = rhs.numElements;
    if (rhs.data == NULL) { 
      data = NULL; 
      return *this;
    }
    int * temp = new int[numElements];
    for (int i = 0; i < numElements; i++) {
      temp[i] = rhs.data[i];
    }
    if (data != NULL) { delete[] data; }
    data = temp;
    
  }
  return *this;
}

const int & IntArray::operator[](int index) const {
  assert(index < numElements && index >= 0);
  assert(data != NULL);
  return data[index];
}
int & IntArray::operator[](int index) {
  assert(index < numElements && index >= 0);
  assert(data != NULL);
  return data[index];
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (this == &rhs) { return true; }
  if (numElements != rhs.numElements) { return false; }
  if (data != rhs.data) {
    if (data == NULL || rhs.data == NULL) { return false; }
    for (int i = 0; i < numElements; i++) {
      if (data[i] != rhs.data[i]) { return false; }
    }
  }
  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  return !(*this == rhs);
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  int n = rhs.size();
  if (n < 1) {
    s << "{}";
    return s;
  }
  s << "{";
  for (int i = 0; i < n - 1; i++) {
    s << rhs[i] << ", ";
  }
  s << rhs[n - 1] <<  "}";
  return s;
}
