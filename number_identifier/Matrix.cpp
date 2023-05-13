#include "Matrix.h"

#define MIN_COLOR_VAL 0.1
#define DEFAULT_MATRIX_VALUE 0
#define DEFAULT_ROWS_SIZE 1
#define DEFAULT_COLS_SIZE 1

Matrix::Matrix (const int rows, const int cols)
{
  if (rows < 1 || cols < 1)
  {
    throw std::length_error ("matrix size should be positive integers");
  }
  this->rows = rows;
  this->cols = cols;
  this->mat = new float *[rows];
  for (int i = 0; i < rows; i++)
  {
    this->mat[i] = new float[cols];
  }
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      this->mat[i][j] = 0;
    }
  }
}

Matrix::Matrix ()
{
  this->rows = DEFAULT_ROWS_SIZE;
  this->cols = DEFAULT_COLS_SIZE;
  this->mat = new float *[DEFAULT_ROWS_SIZE];
  for (int i = 0; i < DEFAULT_ROWS_SIZE; i++)
  {
    this->mat[i] = new float[DEFAULT_COLS_SIZE];
  }
  for (int i = 0; i < DEFAULT_ROWS_SIZE; i++)
  {
    for (int j = 0; j < DEFAULT_COLS_SIZE; j++)
    {
      this->mat[i][i] = DEFAULT_MATRIX_VALUE;
    }
  }
}

Matrix::Matrix (const Matrix &m)
{
  this->rows = m.rows;
  this->cols = m.cols;
  this->mat = new float *[m.rows];
  for (int i = 0; i < m.rows; i++)
  {
    this->mat[i] = new float[m.cols];
  }
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      this->mat[i][j] = m.mat[i][j];
    }
  }
}

Matrix::~Matrix ()
{
  for (int i = 0; i < this->rows; i++)
  {
    delete[] this->mat[i];
  }
  delete[] this->mat;
}

int Matrix::get_rows () const
{
  return this->rows;
}

int Matrix::get_cols () const
{
  return this->cols;
}

Matrix &Matrix::transpose ()
{
  Matrix temp (*this);
  *this = Matrix (temp.cols, temp.rows);
  for (int i = 0; i < temp.rows; i++)
  {
    for (int j = 0; j < temp.cols; j++)
    {
      this->mat[j][i] = temp.mat[i][j];
    }
  }
  return *this;
}

Matrix &Matrix::vectorize ()
{
  Matrix temp = *this;
  for (int i = 0; i < this->rows; i++)
  {
    delete[] this->mat[i];
  }
  delete[] this->mat;
  this->rows = temp.rows * temp.cols;
  this->cols = 1;
  this->mat = new float *[temp.rows * temp.cols];
  for (int i = 0; i < this->rows; i++)
  {
    this->mat[i] = new float[1];
  }
  for (int i = 0; i < temp.rows; i++)
  {
    for (int j = 0; j < temp.cols; j++)
    {
      this->mat[i * temp.cols + j][0] = temp.mat[i][j]; //no need 2 []
    }
  }
  return *this;
}

void Matrix::plain_print () const
{
  for (int i = 0; i < this->rows; i++)
  {
    for (int j = 0; j < this->cols; j++)
    {
      std::cout << this->mat[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

Matrix Matrix::dot (Matrix const &m) const
{
  if (m.rows != this->rows || m.cols != this->cols)
  {
    throw std::length_error ("Matrix sizes are not equal");
  }
  Matrix mult (this->rows, this->cols);
  for (int i = 0; i < this->rows; i++)
  {
    for (int j = 0; j < m.cols; j++)
    {
      mult.mat[i][j] += this->mat[i][j] * m.mat[i][j];
    }
  }
  return mult;
}

float Matrix::norm () const
{
  double square_sum = 0;
  for (int i = 0; i < this->rows; i++)
  {
    for (int j = 0; j < this->cols; j++)
    {
      square_sum += pow (this->mat[i][j], 2);
    }
  }
  return (float) sqrt (square_sum);
}

Matrix Matrix::operator+ (Matrix const &m) const
{
  if (m.rows != this->rows || m.cols != this->cols)
  {
    throw std::length_error ("Matrix sizes are not equal");
  }
  Matrix sum (this->rows, this->cols);
  for (int i = 0; i < this->rows; i++)
  {
    for (int j = 0; j < this->cols; j++)
    {
      sum.mat[i][j] = this->mat[i][j] + m.mat[i][j];
    }
  }
  return sum;
}

Matrix &Matrix::operator= (const Matrix &m)
{
  if (this == &m)
  {
    return *this;
  }
  for (int i = 0; i < this->rows; i++)
  {
    delete[] this->mat[i];
  }
  delete[] this->mat;
  this->rows = m.rows;
  this->cols = m.cols;
  this->mat = new float *[m.rows];
  for (int i = 0; i < m.rows; i++)
  {
    this->mat[i] = new float[m.cols];
  }
  for (int i = 0; i < this->rows; i++)
  {
    for (int j = 0; j < this->cols; j++)
    {
      this->mat[i][j] = m.mat[i][j];
    }
  }
  return *this;
}

Matrix Matrix::operator* (Matrix const &m) const
{
  if (m.rows != this->cols)
  {
    throw std::length_error ("Matrix sizes are not equal");
  }
  Matrix mult (this->rows, m.cols);
  for (int i = 0; i < this->rows; i++)
  {
    for (int j = 0; j < m.cols; j++)
    {
      for (int t = 0; t < m.rows; t++)
      {
        mult.mat[i][j] += this->mat[i][t] * m.mat[t][j];
      }
    }
  }
  return mult;
}

Matrix Matrix::operator* (float const c) const
{
  Matrix mult (this->rows, this->cols);
  for (int i = 0; i < this->rows; i++)
  {
    for (int j = 0; j < this->cols; j++)
    {
      mult.mat[i][j] = this->mat[i][j] * c;
    }
  }
  return mult;
}

Matrix operator* (float const c, Matrix const &m)
{
  Matrix mult (m.rows, m.cols);
  for (int i = 0; i < m.rows; i++)
  {
    for (int j = 0; j < m.cols; j++)
    {
      mult.mat[i][j] = m.mat[i][j] * c;
    }
  }
  return mult;
}

Matrix &Matrix::operator+= (Matrix const &m)
{
  if (m.rows != this->rows || m.cols != this->cols)
  {
    throw std::length_error ("Matrix sizes are not equal");
  }
  for (int i = 0; i < this->rows; i++)
  {
    for (int j = 0; j < this->cols; j++)
    {
      this->mat[i][j] += m.mat[i][j];
    }
  }
  return *this;
}

float &Matrix::operator() (int const row, int const col)
{
  if (row < 0 || row >= this->rows || col < 0 || col >= this->cols)
  {
    throw std::out_of_range ("not legal index");
  }
  return this->mat[row][col];
}

float &Matrix::operator[] (int i)
{
  int col = i % this->cols;
  int row = i / this->cols;
  if (row < 0 || row >= this->rows || col < 0 || col >= this->cols)
  {
    throw std::out_of_range ("not legal index");
  }
  return this->mat[row][col];
}

float Matrix::operator() (int const row, int const col) const
{
  if (row < 0 || row >= this->rows || col < 0 || col >= this->cols)
  {
    throw std::out_of_range ("not legal index");
  }
  return this->mat[row][col];
}

float Matrix::operator[] (int i) const
{
  int col = i % this->cols;
  int row = i / this->cols;
  if (row < 0 || row >= this->rows || col < 0 || col >= this->cols)
  {
    throw std::out_of_range ("not legal index");
  }
  return this->mat[row][col];
}

std::ostream &operator<< (std::ostream &s, const Matrix &m)
{
  for (int i = 0; i < m.rows; i++)
  {
    for (int j = 0; j < m.cols; j++)
    {
      if (m.mat[i][j] > MIN_COLOR_VAL)
      {
        std::cout << "**";
      }
      else
      {
        std::cout << "  ";
      }
    }
    std::cout << std::endl;
  }
  return s;
}

std::istream &operator>> (std::ifstream &is, Matrix &m)
{
  char *buffer = new char[sizeof (float)];
  for (int i = 0; i < m.get_rows() * m.get_cols(); i++)
  {
    if (is.read (buffer, sizeof (float)))
    {
      m[i] = *((float *) buffer);
    }
    else
    {
      delete[] buffer;
      throw std::out_of_range ("matrix bigger than file");
    }
  }
  if (is.read (buffer, 1))
  {
    delete[] buffer;
    throw std::out_of_range ("matrix bigger than file");
  }
  delete[] buffer;
  return is;
}