#include <iostream>
#include "Matrix.h"

int main() {
    double twos[4] =    {1.0,2.0,
                        3.0,4.3};
    Matrix<double> m(2,2,twos); 
    Matrix<double> n(2,2,twos); 
    Matrix<double> k = m*n;
    k.print();
    Matrix<double> l = 2*k;
    l.print();
    return 0;
}