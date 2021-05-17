#include <iostream>
#include <matrix.h>
//Implmentation of overloading the << operator to display the vector
ostream &operator<<(ostream &os, vector3D &v)
{

    return os << "[" << v.X << "," << v.Y << "," << v.Z << "]"; // display the result in [x,y,z] format
}

//Implmentation of overloading the << operator to display the matrix
ostream &operator<<(ostream &os, Matrix &m)
{

    return os << m.values[0] << "," << m.values[1] << "," << m.values[2] << endl
              << m.values[3] << "," << m.values[4] << "," << m.values[5] << endl
              << m.values[6] << "," << m.values[7] << "," << m.values[8];
}

bool add(Matrix& m1, Matrix& m2){

    return ( m1+m2== Matrix(vector3D(-1,4,6,8)))? 1:0;
}


bool subtract(Matrix& m1, Matrix& m2){

    return ( m1-m2 == Matrix(vector3D(-1,-2,-2,-2))) ? 1:0;

}


bool multiply(Matrix& m1, Matrix& m2){

    return ( m1*m2 == Matrix(vector3D(-1,3,8,15))) ? 1:0;

}

int Run_Test(Matrix& m1, Matrix& m2) {

    if (add(m1, m2) && subtract(m1, m2) && multiply(m1, m2)) {
        return 0;
    } else
        return 1;

}




int main()
{

    const double a = 1.0, b = 2.0, c = 3.0, d = 4.0, e = 5.0;

    //define two diagonal matrixes
    vector3D v_1(0, a, b, c);
    vector3D v_2(1, c, d, e);
    Matrix m1(v_1);
    Matrix m2(v_2);

    return Run_Test(m1,m2);
}