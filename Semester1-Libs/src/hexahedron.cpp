#include "hexahedron.h"

//----------------------------------------------------------
//implementation of the destructor
Hexahedron::~Hexahedron()
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
Hexahedron::Hexahedron(const Hexahedron &h)
{

	//because when using the defalut copy constructor ,the two pointers will point to the same memory address when making the copy
	//so that will cause the same memory area to be released twice when the destructor is called
	//so a new memory area must be allocated to the object we ara creating 
	if (h.cell_vertices != NULL && h.ID != NULL && h.Shape != NULL && h.M != NULL)
	{
		this->cell_vertices = new vector3D[8];
		for (int i = 0; i < 8; i++)
		{
			this->cell_vertices[i] = h.cell_vertices[i];
		}

		this->ID = new int(*(h.ID));

		this->Shape = new char(*(h.Shape));

		this->M = new Material(*(h.M));
	}
}

//---------------------------------------------------------------------------------------------------------------
//implementation of overloading the = operator
Hexahedron &Hexahedron::operator=(const Hexahedron &h)
{
	// the process is kind similar to the copy constructor ,but the only difference is i have to delete the memroy that have been allocated to
	// the left operand and allocate a new mermory to it to do the assignement ,the reason i am doing this step is because when doing the assignment
	// we can assume the Hexahedron has already been initialized so if we make the pointer points to a new memory address without deleting the original memory address
	// then the data stored in the original memory address will go to dangling state which is not acceptable.
	if (this->cell_vertices != NULL && this->ID != NULL && this->M != NULL && this->Shape != NULL)
	{
		delete[] this->cell_vertices;
		delete this->ID;
		delete this->M;
		delete this->Shape;
	}

	this->cell_vertices = new vector3D[8];
	for (int i = 0; i < 8; i++)
	{

		this->cell_vertices[i] = h.cell_vertices[i];
	}

	this->ID = new int(*(h.ID));

	this->Shape = new char(*(h.Shape));

	this->M = new Material(*(h.M));

	return *this;
}

//---------------------------------------------------------------------------------------------------------------
//calculate volume of irregular hexahedron
//by calculating six pyramids and add them together
//return result in double back to user
double Hexahedron::getVolume()
{

	double volume, volume1, volume2, volume3, volume4, volume5, volume6;

	vector3D Xc = (cell_vertices[0] + cell_vertices[1] + cell_vertices[2] + cell_vertices[3] + cell_vertices[4] + cell_vertices[5] + cell_vertices[6] + cell_vertices[7]) / 8;
	vector3D x1 = (cell_vertices[0] + cell_vertices[1] + cell_vertices[2] + cell_vertices[3]) / 4;
	vector3D x2 = (cell_vertices[5] + cell_vertices[1] + cell_vertices[2] + cell_vertices[6]) / 4;
	vector3D x3 = (cell_vertices[0] + cell_vertices[1] + cell_vertices[4] + cell_vertices[5]) / 4;
	vector3D x4 = (cell_vertices[0] + cell_vertices[3] + cell_vertices[4] + cell_vertices[7]) / 4;
	vector3D x5 = (cell_vertices[4] + cell_vertices[5] + cell_vertices[6] + cell_vertices[7]) / 4;
	vector3D x6 = (cell_vertices[2] + cell_vertices[3] + cell_vertices[6] + cell_vertices[7]) / 4;

	vector3D A1 = (Xc - x1); //1234
	vector3D A2 = (Xc - x2); //2367
	vector3D A3 = (Xc - x3); //1256
	vector3D A4 = (Xc - x4); //1458
	vector3D A5 = (Xc - x5); //5678
	vector3D A6 = (Xc - x6); //3478

	vector3D B1 = (cell_vertices[0] - cell_vertices[1] + cell_vertices[3] - cell_vertices[2]); //1234
	vector3D C1 = (cell_vertices[0] + cell_vertices[1] - cell_vertices[2] - cell_vertices[3]);
	vector3D B2 = (cell_vertices[1] - cell_vertices[6] + cell_vertices[2] - cell_vertices[5]); //2367
	vector3D C2 = (cell_vertices[1] + cell_vertices[5] - cell_vertices[2] - cell_vertices[6]);
	vector3D B3 = (cell_vertices[0] - cell_vertices[4] + cell_vertices[1] - cell_vertices[5]); //1256
	vector3D C3 = (cell_vertices[0] + cell_vertices[4] - cell_vertices[1] - cell_vertices[5]);
	vector3D B4 = (cell_vertices[0] - cell_vertices[4] + cell_vertices[3] - cell_vertices[7]); //1458
	vector3D C4 = (cell_vertices[0] + cell_vertices[4] - cell_vertices[3] - cell_vertices[7]);
	vector3D B5 = (cell_vertices[4] - cell_vertices[6] + cell_vertices[7] - cell_vertices[5]); //5678
	vector3D C5 = (cell_vertices[4] + cell_vertices[5] - cell_vertices[7] - cell_vertices[6]);
	vector3D B6 = (cell_vertices[3] - cell_vertices[6] + cell_vertices[2] - cell_vertices[7]); //3478
	vector3D C6 = (cell_vertices[3] + cell_vertices[7] - cell_vertices[2] - cell_vertices[6]);

	volume1 = A1 * (B1 ^ C1);
	volume2 = A2 * (B2 ^ C2);
	volume3 = A3 * (B3 ^ C3);
	volume4 = A4 * (B4 ^ C4);
	volume5 = A5 * (B5 ^ C5);
	volume6 = A6 * (B6 ^ C6);

	//avoid any negative value of volume
	if (volume1 < 0)
	{
		volume1 = -volume1;
	}
	if (volume2 < 0)
	{
		volume2 = -volume2;
	}
	if (volume3 < 0)
	{
		volume3 = -volume3;
	}
	if (volume4 < 0)
	{
		volume4 = -volume4;
	}
	if (volume5 < 0)
	{
		volume5 = -volume5;
	}
	if (volume6 < 0)
	{
		volume6 = -volume6;
	}

	volume = volume1 + volume2 + volume3 + volume4 + volume5 + volume6;

	return volume / 12;
}

//---------------------------------------------------------------------------------------------------------------
//find the centroid of hexahedron
//by calculating the average of all vertices
//return result in vector back to user
vector3D Hexahedron::getCenterOfGravity()
{

	vector3D centroid = (cell_vertices[0] + cell_vertices[1] + cell_vertices[2] + cell_vertices[3] + cell_vertices[4] + cell_vertices[5] + cell_vertices[6] + cell_vertices[7]) / 8;

	return centroid;
}

//---------------------------------------------------------------------------------------------------------------
//calculate the weight of hexahedron
//return result in double back to user
double Hexahedron::getWeight(const double &volume)
{

	double weight, mass;
	double gravity = 9.80665;

	mass = M->get_Density() * volume;
	weight = mass * gravity;

	return weight;
}
//---------------------------------------------------------------------------------------------------------------