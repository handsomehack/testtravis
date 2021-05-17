#include "cell.h"
//----------------------------------------------------------
//implementation of the default constructor
Cell::Cell()
{
     this->cell_vertices = NULL;
     this->ID=NULL;
     this->M=NULL;
     this->Shape=NULL;   
}


//----------------------------------------------------------
//implentation of the virtual functions in the base class 
double Cell ::getVolume()
{
     return 0.0;
}

vector3D Cell::getCenterOfGravity()
{
     return vector3D();
}

double Cell::getWeight(const double &volume)
{

     return 0.0;
}

//---------------------------------------------------------------
//funtion to get the ID of the cell
//return the ID
int Cell::get_cell_ID()
{
     return *(this->ID);
}

//---------------------------------------------------------------
//function to get the shape type of the cell
char Cell::get_cell_type()
{
     return *(this->Shape);
}