#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "../matrix/matrix.h"

// funcion que recibe el cursor de un archivo y lee una matriz de n x n
Matrix * readMatrix(ifstream * file, int n){
  Matrix * matrix = new Matrix(n, n);
  M matrixData;
  for(int i = 0; i < n; i++) {
    vector<int> row;
    for(int j = 0; j < n; j++) {
      int value;
      *file >> value;
      row.push_back(value);
    }
    matrixData.push_back(row);
  }
  matrix->setMatrix(matrixData);
  return matrix;
}

// Funcion que lee un archivo de instancia y retorna las matrices de costo y flujo
vector<Matrix *> readFile(string filename) {
  ifstream file (filename);
  string line;

  vector<Matrix *> returnMatrices;

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

