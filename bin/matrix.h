#ifndef MATRIX_H
#define MATARIX_H

class Matrix {
    public:
        Matrix(unsigned, unsigned);
        Matrix(unsigned, unsigned, double []);
        unsigned row_size() const;
        unsigned col_size() const;
        void print();
        double& operator() (unsigned, unsigned);
        double operator() (unsigned, unsigned) const;
        ~Matrix();
        Matrix(const Matrix&);

        Matrix& operator=(const Matrix&);
        Matrix& operator+=(const Matrix&);
        Matrix& operator-=(const Matrix&);
        Matrix& operator*=(const Matrix&);
        Matrix& operator*=(const double&);
    private:
        unsigned rows_,cols_;
        double* data_;
};

Matrix operator+(const Matrix&, const Matrix&);
Matrix operator*(const Matrix&, const Matrix&);
Matrix operator*(double, const Matrix&);
Matrix operator*(const Matrix&, double);

#endif