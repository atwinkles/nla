#ifndef MATRIX_H
#define MATARIX_H

class Matrix {
    public:
        Matrix(unsigned rows, unsigned cols);
        Matrix(unsigned rows, unsigned cols, double mat[]);
        unsigned row_size() const;
        unsigned col_size() const;
        void print();
        double& operator() (unsigned row, unsigned col);
        double operator() (unsigned row, unsigned col) const;
        ~Matrix();
        Matrix(const Matrix& m);

        Matrix& operator=(const Matrix& m);
        Matrix& operator+=(const Matrix& rhs);
        Matrix& operator*=(const Matrix& rhs);
        Matrix& operator*=(const double& rhs);
    private:
        unsigned rows_,cols_;
        double* data_;
};

#endif