#ifndef MATRIX_H
#define MATRIX_H
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector3d.h>
#include <cstring>

class Matrix
{

    friend ostream& operator<<(ostream &os, Matrix &m); // overloading the << operator for use to print out the matrix

public:
    Matrix(); // constructor for the zero matrix, i.e., Zeros just everywhere

    explicit Matrix(const vector3D &v); //constructor for Diagonal/scalar/Unit Matrix, i.e.,A diagonal matrix has zero anywhere not on the main diagonal

    Matrix(const vector3D &v1, const vector3D &v2, const char &type); // constructor for the triangular Matrix


    ~Matrix(); //destructor for the Matrix class

    Matrix(const Matrix &m); //copy constructor 

    Matrix& operator=(const Matrix &m); //overloading the = operator

    Matrix operator-(const Matrix &m); // overloading the - operator to do the matrix subtraction

    Matrix operator+(const Matrix &m); // overloading the + operator to do the matrix addition

    Matrix operator*(const Matrix &m); //overloading the * operator to do the matrix mutiplication with a matrix

    bool operator==(const Matrix &m) const;

    vector3D operator*(const vector3D &v); //overloading the * operator to do the matrix mutiplication with a vector,i.e,(1x3*3x3)

    Matrix Inverse(); // function does the Matrix Inversion

    void transpose(); //function does the Matrix transpose

private:
    double* values; //define an array to form the 3x3 matrix
};
#endif // MATRIX_H
