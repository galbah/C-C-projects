#include "MlpNetwork.h"
#include "Dense.h"
#include "Activation.h"

MlpNetwork::MlpNetwork (Matrix *weights, Matrix *biases)
{
  for(int i = 0 ; i < MLP_SIZE ; i++)
  {
    this->weights[i] = weights[i];
    this->biases[i] = biases[i];
  }
}

digit MlpNetwork::operator() (const Matrix& m)
{
  Matrix cur = m;
  for(int i = 0 ; i < MLP_SIZE ; ++i)
  {
    if (i != MLP_SIZE - 1){
      Dense layer (weights[i], biases[i], activation::relu);
      cur = layer (cur);
    }
    else{
      Dense layer (weights[MLP_SIZE - 1], biases[MLP_SIZE - 1],
                      activation::softmax);
      cur = layer(cur);
    }
  }
  float prob = 0;
  unsigned int best_prob_index;
  for(int i = 0 ; i < cur.get_rows() ; i++)
  {
    if (cur[i] > prob)
    {
      prob = cur[i];
      best_prob_index = i;
    }
  }
  digit dig = {best_prob_index, prob};
  return dig;
}


