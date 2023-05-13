#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"

// Insert Dense class here...

class Dense
{
 private:
  Matrix weights;
  Matrix bias;
  ActivFunc activ_func;

 public:

  // constructor
  Dense(Matrix& weights, Matrix& bias, ActivFunc activ_func);

  // getters
  Matrix get_weights() const;
  Matrix get_bias() const;
  ActivFunc get_activation() const;

  // activates the function on 2 matrix
  Matrix operator() (Matrix& mat);
};

#endif //DENSE_H
