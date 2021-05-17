#ifndef HEXAHEDRON_H
#define HEXAHEDRON_H
#include <vector3d.h>
#include "cell.h"

class Hexahedron : public Cell {
	//inherit properties from cell class

public:
	//constructor
	Hexahedron(int* id, Material* material, char* shape, vector3D* Vertices){ 

		//define 8 vertices
		this->cell_vertices = new vector3D[8];
		this->cell_vertices[0] = Vertices[0];
		this->cell_vertices[1] = Vertices[1];
		this->cell_vertices[2] = Vertices[2];
		this->cell_vertices[3] = Vertices[3];
		this->cell_vertices[4] = Vertices[4];
		this->cell_vertices[5] = Vertices[5];
		this->cell_vertices[6] = Vertices[6];
		this->cell_vertices[7] = Vertices[7];

        //allcate memmory for ID / shape type / material
		this->ID = new int(*id);

		this->Shape = new char(*shape);

		this->M = new Material(*material);
 

	};

	Hexahedron(const Hexahedron &h);// copy constructor 
	
    Hexahedron& operator=(const Hexahedron &h);// overloading the = operator 

	virtual~Hexahedron(); //destrucotr

    // re-implement the virtual functions in the sub-class
   	virtual double getVolume();
	virtual vector3D getCenterOfGravity();
	virtual double getWeight(const double &volume);
};


#endif // HEXAHEDRON_H