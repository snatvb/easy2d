#pragma once
#include <easy2d/lib/assert.hpp>

namespace easy2d
{

  class matrix
  {
    using size_t = decltype(sizeof(int));

  private:
    float *_table;
    size_t _rows;
    size_t _cols;

  public:
    matrix(size_t rows, size_t cols)
    {
      _table = new float[rows * cols]{0};
    }

    matrix(float m[], size_t rows, size_t cols)
    {
      set(m, rows, cols);
    }

    ~matrix()
    {
      delete _table;
    }

    matrix &set(float m[], size_t rows, size_t cols)
    {
      size_t length = rows * cols;
      _table = new float[length]{0};
      for (size_t i = 0; i < length; ++i)
      {
        _table[i] = m[i];
      }
      return *this;
    }

    matrix &insert(size_t row, size_t col, float value)
    {
      ASSERT(row > _rows, "Incorrect row: " << row);
      ASSERT(col > _cols, "Incorrect col: " << col);

      _table[row, col] = value;

      return *this;
    }

    float get(size_t row, size_t col)
    {
      ASSERT(row > _rows, "Incorrect row: " << row);
      ASSERT(col > _cols, "Incorrect col: " << col);

      return _table[row, col];
    }

    matrix operator*(matrix &m2)
    {
      ASSERT(_rows == m2._cols, "Error matrix multiply: " << _cols << " != " << m2._rows);

      matrix res(_rows, m2._cols);
      for (size_t i = 0; i < _rows; ++i)
      {
        for (size_t j = 0; j < m2._cols; ++j)
        {
          for (size_t k = 0; k < _cols; ++k)
          {
            res._table[i * m2._cols + j] += _table[i * _cols + k] * m2._table[k * m2._cols + j];
          }
        }
      }
      return res;
    }
  };
} // -- easy2d
