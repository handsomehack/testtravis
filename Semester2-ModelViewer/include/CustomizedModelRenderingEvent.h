#ifndef CUSTOMIZEDMODELRENDERINGEVENT_H
#define CUSTOMIZEDMODELRENDERINGEVENT_H
#include <qvector.h>
#include <VTKPipeLine.h>
#include <vtkSmartPointer.h>
#include <vector3d.h>
#define Data_Inventory DataInventory::Get_Instance()
#define Render_Window  RenderWindow::Get_Instance()
class vtkUnstructuredGrid;
using Superclass=VTKPipeLine;

/*
 * Copyright:Group6
 */


///This class is used to render the primitive cells(e.g.triangle, quad ,pyramid, tetra and etc)
///
///This class also provides the functionality that users can create their own cells by giving the vertex information
class CustomizedModelRenderingEvent: public VTKPipeLine
{
public:

    ///The first three members(i.e.pyramid, tetra, hexa) already had pre-defined vertices
    ///so the users can just directly use them without having to provide the vertex information
    enum class Mode{
        PYRAMID_RENDER,
        TETRA_RENDER,
        HEXA_RENDER,
        USER_DEFINED_RENDER
    };

    ///This enum holds the available cell's type that the users can choose to render by giving corresponding vertex information
    ///VTK provides lots of built-in cell choices, but the rendering procedure is totally the same, so here I am just gonna provide some cells that are commonly used
    enum class CellType{

        VTK_HEXAHEDRON,
        VTK_POLYGON,
        VTK_PYRAMID,
        VTK_TETRA,
        VTK_QUAD,
        VTK_TRIANGLE,
        VTK_LINE

    };


   // explicit CustomizedModelRenderingEvent(CustomizedModelRenderingEvent::Mode mode)
    //:Superclass(VTKPipeLine::MapperType::DATASET_MAPPER),mMode(mode){};

    ///constructor of the class
    ///@param mode the Mode you want(i.e. using pre-defined vertex or defining the vertices manually)
    ///@param cellType the cell's type
    ///@param Color the cell's color
    ///@param VertexList a list of vertices related to the cell
    explicit CustomizedModelRenderingEvent(CustomizedModelRenderingEvent::Mode mode =Mode(), CustomizedModelRenderingEvent::CellType cellType = CellType(),double* Color= nullptr, QVector<vector3D> VertexList=QVector<vector3D>())
    :Superclass(VTKPipeLine::MapperType::DATASET_MAPPER),mMode(mode),mCellType(cellType),mColor(Color),mVertices(std::move(VertexList)){};


    ///@note This is a reimplemented method
    ///This method contains the procedure from **source** to **mapper**
    void Source_To_Mapper() override;

    ///@note This is a reimplemented method
    ///This method contains the procedure from **Actor** to **Renderer**
    void Actor_To_Renderer() override;


    ///@note This is a reimplemented method
    ///This method is used to set the Actor's properties
    void Set_Actor_Property() override;


    ///@note This is a reimplemented method
    ///This method is used to store the information of an Actor
    void Store_Model_Data() override;


private:

    CellType mCellType{};
    Mode mMode{};
    double* mColor{};
    QVector<vector3D>  mVertices;
    vtkSmartPointer<vtkUnstructuredGrid> mUnstructuredGrid;


};

#endif // CUSTOMIZEDMODELRENDERINGEVENT_H
