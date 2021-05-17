#ifndef TETRAHEDRON_H
#define TETRAHEDRON_H
#include <vector3d.h>
#include "cell.h"

class Tetrahedron : public Cell
{
	//inherit properties from cell class

public:
	//constructor
	Tetrahedron(int* id, Material* material, char* shape, vector3D* Vertices)
	{

		//define 4 vertices
		this->cell_vertices = new vector3D[4];
		this->cell_vertices[0] = Vertices[0];
		this->cell_vertices[1] = Vertices[1];
		this->cell_vertices[2] = Vertices[2];
		this->cell_vertices[3] = Vertices[3];

		//allcate memmory for ID / shape type / material
		this->ID = new int(*id);

		this->Shape = new char(*shape);

		this->M = new Material(*material);
	};

	Tetrahedron(const Tetrahedron &t); // copy constructor

	Tetrahedron &operator=(const Tetrahedron &t); // overloading the = operator

	virtual~Tetrahedron(); //destructor

	// re-implement the virtual functions in the sub-class
	virtual double getVolume();
	virtual vector3D getCenterOfGravity();
	virtual double getWeight(const double &volume);
};

#endif // TETRAHEDRON_H