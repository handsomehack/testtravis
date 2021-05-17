#include <vector3d.h>


bool add(vector3D& V1,vector3D& V2){

    return ( V1+V2 == vector3D(-1,3,3,3)) ? 1:0;

}


bool subtract(vector3D& V1, vector3D& V2){

    return (V1-V2 == vector3D(-1,-1,-1,-1)) ? 1:0;

}


bool divide(vector3D& V){


    return (V/2 == vector3D(-1,1,1,1)) ? 1:0;

}

bool ScalarProduct(vector3D& V1 , vector3D& V2){

    return (V1*V2 == 6)? 1:0;

}


int Run_Test(vector3D& v1, vector3D& v2){


    if(add(v1, v2)  &&  subtract(v1, v2) && divide(v2) && ScalarProduct(v1,v2)){
        return 0;
    }
    else
        return 1;


}



int main(){

    vector3D v1(0,1,1,1);
    vector3D v2(1,2,2,2);
    return Run_Test(v1,v2);

}
