#ifndef VECTOR3D_H
#define VECTOR3D_H
#include <iostream>
using namespace std;

class vector3D
{

    friend ostream& operator<<(ostream& os,  vector3D &v); // make the overloading << operator as a friend to print out the vector

    friend istream& operator>>(istream& is,  vector3D &v); // make the overloading >> operator as a firend for use to read VTK style data from a file 

    friend class Matrix; //make matrix class as a friend to let it access the private variables.

public:
    vector3D();//default constructor

    vector3D(const int &index,const double &xi, const double &yi,const double &zi) :Index(index), X(xi), Y(yi), Z(zi){}; //constructor

    vector3D operator-(const vector3D &v); // overloading the - operator to do the vector subtraction

    vector3D operator+(const vector3D &v); // overloading the + operator to do the vector addition

    vector3D operator^(const vector3D &v); // overloading the ^ operator to do the vector/outer product calculation

    vector3D operator/(const double &v);  //overloading the /operator to do the vector division with a floating number

    bool operator==(const vector3D& v) const;  // check if the two vectors are equal

    double operator*(const vector3D &v); // overloading the * operator to do the scalar product calculation

    int get_ID()const{return this->Index;}; //function to get the vector Index;

    double get_X()const{return this->X;};   //get x 

    double get_Y()const{return this->Y;};   //get y 

    double get_Z()const{return this->Z;};   //get z

    vector3D& get_Vector(){return *this;}; // accessor

    void set_Vector(const double &x, const double &y, const double &z); // mutator

private:
    double X, Y, Z; // define 3 variables to store the X-axis, Y-axis, Z-axis value of a vector
    
    int Index;  // this the unique index for a vector 
};
#endif // VECTOR3D_H
