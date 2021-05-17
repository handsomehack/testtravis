#include "tetrahedron.h"


//----------------------------------------------------------
//implementation of the destructor
Tetrahedron::~Tetrahedron()
{
	// free the allocated memory when the destructor is called
	if (this->cell_vertices != NULL && this->ID != NULL && this->M != NULL && this->Shape != NULL)
	{
		delete[] this->cell_vertices;
		delete this->ID;
		delete this->M;
		delete this->Shape;
		this->cell_vertices = NULL;
		this->ID = NULL;
		this->M = NULL;
		this->Shape = NULL;
	}
}

//---------------------------------------------------------------------------------------------------------------
//implementation of the copy constructors
Tetrahedron::Tetrahedron(const Tetrahedron &t)
{

	
	//because when using the defalut copy constructor ,the two pointers will point to the same memory address when making the copy
	//so that will cause the same memory area to be released twice when the destructor is called
	//so a new memory address must be allocated
	if (t.cell_vertices != NULL && t.ID != NULL && t.Shape != NULL && t.M != NULL)
	{
		this->cell_vertices = new vector3D[4];
		for (int i = 0; i < 4; i++)
		{
			this->cell_vertices[i] = t.cell_vertices[i];
		}

		this->ID = new int(*(t.ID));

		this->Shape = new char(*(t.Shape));

		this->M = new Material(*(t.M));
	}
}

//---------------------------------------------------------------------------------------------------------------
//implementation of overloading the = operator
Tetrahedron &Tetrahedron::operator=(const Tetrahedron &t)
{   
	// the process is kind similar to the copy constructor ,but the only difference is i have to delete the memroy that have been allocated to
	// the left operand and allocate a new mermory to it to do the assignement ,the reason i am doing this step is because when doing the assignment
	// we can assume the pyramid has already been initialized so if we make the pointer points to a new memory address without deleting the original memory address
	// then the data stored in the original memory address will go to dangling state which is not acceptable.
	if (this->cell_vertices != NULL && this->ID != NULL && this->M != NULL && this->Shape != NULL)
	{
		delete[] this->cell_vertices;
		delete this->ID;
		delete this->M;
		delete this->Shape;
	}

	this->cell_vertices = new vector3D[4];
	for (int i = 0; i < 4; i++)
	{

		this->cell_vertices[i] = t.cell_vertices[i];
	}

	this->ID = new int(*(t.ID));

	this->Shape = new char(*(t.Shape));

	this->M = new Material(*(t.M));

	return *this;
}

//---------------------------------------------------------------------------------------------------------------
//calculate volume of irregular tetrahedron
//return result in double back to user
double Tetrahedron::getVolume(){

	double volume;

	vector3D a = cell_vertices[1] - cell_vertices[0];
	vector3D b = cell_vertices[2] - cell_vertices[0];
	vector3D c = cell_vertices[3] - cell_vertices[0];
	vector3D cross = a^b;
	volume = (cross * c)/6;

	//avoid any negative value of volume
	if ( volume < 0 ){
		volume = -volume;
	}

	return volume;
}

//---------------------------------------------------------------------------------------------------------------
//find the centroid of tetrahedron
//by calculating the average of all vertices
//return result in vector back to user
vector3D Tetrahedron::getCenterOfGravity(){
	
	vector3D centroid = (cell_vertices[0] + cell_vertices[1] + cell_vertices[2] + cell_vertices[3])/4;

	return centroid;
}

//---------------------------------------------------------------------------------------------------------------
//calculate the weight of tetrahedron
//return result in double back to user
double Tetrahedron::getWeight(const double &volume){

	double weight,mass;
	double gravity = 9.80665;

	mass = M->get_Density() * volume;
	weight = mass * gravity;
 
	return weight;
}
//---------------------------------------------------------------------------------------------------------------