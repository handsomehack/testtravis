#include "matrix.h"
//----------------------------------------------------------------------------------------------------------------
//destructor for all kinds of constructors
Matrix::~Matrix()
{
    //check if the pointer is valid
    if (this->values != 0)
    {
        delete[] this->values; //free the allocated memory 
        this->values = NULL; //make the pointer points to NULL for safety
    }
   
}

//----------------------------------------------------------------------------------------------------------------
//copy constructor for the zero matrix
//@noticed I have to overwrite the copy constructors because the class contains a pointer member,if it doens't the default copy constructors is enough to do all the work
Matrix::Matrix(const Matrix &m)
{
    //because when using the defalut copy constructor ,the two pointers will point to the same memory address when making the copy
    //so that will cause the same memory area to be released twice when the destructor is called
    //so a new memory address must be allocated
    if (m.values != 0)
    {

        this->values = new double[9];
        for (int i = 0; i < 9; i++)
        {

            this->values[i] = m.values[i];
        }
    }
    
}

//----------------------------------------------------------------------------------------------------------------
//In my program this operator overloading doesn't necessary needed because in the main function i am only doing Matrix initialization not assignment
//so the overloading = operator won't be invoked in this case
//but for other users can better use my program i might just proivde one, because
//the class private member contains a pointer which might cause problem if they need to do the assignment 
Matrix& Matrix ::operator=(const Matrix &m)
{

    // the process is kind similar to the copy constructor ,but the only difference is i have to delete the memroy that have been allocated to
    // the left operand and allocate a new mermory to it to do the assignement ,the reason i am doing this step is because when doing the assignment 
    // we can assume the matrix has already been initialized so if we make the pointer points to a new memory address without deleting the original one
    // then the data stored in the original memory address will go to dangling state which is not acceptable.
    if (this->values != 0)
    {

        delete[] this->values;
        this->values = NULL;
        this->values = new double[9];
        for (int i = 0; i < 9; i++)
        {

            this->values[i] = m.values[i];
        }
    }
    return *this;
}

//----------------------------------------------------------------------------------------------------------------
//constructor for the zero matrix
Matrix::Matrix()
{
   
    values = new double[9];
    // initialize a matrix by assigning each element 0 value.
    for (int i = 0; i < 9; i++)
    {

        values[i] = 0;
    }
}

//------------------------------------------------------------------------------------------------------------------
//constructor for the Diagonal/scalar/Unit Matrix
//The function takes a 3Dvector as an arguement and assign the x,y,z value of the vector to the Matrix's diagonal
Matrix ::Matrix(const vector3D &v)
{
    
    values = new double[9];
    //assign all the elements zero value except the diagonal
    this->values[1] = this->values[2] = static_cast<double>(0);
    this->values[3] = this->values[5] = static_cast<double>(0);
    this->values[6] = this->values[7] = static_cast<double>(0);

    //populate the diagonal with vector
    this->values[0] = v.X;
    this->values[4] = v.Y;
    this->values[8] = v.Z;
}

//-------------------------------------------------------------------------------------------------------------------
//constructor for the triangular Matrix
//The function takes two 3Dvector as the first two arguements to populate the Matrix
//The third argument is to determine whether it is Upper triangular Matrix or lower triangular Matrix
Matrix ::Matrix(const vector3D &v1, const vector3D &v2, const char &type)
{
 
    values = new double[9];
    //if user is passing 'U' as the third argument, that means he wants upper triangular Matrix
    //populate the matrix with uppper triangular style
    if (type == 'U')
    {
        this->values[0] = v1.X;
        this->values[1] = v1.Y;
        this->values[2] = v1.Z;
        this->values[3] = static_cast<double>(0);
        this->values[4] = v2.X;
        this->values[5] = v2.Y;
        this->values[6] = static_cast<double>(0);
        this->values[7] = static_cast<double>(0);
        this->values[8] = v2.Z;
    }

    //if user is passing 'L' as the third argument, that means he wants lower triangular Matrix
    //populate the matrix with lower triangular style
    if (type == 'L')
    {

        this->values[0] = v1.X;
        this->values[1] = static_cast<double>(0);
        this->values[2] = static_cast<double>(0);
        this->values[3] = v1.Y;
        this->values[4] = v1.Z;
        this->values[5] = static_cast<double>(0);
        this->values[6] = v2.X;
        this->values[7] = v2.Y;
        this->values[8] = v2.Z;
    }
}


//-------------------------------------------------------------------------------------------------------------------
//function does the matrix addition and return the result which is also a matrix back to the user
Matrix Matrix ::operator+(const Matrix &m)
{

     Matrix result; //define a matrix to store the result
                         

    //loop through each element and do the addition
    for (int i = 0; i < 9; i++)
    {

        result.values[i] = this->values[i] + m.values[i];
    }

    return result; // return the result
}

//----------------------------------------------------------------------------------------------------------------
//function does the matrix subtraction and return the result which is also a matrix back to the user
Matrix Matrix ::operator-(const Matrix &m)
{

     Matrix result; //define a matrix to store the result

    //loop through each element and do the subtraction
    for (int i = 0; i < 9; i++)
    {

        result.values[i] = this->values[i] - m.values[i];
    }

    return result; //return the result
}

//----------------------------------------------------------------------------------------------------------------
//function does the matrix mutiplication and return the result wich is a matrix back to the user
Matrix Matrix ::operator*(const Matrix &m)
{

    Matrix result; //define a matrix to store the result

    //loop through each element and do the mutiplication
    for (int i = 0; i < 9; i++)
    {

        result.values[i] = this->values[i] * m.values[i];
    }

    return result; // return the result
}

//----------------------------------------------------------------------------------------------------------------
//function does the matrix mutiplication and return the result wich is a vector back to the user
vector3D Matrix ::operator*(const vector3D &v)
{

    vector3D result(-1, v.X * (this->values[0]) + v.Y * (this->values[3]) + v.Z * (this->values[6]), v.X * (this->values[1]) + v.Y * (this->values[4]) + v.Z * (this->values[7]),
                           v.X * (this->values[2]) + v.Y * (this->values[5]) + v.Z * (this->values[8]));

    return result; // return the result
}

//----------------------------------------------------------------------------------------------------------------
//function does the matrix inversion and return the result which is also a matrix back to the user.
Matrix Matrix ::Inverse()
{

    //caculate the absolute determinant value of the original matrix
    double determinant = abs((this->values[0] * this->values[4] * this->values[8] + this->values[1] * this->values[5] * this->values[6] +
                             this->values[2] * this->values[3] * this->values[7]) -
                            (this->values[6] * this->values[4] * this->values[2] + this->values[7] * this->values[5] * this->values[0] +
                             this->values[8] * this->values[3] * this->values[1]));

     Matrix result; // define a new matrix to store the result
    // do the calculation , replace each element by its new value
    result.values[0] = (this->values[4] * this->values[8] - this->values[5] * this->values[7]) / determinant;
    result.values[1] = -(this->values[3] * this->values[8] - this->values[5] * this->values[6]) / determinant;
    result.values[2] = (this->values[3] * this->values[7] - this->values[6] * this->values[4]) / determinant;
    result.values[3] = -(this->values[1] * this->values[8] - this->values[2] * this->values[7]) / determinant;
    result.values[4] = (this->values[0] * this->values[8] - this->values[2] * this->values[6]) / determinant;
    result.values[5] = -(this->values[0] * this->values[7] - this->values[6] * this->values[1]) / determinant;
    result.values[6] = (this->values[1] * this->values[5] - this->values[2] * this->values[4]) / determinant;
    result.values[7] = -(this->values[0] * this->values[5] - this->values[2] * this->values[3]) / determinant;
    result.values[8] = (this->values[4] * this->values[0] - this->values[3] * this->values[1]) / determinant;

    return result; // return the result back to the user
}

//----------------------------------------------------------------------------------------------------------------
//function to do the matrix transpose
void Matrix ::transpose()
{

    // do the transpose
    double temp; // introduced a temp variable for use to swap the values that symmetric about the diagonal

    temp = this->values[1];
    this->values[1] = this->values[3];
    this->values[3] = temp;

    temp = this->values[2];
    this->values[2] = this->values[6];
    this->values[6] = temp;

    temp = this->values[5];
    this->values[5] = this->values[7];
    this->values[7] = temp;
}

bool Matrix::operator==(const Matrix &m) const {
    if(this->values[0]== m.values[0]
    && this->values[1]== m.values[1]
    && this->values[2]== m.values[2]
    && this->values[3]== m.values[3]
    && this->values[4]== m.values[4]
    && this->values[5]== m.values[5]
    && this->values[6]== m.values[6]
    && this->values[7]== m.values[7]
    && this->values[8]== m.values[8])
        return true;
    else
        return false;
}
