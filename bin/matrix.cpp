#include <stdexcept>
#include <iostream>
#include "matrix.h"

/* PUBLIC MEMBER FUNCTIONS */

// Constructor without data
Matrix::Matrix(unsigned rows, unsigned cols)
{
    rows_ = rows;
    cols_ = cols;
    if (rows == 0 || cols == 0)
        throw std::out_of_range("Matrix constructor has 0 size");
    data_ = new double[rows*cols];
}

// Constructor with data
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

// Returns the number of rows
unsigned Matrix::row_size() const
{
    return rows_;
}

// Returns the number of columns
unsigned Matrix::col_size() const
{
    return cols_;
}

// Nicely prints the matrix
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

// Operator overload for () used for changing element
double& Matrix::operator() (unsigned row, unsigned col)
{
    if (row >= rows_ || col >= cols_)
        throw std::out_of_range("Matrix subscript out of bounds");
    return data_[cols_*row + col];
}

// Operator overload for () used displaying element
double Matrix::operator() (unsigned row, unsigned col) const
{
    if (row >= rows_ || col >= cols_)
        throw std::out_of_range("const Matrix substript out of bounds");
    return data_[cols_*row + col];
}

// Destructor
Matrix::~Matrix()
{
    delete[] data_;
}

// Copy Constructor
Matrix::Matrix(const Matrix& m) : rows_(m.row_size()), cols_(m.col_size())
{
    data_ = new double[rows_*cols_];
    for (unsigned i = 0; i< rows_; i++) {
        for (unsigned j = 0; j < cols_; j++) {
            data_[cols_*i + j] = m(i,j);
        }
    }
}

// Function to create identity matrix of size n*n
Matrix Matrix::identity(unsigned n)
{
    Matrix m(n,n);
    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j < n; j++) {
            if (i == j) {
                m(i,j) = 1;
            }
            else {
                m(i,j) = 0;
            }
        }  
    }
    return m;
}

// Assignment operator
Matrix& Matrix::operator= (const Matrix& m)
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
            for (unsigned j = 0; j < cols_; j++) {
                data_[cols_*i + j] = m(i,j);
            }
        }
    }
    return *this;
}

// Operator overload for +=
Matrix& Matrix::operator+=(const Matrix& rhs)
{
    if (cols_ != rhs.col_size() || rows_ != rhs.row_size())
        throw std::out_of_range("Matrices are not the same size");
    for (unsigned i = 0; i < rows_; i++) {
        for (unsigned j = 0; j < cols_; j++) {
            data_[cols_*i + j] += rhs(i,j);
        }
    }
    return *this;
}

// Operator overload for -=
Matrix& Matrix::operator-=(const Matrix& rhs)
{
    if (cols_ != rhs.col_size() || rows_ != rhs.row_size())
        throw std::out_of_range("Matrices are not the same size");
    for (unsigned i = 0; i < rows_; i++) {
        for (unsigned j = 0; j < cols_; j++) {
            data_[cols_*i + j] -= rhs(i,j);
        }
    }
    return *this;
}

// Operator overload for *= with another matrix
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

// Operator overload for *= with a scalar
Matrix& Matrix::operator*=(const double& rhs)
{
    for (unsigned i = 0; i < rows_*cols_; i++) {
        data_[i] *= rhs;
    }
    return *this;
}

/* STATIC CLASS FUNCTIONS */

// Dot product for vectors
double Matrix::dot(const Matrix& lhs, const Matrix& rhs)
{
    if (lhs.row_size() != rhs.row_size() && lhs.col_size() != 1 && rhs.col_size() != 1)
        throw std::out_of_range("Vectors are not the same size for a dot product");
    double sumval = 0;
    for (unsigned i = 0; i < lhs.row_size(); i++) {
        sumval += lhs(i,0) * rhs(i,0);
    }
    return sumval;
}

// Outer product for vectors
Matrix Matrix::outer(const Matrix& lhs, const Matrix& rhs)
{
    if (lhs.col_size() != 1 && rhs.col_size() != 1)
        throw std::out_of_range("Not a vector for an outer product");
    double tempdata[lhs.row_size()*rhs.row_size()];
    for (unsigned i = 0; i < lhs.row_size(); i++) {
        for (unsigned j = 0; j < rhs.row_size(); j++) {
            tempdata[rhs.row_size()*i + j] = lhs(i,0) * rhs(j,0);
        }
    }
    Matrix temp(lhs.row_size(),rhs.row_size(),tempdata);
    return temp;
}

/* NON-MEMBER FUNCTIONS */

// Operator overload for + using += member function
Matrix operator+(const Matrix& m1, const Matrix& m2)
{
    Matrix temp(m1);
    return (temp += m2);
}

// Operator overload for * using *= member funciton with another matrix
Matrix operator*(const Matrix& m1, const Matrix& m2)
{
    Matrix temp(m1);
    return (temp *= m2);
}

// Operator overload for * using *= member funciton with a scalar
Matrix operator*(double num, const Matrix& m1)
{
    Matrix temp(m1);
    return (temp *= num);
}

// Operator overload for * using *= member funciton with a scalar
Matrix operator*(const Matrix& m1, double num)
{
    Matrix temp(m1);
    return (temp *= num);
}
