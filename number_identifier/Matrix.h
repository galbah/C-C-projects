// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>
#include <cmath>

/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
    int rows, cols;
} matrix_dims;

// Insert Matrix class here...

class Matrix
{
 private:

  float **mat;
  int rows;
  int cols;

 public:

  // constructors
  Matrix (int rows, int cols);
  Matrix ();
  Matrix (const Matrix &m);

  // destructor
  ~Matrix ();

  // getters
  int get_rows () const;
  int get_cols () const;

  Matrix &transpose (); // converts a matrix to its transpose
  Matrix &vectorize (); // converts a matrix to a vector
  void plain_print () const; // prints the matrix's value by index

  /**
   * multiples 2 matrix by matching coordinates
   * @param m matrix
   * @return a new matrix after the multiplication
   */
  Matrix dot (Matrix const &m) const;

  /**
   * returns the normalization value of a matrix
   * @return the square root of the sum of all matrix value power by 2
   */
  float norm () const;

  // operators

  // returns a new matrix - sum of the 2
  Matrix operator+ (Matrix const &m) const;
  // copies rhs matrix value to the lhs matrix
  Matrix &operator= (const Matrix &m);
  // returns a new matrix - the multiplication of the 2
  Matrix operator* (Matrix const &m) const;
  // returns a new matrix - the multiplication of the matrix with c
  Matrix operator* (float c) const;
  // same as prev - supports multiplication of c from the left
  friend Matrix operator* (float c, Matrix const &m);
  // adds the rhs matrix values to lhs matrix value
  Matrix &operator+= (Matrix const &m);
  // supports access to matrix value by m(i,j)
  float &operator() (int row, int col);
  float operator() (int row, int col) const;
  // supports access to matrix value by 1 index
  float &operator[] (int i);
  float operator[] (int i) const;

  /**
   * prints the matrix as a picture - '**' for a color, '  ' for blank
   * @param s output stream
   * @param m the output matrix
   * @return the stream to support chaining
   */
  friend std::ostream &operator<< (std::ostream &s, const Matrix &m);

  /**
   * reads a file into a matrix - fills it value from the file
   * @param is the stream of the file
   * @param m the matrix to fill
   * @return the stream to support chaining
   */
  friend std::istream &operator>> (std::ifstream &is, Matrix &m);
};

#endif //MATRIX_H