#ifndef PYRAMID_H
#define PYRAMID_H
#include <vector3d.h>
#include "cell.h"

class Pyramid : public Cell {
	//inherit properties from cell class

public:
	//constructor
	Pyramid(int* id, Material* material, char* shape, vector3D* Vertices){

		//define 5 vertices
		this->cell_vertices = new vector3D[5];
		this->cell_vertices[0] = Vertices[0];
		this->cell_vertices[1] = Vertices[1];
		this->cell_vertices[2] = Vertices[2];
		this->cell_vertices[3] = Vertices[3];
		this->cell_vertices[4] = Vertices[4];

	    //allcate memmory for ID / shape type / material
		this->ID = new int(*id);

		this->Shape = new char(*shape);

		this->M = new Material(*material);

	};

	Pyramid(const Pyramid &p);// copy constructor 
	
    Pyramid& operator=(const Pyramid &p);// overloading the = operator 

	virtual~Pyramid();//destrucotr 

    // re-implement the virtual functions in the sub-class
   	virtual double getVolume();
	virtual vector3D getCenterOfGravity();
	virtual double getWeight(const double &volume);
};

#endif // PYRAMID_H