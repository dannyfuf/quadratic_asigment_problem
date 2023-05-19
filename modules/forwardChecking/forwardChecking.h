#ifndef FORWARD_CHECKING_H
#define FORWARD_CHECKING_H

#include <vector>
#include "../matrix/matrix.h"

struct Result {
  int cost;
  int time;
  vector<int> assignment;
};

class ForwardChecking {
  public:
    ForwardChecking(int n);
    ~ForwardChecking();
    void printFlowMatrix();
    void printDistanceMatrix();
    void printResult(double time);
    void solve();

    // setters
    void setFlow(Matrix* flow);
    void setDistance(Matrix* distance);

    // getters
    int getCost(int row, int col);

  private:
    int size;
    Matrix* costMatrix;
    Matrix* flow;
    Matrix* distance;
    Result* result;
};

#endif //FORWARD_CHECKING_H