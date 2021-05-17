#include <vector3d.h>
#include <material.h>
#include <cell.h>
#include <pyramid.h>
#include <tetrahedron.h>
#include <hexahedron.h>



ostream& operator<<(ostream &os, vector3D &v)
{

    return os << "[" << v.X << "," << v.Y << "," << v.Z << "]"; // display the result in [x,y,z] format
}


int Run_Test(Cell* c){

    if(c->getVolume()==44 && c->getCenterOfGravity()==vector3D(-1,3.2,2.2, -2.4)){
        return  0;
    }
    else
        return 1;

}


int main(){


    vector3D vertices[4]={vector3D(0, 0.0, 0.0, 0.0),vector3D(1,4.0,0.0,0.0),vector3D(2,4.0,6.0,0.0),vector3D(3,4.0,0.0,4.0)};
    vector3D Pvertices[5] = {vector3D(0, 1.0, 1.0, 0.0),vector3D(1,5.0,1.0,0.0),vector3D(2,6.0,1.0,-6.0),vector3D(3,1.0,1.0,-4.0),vector3D(4, 3.0, 7.0, -2.0)};
    vector3D Hvertices[8]={vector3D(0, 0.0, 0.0, 0.0),vector3D(1,4.0,0.0,0.0),vector3D(2,4.0,6.0,0.0),vector3D(3,0.0,4.0,0.0),vector3D(4, 0.0, 0.0, 4.0),vector3D(5,4.0,0.0,4.0),vector3D(6,4.0,7.0,4.0),vector3D(7,0.0,4.0,4.0)};
    Material m1(0,"copper","b87373",8940);


    int ID_0=0, ID_1=1 ,ID_2=2;
    char a='t', b='h', c='p';
    Tetrahedron t(&ID_0,&m1,&a,vertices);
    Hexahedron h(&ID_1,&m1,&b,Hvertices);
    Pyramid p(&ID_2,&m1,&c,Pvertices);


    return Run_Test(&p);


}