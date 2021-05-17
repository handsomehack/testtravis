#include <model.h>
#include <iostream>
using namespace std;


//output file stream
ostream& operator<<(ostream& os, vector3D &v)
{

    return os <<"v "<< v.Index << " " << v.X << " " << v.Y << " " << v.Z;
}

ostream& operator<<(ostream& os, Material &m)
{

    os<<"m "<<m.ID<<" "<< m.Density<<" "<<m.Colour<<" "<<m.Name;
    return os;
}

//input file stream
istream& operator>>(istream& is, vector3D &v){

    is>>v.Index>>v.X>>v.Y>>v.Z;
    return is;
}

istream& operator>>(istream& is, Material &m){

    is>>m.ID>>m.Density>>m.Colour>>m.Name;
    return is;
}


int Run_Test(Model& m){

    if(m.get_Cell_num()==129 && m.get_material_num()==2 && m.get_vertex_num()==301){
        cout<<"1";
        return 0;
    }
    else
        return 1;

}


int main(){

    Model m1;
    m1.Read_from_A_file("../../Testing/test.txt");
    return Run_Test(m1);
}