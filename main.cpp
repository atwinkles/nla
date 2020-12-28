#include <iostream>
#include "bin/matrix.h"

int main() {
    double testone[3] = {1.0,
	    		 2.0,
                         3.0};
    double testtwo[2] = {4,
	    		 5};
    Matrix m(3,1,testone); 
    Matrix n(2,1,testtwo); 
    Matrix l = Matrix::outer(m,n);
    l.print();
    Matrix j = Matrix::identity(5);
    j.print();
    return 0;

}
