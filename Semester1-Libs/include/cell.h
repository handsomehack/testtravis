#ifndef CELL_H
#define CELL_H
#include <vector3d.h>
#include <material.h>

/// This is a brief description for this class
/// Hello World
/// This is detailed description
class Cell
{
	friend class Model; //let Model class to access the protected data
	friend class FileIOEvent;

public:
	/// Default constructor
	Cell();

	/// get the ID of a cell 
	int get_cell_ID();

	/// Get the type of a cell
	char get_cell_type();
    
	virtual~ Cell(){}; //destructor， make it virtual in case the derived classes object was creating on the heap,if tring to deallocate the memory,then the derived class destructor can be called first.

	/// Allow other shape classes to access to the correct getVolume() function
	/// @returns Volume of Shape
	virtual double getVolume();

	/// Allow other shape classes to access to the correct getCenterOfGravity() function
	/// @returns Center of Shape in X,Y,Z coordinate
	virtual vector3D getCenterOfGravity();

	/// Allow other shape classes to access to the correct getWeight() function
	/// @param volume This describes volume
	/// @returns Weight of Shape
	/// @see getVolume()
	virtual double getWeight(const double &volume);

protected:
	Material *M;
	vector3D *cell_vertices;
	int *ID;
	char *Shape;
};

#endif // CELL_H
