#ifndef VTKBOXCALLBACK_H
#define VTKBOXCALLBACK_H
#include <vtkCommand.h>
#include <vtkBoxRepresentation.h>
#include <vtkBoxWidget2.h>
#include <vtkTransform.h>
#include <utility>
class vtkActor;

/*
 * Coyright:Group 6
 */

///The box is dimensioned and positioned by passing a bounding box to PlaceWidget method,
///with the SetPlaceFactor method providing a scaling factor in relation to that bounding box.
///The transformations applied to the box can be used to manipulate any number of object(s),
///via a custom callback class, which is passed to the box widget through the AddObserver method.
class vtkBoxCallBack :public vtkCommand
{
public:
    ///This function is used to dynamically creating instance of this class
    ///@return a pointer to the instance
    static vtkBoxCallBack* New()
    {
        return new vtkBoxCallBack;
    }

    ///This function is used to set the actor to apply boxWidget on
    void SetActor(vtkSmartPointer<vtkActor> actor)
    {
        m_actor = std::move(actor);
    }

    ///This method is called when the users interact with the boxWidget
   void Execute(vtkObject* caller, unsigned long, void*) override
    {
        vtkSmartPointer<vtkBoxWidget2> boxWidget =
                dynamic_cast<vtkBoxWidget2*>(caller);

        vtkNew<vtkTransform> t;

        dynamic_cast<vtkBoxRepresentation*>(boxWidget->GetRepresentation())
                ->GetTransform(t);
        this->m_actor->SetUserTransform(t);
    }
    //default constructor
    vtkBoxCallBack()=default;

    vtkSmartPointer<vtkActor> m_actor;
};

#endif // VTKBOXCALLBACK_H
