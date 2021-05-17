#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H
#include <vtkSmartPointer.h>
class VTKPipeLine;
class vtkActor;
class vtkGenericOpenGLRenderWindow;
class vtkRenderer;
class vtkAxesActor;
class vtkOrientationMarkerWidget;
class QString;
class vtkCubeAxesActor;
class vtkImplicitPlaneWidget2;
class vtkPlane;
class vtkBoxWidget2;
#define Data_Inventory DataInventory::Get_Instance()
#define Active_Camera  CameraReaction::Get_Instance()

/*
 * Copyright:Group 6
 */


///This class encapsulate the vtk's renderer ,renderWindow and other graphical widgets
///This class is using Singleton design pattern as there is only one RenderWindow on the GUI
class RenderWindow {
public:

    ///This method is used to get the singleton of this class
    ///@return the reference to the singleton
    static RenderWindow &Get_Instance();

    ///This method is used to establish the pipeline
    ///@param Pipeline a subclass instaance of the vtkpipeline to execute the polymorphism
    static void Establish_PipeLine(VTKPipeLine &Pipeline);

    ///This method is used to set the background color of the RenderWindow
    ///@param r color code of red
    ///@param g color code of green
    ///@param b color code of blue
    void Set_Window_Background_Color(const double &r, const double &g, const double &b);

    ///This method is used to visualize the changes in the scene
    void Render();

    ///This method is used to set the camera to a desired position based on the bounds of the model so that the model can be seen by the users
    ///@param ModelName the name of the model
    void Reset_Camera(const QString &ModelName);

    ///This method is used to add actor to the render
    ///@param Actor a smart_ptr to the actor
    void Add_Actor(const vtkSmartPointer<vtkActor> &Actor);

    ///This method is used to show the actor selected by the users in the GUI's treeWidget
    ///for example, when the users check the checkbox on an treeWidgetItem
    ///@param the name of the actor
    void Show_Actor(const QString &ActorName);

    ///This method is used to hide the actor selected by the users in the GUI's treeWidget
    ///for example, when the users uncheck the checkbox on an treeWidgetItem
    ///@param the name of the actor
    void Hide_Actor(const QString &ActorName);

    ///This method is used to remove the actor selected by the users in the GUI's treeWidget
    ///for example, when the users use right-clicked menu to delete the treeWidgetItem
    ///@param the name of the actor
    void Remove_Actor(const QString &ActorName);

    ///This method is used to get the renderer
    ///@return a smart_ptr to the renderer
    vtkSmartPointer<vtkRenderer> Get_Renderer() const { return mRenderer; };

    ///This method is used to get the renderWindow
    ///@return a smart_ptr to the renderWindow
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> Get_RenderWindow() const { return mRenderWindow; };

    ///This method is used to inti the axes actor to visualize the current x-y-z directions withe respect to the model
    void Init_Axes_Actor();

    ///This method is used to init the axes grid actor to do some measurements on the model
    void Show_Axis_Grid_Actor(const QString& SourceName);

    ///This method is used to show the axes actor when the users interact with the checkbox
    void Show_Orientation_Axes_Actor();

    ///This method is used to hide the axes actor when the  users interact with the checkbox
    void Hide_Orientation_Axes_Actor();

    ///This method is used to show the clipping plane around a model
    ///@param Plane the current clipping plane
    ///@param Actor the name of the actor(Model)
    void Show_Clipping_Plane_Actor(const vtkSmartPointer<vtkPlane>& Plane, const vtkSmartPointer<vtkActor>& Actor);

    ///This method is used to hide the clipping plane
    void Hide_Clipping_Plane_Actor();

    ///This method is used to show the box widget, which can be used to scale the actor
    void Show_Box_Widget(const QString& SourceName);

    ///This method is used to hide the box widget
    void Hide_Box_Widget();


    RenderWindow(const RenderWindow&)= delete;

    RenderWindow& operator=(const RenderWindow&)= delete;

private:
    //constructor  of the class
    RenderWindow();

    ///@attention This method is used internally in this class
    ///This method is used to init the Axis grid actor
    void Init_Axis_Grid_Actor();

private:

    vtkSmartPointer<vtkGenericOpenGLRenderWindow> mRenderWindow;
    vtkSmartPointer<vtkRenderer> mRenderer;
    vtkSmartPointer<vtkAxesActor> mAxes;
    vtkSmartPointer<vtkCubeAxesActor> mAxisGrid;
    vtkSmartPointer<vtkOrientationMarkerWidget> mWidget;
    vtkSmartPointer<vtkImplicitPlaneWidget2> mPlaneWidget;
    vtkSmartPointer<vtkBoxWidget2> mBoxWidget;

};


#endif // VTKRENDERWINDOW_H
