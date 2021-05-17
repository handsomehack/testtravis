#ifndef VTKIPWCALLBACK_H
#define VTKIPWCALLBACK_H
#include <vtkImplicitPlaneWidget2.h>
#include <vtkImplicitPlaneRepresentation.h>
#include <vtkCommand.h>
#include <vtkSmartPointer.h>
class vtkPlane;
class vtkActor;

/*
 * Copyright:Group 6
 */

// Callback for the interaction
// This does the actual work: updates the vtkPlane implicit function.
// This in turn causes the pipeline to update and clip the object.
class vtkIPWCallback: public vtkCommand
{
public:
    ///This function is used to dynamically creating instance of this class
    ///@return a pointer to the instance
    static vtkIPWCallback* New()
    {
        return new vtkIPWCallback;
    }

    ///This method is called  everytime the users interact with the clipping plane
    void Execute(vtkObject* caller, unsigned long, void*) override
    {
        auto* planeWidget =
                reinterpret_cast<vtkImplicitPlaneWidget2*>(caller);
        auto* rep =
                reinterpret_cast<vtkImplicitPlaneRepresentation*>(
                        planeWidget->GetRepresentation());
        rep->GetPlane(this->Plane);
    }

    ///default constructor
    vtkIPWCallback()=default;

    vtkSmartPointer<vtkPlane> Plane;
    vtkSmartPointer<vtkActor> Actor;
};

#endif // VTKIPWCALLBACK_H
