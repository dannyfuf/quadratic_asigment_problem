#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "matrix.h"
using MM = vector<vector<int>>;

// ------------------------------
// Matrix Methods implementation
// ------------------------------
// constructor
Matrix::Matrix(int rows, int cols) {
  this->rows = rows;
  this->cols = cols;
}

// destructor
Matrix::~Matrix() {
  for (int i = 0; i < rows; i++) {
    matrix[i].clear();
  }
  matrix.clear();
}

// imprime la matriz
void Matrix::print() {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cout << matrix[i][j] << " ";
    }
    cout << std::endl;
  }
}

// getters

// retorna un elemento de la matriz
int Matrix::getElement(int row, int col) {
  return matrix[row][col];
}

// retorna el tamaño de la matriz
int Matrix::getSize() {
  return rows;
}


// setters
// almacenar un elemento en la matriz
void Matrix::setElement(int row, int col, int value) {
  matrix[row][col] = value;
}

// almacenar una matriz en el objeto
void Matrix::setMatrix(MM matrix) {
  this->matrix = matrix;
}

// crear una matriz de ceros
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