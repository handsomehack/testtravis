#ifndef VTKPIPELINE_H
#define VTKPIPELINE_H
#include <vtkSmartPointer.h>
class vtkMoleculeMapper;
class vtkActor;
class vtkDataSetMapper;
class vtkPolyDataMapper;
class QString;

///This is an abstract class
///This class provides several APIs to users so that they can customize their own PipeLine
class VTKPipeLine {

public:
    enum class MapperType {
        POLY_MAPPER,
        DATASET_MAPPER,
    };

    ///default constructor
    VTKPipeLine()=default;

    ///constructor
    ///@note this a a convenient way to allocate memories for the mapper that often used(DataSetMapper or PolydataMapper) and actor
    ///@param MapperType mapper type
    explicit VTKPipeLine(VTKPipeLine::MapperType
    MapperType);

    ///This method describes the procedures between source and mapper
    virtual void Source_To_Mapper() = 0;

    ///This method describes the procedures between actor and renderer
    virtual void Actor_To_Renderer() = 0;

    ///This method describes the actor's appearance
    virtual void Set_Actor_Property() = 0;

    ///This method describes the data need to be stored with respect to a model
    virtual void Store_Model_Data() = 0;


protected:

    vtkSmartPointer<vtkDataSetMapper> mDataSetMapper;
    vtkSmartPointer<vtkPolyDataMapper> mPolyDataMapper;
    vtkSmartPointer<vtkMoleculeMapper> mMoleculeMapper;
    vtkSmartPointer<vtkActor> mActor;

};

#endif // VTKPIPELINE_H
