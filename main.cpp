// Importing Standard Libraries
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

// Importing custom modules
#include "modules/matrix/matrix.h"
#include "modules/readFiles/readFiles.h"
#include "modules/forwardChecking/forwardChecking.h"

int main( int argc, char** argv ){
  auto start_time = chrono::high_resolution_clock::now();
  int size = 0;
  vector<Matrix *> matrices = readFile(argv[1]);
  size = matrices[0]->getSize();

  ForwardChecking fc(size);
  fc.setFlow(matrices[0]);
  fc.setDistance(matrices[1]);
  fc.solve();


  auto end_time = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() / 1000000.0;
  fc.printResult(duration);
  return 0;
}