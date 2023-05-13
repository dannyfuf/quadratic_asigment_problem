// Importing Standard Libraries
#include <iostream>
#include <vector>
using namespace std;

// Importing custom modules
#include "modules/readFiles/readFiles.h"

int main(){
  vector<Matrix> matrices = readFile("./data/nug14.dat");
  matrices[0].print();
  cout << endl;
  matrices[1].print();
  return 0;
}