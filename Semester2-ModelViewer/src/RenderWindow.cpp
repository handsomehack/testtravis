#include <RenderWindow.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkAxesActor.h>
#include <VTKPipeLine.h>
#include <DataInventory.h>
#include <vtkCubeAxesActor.h>
#include <vtkTextProperty.h>
#include <CameraReaction.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkNamedColors.h>
#include <vtkPlane.h>
#include <vtkClipPolyData.h>
#include <vtkImplicitPlaneWidget2.h>
#include <vtkImplicitPlaneRepresentation.h>
#include <vtkIPWCallback.hpp>
#include <vtkBoxWidget2.h>
#include <vtkBoxCallBack.hpp>



RenderWindow::RenderWindow()
{
    //allocate memory
    mWidget=vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    mRenderer=vtkSmartPointer<vtkRenderer>::New();
    mRenderWindow=vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    mAxes=vtkSmartPointer<vtkAxesActor>::New();
    mAxisGrid=vtkSmartPointer<vtkCubeAxesActor>::New();
    this->Init_Axis_Grid_Actor();

}

RenderWindow& RenderWindow::Get_Instance() {
    //create and return the singleton
    static RenderWindow Singleton;
    return Singleton;
}


void RenderWindow::Add_Actor(const vtkSmartPointer<vtkActor>& Actor) {
    //add actor to the renderer
    mRenderer->AddActor(Actor);

}

void RenderWindow::Init_Axes_Actor() {

    //set up axes acotr
    mAxes->SetTotalLength(1.5, 1.5, 1.5);
    mWidget->SetViewport(0.0, 0.0, 0.25, 0.25);
    mWidget->SetOrientationMarker(mAxes);
    mWidget->SetInteractor(mRenderWindow->GetInteractor());
    mWidget->SetEnabled(1);
    mWidget->SetInteractive(false);
    this->Render();

}

void RenderWindow::Establish_PipeLine(VTKPipeLine& Pipeline) {
    //generic vtk pipeline Source->mapper->actor ->renderer
    Pipeline.Source_To_Mapper();
    Pipeline.Actor_To_Renderer();

}

void RenderWindow::Render() {
    //render
    mRenderWindow->Render();

}

void RenderWindow::Reset_Camera(const QString& ModelName) {
    // reset the camera
    if (Data_Inventory.Get_Value_From_BoundSet(ModelName) != nullptr) {
        mRenderer->ResetCamera(Data_Inventory.Get_Value_From_BoundSet(ModelName));
        mRenderer->ResetCameraClippingRange(Data_Inventory.Get_Value_From_BoundSet(ModelName));
    }
}


void RenderWindow::Set_Window_Background_Color(const double &r, const double &g, const double &b) {
   // set the background color
    mRenderer->SetBackground(r,g,b);
}

void RenderWindow::Show_Actor(const QString &ActorName) {
    //find the actor from the inventory and reset the camera to a good position
    Data_Inventory.Get_Value_From_ActorSet(ActorName)->VisibilityOn();
    this->Reset_Camera(ActorName);
    this->Render();

}

void RenderWindow::Hide_Actor(const QString &ActorName) {
    //find the actor from the inventory and hide it
    Data_Inventory.Get_Value_From_ActorSet(ActorName)->VisibilityOff();
    this->Render();

}

void RenderWindow::Remove_Actor(const QString &ActorName) {
    //remove actor from the renderer and inventory
    mRenderer->RemoveActor(Data_Inventory.Get_Value_From_ActorSet(ActorName));
    Data_Inventory.ActorSet_Pop_Back(ActorName);
    this->Render();
}

void RenderWindow::Show_Axis_Grid_Actor(const QString& SourceName) {
    //show axis grid based on the current model
    mAxisGrid->SetBounds(Data_Inventory.Get_Value_From_BoundSet(SourceName));
    mAxisGrid->VisibilityOn();

}

void RenderWindow::Init_Axis_Grid_Actor() {

    //init the axis grid
    mAxisGrid->SetCamera(Active_Camera.Get_Camera());
    mAxisGrid->GetTitleTextProperty(0)->SetColor(1.0, 0.0, 0.0);
    mAxisGrid->GetLabelTextProperty(0)->SetColor(1.0, 0.0, 0.0);

    mAxisGrid->GetTitleTextProperty(1)->SetColor(0.0, 1.0, 0.0);
    mAxisGrid->GetLabelTextProperty(1)->SetColor(0.0, 1.0, 0.0);

    mAxisGrid->GetTitleTextProperty(2)->SetColor(0.0, 0.0, 1.0);
    mAxisGrid->GetLabelTextProperty(2)->SetColor(0.0, 0.0, 1.0);

    mAxisGrid->DrawXGridlinesOn();
    mAxisGrid->DrawYGridlinesOn();
    mAxisGrid->DrawZGridlinesOn();

    mAxisGrid->SetGridLineLocation(
            mAxisGrid->VTK_GRID_LINES_FURTHEST);

    mAxisGrid->XAxisMinorTickVisibilityOff();
    mAxisGrid->YAxisMinorTickVisibilityOff();
    mAxisGrid->ZAxisMinorTickVisibilityOff();
    mAxisGrid->VisibilityOff();
    mRenderer->AddActor(mAxisGrid);
    Data_Inventory.ActorSet_Push_Back("Axis Grid",mAxisGrid);

}

void RenderWindow::Show_Orientation_Axes_Actor() {
    //show axis actor
    mAxes->VisibilityOn();
    this->Render();
}

void RenderWindow::Hide_Orientation_Axes_Actor() {
    //hide axis actor
    mAxes->VisibilityOff();
    this->Render();

}

void RenderWindow::Show_Clipping_Plane_Actor(const vtkSmartPointer<vtkPlane>& Plane, const vtkSmartPointer<vtkActor>& Actor) {

    // The callback will do the work
    vtkNew<vtkIPWCallback> myCallback;
    myCallback->Plane = Plane;
    myCallback->Actor = Actor;

    vtkNew<vtkImplicitPlaneRepresentation> rep;
    rep->SetPlaceFactor(1.25); // This must be set prior to placing the widget
    rep->PlaceWidget(Actor->GetBounds());
    rep->SetNormal(Plane->GetNormal());

    mPlaneWidget = vtkSmartPointer<vtkImplicitPlaneWidget2>::New();
    mPlaneWidget->SetInteractor(mRenderWindow->GetInteractor());
    mPlaneWidget->SetRepresentation(rep);
    mPlaneWidget->AddObserver(vtkCommand::InteractionEvent, myCallback);
    mPlaneWidget->On();

}

void RenderWindow::Hide_Clipping_Plane_Actor() {
    //hide clipping plane
    mPlaneWidget->Off();

}

void RenderWindow::Show_Box_Widget(const QString& SourceName) {

    mBoxWidget=vtkSmartPointer<vtkBoxWidget2>::New();
    mBoxWidget->SetInteractor(mRenderWindow->GetInteractor());
    mBoxWidget->GetRepresentation()->SetPlaceFactor(1); // Default is 0.5
    mBoxWidget->GetRepresentation()->PlaceWidget(Data_Inventory.Get_Value_From_BoundSet(SourceName));

    // Set up a callback for the interactor to call so we can manipulate the actor
    vtkNew<vtkBoxCallBack> boxCallback;
    boxCallback->SetActor(Data_Inventory.Get_Value_From_ActorSet(SourceName));
    mBoxWidget->AddObserver(vtkCommand::InteractionEvent, boxCallback);
    mBoxWidget->On();
    this->Render();

}

void RenderWindow::Hide_Box_Widget() {
    //hide box widget
    mBoxWidget->Off();
    this->Render();

}



