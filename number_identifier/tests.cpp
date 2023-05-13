#include "Matrix.h"

int main (int argc, char **argv)
{
  Matrix m1 (28, 28);
  Matrix m2 (28, 28);
  Matrix m3;
  m3.plain_print();
  m3.transpose();
  m3.plain_print();
  m3.vectorize();
  m3.plain_print();
  m3.norm();
  m3.plain_print();
//  std::ifstream rf1("../images/im2", std::ios::out | std::ios::binary);
//  std::ifstream rf2("../images/im4", std::ios::out | std::ios::binary);
//  rf1 >> m1;
//  rf2 >> m2;
//  m2.plain_print();
//  m2.transpose();
//  m2.plain_print();
  return 0;
}