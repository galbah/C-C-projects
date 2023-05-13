#include "Activation.h"
#include <cmath>


Matrix activation::relu(const Matrix& m)
{
  Matrix temp = m;
  for(int i = 0 ; i < temp.get_cols() * temp.get_rows() ; i++)
  {
    if (temp[i] < 0)
    {
      temp[i] = 0;
    }
  }
  return temp;
}

Matrix activation::softmax(const Matrix& m)
{
  float sum = 0;
  Matrix new_mat (m.get_rows(), m.get_cols());
  for (int i = 0 ; i < m.get_cols() * m.get_rows() ; i++)
  {
    sum += expf( m[i]);
    new_mat[i] = expf(m[i]);
  }
  return new_mat * (1/sum);
}