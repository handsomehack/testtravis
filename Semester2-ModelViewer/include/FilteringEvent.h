#ifndef FILTERINGEVENT_H
#define FILTERINGEVENT_H
#include <VTKPipeLine.h>
#include <vtkSmartPointer.h>
#include <QAction>
#define Data_Inventory DataInventory::Get_Instance()
#define Render_Window  RenderWindow::Get_Instance()
class vtkOutlineFilter;
class vtkTriangleFilter;
class vtkSmoothPolyDataFilter;
class vtkDataSetSurfaceFilter;
class vtkDelaunay2D;
class vtkClipPolyData;
class vtkCutter;
class vtkShrinkFilter;
class vtkIdTypeArray;
class vtkUnstructuredGrid;
class vtkPolyData;
class vtkMolecule;
class vtkPlane;
using Superclass=VTKPipeLine;


/*
 * Copyright:Group 6
 */


///This class is used to apply filters to the model
class FilteringEvent:public VTKPipeLine
{
public:

    ///This enum holds the available filters to users
    enum class Mode {

        TRIANGULATE,
        OUTLINE,
        SMOOTH,
        CLIP,
        CONTOUR,
        DELAUNAY2D,
        SHRINK,
        CELL_IS,
        CELL_IS_BETWEEN,
        CELL_GREATER_EQUAL_THAN,
        CELL_LESS_EQUAL_THAN,
        CELL_MAX,
        CELL_MIN

    };

    ///constructor of the class
    ///@param SourceName name of the input source of the filter
    ///@param mode the type of the filter to apply on the model
    ///@param Color the color of the model after applying filter on it
    explicit FilteringEvent(QString  SourceName,double* Color, FilteringEvent::Mode mode)
    :mMode(mode),mInputSource(std::move(SourceName)),mColor(Color){};

    ///This method is used to convert unstructuredgrid to polydata
    ///@param UGrid a smart_ptr to unstructuredgrid
    ///@return a smart_ptr to polydata
    static vtkSmartPointer<vtkPolyData> UGrid_To_PolyData(const vtkSmartPointer<vtkUnstructuredGrid>& UGrid);

    ///This method is used to convert molecule to polydata
    ///@param Molecule a smart_ptr to molecule
    ///@return a smart_ptr to polydata
    static vtkSmartPointer<vtkPolyData> Molecule_To_PolyData(const vtkSmartPointer<vtkMolecule>& Molecule);

    ///@note This is a reimplemented method
    ///This method contains the procedure from **source** to **mapper**
    void Source_To_Mapper() override;

    ///@note This is a reimplemented method
    ///This method contains the procedure from **Actor** to **Renderer*
    void Actor_To_Renderer() override;


    ///@note This is a reimplemented method
    ///This method is used to set the Actor's properties
    void Set_Actor_Property() override;

    ///@note This is a reimplemented method
    ///This method is used to store the information of an Actor
    void Store_Model_Data() override;


private:

    ///@attention This method is used internally
    ///This method is important in doing the cell filtering as it is used to extract the cells selected by the users
    void Set_Cell_Selection(const vtkSmartPointer<vtkIdTypeArray>& IDs);

private:

    double* mColor;
    Mode mMode{};
    QString mInputSource;
    vtkSmartPointer<vtkOutlineFilter> mOutlineFilter;
    vtkSmartPointer<vtkTriangleFilter> mTriangleFilter;
    vtkSmartPointer<vtkSmoothPolyDataFilter> mSmoothFilter;
    vtkSmartPointer<vtkDelaunay2D> mDelaunay2DFilter;
    vtkSmartPointer<vtkClipPolyData> mClipFilter;
    vtkSmartPointer<vtkPlane> mClippingPlane;
    vtkSmartPointer<vtkCutter> mCutter;
    vtkSmartPointer<vtkShrinkFilter> mShrinkFilter;
    vtkSmartPointer<vtkUnstructuredGrid> mSelectedCells;

};

#endif // VTKFILTERS_H
