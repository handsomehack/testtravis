#ifndef BUILTINSOURCESRENDERINGEVENT_H
#define BUILTINSOURCESRENDERINGEVENT_H
#include <VTKPipeLine.h>
#include <vtkSmartPointer.h>
#define Data_Inventory DataInventory::Get_Instance()
#define Render_Window  RenderWindow::Get_Instance()
class vtkCubeSource;
class vtkSphereSource;
class vtkConeSource;
class vtkCylinderSource;
class vtkDiskSource;
class vtkLineSource;
class vtkArrowSource;
class vtkEarthSource;
using Superclass=VTKPipeLine;



/*
 * Copyright: Group6
 *
 */

///The BuiltInSourceRenderingEvent class is used for rendering the Built-in sources from the vtk library
///
///VTK library already provided a number of sources, So the users don't need to create some of the models from scratch
///
/// ### Example
///  BuiltInSourceRenderingEvent CubeRender(BuiltInSourceRenderingEvent::Mode::CUBE_RENDER);
///
class BuiltInSourceRenderingEvent : public VTKPipeLine {


public:

    ///This enum holds the sources available to the users
    ///VTK provides lots of built-in source, but the rendering procedure is totally the same, so here I am just gonna provide some sources that are commonly used
    enum class Mode {

        CUBE_RENDER,
        SPHERE_RENDER,
        CONE_RENDER,
        CYLINDER_RENDER,
        DISK_RENDER,
        LINE_RENDER,
        ARROW_RENDER
    };


    ///The constructor of the class
    ///@param mode the source that the users want to render
    explicit BuiltInSourceRenderingEvent(BuiltInSourceRenderingEvent::Mode mode)
    : Superclass(MapperType::POLY_MAPPER),mMode(mode){};


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


    BuiltInSourceRenderingEvent(const BuiltInSourceRenderingEvent& )= delete;

    BuiltInSourceRenderingEvent& operator=(const BuiltInSourceRenderingEvent& )= delete;


private:

    Mode mMode{};
    vtkSmartPointer<vtkCubeSource> mCubeSource;
    vtkSmartPointer<vtkSphereSource> mSphereSource;
    vtkSmartPointer<vtkConeSource> mConeSource;
    vtkSmartPointer<vtkCylinderSource> mCylinderSource;
    vtkSmartPointer<vtkDiskSource> mDiskSource;
    vtkSmartPointer<vtkLineSource> mLineSource;
    vtkSmartPointer<vtkArrowSource> mArrowSource;
    vtkSmartPointer<vtkEarthSource> mEarthSource;

};

#endif
