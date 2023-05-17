#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#define M vector<vector<int>>

class Matrix {
  public:
    Matrix(int rows, int cols);
    ~Matrix();
    void print();
    
    // getters
    int getElement(int row, int col);
    int getSize();
    
    // setters
    void setElement(int row, int col, int value);
    void setMatrix(M matrix);
    void setZeroMatrix(int row, int col);

  private:
    int rows;
    int cols;
    M matrix;
};

#endif //MATRIX_H