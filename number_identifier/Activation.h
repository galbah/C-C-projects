#include "Matrix.h"

#ifndef ACTIVATION_H
#define ACTIVATION_H

// Insert Activation class here...

typedef Matrix (*ActivFunc) (const Matrix &matrix);

namespace activation
{
    // returns a vector that its values are not-negative number
    // and there sum is 1
    Matrix softmax (const Matrix &m);

    // makes all negative values 0
    Matrix relu (const Matrix &m);
};

#endif //ACTIVATION_H