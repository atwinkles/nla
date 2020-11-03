#ifndef MATRIX_H
#define MATRIX_H

template <typename T>
class Matrix {
    public:
        Matrix(unsigned rows, unsigned cols);   // Constructor
        Matrix(unsigned rows, unsigned cols, T mat[]); // Constructor
        unsigned row_size() const;
        unsigned col_size() const;
        void print();

        Matrix<T> operator+(const Matrix<T>& n);
        Matrix<T> operator*(const Matrix<T>& n);
        Matrix<T> operator*(const T& n);
        T& operator() (unsigned row, unsigned col); // Assigns value at (row,col)
        T operator() (unsigned row, unsigned col) const; // Returns value at (row,col)

        ~Matrix();                              // Destructor
        Matrix(const Matrix& m);                // Copy constructor
        Matrix& operator= (const Matrix& m);    // Assignment operator

    private:
        unsigned rows_, cols_;
        T* data_;
};

#endif