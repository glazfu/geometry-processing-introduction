#include "euler_characteristic.h"
#include "edges.h"
int euler_characteristic(const Eigen::MatrixXi &F)
{
  int Chi = 0;
  // ADD YOUR CODE HERE
  int v_max_num = F.maxCoeff()+1;
  Eigen::VectorXi v_exist = Eigen::VectorXi::Zero(v_max_num);

#pragma omp parallel for default(none) shared(v_exist,v_max_num)
  for(int i = 0; i < v_max_num; i++)
  {
    v_exist[i] = 1;
  }
  int e = edges(F).rows();
  int f = F.rows();
  int v = v_exist.sum();
  Chi = v - e + f;

  return Chi;
}
