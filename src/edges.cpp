#include "edges.h"
#include <vector>
#include <set>
Eigen::MatrixXi edges(const Eigen::MatrixXi &F)
{
  Eigen::MatrixXi E;
  // ADD YOUR CODE HERE
  typedef std::pair<int,int> IJ;
  std::vector<IJ> edge_pairs(F.size());
  int cols = F.cols();
  int rows = F.rows();
  int offset = cols;
#pragma omp parallel for default(none) shared(F,edge_pairs,rows,cols,offset)
  for (int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++) {
      int s = F(i, j);
      int e = F(i, (j+1)%cols);
      if(s > e)
        std::swap(s,e);
      edge_pairs[i * offset + j] = IJ(s, e);
    }
  }
  std::set<IJ> edge_set(edge_pairs.begin(),edge_pairs.end());
  E = Eigen::MatrixXi(edge_set.size(),2);
  int i = 0;
  for(auto it: edge_set)
  {
    E.row(i++) = Eigen::Vector2i(it.first,it.second);
  }
  return E;
}
