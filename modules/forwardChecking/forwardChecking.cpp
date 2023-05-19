#include <iostream>
#include <omp.h>
#include <vector>
#include <algorithm>
#include <thread>
using namespace std;

#include "forwardChecking.h"
#include "../matrix/matrix.h"

// constructor
ForwardChecking::ForwardChecking(int n) {
  this->size = n;
}

// destructor
ForwardChecking::~ForwardChecking() {
}

// imprime la matriz de flujo
void ForwardChecking::printFlowMatrix() {
  flow->print();
}

// imprime la matriz de distancia
void ForwardChecking::printDistanceMatrix() {
  distance->print();
}

// imprime un vector dado
void printVector(vector<int> vec){
  for(auto i: vec){
    cout << i << " ";
  }
  cout << endl;
}

// recibe el tiempo de ejecucion e imprime el costo, tiempo y la permutacion asignada
void ForwardChecking::printResult(double time) {
  cout << result->cost << " " << time << endl;
  cout << size << endl;
  printVector(result->assignment);
}

// inicializa un vector con numeros de 0 a size-1 o con -1 en cada posicion
vector<int> initializeDomains(int size, bool range = true ) {
  vector<int> domains;
  for (int i = 0; i < size; i++) {
    if(range){
      domains.push_back(i);
    } else {
      domains.push_back(-1);
    }
  }
  return domains;
}

// funcion que recibe los nombres de los recursos y la asignacion actual y retorna los recursos disponibles
vector<int> getAvailableResources(vector<int> resources, vector<int> currentAssignment){
  vector<int> availableLocations;
  for(auto i: resources){
    if(find(currentAssignment.begin(), currentAssignment.end(), i) == currentAssignment.end()){
      availableLocations.push_back(i);
    }
  }
  return availableLocations;
}

// funcion que recibe la asignacion actual y retorna las ubicaciones que no han sido asignadas
vector<int> getRemainingLocations(vector<int> currentAssignment){
  vector<int> remainingLocations;
  for(long unsigned int i = 0; i < currentAssignment.size(); i++){
    if(currentAssignment[i] == -1){
      remainingLocations.push_back(i);
    }
  }
  return remainingLocations;
}

// funcion que recibe la asignacion actual y retorna el costo de la asignacion
int computeCost(vector<int> assigned, Matrix* flow, Matrix* distance){
  int cost = 0;

  for(long unsigned int i = 0; i < assigned.size(); i++){
    for(long unsigned int j = 0; j < assigned.size(); j++){
      if(assigned[i]  >= 0 && assigned[j] >= 0){
        cost += flow->getElement(assigned[i], assigned[j]) * distance->getElement(i, j);
      }
    }
  }
  return cost;
}

// funcion que recibe la asignacion actual y retorna el numero de ubicaciones asignadas
int countAssigned(vector<int> assigned){
  int count = 0;
  for(auto i: assigned){
    if(i >= 0){
      count++;
    }
  }
  return count;
}

// funcion que recibe la asignacion actual, un puntero a la matriz de flujo, un puntero a la matriz de distancia, un vector con los recursos disponibles y un vector de vectores con los resultados de cada thread
// aplica el algoritmo de forward checking y retorna la asignacion con menor costo encontrada, asignada al en el vector de resultados de cada thread
vector<int> applyAlgorithm(vector<int> assignment, Matrix* flow, Matrix* distance, vector<int> resources, vector<vector<int>>& resultsThreads){
  vector<int> remainingLocations = getRemainingLocations(assignment);
  vector<int> availableResources = getAvailableResources(resources, assignment);
  vector<int> currentAssignment(assignment);
  vector<int> best;
  if(availableResources.size() == 1){
    assignment[remainingLocations[0]] = availableResources[0];
    return assignment;
  } else {
    int minCost = 999999999;
    #pragma omp parallel for shared(minCost, best, currentAssignment, availableResources, remainingLocations, flow, distance, resources, resultsThreads)
    for(auto i: availableResources){
      vector<int> currentAssignment(assignment);
      currentAssignment[remainingLocations[0]] = i;
      currentAssignment = applyAlgorithm(currentAssignment, flow, distance, resources, resultsThreads);
      int currentCost = computeCost(currentAssignment, flow, distance);
      if(currentCost < minCost){
        minCost = currentCost;
        best = currentAssignment;
      }
    }
    resultsThreads[assignment[0]] = best;
    return best;
  }
}

// funcion que aplica el algoritmo de forward checking utilizando threads
void ForwardChecking::solve(){
  Result* result = new Result();
  result->cost = 0;
  result->time = 0;


  vector<int> locations = initializeDomains(size);
  vector<int> resources = initializeDomains(size);
  vector<int> assignment = initializeDomains(size, false);

  vector<vector<int>> resultsThreads(size);
  vector<thread> threads;
  threads.reserve(size);

  for(int i = 0; i < size; ++i){
    assignment[0] = i;
    threads.emplace_back(applyAlgorithm, assignment, flow, distance, resources, ref(resultsThreads));
  }

  for(auto& thread: threads){
    thread.join();
  }

  int minCost = 999999999;
  for(auto i: resultsThreads){
    int currentCost = computeCost(i, flow, distance);
    if(currentCost < minCost){
      minCost = currentCost;
      result->assignment = i;
    }
  }

  result->cost = minCost;
  this->result = result;
}

//  funcion que almacena la matriz de flujo
void ForwardChecking::setFlow(Matrix* flow) {
  this->flow = flow;
}

// funcion que almacena la matriz de distancia
void ForwardChecking::setDistance(Matrix* distance) {
  this->distance = distance;
}