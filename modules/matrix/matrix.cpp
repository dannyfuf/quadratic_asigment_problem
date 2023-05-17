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

// getters
int Matrix::getElement(int row, int col) {
  return matrix[row][col];
}

int Matrix::getSize() {
  return rows;
}


// setters

void Matrix::setElement(int row, int col, int value) {
  matrix[row][col] = value;
}

void Matrix::setMatrix(MM matrix) {
  this->matrix = matrix;
}

void Matrix::setZeroMatrix(int row, int col) {
  MM matrix;
  for (int i = 0; i < row; i++) {
    vector<int> row;
    for (int j = 0; j < col; j++) {
      row.push_back(0);
    }
    matrix.push_back(row);
  }
  this->matrix = matrix;
}