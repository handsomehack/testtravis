#include <CustomizedModelRenderingEvent.h>
#include <vtkPoints.h>
#include <vtkPyramid.h>
#include <vtkUnstructuredGrid.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <RenderWindow.h>
#include <vtkProperty.h>
#include <DataInventory.h>
#include <FilteringEvent.h>
#include <vtkHexahedron.h>
#include <vtkPolygon.h>
#include <vtkTetra.h>
#include <vtkQuad.h>
#include <vtkTriangle.h>
#include <vtkLine.h>
#include <qdebug.h>

void CustomizedModelRenderingEvent::Source_To_Mapper() {

        switch (this->mMode) {

            case Mode::PYRAMID_RENDER: {
                //define vertices
                vector3D vertices[5] = {vector3D(0, 1.0, 1.0, 1.0), vector3D(1, -1.0, 1.0, 1.0),
                                        vector3D(2, -1.0, -1.0, 1.0),
                                        vector3D(3, 1.0, -1.0, 1.0), vector3D(4, 0.0, 0.0, 0.0)};

                for (auto &vertice : vertices) {
                    mVertices.push_back(vertice);
                }

                // Create the points.
                auto points = vtkSmartPointer<vtkPoints>::New();

                // Create a pyramid from the points.
                auto pyramid = vtkSmartPointer<vtkPyramid>::New();

                for (auto i = 0; i < mVertices.size(); ++i) {
                    points->InsertNextPoint(mVertices[i].get_X(), mVertices[i].get_Y(), mVertices[i].get_Z());
                    pyramid->GetPointIds()->SetId(i, i);
                }

                // Add the points and pyramid to an unstructured grid.
                mUnstructuredGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
                mUnstructuredGrid->SetPoints(points);
                mUnstructuredGrid->InsertNextCell(pyramid->GetCellType(), pyramid->GetPointIds());
                mDataSetMapper->SetInputData(mUnstructuredGrid);
                break;
            }
            case Mode::TETRA_RENDER: {
                //define vertices
                vector3D vertices[4] = {vector3D(0, 0.0, 0.0, 0.0), vector3D(1, 1.0, 0.0, 0.0),
                                        vector3D(2, 1.0, 1.0, 0.0),
                                        vector3D(3, 0.0, 1.0, 1.0)};

                auto points =
                        vtkSmartPointer<vtkPoints>::New();
                points->InsertNextPoint(vertices[0].get_X(), vertices[0].get_Y(), vertices[0].get_Z());
                points->InsertNextPoint(vertices[1].get_X(), vertices[1].get_Y(), vertices[1].get_Z());
                points->InsertNextPoint(vertices[2].get_X(), vertices[2].get_Y(), vertices[2].get_Z());
                points->InsertNextPoint(vertices[3].get_X(), vertices[3].get_Y(), vertices[3].get_Z());

                // Add the points and tetrahedron to an unstructured grid.
                mUnstructuredGrid =vtkSmartPointer<vtkUnstructuredGrid>::New();
                mUnstructuredGrid->SetPoints(points);

                vtkIdType ptIds[] = {0, 1, 2, 3};
                mUnstructuredGrid->InsertNextCell(VTK_TETRA, 4, ptIds);
                mDataSetMapper->SetInputData(mUnstructuredGrid);
                break;
            }
            case Mode::HEXA_RENDER:{
                vector3D vertices[8] = {vector3D(0, 0.0, 0.0, 0.0), vector3D(1, 1.0, 0.0, 0.0), vector3D(2, 1.0, 1.0, 0.0),
                                        vector3D(3, 0.0, 1.0, 0.0),
                                        vector3D(4, 0.0, 0.0, 1.0), vector3D(5, 1.0, 0.0, 1.0), vector3D(6, 1.0, 1.0, 1.0),
                                        vector3D(7, 0.0, 1.0, 1.0)};

                for (auto &vertice : vertices) {
                    mVertices.push_back(vertice);
                }
                // Create the points.
                auto points =vtkSmartPointer<vtkPoints>::New();

                // Create a hexahedron from the points.
                auto hex = vtkSmartPointer<vtkHexahedron>::New();

                for (auto i = 0; i < mVertices.size(); ++i) {
                    points->InsertNextPoint(mVertices[i].get_X(), mVertices[i].get_Y(), mVertices[i].get_Z());
                    hex->GetPointIds()->SetId(i, i);
                };

                // Add the points and hexahedron to an unstructured grid.
                mUnstructuredGrid=vtkSmartPointer<vtkUnstructuredGrid>::New();
                mUnstructuredGrid->SetPoints(points);
                mUnstructuredGrid->InsertNextCell(hex->GetCellType(), hex->GetPointIds());
                mDataSetMapper->SetInputData(mUnstructuredGrid);
                break;
            }
            case Mode::USER_DEFINED_RENDER: {
                switch (this->mCellType) {
                    case CellType::VTK_HEXAHEDRON: {
                        // Create the points.
                        auto points = vtkSmartPointer<vtkPoints>::New();

                        // Create a hexahedron from the points.
                        auto hex = vtkSmartPointer<vtkHexahedron>::New();

                        for (auto i = 0; i < mVertices.size(); ++i) {
                            points->InsertNextPoint(mVertices[i].get_X(), mVertices[i].get_Y(), mVertices[i].get_Z());
                            hex->GetPointIds()->SetId(i, i);
                        }

                        // Add the points and hexahedron to an unstructured grid.
                        mUnstructuredGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
                        mUnstructuredGrid->SetPoints(points);
                        mUnstructuredGrid->InsertNextCell(hex->GetCellType(), hex->GetPointIds());
                        mDataSetMapper->SetInputData(mUnstructuredGrid);
                        break;
                    }
                    case CellType::VTK_POLYGON: {
                        // Create the points.
                        auto points = vtkSmartPointer<vtkPoints>::New();

                        // Create a hexahedron from the points.
                        auto polygon = vtkSmartPointer<vtkPolygon>::New();

                        for (auto i = 0; i < mVertices.size(); ++i) {
                            points->InsertNextPoint(mVertices[i].get_X(), mVertices[i].get_Y(), mVertices[i].get_Z());
                            polygon->GetPointIds()->SetId(i, i);
                        }

                        // Add the points and hexahedron to an unstructured grid.
                        mUnstructuredGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
                        mUnstructuredGrid->SetPoints(points);
                        mUnstructuredGrid->InsertNextCell(polygon->GetCellType(), polygon->GetPointIds());
                        mDataSetMapper->SetInputData(mUnstructuredGrid);
                        break;
                    }

                    case CellType::VTK_PYRAMID: {
                        // Create the points.
                        auto points = vtkSmartPointer<vtkPoints>::New();

                        // Create a hexahedron from the points.
                        auto pyramid = vtkSmartPointer<vtkPyramid>::New();

                        for (auto i = 0; i < mVertices.size(); ++i) {
                            points->InsertNextPoint(mVertices[i].get_X(), mVertices[i].get_Y(), mVertices[i].get_Z());
                            pyramid->GetPointIds()->SetId(i, i);
                        }

                        // Add the points and hexahedron to an unstructured grid.
                        mUnstructuredGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
                        mUnstructuredGrid->SetPoints(points);
                        mUnstructuredGrid->InsertNextCell(pyramid->GetCellType(), pyramid->GetPointIds());
                        mDataSetMapper->SetInputData(mUnstructuredGrid);
                        break;
                    }
                    case CellType::VTK_TETRA: {
                        // Create vertices
                        auto points = vtkSmartPointer<vtkPoints>::New();

                        // Create a hexahedron from the vertices.
                        auto tetra = vtkSmartPointer<vtkTetra>::New();

                        for (auto i = 0; i < mVertices.size(); ++i) {
                            points->InsertNextPoint(mVertices[i].get_X(), mVertices[i].get_Y(), mVertices[i].get_Z());
                            tetra->GetPointIds()->SetId(i, i);
                        }

                        // Add the points and hexahedron to an unstructured grid.
                        mUnstructuredGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
                        mUnstructuredGrid->SetPoints(points);
                        mUnstructuredGrid->InsertNextCell(tetra->GetCellType(), tetra->GetPointIds());
                        mDataSetMapper->SetInputData(mUnstructuredGrid);
                        break;
                    }
                    case CellType::VTK_QUAD: {
                        // Create vertices
                        auto points = vtkSmartPointer<vtkPoints>::New();

                        // Create a hexahedron from the vertices.
                        auto quad = vtkSmartPointer<vtkQuad>::New();

                        for (auto i = 0; i < mVertices.size(); ++i) {
                            points->InsertNextPoint(mVertices[i].get_X(), mVertices[i].get_Y(), mVertices[i].get_Z());
                            quad->GetPointIds()->SetId(i, i);
                        }

                        // Add the points and hexahedron to an unstructured grid.
                        mUnstructuredGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
                        mUnstructuredGrid->SetPoints(points);
                        mUnstructuredGrid->InsertNextCell(quad->GetCellType(), quad->GetPointIds());
                        mDataSetMapper->SetInputData(mUnstructuredGrid);
                        break;
                    }
                    case CellType::VTK_TRIANGLE: {
                        // Create vertices
                        auto points = vtkSmartPointer<vtkPoints>::New();

                        // Create a hexahedron from the vertices.
                        auto triangle = vtkSmartPointer<vtkTriangle>::New();

                        for (auto i = 0; i < mVertices.size(); ++i) {
                            points->InsertNextPoint(mVertices[i].get_X(), mVertices[i].get_Y(), mVertices[i].get_Z());
                            triangle->GetPointIds()->SetId(i, i);
                        }

                        // Add the points and hexahedron to an unstructured grid.
                        mUnstructuredGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
                        mUnstructuredGrid->SetPoints(points);
                        mUnstructuredGrid->InsertNextCell(triangle->GetCellType(), triangle->GetPointIds());
                        mDataSetMapper->SetInputData(mUnstructuredGrid);
                        break;
                    }
                    case CellType::VTK_LINE: {
                        // Create vertices
                        auto points = vtkSmartPointer<vtkPoints>::New();

                        // Create a hexahedron from the vertices.
                        auto line = vtkSmartPointer<vtkLine>::New();

                        for (auto i = 0; i < mVertices.size(); ++i) {
                            points->InsertNextPoint(mVertices[i].get_X(), mVertices[i].get_Y(), mVertices[i].get_Z());
                            line->GetPointIds()->SetId(i, i);
                        }

                        // Add the points and hexahedron to an unstructured grid.
                        mUnstructuredGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
                        mUnstructuredGrid->SetPoints(points);
                        mUnstructuredGrid->InsertNextCell(line->GetCellType(), line->GetPointIds());
                        mDataSetMapper->SetInputData(mUnstructuredGrid);
                        break;
                    }
                }
                break;
            }
        }

}

void CustomizedModelRenderingEvent::Actor_To_Renderer() {

    //This method basically contains 3 steps:
    //step 1: establish the connection between the Actor and the Mapper
    //step 2: set the Actor's properties
    //step 3: Add the Actor to the scene
    mActor->SetMapper(mDataSetMapper);
    this->Set_Actor_Property();
    Render_Window.Add_Actor(mActor);

}

void CustomizedModelRenderingEvent::Set_Actor_Property() {

    ///This method sets the actor's color to the color chosen by the users and the color is blue by default
    switch(this->mMode){

        case Mode::USER_DEFINED_RENDER: {
            mActor->GetProperty()->SetColor(mColor[0], mColor[1], mColor[2]);
            break;
        }

        default:
            mActor->GetProperty()->SetColor(1, 0, 0);

    }


}

void CustomizedModelRenderingEvent::Store_Model_Data() {

    //This method contains 3 steps:
    //step 1: push the Bounding information associated with actor to the Map container
    //step 2: push the PolyData associated with the actor to the Map container
    //step 3: push the Actor to the Map container
    //to be notice there is a conversion between polydata and unstructured grid, the reason I am doing that is from my experience
    //most of the filter takes vtkDataObject, which is the base class of vtkPolyData as the input source to implement the polymorphism
    //therefore if the user want to apply filter to the cell they just created, an PolyData to ugrid conversion is needed
    switch (this->mMode) {

        case Mode::PYRAMID_RENDER:
            Data_Inventory.BoundSet_Push_Back("Pyramid", mUnstructuredGrid->GetBounds());
            Data_Inventory.PolyDataSet_Push_Back("Pyramid",FilteringEvent::UGrid_To_PolyData(mUnstructuredGrid));
            Data_Inventory.ActorSet_Push_Back("Pyramid", mActor);
            break;
        case Mode::TETRA_RENDER:
            Data_Inventory.BoundSet_Push_Back("Tetrahedron", mUnstructuredGrid->GetBounds());
            Data_Inventory.PolyDataSet_Push_Back("Tetrahedron",FilteringEvent::UGrid_To_PolyData(mUnstructuredGrid));
            Data_Inventory.ActorSet_Push_Back("Tetrahedron", mActor);
            break;
        case Mode::HEXA_RENDER:
            Data_Inventory.BoundSet_Push_Back("Hexahedron", mUnstructuredGrid->GetBounds());
            Data_Inventory.PolyDataSet_Push_Back("Hexahedron",FilteringEvent::UGrid_To_PolyData(mUnstructuredGrid));
            Data_Inventory.ActorSet_Push_Back("Hexahedron", mActor);
            break;
        case Mode::USER_DEFINED_RENDER:
            switch (this->mCellType) {
                case CellType::VTK_HEXAHEDRON:
                    Data_Inventory.BoundSet_Push_Back("VTK_HEXAHEDRON", mUnstructuredGrid->GetBounds());
                    Data_Inventory.PolyDataSet_Push_Back("VTK_HEXAHEDRON",FilteringEvent::UGrid_To_PolyData(mUnstructuredGrid));
                    Data_Inventory.ActorSet_Push_Back("VTK_HEXAHEDRON", mActor);
                    break;
                case CellType::VTK_POLYGON:
                    Data_Inventory.BoundSet_Push_Back("VTK_POLYGON", mUnstructuredGrid->GetBounds());
                    Data_Inventory.PolyDataSet_Push_Back("VTK_POLYGON",FilteringEvent::UGrid_To_PolyData(mUnstructuredGrid));
                    Data_Inventory.ActorSet_Push_Back("VTK_POLYGON", mActor);
                    break;
                case CellType::VTK_PYRAMID:
                    Data_Inventory.BoundSet_Push_Back("VTK_PYRAMID", mUnstructuredGrid->GetBounds());
                    Data_Inventory.PolyDataSet_Push_Back("VTK_PYRAMID",FilteringEvent::UGrid_To_PolyData(mUnstructuredGrid));
                    Data_Inventory.ActorSet_Push_Back("VTK_PYRAMID", mActor);
                    break;
                case CellType::VTK_TETRA:
                    Data_Inventory.BoundSet_Push_Back("VTK_TETRA", mUnstructuredGrid->GetBounds());
                    Data_Inventory.PolyDataSet_Push_Back("VTK_TETRA",FilteringEvent::UGrid_To_PolyData(mUnstructuredGrid));
                    Data_Inventory.ActorSet_Push_Back("VTK_TETRA", mActor);
                    break;
                case CellType::VTK_QUAD:
                    Data_Inventory.BoundSet_Push_Back("VTK_QUAD", mUnstructuredGrid->GetBounds());
                    Data_Inventory.PolyDataSet_Push_Back("VTK_QUAD",FilteringEvent::UGrid_To_PolyData(mUnstructuredGrid));
                    Data_Inventory.ActorSet_Push_Back("VTK_QUAD", mActor);
                    break;
                case CellType::VTK_TRIANGLE:
                    Data_Inventory.BoundSet_Push_Back("VTK_TRIANGLE", mUnstructuredGrid->GetBounds());
                    Data_Inventory.PolyDataSet_Push_Back("VTK_TRIANGLE",FilteringEvent::UGrid_To_PolyData(mUnstructuredGrid));
                    Data_Inventory.ActorSet_Push_Back("VTK_TRIANGLE", mActor);
                    break;
                case CellType::VTK_LINE:
                    Data_Inventory.BoundSet_Push_Back("VTK_LINE", mUnstructuredGrid->GetBounds());
                    Data_Inventory.PolyDataSet_Push_Back("VTK_LINE",FilteringEvent::UGrid_To_PolyData(mUnstructuredGrid));
                    Data_Inventory.ActorSet_Push_Back("VTK_LINE", mActor);
                    break;
            }
            break;
    }

}
