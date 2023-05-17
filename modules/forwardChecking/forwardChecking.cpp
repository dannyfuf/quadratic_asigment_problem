#include <iostream>
#include <omp.h>
#include <vector>
#include <algorithm>
#include <thread>
using namespace std;

#include "forwardChecking.h"
#include "../matrix/matrix.h"

ForwardChecking::ForwardChecking(int n) {
  this->size = n;
}

ForwardChecking::~ForwardChecking() {
}


void ForwardChecking::printFlowMatrix() {
  flow->print();
}

void ForwardChecking::printDistanceMatrix() {
  distance->print();
}

void ForwardChecking::printResult() {
  cout << "Cost: " << result->cost << endl;
  cout << "Time: " << result->time << endl;
  cout << "Assignment: ";
  for (auto i: result->assignment) {
    cout << i << " ";
  }
  cout << endl;
}

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

vector<int> getAvailableResources(vector<int> locations, vector<int> currentAssignment){
  vector<int> availableLocations;
  for(auto i: locations){
    if(find(currentAssignment.begin(), currentAssignment.end(), i) == currentAssignment.end()){
      availableLocations.push_back(i);
    }
  }
  return availableLocations;
}

vector<int> getRemainingLocations(vector<int> currentAssignment){
  vector<int> remainingLocations;
  for(long unsigned int i = 0; i < currentAssignment.size(); i++){
    if(currentAssignment[i] == -1){
      remainingLocations.push_back(i);
    }
  }
  return remainingLocations;
}

void printVector(vector<int> vec){
  for(auto i: vec){
    cout << i << " ";
  }
  cout << endl;
}

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

int countAssigned(vector<int> assigned){
  int count = 0;
  for(auto i: assigned){
    if(i >= 0){
      count++;
    }
  }
  return count;
}

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

void ForwardChecking::setFlow(Matrix* flow) {
  this->flow = flow;
}

void ForwardChecking::setDistance(Matrix* distance) {
  this->distance = distance;
}


// getters
int ForwardChecking::getCost(int row, int col) {
  return costMatrix->getElement(row, col);
}



  // for(auto i: locations){
  //   vector<int> currentAssignment = {i};
  //   vector<int> leftLocations = getAvailableLocations(locations, currentAssignment);

  //   for(auto j: leftLocations){
  //     vector<int> availableLocations = getAvailableLocations(locations, currentAssignment);
  //     currentCost = getCost(i, j);
  
  //     int tmpMinCost = 999999999;
  //     int tmpMinIndex = -1;
  //     for(auto k: availableLocations){
  //       if(getCost(i, k) < tmpMinCost){
  //         tmpMinCost = getCost(i, k);
  //         tmpMinIndex = k;
  //       }
  //     }
  //     currentCost += tmpMinCost;
  //     currentAssignment.push_back(tmpMinIndex);
  //   }

  //   if(currentCost < minCost){
  //     minCost = currentCost;
  //     result->assignment = currentAssignment;
  //   }
  // }

  // result->cost = minCost;
  // this->result = result;