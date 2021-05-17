#ifndef MODEL_H
#define MODEL_H
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <vector3d.h>
#include <material.h>
#include <cell.h>
#include <memory>


class Model
{
    friend class FileIOEvent;

public:

    void Read_from_A_file(const string &fileName);  //function to Read VTk style data from a file

    void Write_to_A_file(const string &fileName);   //function to write VTK style data to a file 

    void vertices_parser(const string &dataline);   //function to parse the vertices and push_back into a vector array

    void material_parser(const string &dataline);   //function to parse the materials and push_back into a material array 

    void cell_parser(const string &dataline);       //function to parse the cells of index<10 and push_back into a cell array   

    void cell_parser_index_greater_than_10(const string &dataline);   //function to parse the cells of index >=10 and push_back into a cell array 

    void cell_parser_index_greater_than_100(const string &dataline);   //function to parse the cells of index >=100 and push_back into a cell array 

    int get_material_num()const;   //function to get the number of materials 

    int get_vertex_num()const;    //function to get the number of the vertices

    int get_Cell_num()const;      //function to get the number of the cells

    char get_cell_type(const int &cell_ID)const;   //function to get the type of a cell of a specified ID
    
    vector3D get_center(const int &cell_ID)const;   //function to get the center of a cell of a specified ID

    vector3D* get_vertices(const int &cell_ID); //function to get the all the vertices of a cell of a specified ID


private:
    vector<vector3D> points; //array to store vertices

    vector<Material> Materials;  //array to store materials 

    vector<unique_ptr<Cell>> Cells;    //array to store cells 
};
#endif 
