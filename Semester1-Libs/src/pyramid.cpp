#include "pyramid.h"


//----------------------------------------------------------
//implementation of the destructor
Pyramid::~Pyramid()
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
Pyramid::Pyramid(const Pyramid &p)
{

	//because when using the defalut copy constructor ,the two pointers will point to the same memory address when making the copy
	//so that will cause the same memory area to be released twice when the destructor is called
	//so a new memory address must be allocated
	if (p.cell_vertices != NULL && p.ID != NULL && p.Shape != NULL && p.M != NULL)
	{
		this->cell_vertices = new vector3D[5];
		for (int i = 0; i < 5; i++)
		{
			this->cell_vertices[i] = p.cell_vertices[i];
		}

		this->ID = new int(*(p.ID));

		this->Shape = new char(*(p.Shape));

		this->M = new Material(*(p.M));
	}

}

//---------------------------------------------------------------------------------------------------------------
//implementation of overloading the = operator
Pyramid &Pyramid::operator=(const Pyramid &p)
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

	this->cell_vertices = new vector3D[5];
	for (int i = 0; i < 5; i++)
	{

		this->cell_vertices[i] = p.cell_vertices[i];
	}

	this->ID = new int(*(p.ID));

	this->Shape = new char(*(p.Shape));

	this->M = new Material(*(p.M));

	return *this;
}

//---------------------------------------------------------------------------------------------------------------
//calculate volume of irregular pyramid
//by calculating two irregular tetrahedron and add them together
//return result in double back to user
double Pyramid::getVolume(){

	double volume,vol1,vol2;

	//calculate volume of first half of pyramid
	vector3D a1 = cell_vertices[1] - cell_vertices[0];
	vector3D b1 = cell_vertices[3] - cell_vertices[0];
	vector3D c1 = cell_vertices[4] - cell_vertices[0];
	vector3D cross1 = a1^b1;
	vol1 = (cross1 * c1)/6;

	//calculate volume of second half of pyramid
	vector3D a2 = cell_vertices[1] - cell_vertices[2];
	vector3D b2 = cell_vertices[3] - cell_vertices[2];
	vector3D c2 = cell_vertices[4] - cell_vertices[2];
	vector3D cross2 = a2^b2;
	vol2 = (cross2 * c2)/6;

	//avoid any negative value of volume
	if (vol1 < 0){
	
		vol1 = vol1 * -1;
	}
	if (vol2 < 0){
		
		vol2 = vol2 * -1;
	}	
	
	volume = vol1 + vol2;

	return volume;
}

//---------------------------------------------------------------------------------------------------------------
//find the centroid of pyramid
//by calculating the average of all vertices
//return result in vector back to user
vector3D Pyramid::getCenterOfGravity(){
	
	vector3D centroid = (cell_vertices[0] + cell_vertices[1] + cell_vertices[2] + cell_vertices[3] + cell_vertices[4])/5;

	return centroid;
}

//---------------------------------------------------------------------------------------------------------------
//calculate the weight of pyramid
//return result in double back to user
double Pyramid::getWeight(const double &volume){

	double weight,mass;
	double gravity = 9.80665;

	mass = M->get_Density() * volume;
	weight = mass * gravity;
 
	return weight;
}
//---------------------------------------------------------------------------------------------------------------