#include "Matrix.h"
#include <stdexcept>
#include <iostream>

Matrix::Matrix(unsigned rows, unsigned cols)
{
    rows_ = rows;
    cols_ = cols;
    if (rows == 0 || cols == 0)
        throw std::out_of_range("Matrix constructor has 0 size");
    data_ = new double[rows*cols];
}

Matrix::Matrix(unsigned rows, unsigned cols, double mat[])
{
    rows_ = rows;
    cols_ = cols;
    if (rows == 0 || cols == 0)
        throw std::out_of_range("Matrix constructor has 0 size");
    data_ = new double[rows*cols];
    for (int i = 0; i < rows*cols; i++) {
        data_[i] = mat[i];
    }
}

Matrix::Matrix(unsigned rows, unsigned cols, double mat[][cols])
{
    rows_ = rows;
    cols_ = cols;
    if (rows == 0 || cols == 0)
        throw std::out_of_range("Matrix constructor has 0 size");
    data_ = new double[rows*cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data_[i*j] = mat[i][j];
        }
    }
}

Matrix::~Matrix()
{
    delete[] data_;
}

double& Matrix::operator() (unsigned row, unsigned col)
{
    if (row >= rows_ || col >= cols_)
        throw std::out_of_range("Matrix subscript out of bounds");
    return data_[cols_*row + col];
}

double Matrix::operator() (unsigned row, unsigned col) const
{
    if (row >= rows_ || col >= cols_)
        throw std::out_of_range("const Matrix substript out of bounds");
    return data_[cols_*row + col];
}