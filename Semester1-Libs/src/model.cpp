#include "model.h"
#include <hexahedron.h>
#include <tetrahedron.h>
#include <pyramid.h>
#include <string.h>
using namespace std;

//======================================================================================
//function to parse the vertices and push_back into a vector array
void Model::vertices_parser(const string &dataline)
{
     //--------------------------------------------------------------
     // To ignore the the first letter 'v' ,for example if the dataline= "v 0 0.00195 0.00115 0.0015"
     // then the sorted would be " 0 0.00195 0.00115 0.0015 "
     string sorted;
     for (int i = 0; dataline[i] != '\0'; i++)
     {

          sorted.push_back(dataline[i + 1]);
     }

     //--------------------------------------------------------------
     //using the sorted dataline to construct a temp vector3D object, and push this object into a vector array
     vector3D temp;
     istringstream mydata(sorted);
     for (; mydata >> temp;) //@notice ,the >> operator needs to be overload, see the main function for implmentation
     {
          
          this->points.push_back(temp);
     }
}

//======================================================================================
//function to parse the materials and push_back into a vector array
void Model::material_parser(const string &dataline)
{
     //--------------------------------------------------------------
     // To ignore the the first letter 'm' ,for example if the dataline= "m 0 8940 b87333 cu"
     // then the sorted would be " 0 8940 b87333 cu "
     string sorted;
     for (int i = 0; dataline[i] != '\0'; i++)
     {

          sorted.push_back(dataline[i + 1]);
     }

     //--------------------------------------------------------------
     //using the sorted dataline to construct a temp Material object, and push this object into a vector array
     Material temp;
     istringstream mydata(sorted);
     for (; mydata >> temp;) //@notice ,the >> operator needs to be overload, see the main function for implmentation
     {
          
          this->Materials.push_back(temp);
     }
}

//======================================================================================
//function to parse the cells of index<10 and push_back into a cell array
void Model::cell_parser(const string &dataline)
{
     //for example if the dataline is "c 5 h 0 20 21 23 22 24 25 27 26"

     //----------------------------------------------------------------------------------------
     //get the ID of the cell and convert the sting to int type, in this case that would be 5
     string str0;

     str0.push_back(dataline[2]);

     int *Cell_ID = new int(stoi(str0)); //allocating  memory to store the ID

     //----------------------------------------------------------------------------------------
     //get the tyep of the cell, in this case that would be h

     char *temp_type = new char(dataline[4]); //allocating  memory to store the type

     //----------------------------------------------------------------------------------------
     //get the ID of the material and convert the string to int type, in this case that would be 0
     string str1;
     str1.push_back(dataline[6]);
     int *material_ID = new int(stoi(str1)); //allocating  memory to store the ID

     //-----------------------------------------------------------------------------------------
     //get the all the vertices ID and push them into a vector array , in this case that would be 20 21 23 22 24 25 27 26
     string vertices;
     for (int i = 7; dataline[i] != '\0'; i++)
     {
          vertices.push_back(dataline[i + 1]);
     }
     istringstream ss(vertices);
     vector<int> vertices_IDs;
     int i = 0;
     while (ss >> i)
     {
          vertices_IDs.push_back(i);
     }

     //--------------------------------------------------------------------------------------------
     int num_vertices = (vertices_IDs.size()); //calculate how many vertices of a cell ,in this case the cell is a hexahedron, so that would be 8 vertices in total

     vector3D *temp_v = new vector3D[num_vertices]; // allocating memory to construct each vertex

     Material *temp_m = new Material(); //allocating memory to construct the Material

     //---------------------------------------------------------------------------------------------
     //because the cell could be hexahedron/pyramid/tetrahedron, so i need to determine what kind of cell i am going to construct
     //this if statement is for constructing a tetrahedron
     if (num_vertices == 4)
     {
          // do the index matching with all the Materials that have been stored in the vector array
          // previouly I extracted the ID of the Material in a cell dataline, so matching it with each Material that has been stored in the vector array
          for (vector<Material>::const_iterator m_it = this->Materials.begin(); m_it != this->Materials.end(); m_it++)
          {
               //if the indices matched ,do the assignment
               if (*material_ID == (*m_it).get_ID())
               {
                    *temp_m = (*m_it);
               }
          }

          // same as above ,but this block is for matching and constructing each vertex
          for (int i = 0; i < num_vertices; i++)
          {
               for (vector<vector3D>::const_iterator v_it = this->points.begin(); v_it != this->points.end(); v_it++)
               {
                    if (vertices_IDs[i] == (*v_it).get_ID())
                    {
                         temp_v[i] = (*v_it);
                    }
               }
          }

          //construct a tetrahedron using all the data acquired so far

          Cells.push_back(make_unique<Tetrahedron>(Cell_ID, temp_m, temp_type, temp_v)); //pushing the tetrahedron into the vector<Cell*> container
     }

     // idea is the same as above for tetrahedron ,but this time is for constructing a pyramid
     if (num_vertices == 5)
     {
          for (vector<Material>::const_iterator m_it = this->Materials.begin(); m_it != this->Materials.end(); m_it++)
          {

               if (*material_ID == (*m_it).get_ID())
               {
                    *temp_m = (*m_it);
               }
          }

          for (int i = 0; i < num_vertices; i++)
          {
               for (vector<vector3D>::const_iterator v_it = this->points.begin(); v_it != this->points.end(); v_it++)
               {
                    if (vertices_IDs[i] == (*v_it).get_ID())
                    {
                         temp_v[i] = (*v_it);
                    }
               }
          }

          //Pyramid *temp_p = new Pyramid(Cell_ID, temp_m, temp_type, temp_v);
          Cells.push_back(make_unique<Pyramid>(Cell_ID, temp_m, temp_type, temp_v));
     }

     // idea is the same as above for tetrahedron ,but this time is for constructing a hexahedron
     if (num_vertices == 8)
     {

          for (vector<Material>::const_iterator m_it = this->Materials.begin(); m_it != this->Materials.end(); m_it++)
          {

               if (*material_ID == (*m_it).get_ID())
               {
                    *temp_m = (*m_it);
               }
          }

          for (int i = 0; i < num_vertices; i++)
          {
               for (vector<vector3D>::const_iterator v_it = this->points.begin(); v_it != this->points.end(); v_it++)
               {
                    if (vertices_IDs[i] == (*v_it).get_ID())
                    {
                         temp_v[i] = (*v_it);
                    }
               }
          }

         // Hexahedron *temp_h = new Hexahedron(Cell_ID, temp_m, temp_type, temp_v);
          Cells.push_back(make_unique<Hexahedron>(Cell_ID, temp_m, temp_type, temp_v));
     }

     //free the allocating memory for constructing a cell
     delete[] temp_v;
     temp_v = NULL;

     delete temp_m;
     temp_m = NULL;

     delete Cell_ID;
     Cell_ID = NULL;

     delete material_ID;
     material_ID = NULL;

     delete temp_type;
     temp_type = NULL;
}

//======================================================================================
//function to parse the cells of index>=10 and push_back into a cell array
//@notice the idea is basically the same as the function above , the only difference is the index of the string dataline changes
//so i am not going to explain in to more detail.
void Model::cell_parser_index_greater_than_10(const string &dataline)
{

     //----------------------------------------------------------------------------------------

     string str0;
     for (int i = 2; i < 4; i++)
     {

          str0.push_back(dataline[i]);
     }
     int *Cell_ID = new int(stoi(str0));

     //----------------------------------------------------------------------------------------

     char *temp_type = new char(dataline[5]);

     //----------------------------------------------------------------------------------------

     string str1;
     str1.push_back(dataline[7]);
     int *material_ID = new int(stoi(str1));

     //-----------------------------------------------------------------------------------------

     string vertices;
     for (int i = 8; dataline[i] != '\0'; i++)
     {
          vertices.push_back(dataline[i + 1]);
     }
     istringstream ss(vertices);
     vector<int> vertices_IDs;
     int i = 0;
     while (ss >> i)
     {
          vertices_IDs.push_back(i);
     }

     //--------------------------------------------------------------------------------------------
     int num_vertices = (vertices_IDs.size());
     vector3D *temp_v = new vector3D[num_vertices];
     Material *temp_m = new Material();
     //---------------------------------------------------------------------------------------------
     if (num_vertices == 4)
     {

          for (vector<Material>::const_iterator m_it = this->Materials.begin(); m_it != this->Materials.end(); m_it++)
          {

               if (*material_ID == (*m_it).get_ID())
               {
                    *temp_m = (*m_it);
               }
          }

          for (int i = 0; i < num_vertices; i++)
          {
               for (vector<vector3D>::const_iterator v_it = this->points.begin(); v_it != this->points.end(); v_it++)
               {
                    if (vertices_IDs[i] == (*v_it).get_ID())
                    {
                         temp_v[i] = (*v_it);
                    }
               }
          }
          //Tetrahedron *temp_t = new Tetrahedron(Cell_ID, temp_m, temp_type, temp_v);

          Cells.push_back(make_unique<Tetrahedron>(Cell_ID, temp_m, temp_type, temp_v));
     }

     if (num_vertices == 5)
     {
          for (vector<Material>::const_iterator m_it = this->Materials.begin(); m_it != this->Materials.end(); m_it++)
          {

               if (*material_ID == (*m_it).get_ID())
               {
                    *temp_m = (*m_it);
               }
          }

          for (int i = 0; i < num_vertices; i++)
          {
               for (vector<vector3D>::const_iterator v_it = this->points.begin(); v_it != this->points.end(); v_it++)
               {
                    if (vertices_IDs[i] == (*v_it).get_ID())
                    {
                         temp_v[i] = (*v_it);
                    }
               }
          }

          //Pyramid *temp_p = new Pyramid(Cell_ID, temp_m, temp_type, temp_v);
          Cells.push_back(make_unique<Pyramid>(Cell_ID, temp_m, temp_type, temp_v));
     }

     if (num_vertices == 8)
     {

          for (vector<Material>::const_iterator m_it = this->Materials.begin(); m_it != this->Materials.end(); m_it++)
          {

               if (*material_ID == (*m_it).get_ID())
               {
                    *temp_m = (*m_it);
               }
          }

          for (int i = 0; i < num_vertices; i++)
          {
               for (vector<vector3D>::const_iterator v_it = this->points.begin(); v_it != this->points.end(); v_it++)
               {
                    if (vertices_IDs[i] == (*v_it).get_ID())
                    {
                         temp_v[i] = (*v_it);
                    }
               }
          }

        //  Hexahedron *temp_h = new Hexahedron(Cell_ID, temp_m, temp_type, temp_v);
          Cells.push_back(make_unique<Hexahedron>(Cell_ID, temp_m, temp_type, temp_v));
     }

     delete[] temp_v;
     temp_v = NULL;

     delete temp_m;
     temp_m = NULL;

     delete Cell_ID;
     Cell_ID = NULL;

     delete material_ID;
     material_ID = NULL;

     delete temp_type;
     temp_type = NULL;
}

//======================================================================================
//function to parse the cells of index>=100 and push_back into a cell array
//@notice the idea is basically the same as the function above , the only difference is the index of the string dataline changes
//so i am not going to explain in to more detail.
void Model::cell_parser_index_greater_than_100(const string &dataline)
{

     //----------------------------------------------------------------------------------------
     //only thing to notice! when the cell index>=10 ( c 10 h 0 20 21 23 22 24 25 27 26 )
     //the 10 is seperated in a string, i.e., '1' and '0', so i have use a for loop to group them together as an integer '10'
     string str0;
     for (int i = 2; i < 5; i++)
     {

          str0.push_back(dataline[i]);
     }
     int *Cell_ID = new int(stoi(str0));

     //----------------------------------------------------------------------------------------

     char *temp_type = new char(dataline[6]);

     //----------------------------------------------------------------------------------------

     string str1;
     str1.push_back(dataline[8]);
     int *material_ID = new int(stoi(str1));

     //-----------------------------------------------------------------------------------------

     string vertices;
     for (int i = 9; dataline[i] != '\0'; i++)
     {
          vertices.push_back(dataline[i + 1]);
     }
     istringstream ss(vertices);
     vector<int> vertices_IDs;
     int i = 0;
     while (ss >> i)
     {
          vertices_IDs.push_back(i);
     }

     //--------------------------------------------------------------------------------------------
     int num_vertices = (vertices_IDs.size());
     vector3D *temp_v = new vector3D[num_vertices];
     Material *temp_m = new Material();
     //---------------------------------------------------------------------------------------------
     if (num_vertices == 4)
     {

          for (vector<Material>::const_iterator m_it = this->Materials.begin(); m_it != this->Materials.end(); m_it++)
          {

               if (*material_ID == (*m_it).get_ID())
               {
                    *temp_m = (*m_it);
               }
          }

          for (int i = 0; i < num_vertices; i++)
          {
               for (vector<vector3D>::const_iterator v_it = this->points.begin(); v_it != this->points.end(); v_it++)
               {
                    if (vertices_IDs[i] == (*v_it).get_ID())
                    {
                         temp_v[i] = (*v_it);
                    }
               }
          }
          //Tetrahedron *temp_t = new Tetrahedron(Cell_ID, temp_m, temp_type, temp_v);

          Cells.push_back(make_unique<Tetrahedron>(Cell_ID, temp_m, temp_type, temp_v));
     }

     if (num_vertices == 5)
     {
          for (vector<Material>::const_iterator m_it = this->Materials.begin(); m_it != this->Materials.end(); m_it++)
          {

               if (*material_ID == (*m_it).get_ID())
               {
                    *temp_m = (*m_it);
               }
          }

          for (int i = 0; i < num_vertices; i++)
          {
               for (vector<vector3D>::const_iterator v_it = this->points.begin(); v_it != this->points.end(); v_it++)
               {
                    if (vertices_IDs[i] == (*v_it).get_ID())
                    {
                         temp_v[i] = (*v_it);
                    }
               }
          }

          //Pyramid *temp_p = new Pyramid(Cell_ID, temp_m, temp_type, temp_v);
          Cells.push_back(make_unique<Pyramid>(Cell_ID, temp_m, temp_type, temp_v));
     }

     if (num_vertices == 8)
     {

          for (vector<Material>::const_iterator m_it = this->Materials.begin(); m_it != this->Materials.end(); m_it++)
          {

               if (*material_ID == (*m_it).get_ID())
               {
                    *temp_m = (*m_it);
               }
          }

          for (int i = 0; i < num_vertices; i++)
          {
               for (vector<vector3D>::const_iterator v_it = this->points.begin(); v_it != this->points.end(); v_it++)
               {
                    if (vertices_IDs[i] == (*v_it).get_ID())
                    {
                         temp_v[i] = (*v_it);
                    }
               }
          }

         // Hexahedron *temp_h = new Hexahedron(Cell_ID, temp_m, temp_type, temp_v);
          Cells.push_back(make_unique<Hexahedron>(Cell_ID, temp_m, temp_type, temp_v));
     }

     delete[] temp_v;
     temp_v = NULL;

     delete temp_m;
     temp_m = NULL;

     delete Cell_ID;
     Cell_ID = NULL;

     delete material_ID;
     material_ID = NULL;

     delete temp_type;
     temp_type = NULL;
}

//====================================================================================
//function to Read VTk style data from a file
void Model::Read_from_A_file(const string &fileName)
{

     ifstream myfile(fileName);
     string dataline;
     if (myfile.is_open())
     {
          //get each line in a file
          for (; getline(myfile, dataline);)
          {

               //if the line is for a vector, then go to the vertices_parser function
               if (dataline[0] == 'v')
               {

                    this->vertices_parser(dataline);
               }

               //if the line is for a Material, then go to the material_parser function
               if (dataline[0] == 'm')
               {

                    this->material_parser(dataline);
               }

               //if the line is for a cell , then go to one of these functions below
               if (dataline[0] == 'c')
               {

                    // To parse cell's index greater equal than 100
                    if (this->get_Cell_num() >= 100)
                    {

                         this->cell_parser_index_greater_than_100(dataline);
                    }

                    // To parse cell's index greater equal than 10 but less than 100
                    if (this->get_Cell_num() >= 10 && this->get_Cell_num() < 100)
                    {

                         this->cell_parser_index_greater_than_10(dataline);
                    }

                    // To parse cell's index below 10
                    if (this->get_Cell_num() < 10)
                    {
                         this->cell_parser(dataline);
                    }
               }
          }
          myfile.close();
     }
     else
     {
          cout << "can't not open the file! please check again"<<endl;
     }
}

//====================================================================================
//function to write VTk style data to a file
void Model ::Write_to_A_file(const string &fileName)
{

     ofstream myfile(fileName);

     //write each material data stored in the Materials array to a file
     for (int i = 0; i < this->Materials.size(); i++)
     {

          myfile << this->Materials[i] << endl;
     }

     //write each vertex data stored in the vertices array to a file
     for (int i = 0; i < this->points.size(); i++)
     {

          myfile << this->points[i] << endl;
     }

     //write each cell data stored in the cells array to a file
     for (int j = 0; j < this->Cells.size(); j++)
     {

          myfile << "c"<< " " << this->Cells[j]->get_cell_ID() << " " << this->Cells[j]->get_cell_type() << " " << this->Cells[j]->M->get_ID() << " ";
          //write data in tetrahedron format 
          if (this->Cells[j]->get_cell_type() == 't')
          {

               for (int i = 0; i < 4; i++)
               {

                    myfile << this->Cells[j]->cell_vertices[i].get_ID() << " ";
               }
          }
 
          //write data in pyramid format 
          if (this->Cells[j]->get_cell_type() == 'p')
          {

               for (int i = 0; i < 5; i++)
               {

                    myfile << this->Cells[j]->cell_vertices[i].get_ID() << " ";
               }
          }

          //write data in hexahedron format 
          if (this->Cells[j]->get_cell_type() == 'h')
          {

               for (int i = 0; i < 8; i++)
               {

                    myfile << this->Cells[j]->cell_vertices[i].get_ID() << " ";
               }
          }

          myfile << endl;
     }
}



//====================================================================================
//function to get the number of cells in the model 
int Model::get_Cell_num() const
{

     return this->Cells.size();
}


//====================================================================================
//function to get the number of materials in the model 
int Model::get_material_num() const
{

     return this->Materials.size();
}


//====================================================================================
//function to get the number of vertices in the model 
int Model::get_vertex_num() const
{
     return this->points.size();
}



//====================================================================================
//function to get the type of a cell of a specified ID
char Model::get_cell_type(const int &cell_ID) const
{
     char result = 'x';
     //loop through the array to get the coresponding type 
     for (auto it = this->Cells.begin(); it != Cells.end(); it++)
     {
          if ((*it)->get_cell_ID() == cell_ID)
          {

               result = (*it)->get_cell_type();
          }
     }

     return result;
}


//======================================================================================
//function to get the center of a cell of a specified ID
vector3D Model::get_center(const int &cell_ID) const
{
   
     vector3D result;
     //loop through the array to get the coresponding centorid  
     for (auto it = this->Cells.begin(); it != Cells.end(); it++)
     {
          if ((*it)->get_cell_ID() == cell_ID)
          {

               result = (*it)->getCenterOfGravity();
          }
     }

     return result;
}

//==============================================================================
//get all the vertices that used to construct a polygon 
//rememer to deallocated the memory in the scope where this function is called 
vector3D* Model::get_vertices(const int &cell_ID)
{

    char tem_tpe=this->Cells[cell_ID]->get_cell_type();
    vector3D* vertices=NULL;
    if(tem_tpe == 'h'){
      
      vertices =new vector3D[8];
      for(int i=0;i<8;i++){
      vertices[i]=this->Cells[cell_ID]->cell_vertices[i];
      }

    }

    if(tem_tpe == 'p'){
     
      vertices =new vector3D[5];
      for(int i=0;i<5;i++){
      vertices[i]=this->Cells[cell_ID]->cell_vertices[i];
      }

 
    }

    if(tem_tpe == 't'){

      vertices =new vector3D[4];
      for(int i=0;i<4;i++){
      vertices[i]=this->Cells[cell_ID]->cell_vertices[i];

      }
    }

    return vertices;
}


