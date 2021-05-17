#ifndef CAMERAREACTION_H
#define CAMERAREACTION_H
#include <vtkSmartPointer.h>
class vtkCamera;
class QString;


/*
 * Copyright: Group6
 *
 */

///The CameraReaction class is used to handle the users' interaction with the camera
///
///This is class is using the Singleton design pattern as there is only one camera in the scene, so don't need more than one instance of this class
///
class CameraReaction
{
public:

    /// This enum holds the interactions that can make the camera points to one of the fixed directions.
    enum class Mode
    {
        RESET_CAMERA,
        RESET_POSITIVE_X,
        RESET_POSITIVE_Y,
        RESET_POSITIVE_Z,
        RESET_NEGATIVE_X,
        RESET_NEGATIVE_Y,
        RESET_NEGATIVE_Z,
    };


    /// This method is used to set the reaction to one of the modes defined above
    void Adjust_Camera_Position(CameraReaction::Mode mode);

    /// This method is used to get the Singleton
    ///@return the reference to the Singleton
    static CameraReaction& Get_Instance();

    /// This is an overloaded operator++
    /// This method is used to rotate the camera clockwise by 10 degree
    void operator++();

    /// This is an overloaded operator--
    /// This method is used to rotate the camera anti-clockwise by 10 degree
    void operator--();

    /// This is an overloaded operator+
    /// This method is used to rotate the camera clockwise by the user-defined degree
    ///@param Angle degree specified by the user
    void operator+(const double& Angle);

    /// This is an overloaded operator-
    /// This method is used to rotate the camera anti-clockwise by the user-defined degree
    ///@param Angle degree specified by the user
    void operator-(const double& Angle);


    /// This method is used get the camera.
    ///@return the row pointer of the vtkCamera
    vtkCamera* Get_Camera() const ;


    CameraReaction(const CameraReaction& )= delete;

    CameraReaction& operator=(const CameraReaction& )= delete;


private:
    /// The constructor of the class
    CameraReaction();


private:
    vtkSmartPointer<vtkCamera> mCamera;
    Mode mMode{};

};

#endif // VTKCAMERA_H
