#include <CameraReaction.h>
#include <vtkCamera.h>


CameraReaction& CameraReaction::Get_Instance() {
    //create a static instance and return it
    static CameraReaction Singleton;
    return Singleton;

}

CameraReaction::CameraReaction()
{
    //init the camera
    mCamera = vtkSmartPointer<vtkCamera>::New();
    mCamera->SetViewUp(0, 1, 0);
    mCamera->SetPosition(0, 0, 10);
    mCamera->SetFocalPoint(0, 0, 0);

}

void CameraReaction::Adjust_Camera_Position(CameraReaction::Mode mode) {

    //set the mode and do the corresponding reaction
    this->mMode=mode;
    switch (this->mMode)
    {
        case Mode::RESET_CAMERA:
            mCamera->SetViewUp(0, 1, 0);
            mCamera->SetPosition(0, 0, 10);
            mCamera->SetFocalPoint(0, 0, 0);
            break;

        case Mode::RESET_POSITIVE_X:
            mCamera->SetPosition(0, 0, 0);
            mCamera->SetFocalPoint(1, 0, 0);
            mCamera->SetViewUp(0, 0, 1);
            break;

        case Mode::RESET_POSITIVE_Y:
            mCamera->SetPosition(0, 0, 0);
            mCamera->SetFocalPoint(0, 1, 0);
            mCamera->SetViewUp(0, 0, 1);
            break;

        case Mode::RESET_POSITIVE_Z:
            mCamera->SetPosition(0, 0, 0);
            mCamera->SetFocalPoint(0, 0, 1);
            mCamera->SetViewUp(0, 1, 0);
            break;

        case Mode::RESET_NEGATIVE_X:
            mCamera->SetPosition(0,0,0);
            mCamera->SetFocalPoint(-1,0,0);
            mCamera->SetViewUp(0,0,1);
            break;

        case Mode::RESET_NEGATIVE_Y:
            mCamera->SetPosition(0, 0, 0);
            mCamera->SetFocalPoint(0, -1, 0);
            mCamera->SetViewUp(0, 0, 1);
            break;

        case Mode::RESET_NEGATIVE_Z:
            mCamera->SetPosition(0, 0, 0);
            mCamera->SetFocalPoint(0, 0, -1);
            mCamera->SetViewUp(0, 1, 0);
            break;

    }


}

vtkCamera *CameraReaction::Get_Camera() const {

   return mCamera.GetPointer();

}

void CameraReaction::operator++() {
    //rotate the camera
    mCamera->Roll(-10.0);

}

void CameraReaction::operator--() {
    //rotate the camera
    mCamera->Roll(10.0);
}

void CameraReaction::operator+(const double &Angle) {
    //rotate the camera
    mCamera->Roll(-Angle);

}

void CameraReaction::operator-(const double &Angle) {
    //rotate the camera
    mCamera->Roll(Angle);

}








