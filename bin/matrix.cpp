#include <stdexcept>
#include <iostream>
#include "matrix.h"

/* PUBLIC MEMBER FUNCTIONS */

Matrix::Matrix(unsigned rows, unsigned cols)   // Constructor
{
    rows_ = rows;
    cols_ = cols;
    if (rows == 0 || cols == 0)
        throw std::out_of_range("Matrix constructor has 0 size");
    data_ = new double[rows*cols];
}
Matrix::Matrix(unsigned rows, unsigned cols, double mat[]) // Constructor
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
unsigned Matrix::row_size() const
{
    return rows_;
}
unsigned Matrix::col_size() const
{
    return cols_;
}
void Matrix::print()
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
double& Matrix::operator() (unsigned row, unsigned col) // Assigns value at (row,col)
{
    if (row >= rows_ || col >= cols_)
        throw std::out_of_range("Matrix subscript out of bounds");
    return data_[cols_*row + col];
}
double Matrix::operator() (unsigned row, unsigned col) const // Returns value at (row,col)
{
    if (row >= rows_ || col >= cols_)
        throw std::out_of_range("const Matrix substript out of bounds");
    return data_[cols_*row + col];
}
Matrix::~Matrix()   // Destructor
{
    delete[] data_;
}
Matrix::Matrix(const Matrix& m) : rows_(m.row_size()), cols_(m.col_size())             // Copy constructor
{
    for (unsigned i = 0; i< rows_; i++) {
        for (unsigned j = 0; j < cols_; j++) {
            data_[cols_*i + j] = m(i,j);
        }
    }
}

Matrix& Matrix::operator= (const Matrix& m)    // Assignment operator
{
    if (this == &m) {
        return *this;
    }
    
    if (rows_ != m.row_size() || cols_ != m.col_size()){
        delete[] data_;
        rows_ = m.row_size();
        cols_ = m.col_size();
        data_ = new double[rows_*cols_];
        for (unsigned i = 0; i < rows_; i++) {
            for (unsigned j = 0; j < cols_; j++)
            data_[cols_*i + j] = m(i,j);
        }
    }
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& rhs)
{
    if (cols_ != rhs.col_size() || rows_ != rhs.row_size())
        throw std::out_of_range("Matrices are not the same size");
    Matrix temp(rows_,cols_);
    for (unsigned i = 0; i < rows_; i++) {
        for (unsigned j = 0; j < cols_; j++) {
            temp(i,j) = data_[cols_*i + j] + rhs(i,j);
        }
    }
    return (*this = temp);
}

Matrix& Matrix::operator*=(const Matrix& rhs)
{
    if (cols_ != rhs.row_size())
        throw std::out_of_range("Matrices are not the same size");
    Matrix temp(rows_,rhs.col_size());
    for (unsigned i = 0; i < temp.row_size(); i++)
    {
        for (unsigned j = 0; j < temp.col_size(); j++)
        {
            for (unsigned k = 0; k < cols_; k++) { 
                temp(i,j) += data_[cols_*i + k] * rhs(k,j);
            }
        }
    }
    return (*this = temp);
}
Matrix& Matrix::operator*=(const double& rhs)
{
    for (unsigned i = 0; i < rows_*cols_; i++) {
        data_[i] *= rhs;
    }
    return *this;
}