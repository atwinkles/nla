#include "Matrix.h"
#include <stdexcept>
#include <iostream>

template<class T>
Matrix<T>::Matrix(unsigned rows, unsigned cols)
{
    rows_ = rows;
    cols_ = cols;
    if (rows == 0 || cols == 0)
        throw std::out_of_range("Matrix constructor has 0 size");
    data_ = new T[rows*cols];
}

template<class T>
Matrix<T>::Matrix(unsigned rows, unsigned cols, T mat[])
{
    rows_ = rows;
    cols_ = cols;
    if (rows == 0 || cols == 0)
        throw std::out_of_range("Matrix constructor has 0 size");
    data_ = new T[rows*cols];
    for (int i = 0; i < rows*cols; i++) {
        data_[i] = mat[i];
    }
}

template<class T>
unsigned Matrix<T>::row_size() const
{
    return rows_;
}

template<class T>
unsigned Matrix<T>::col_size() const
{
    return cols_;
}

template<class T>
Matrix<T>::~Matrix()
{
    delete[] data_;
}

template<class T>
void Matrix<T>::print()
{
    for (unsigned i = 0; i < rows_; i++)
    {
        std::cout << "|";
        for (unsigned j = 0; j < cols_; j++)
        {
            std::cout << (*this)(i,j) << " ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::endl;
}

template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& n)
{
    unsigned row = rows_;
    unsigned col = cols_;
    if (row != n.row_size() || col != n.col_size())
        throw std::out_of_range("Matrices are not the same size");
    Matrix<T> result(row,col);
    for (unsigned i = 0; i < row; i++)
    {
        for (unsigned j = 0; j < col; j++)
        {
            result(i,j) = (*this)(i,j) + n(i,j);
        }
    }
    return result;
}

template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& n)
{
    unsigned row = rows_;
    unsigned col = cols_;
    if (col != n.row_size())
        throw std::out_of_range("Matrices are not the same size");
    Matrix<T> result(row,n.col_size());
    for (unsigned i = 0; i < row; i++)
    {
        for (unsigned j = 0; j < col; j++)
        {
            result(i,j) = 0;
            for (unsigned k = 0; k < col; k++) {
                result(i,j) += (*this)(i,k) * n(k,j);
            }
        }
    }
    return result;
}

/*template<class T>
Matrix<T> Matrix<T>::operator*(Matrix<T> m, const Matrix<T> k)
{
    m *= k;
    return m;
}*/

template<class T>
Matrix<T> Matrix<T>::operator*(const T& k)
{
    T data[rows_*cols_];
    for (unsigned i = 0; i < rows_*cols_; i++) {
        data[i] = k * data_[i];
    }
    Matrix<T> result(rows_,cols_,data);
    return result;
}

template<class T>
T& Matrix<T>::operator() (unsigned row, unsigned col)
{
    if (row >= rows_ || col >= cols_)
        throw std::out_of_range("Matrix subscript out of bounds");
    return data_[cols_*row + col];
}

template<class T>
T Matrix<T>::operator() (unsigned row, unsigned col) const
{
    if (row >= rows_ || col >= cols_)
        throw std::out_of_range("const Matrix substript out of bounds");
    return data_[cols_*row + col];
}

/* Explicit instantiating several data types */
template class Matrix<double>;
template class Matrix<int>;
template class Matrix<float>;