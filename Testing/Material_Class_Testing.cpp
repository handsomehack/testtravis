#include <material.h>

int Run_Test(Material& M){

    if(M.get_ID() == 0 && M.get_Name() == "copper" && M.get_Colour() =="b87373" && M.get_Density()==8960 ){
        return 0;
    }
    else
        return 1;
}


int main(){

    Material m1(0,"copper","b87373",8960);

    return Run_Test(m1);

}