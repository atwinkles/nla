#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
    public:
        Matrix(unsigned rows, unsigned cols);   // Constructor
        Matrix(unsigned rows, unsigned cols, double mat[]); // Constructor
        Matrix(unsigned rows, unsigned cols, double mat[][cols]); // Constructor
        double& operator() (unsigned row, unsigned col); // Assigns value at (row,col)
        double operator() (unsigned row, unsigned col) const; // Returns value at (row,col)

        ~Matrix();                              // Destructor
        Matrix(const Matrix& m);                // Copy constructor
        Matrix& operator= (const Matrix& m);    // Assignment operator

    private:
        unsigned rows_, cols_;
        double* data_;
};

#endif