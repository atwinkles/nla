#include <iostream>
#include "Matrix.h"

int main() {
    Matrix m(3,3);
    m(2,2) = 11;
    std::cout << m(2,2) << "\n";
    double twos[4] = {1.0,2.0,3.0,4.0};
    Matrix n(2,2,twos); 
    std::cout << n(1,1) <<"\n";
    double test[3][3] = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    Matrix C(3,3,test);
    std::cout << C(1,1) << "\n";
    return 0;
}