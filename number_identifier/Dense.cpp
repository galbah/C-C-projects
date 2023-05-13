#include "Dense.h"

Dense::Dense(Matrix& weights, Matrix& bias, ActivFunc activ_func)
{
  this->activ_func = activ_func;
  this->bias = bias;
  this->weights = weights;
}

Matrix Dense::get_weights () const
{
  return this->weights;
}

Matrix Dense::get_bias () const
{
  return this->bias;
}

ActivFunc Dense::get_activation () const
{
  return this->activ_func;
}

Matrix Dense::operator() (Matrix& mat)
{
  return activ_func ((weights * mat) + bias);
}

