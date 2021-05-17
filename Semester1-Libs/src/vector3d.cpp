#include "vector3d.h"

//---------------------------------------------------------------------------------------------------------------
//default constructor
vector3D ::vector3D()
{
    this->Index = -1; //@notice all of the '-1' means the index of the vector hasn't been determined.
    this->X = 0;
    this->Y = 0;
    this->Z = 0;
}

//---------------------------------------------------------------------------------------------------------------
//function does the vector subtraction and return the result which is also a vector back to the user
vector3D vector3D ::operator-(const vector3D &v)
{

    vector3D result(-1, this->X - v.X, this->Y - v.Y, this->Z - v.Z); //do the subtraction according to the vector subtraction rule

    return result; // return the result
}

//----------------------------------------------------------------------------------------------------------------
//function does the vector additon and return the result which is also a vector back to the user
vector3D vector3D ::operator+(const vector3D &v)
{

    vector3D result(-1, this->X + v.X, this->Y + v.Y, this->Z + v.Z); //do the addition according to the vector additon rule

    return result; // return the result
}

//----------------------------------------------------------------------------------------------------------------
//function does the vector/outer product calculation and return the result wich is also a vector back to the user
vector3D vector3D ::operator^(const vector3D &v)
{

    // do the vector product calculation according to the rule
    vector3D result(-1,
                    (this->Y * v.Z) - (v.Y * this->Z),
                    -((this->X * v.Z) - (v.X * this->Z)),
                    (this->X * v.Y) - (v.X * this->Y));

    return result; // return the result
}

//----------------------------------------------------------------------------------------------------------------
//function does the scalar/inner product calculation and return the result wich is a floating number back to the user
double vector3D ::operator*(const vector3D &v)
{

    double result = ((this->X * v.X) + (this->Y * v.Y) + (this->Z * v.Z)); // do the scalar/inner product calculation according to the rule

    return result; // return the result
}


//------------------------------------------------------------------------------------------------------------------------
//funtion does the vector division with a floating number 
vector3D vector3D :: operator/(const double &v){


    vector3D result(-1,(this->X/v),(this->Y/v),(this->Z/v));// do the vector divison with a floating number.

    return result; // return the result 
    
}


//----------------------------------------------------------------------------------------------------------------
//function allows user to set the X,Y,Z value of a vector
void vector3D ::set_Vector(const double &x, const double &y, const double &z)
{

    this->X = x; // set x value
    this->Y = y; // set y value
    this->Z = z; // set z value
}

bool vector3D::operator==(const vector3D &v) const {
    if(this->X == v.X && this->Y == v.Y && this->Z == v.Z){
        return true;
    }
    else
        return false;
}


