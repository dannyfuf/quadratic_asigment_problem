#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "../matrix/matrix.h"

Matrix readMatrix(ifstream * file, int n){
  Matrix matrix(n, n);
  MM matrixData;
  for(int i = 0; i < n; i++) {
    vector<int> row;
    for(int j = 0; j < n; j++) {
      int value;
      *file >> value;
      row.push_back(value);
    }
    matrixData.push_back(row);
  }
  matrix.setMatrix(matrixData);
  return matrix;
}

vector<Matrix> readFile(string filename) {
  ifstream file (filename);
  string line;

  vector<Matrix> returnMatrices;

  int n = 0;
  if (file.is_open()) {
    file >> n;
    returnMatrices.push_back(readMatrix(&file, n));
    returnMatrices.push_back(readMatrix(&file, n));
    file.close();
  }
  else{
    cout << "Unable to open file"; 
  }
  return returnMatrices;
}

