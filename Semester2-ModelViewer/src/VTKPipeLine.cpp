#include <VTKPipeLine.h>
#include <vtkDataSetMapper.h>
#include <vtkPolyDataMapper.h>
#include <vtkSmartPointer.h>
#include <vtkActor.h>


VTKPipeLine::VTKPipeLine(VTKPipeLine::MapperType MapperType) {

    //allocating memory
    switch (MapperType) {

        case MapperType::DATASET_MAPPER:
            mDataSetMapper= vtkSmartPointer<vtkDataSetMapper>::New();
            mActor =vtkSmartPointer<vtkActor>::New();
            mPolyDataMapper= nullptr;
            break;


        case MapperType::POLY_MAPPER:
            mPolyDataMapper= vtkSmartPointer<vtkPolyDataMapper>::New();
            mActor =vtkSmartPointer<vtkActor>::New();
            mDataSetMapper= nullptr;
            break;

    }

}
