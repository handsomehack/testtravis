/* ~ Class 3 Material - header File ~ */
/* ~~~~~~~~~~~~ Group 6 ~~~~~~~~~~~~~ */
/* ~~~~~ Max Barber - 20180656 ~~~~~~ */

// Include needed libraries

#ifndef MATERIAL_H
#define MATERIAL_H
#include <string>
using namespace std;

/* ~ Material Class ~ */
// Values to store (data type):
// ID ~ is a number value (int)
// Name ~ is a word (string)
// Colour ~ is a number value stored in hexidecimal (string)
// Denisty ~ is a number value (int)
/* ~~~~~~~~~~~~~~~~~~ */
// Define a Material class

class Material
{

// Define the friend functions of the class
// this allows functions access to the private varibles of the class

     friend ostream& operator<<(ostream& os, Material &m);

     friend istream& operator>>(istream& is, Material &m);

// Define the public variables

public:

    // Define a material
    Material();

    // Pass the variables to the defined Material
    Material(int id, string name, string colour, int density) : ID(id), Name(name), Colour(colour), Density(density){};

    /* ~ Functions to get values for a Material ~ */

    // Define function to get the ID of a Material
    // integer as the ID is a numerical value
    // constant as the value shouldnt be changed throught the code/program
    int get_ID() const;

    // Define function to get the Name of a Material
    // string as the Name is a alphabetical value
    // constant as the value shouldnt be changed throught the code/program
    string get_Name() const;

    // Define function to get the Colour of a Material
    // string as the Colour is a alphabetical value as stored in hexidecimal
    // constant as the value shouldnt be changed throught the code/program
    string get_Colour() const;

    // Define function to get the Density of a Material
    // integer as the Density is a numerical value
    // constant as the value shouldnt be changed throught the code/program
    int get_Density() const;

    /* ~ Functions to set a new Material ~ */

    // Define function to get a new Material
    // constant as the value shouldnt be changed throught the code/program
    Material get_Material()const;

    // Define function to set the ID of a Material
    // integer as the ID is a numerical value
    void set_ID(int &ID);

    // Define function to set the Name of a Material
    // string as the Name is a alphabetical value
    void set_Name(string &Name);

    // Define function to set the Colour of a Material
    // string as the Colour is a alphabetical value as stored in hexidecimal
    void set_Colour(string &Colour);

    // Define function to set the Density of a Material
    // integer as the Density is a numerical value
    void set_Density(int &Density);

// Define the private variables

private:

    // Integer to store the ID number
    int ID;

    // String to store the Name
    string Name;

    //String to store the Colour
    string Colour;

    //Integer to store the Density
    int Density;
};

#endif // MATERIAL_H