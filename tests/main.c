#include "CBase.h"


void matrixTests();

int main(){
    matrixTests();
    return 0;
}



void matrixTests(){
    //write unit tests for matricies
    Matrix a = initMatrix(2, 2, 0);
    a.data[0][0] = 1; a.data[0][1] = 2; a.data[1][0] = 3; a.data[1][1] = 4;
    Matrix b = initMatrix(2, 2, 0);
    b.data[0][0] = 5; b.data[0][1] = 6; b.data[1][0] = 7; b.data[1][1] = 8;
    Matrix c = a.multiply(a, b);
    Matrix d = a.add(a, c);
    Matrix dT = d.transpose(d);

    a.print("a", a);
    b.print("b", b);
    c.print("c", c);
    d.print("d", d);
    dT.print("d Transposed", dT);
}