using MM = vector<vector<int>>;

class Matrix {
  public:
    Matrix(int rows, int cols);
    ~Matrix();
    void print();
    void setMatrix(MM matrix);
    int getElement(int row, int col);
    
  private:
    int rows;
    int cols;
    MM matrix;
};