// Importing Standard Libraries
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

// Importing custom modules
#include "modules/matrix/matrix.h"
#include "modules/readFiles/readFiles.h"
#include "modules/forwardChecking/forwardChecking.h"

int main(){
  auto start_time = chrono::high_resolution_clock::now();
  int size = 0;
  vector<Matrix *> matrices = readFile("./data/tai12a.dat");
  size = matrices[0]->getSize();
  cout << "Size: " << size << endl;

  ForwardChecking fc(size);
  fc.setFlow(matrices[0]);
  fc.setDistance(matrices[1]);
  fc.solve();
  fc.printResult();


  auto end_time = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() / 1000000.0;
  cout << "Duración del tiempo de ejecución: " << duration << " segundos" << endl;
  return 0;
}