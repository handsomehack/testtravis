/* ~ Class 3 Material - cpp File ~ */
/* ~~~~~~~~~~~ Group 6 ~~~~~~~~~~~ */
/* ~~~~ Max Barber - 20180656 ~~~~ */

// Include needed libraries

#include "material.h"

// Define a object of the material class
Material::Material()
{
    // Initialise the material variables
    // '-1' means haven't been determined 
    this->ID = -1;

    this->Name = "blank";

    this->Colour = "blank";

    this->Density = -1;
}

// Call function to get the Material object
// const type as the values should remain the same and not be changed
Material Material :: get_Material() const
{
    // Return the Material object
    return*this;
}

// Call function to get the ID
// const type as the values should remain the same and not be changed
int Material ::get_ID() const
{
    // Return the ID and store in ID variable
    return this->ID;
}

// Call function to get the Name
// const type as the values should remain the same and not be changed
string Material ::get_Name() const
{
    // Return the Name and store in Name variable
    return this->Name;
}

// Call function to get the Colour
string Material ::get_Colour() const
{
    // Return the Colour and store in Colour variable
    return this->Colour;
}

// Call function to get the Density
int Material ::get_Density() const
{
    // Return the Density and store in Density variable
    return this->Density;
}

// Call function to set the ID of a new object of the Material class
void Material::set_ID(int &ID)
{
    // Store the ID in the ID variable
    this->ID = ID;
}

// Call function to set the Name of a new object of the Material class
void Material ::set_Name(string &Name)
{
    // Store the Name in the Name variable
    this->Name = Name;
}

// Call function to set the Colour of a new object of the Material class
void Material::set_Colour(string &Colour)
{
    // Store the Colour in the Colour variable
    this->Colour = Colour;
}

// Call function to set the Colour of a new object of the Material class
void Material ::set_Density(int &Density)
{
    // Store the Density in the Density variable
    this->Density = Density;
}