#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "matrix.h"
using MM = vector<vector<int>>;

// ------------------------------
// Matrix Methods implementation
// ------------------------------
Matrix::Matrix(int rows, int cols) {
  this->rows = rows;
  this->cols = cols;
}

Matrix::~Matrix() {
  for (int i = 0; i < rows; i++) {
    matrix[i].clear();
  }
  matrix.clear();
}

void Matrix::print() {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cout << matrix[i][j] << " ";
    }
    cout << std::endl;
  }
}

void Matrix::setMatrix(MM matrix) {
  this->matrix = matrix;
}

int Matrix::getElement(int row, int col) {
  return matrix[row][col];
}