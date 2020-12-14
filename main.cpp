#include <iostream>
#include "bin/matrix.h"

int main() {
    double twos[4] =    {1.0,2.0,
                        3.0,4.3};
    double another[6] = {2,4,6,
                         8,10,12};
    Matrix m(2,2,twos); 
    Matrix n(2,3,another); 
    n.print();
    m*=n;
    m.print();
    m*=4;
    m.print();
    m+=n;
    n.print();
    m.print();
    return 0;
}