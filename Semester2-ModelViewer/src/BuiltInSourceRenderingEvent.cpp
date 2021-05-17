#include <BuiltInSourceRenderingEvent.h>
#include <RenderWindow.h>
#include <vtkCubeSource.h>
#include <vtkSphereSource.h>
#include <vtkConeSource.h>
#include <vtkCylinderSource.h>
#include <vtkDiskSource.h>
#include <vtkLineSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <DataInventory.h>
#include <vtkArrowSource.h>
#include <vtkEarthSource.h>

void BuiltInSourceRenderingEvent::Source_To_Mapper() {

    //The program will automatically choose which branch to go to according to the choice of the user.
    switch (this->mMode) {

        //This method basically contains two step:
        //step 1: allocating memory for the source instance specified by the user.
        //step 2: establish the connection between the Source and Mapper
        case Mode::CUBE_RENDER:
            mCubeSource= vtkSmartPointer<vtkCubeSource>::New();
            mPolyDataMapper->SetInputConnection(mCubeSource->GetOutputPort());
            break;

        case Mode::SPHERE_RENDER:
            mSphereSource= vtkSmartPointer<vtkSphereSource>::New();
            mPolyDataMapper->SetInputConnection(mSphereSource->GetOutputPort());
            break;

        case Mode::CONE_RENDER:
            mConeSource= vtkSmartPointer<vtkConeSource>::New();
            mPolyDataMapper->SetInputConnection(mConeSource->GetOutputPort());
            break;

        case Mode::CYLINDER_RENDER:
            mCylinderSource= vtkSmartPointer<vtkCylinderSource>::New();
            mPolyDataMapper->SetInputConnection(mCylinderSource->GetOutputPort());
            break;

        case Mode::DISK_RENDER:
            mDiskSource= vtkSmartPointer<vtkDiskSource>::New();
            mPolyDataMapper->SetInputConnection(mDiskSource->GetOutputPort());
            break;
        case Mode::LINE_RENDER:
            mLineSource= vtkSmartPointer<vtkLineSource>::New();
            mPolyDataMapper->SetInputConnection(mLineSource->GetOutputPort());
            break;
        case Mode::ARROW_RENDER:
            mArrowSource =  vtkSmartPointer<vtkArrowSource>::New();
            mPolyDataMapper->SetInputConnection(mArrowSource->GetOutputPort());
            break;

    }


}

void BuiltInSourceRenderingEvent::Actor_To_Renderer() {

    //This method basically contains 3 steps:
    //step 1: establish the connection between the Actor and the Mapper
    //step 2: set the Actor's properties
    //step 3: Add the Actor to the scene
    mActor->SetMapper(mPolyDataMapper);
    this->Set_Actor_Property();
    Render_Window.Add_Actor(mActor);

}


void BuiltInSourceRenderingEvent::Set_Actor_Property() {

    //This method sets the actor's color to red
   mActor->GetProperty()->SetColor(1,0,0);

}



void BuiltInSourceRenderingEvent::Store_Model_Data() {

    //This method contains 3 steps:
    //step 1: push the Bounding information associated with actor to the Map container
    //step 2: push the PolyData associated with the actor to the Map container
    //step 3: push the Actor to the Map container
    switch (this->mMode) {

        case Mode::CUBE_RENDER:
            Data_Inventory.BoundSet_Push_Back("Cube", mCubeSource->GetOutput()->GetBounds());
            Data_Inventory.PolyDataSet_Push_Back("Cube",mCubeSource->GetOutput());
            Data_Inventory.ActorSet_Push_Back("Cube", mActor);
            break;

        case Mode::SPHERE_RENDER:
            Data_Inventory.BoundSet_Push_Back("Sphere", mSphereSource->GetOutput()->GetBounds());
            Data_Inventory.PolyDataSet_Push_Back("Sphere",mSphereSource->GetOutput());
            Data_Inventory.ActorSet_Push_Back("Sphere", mActor);
            break;

        case Mode::CONE_RENDER:
            Data_Inventory.BoundSet_Push_Back("Cone", mConeSource->GetOutput()->GetBounds());
            Data_Inventory.PolyDataSet_Push_Back("Cone",mConeSource->GetOutput());
            Data_Inventory.ActorSet_Push_Back("Cone", mActor);
            break;

        case Mode::CYLINDER_RENDER:
            Data_Inventory.BoundSet_Push_Back("Cylinder", mCylinderSource->GetOutput()->GetBounds());
            Data_Inventory.PolyDataSet_Push_Back("Cylinder",mCylinderSource->GetOutput());
            Data_Inventory.ActorSet_Push_Back("Cylinder", mActor);
            break;

        case Mode::DISK_RENDER:
            Data_Inventory.BoundSet_Push_Back("Disk", mDiskSource->GetOutput()->GetBounds());
            Data_Inventory.PolyDataSet_Push_Back("Disk",mDiskSource->GetOutput());
            Data_Inventory.ActorSet_Push_Back("Disk", mActor);
            break;
        case Mode::LINE_RENDER:
            Data_Inventory.BoundSet_Push_Back("Line", mLineSource->GetOutput()->GetBounds());
            Data_Inventory.PolyDataSet_Push_Back("Line",mLineSource->GetOutput());
            Data_Inventory.ActorSet_Push_Back("Line", mActor);
            break;

        case Mode::ARROW_RENDER:
            Data_Inventory.BoundSet_Push_Back("Arrow", mArrowSource->GetOutput()->GetBounds());
            Data_Inventory.PolyDataSet_Push_Back("Arrow",mArrowSource->GetOutput());
            Data_Inventory.ActorSet_Push_Back("Arrow", mActor);
            break;

    }


}

