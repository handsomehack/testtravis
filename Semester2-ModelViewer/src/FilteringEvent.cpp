#include <FilteringEvent.h>
#include <vtkOutlineFilter.h>
#include <DataInventory.h>
#include <vtkPolyDataMapper.h>
#include <vtkDataSetMapper.h>
#include <RenderWindow.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkTriangleFilter.h>
#include <vtkSmoothPolyDataFilter.h>
#include <vtkDelaunay2D.h>
#include <vtkPolyDataNormals.h>
#include <vtkClipPolyData.h>
#include <vtkPlane.h>
#include <vtkCutter.h>
#include <vtkShrinkFilter.h>
#include <CellDisplayDialog.h>
#include <vtkIdTypeArray.h>
#include <vtkSelectionNode.h>
#include <vtkSelection.h>
#include <vtkExtractSelection.h>
#include <vtkUnstructuredGrid.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vtkMoleculeToAtomBallFilter.h>
#include <vtkMoleculeToBondStickFilter.h>
#include <vtkMolecule.h>
#include <vtkNamedColors.h>
#include <vtkAppendPolyData.h>
#include <qdebug.h>


void FilteringEvent::Source_To_Mapper() {

    //source -> filter ->mapper
    //to be noticed, the outputs of different filters rely on different mappers(e.g polydatamapper or datasetmapper)
    //from my vtk experience, the PolyData sources rely on PolyDataMapper, whereas UnstructuredGrid sources rely on DatasetMapper
    switch (this->mMode) {

        case Mode::TRIANGULATE: {
            mTriangleFilter = vtkSmartPointer<vtkTriangleFilter>::New();
            mTriangleFilter->SetInputData(Data_Inventory.Get_Value_From_PolyDataSet(mInputSource));
            mTriangleFilter->Update();
            mPolyDataMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
            mPolyDataMapper->SetInputConnection(mTriangleFilter->GetOutputPort());
            break;
        }
        case Mode::OUTLINE: {
            mOutlineFilter = vtkSmartPointer<vtkOutlineFilter>::New();
            mOutlineFilter->SetInputData(Data_Inventory.Get_Value_From_PolyDataSet(mInputSource));
            mOutlineFilter->Update();
            mPolyDataMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
            mPolyDataMapper->SetInputConnection(mOutlineFilter->GetOutputPort());
            break;
        }
        case Mode::SMOOTH: {
            mDelaunay2DFilter = vtkSmartPointer<vtkDelaunay2D>::New();
            mSmoothFilter = vtkSmartPointer<vtkSmoothPolyDataFilter>::New();
            mDelaunay2DFilter->SetInputData(Data_Inventory.Get_Value_From_PolyDataSet(mInputSource));
            mDelaunay2DFilter->Update();
            mSmoothFilter->SetInputConnection(mDelaunay2DFilter->GetOutputPort());
            mSmoothFilter->SetNumberOfIterations(15);
            mSmoothFilter->SetRelaxationFactor(0.1);
            mSmoothFilter->FeatureEdgeSmoothingOff();
            mSmoothFilter->BoundarySmoothingOn();
            mSmoothFilter->Update();
            // Update normals on newly smoothed polydata
            auto normalGenerator = vtkSmartPointer<vtkPolyDataNormals>::New();
            normalGenerator->SetInputConnection(mSmoothFilter->GetOutputPort());
            normalGenerator->ComputePointNormalsOn();
            normalGenerator->ComputeCellNormalsOn();
            normalGenerator->Update();
            mPolyDataMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
            mPolyDataMapper->SetInputConnection(normalGenerator->GetOutputPort());
            break;
        }

        case Mode::CLIP: {
            mClipFilter = vtkSmartPointer<vtkClipPolyData>::New();
            mClippingPlane = vtkSmartPointer<vtkPlane>::New();
            mClipFilter->SetClipFunction(mClippingPlane);
            mClipFilter->InsideOutOn();
            mClipFilter->SetInputData(Data_Inventory.Get_Value_From_PolyDataSet(mInputSource));
            mClipFilter->Update();
            mPolyDataMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
            mPolyDataMapper->SetInputConnection(mClipFilter->GetOutputPort());
            break;
        }

        case Mode::CONTOUR: {
            auto plane =
                    vtkSmartPointer<vtkPlane>::New();
            plane->SetOrigin(Data_Inventory.Get_Value_From_PolyDataSet(mInputSource)->GetCenter());
            plane->SetNormal(1, 1, 1);

            double minBound[3];
            minBound[0] = Data_Inventory.Get_Value_From_BoundSet(mInputSource)[0];
            minBound[1] = Data_Inventory.Get_Value_From_BoundSet(mInputSource)[2];
            minBound[2] = Data_Inventory.Get_Value_From_BoundSet(mInputSource)[4];

            double maxBound[3];
            maxBound[0] = Data_Inventory.Get_Value_From_BoundSet(mInputSource)[1];
            maxBound[1] = Data_Inventory.Get_Value_From_BoundSet(mInputSource)[3];
            maxBound[2] = Data_Inventory.Get_Value_From_BoundSet(mInputSource)[5];

            double center[3];
            center[0] = Data_Inventory.Get_Value_From_PolyDataSet(mInputSource)->GetCenter()[0];
            center[1] = Data_Inventory.Get_Value_From_PolyDataSet(mInputSource)->GetCenter()[1];
            center[2] = Data_Inventory.Get_Value_From_PolyDataSet(mInputSource)->GetCenter()[2];

            double distanceMin = sqrt(vtkMath::Distance2BetweenPoints(minBound, center));
            double distanceMax = sqrt(vtkMath::Distance2BetweenPoints(maxBound, center));

            mCutter = vtkSmartPointer<vtkCutter>::New();
            mCutter->SetCutFunction(plane);
            mCutter->SetInputData(Data_Inventory.Get_Value_From_PolyDataSet(mInputSource));
            mCutter->GenerateValues(20, -distanceMin, distanceMax);
            mPolyDataMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
            mPolyDataMapper->SetInputConnection(mCutter->GetOutputPort());
            mPolyDataMapper->ScalarVisibilityOff();
            break;
        }

        case Mode::DELAUNAY2D: {
            mDelaunay2DFilter = vtkSmartPointer<vtkDelaunay2D>::New();
            mDelaunay2DFilter->SetInputData(Data_Inventory.Get_Value_From_PolyDataSet(mInputSource));
            mPolyDataMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
            mPolyDataMapper->SetInputConnection(mDelaunay2DFilter->GetOutputPort());
            break;
        }
        case Mode::SHRINK: {
            mShrinkFilter = vtkSmartPointer<vtkShrinkFilter>::New();
            mShrinkFilter->SetInputData(Data_Inventory.Get_Value_From_PolyDataSet(mInputSource));
            mShrinkFilter->SetShrinkFactor(.8);
            mShrinkFilter->Update();
            mDataSetMapper = vtkSmartPointer<vtkDataSetMapper>::New();
            mDataSetMapper->SetInputConnection(mShrinkFilter->GetOutputPort());
            break;
        }

        case Mode::CELL_IS: {
            auto IDs = vtkSmartPointer<vtkIdTypeArray>::New();
            IDs->SetNumberOfComponents(1);
            IDs->InsertNextValue(CellDisplayDialog::Get_StartCellID());
            this->Set_Cell_Selection(IDs);
            mDataSetMapper = vtkSmartPointer<vtkDataSetMapper>::New();
            mDataSetMapper->SetInputData(mSelectedCells);
            break;
        }
        case Mode::CELL_IS_BETWEEN: {
            auto IDs = vtkSmartPointer<vtkIdTypeArray>::New();
            IDs->SetNumberOfComponents(1);
            for (unsigned int i = CellDisplayDialog::Get_StartCellID();
                 i < CellDisplayDialog::Get_EndCellID() + 1; i++) {
                IDs->InsertNextValue(i);
            }
            IDs->InsertNextValue(CellDisplayDialog::Get_StartCellID());
            this->Set_Cell_Selection(IDs);
            mDataSetMapper = vtkSmartPointer<vtkDataSetMapper>::New();
            mDataSetMapper->SetInputData(mSelectedCells);
            break;
        }

        case Mode::CELL_GREATER_EQUAL_THAN: {
            auto IDs = vtkSmartPointer<vtkIdTypeArray>::New();
            IDs->SetNumberOfComponents(1);
            for (unsigned int i = CellDisplayDialog::Get_StartCellID();
                 i < Data_Inventory.Get_Value_From_PolyDataSet(mInputSource)->GetNumberOfCells(); i++) {
                IDs->InsertNextValue(i);
            }
            this->Set_Cell_Selection(IDs);
            mDataSetMapper = vtkSmartPointer<vtkDataSetMapper>::New();
            mDataSetMapper->SetInputData(mSelectedCells);
            break;
        }
        case Mode::CELL_LESS_EQUAL_THAN: {
            auto IDs = vtkSmartPointer<vtkIdTypeArray>::New();
            IDs->SetNumberOfComponents(1);
            for (unsigned int i = 0; i < CellDisplayDialog::Get_StartCellID() + 1; i++) {
                IDs->InsertNextValue(i);
            }
            this->Set_Cell_Selection(IDs);
            mDataSetMapper = vtkSmartPointer<vtkDataSetMapper>::New();
            mDataSetMapper->SetInputData(mSelectedCells);
            break;
        }
        case Mode::CELL_MAX: {
            auto IDs = vtkSmartPointer<vtkIdTypeArray>::New();
            IDs->SetNumberOfComponents(1);
            IDs->InsertNextValue(Data_Inventory.Get_Value_From_PolyDataSet(mInputSource)->GetNumberOfCells() - 1);
            this->Set_Cell_Selection(IDs);
            mDataSetMapper = vtkSmartPointer<vtkDataSetMapper>::New();
            mDataSetMapper->SetInputData(mSelectedCells);
            break;
        }

        case Mode::CELL_MIN: {
            auto IDs = vtkSmartPointer<vtkIdTypeArray>::New();
            IDs->SetNumberOfComponents(1);
            IDs->InsertNextValue(0);
            this->Set_Cell_Selection(IDs);
            mDataSetMapper = vtkSmartPointer<vtkDataSetMapper>::New();
            mDataSetMapper->SetInputData(mSelectedCells);
            break;
        }

    }

}

void FilteringEvent::Actor_To_Renderer() {

    //link actor to the corresponding mapper(i.e. PolyDataMapper or DataSetMapper)
    mActor= vtkSmartPointer<vtkActor>::New();
    switch (this->mMode) {

        case Mode::SHRINK:
            mActor->SetMapper(mDataSetMapper);
            break;

        case Mode::CELL_IS:
            mActor->SetMapper(mDataSetMapper);
            break;

        case Mode::CELL_IS_BETWEEN:
            mActor->SetMapper(mDataSetMapper);
            break;

        case Mode::CELL_GREATER_EQUAL_THAN:
            mActor->SetMapper(mDataSetMapper);
            break;

        case Mode::CELL_LESS_EQUAL_THAN:
            mActor->SetMapper(mDataSetMapper);
            break;

        case Mode::CELL_MAX:
            mActor->SetMapper(mDataSetMapper);
            break;

        case Mode::CELL_MIN:
            mActor->SetMapper(mDataSetMapper);
            break;
        default:
            mActor->SetMapper(mPolyDataMapper);
    }
    this->Set_Actor_Property();
    Render_Window.Add_Actor(mActor);

}

void FilteringEvent::Set_Actor_Property() {

    //set the actor's properties according to different filtering events
    mActor->GetProperty()->SetColor(mColor[0], mColor[1], mColor[2]);
    switch (this->mMode) {

        case Mode::TRIANGULATE:
            mActor->GetProperty()->SetRepresentationToWireframe();
            break;

        case Mode::OUTLINE:
            mActor->GetProperty()->SetLineWidth(1.5);
            break;

        case Mode::CONTOUR:
            mActor->GetProperty()->SetLineWidth(3);
            break;
        case Mode::DELAUNAY2D:
            mActor->GetProperty()->EdgeVisibilityOn();
            break;

        case Mode::CLIP:
            vtkNew<vtkNamedColors> colors;
            vtkNew<vtkProperty> backFaces;
            backFaces->SetDiffuseColor(colors->GetColor3d("Gold").GetData());
            mActor->SetBackfaceProperty(backFaces);
            Render_Window.Show_Clipping_Plane_Actor(mClippingPlane, mActor);

    }


}

void FilteringEvent::Store_Model_Data() {

    //store the the model's data after filtering
    switch (this->mMode) {

        case Mode::TRIANGULATE:
            Data_Inventory.ActorSet_Push_Back("Triangulate-" + mInputSource, mActor);
            Data_Inventory.BoundSet_Push_Back("Triangulate-" + mInputSource,
                                              Data_Inventory.Get_Value_From_PolyDataSet(mInputSource)->GetBounds());
            break;

        case Mode::OUTLINE:
            Data_Inventory.ActorSet_Push_Back("Outline-" + mInputSource, mActor);
            Data_Inventory.BoundSet_Push_Back("Outline-" + mInputSource,
                                              Data_Inventory.Get_Value_From_PolyDataSet(mInputSource)->GetBounds());
            break;

        case Mode::SMOOTH:
            Data_Inventory.ActorSet_Push_Back("Smooth-" + mInputSource, mActor);
            Data_Inventory.BoundSet_Push_Back("Smooth-" + mInputSource,
                                              Data_Inventory.Get_Value_From_PolyDataSet(mInputSource)->GetBounds());
            break;
        case Mode::CLIP:
            Data_Inventory.ActorSet_Push_Back("Clip-" + mInputSource, mActor);
            Data_Inventory.BoundSet_Push_Back("Clip-" + mInputSource,
                                              Data_Inventory.Get_Value_From_PolyDataSet(mInputSource)->GetBounds());
            break;
        case Mode::CONTOUR:
            Data_Inventory.ActorSet_Push_Back("Contour-" + mInputSource, mActor);
            Data_Inventory.BoundSet_Push_Back("Contour-" + mInputSource,
                                              Data_Inventory.Get_Value_From_PolyDataSet(mInputSource)->GetBounds());
            break;
        case Mode::DELAUNAY2D:
            Data_Inventory.ActorSet_Push_Back("Delaunay2D-" + mInputSource, mActor);
            Data_Inventory.BoundSet_Push_Back("Delaunay2D-" + mInputSource,
                                              Data_Inventory.Get_Value_From_PolyDataSet(mInputSource)->GetBounds());
            break;
        case Mode::SHRINK:
            Data_Inventory.ActorSet_Push_Back("Shrink-" + mInputSource, mActor);
            Data_Inventory.BoundSet_Push_Back("Shrink-" + mInputSource,
                                              Data_Inventory.Get_Value_From_PolyDataSet(mInputSource)->GetBounds());
            break;

        default:
            Data_Inventory.ActorSet_Push_Back("Cell-" + mInputSource, mActor);
            Data_Inventory.BoundSet_Push_Back("Cell-" + mInputSource,
                                              Data_Inventory.Get_Value_From_PolyDataSet(mInputSource)->GetBounds());

    }


}


void FilteringEvent::Set_Cell_Selection(const vtkSmartPointer<vtkIdTypeArray> &IDs) {

    //set a list of cells to be extracted using the given cells' IDs
    auto selectionNode = vtkSmartPointer<vtkSelectionNode>::New();
    selectionNode->SetFieldType(vtkSelectionNode::CELL);
    selectionNode->SetContentType(vtkSelectionNode::INDICES);
    selectionNode->SetSelectionList(IDs);
    auto selection = vtkSmartPointer<vtkSelection>::New();
    selection->AddNode(selectionNode);

    //extract the selection
    auto extractSelection = vtkSmartPointer<vtkExtractSelection>::New();
    extractSelection->SetInputData(Data_Inventory.Get_Value_From_PolyDataSet(mInputSource));
    extractSelection->SetInputData(1, selection);
    extractSelection->Update();
    mSelectedCells = vtkSmartPointer<vtkUnstructuredGrid>::New();
    mSelectedCells->ShallowCopy(extractSelection->GetOutput());

}

vtkSmartPointer<vtkPolyData> FilteringEvent::UGrid_To_PolyData(const vtkSmartPointer<vtkUnstructuredGrid> &UGrid) {

    //convert UGrid to PolyData
    auto SurfaceFilter = vtkSmartPointer<vtkDataSetSurfaceFilter>::New();
    SurfaceFilter->SetInputData(UGrid);
    SurfaceFilter->Update();
    return SurfaceFilter->GetOutput();

}

vtkSmartPointer<vtkPolyData> FilteringEvent::Molecule_To_PolyData(const vtkSmartPointer<vtkMolecule> &Molecule) {

    //convert molecule to PolyData
    //one atom is equal to one triangulated sphere and one bond is equal to one cylinder
    //need to used appendPolyData filter to add spheres and cylinders together
    auto MoleculeToAtomBallFilter = vtkSmartPointer<vtkMoleculeToAtomBallFilter>::New();
    auto MoleculeToBondStickFilter = vtkSmartPointer<vtkMoleculeToBondStickFilter>::New();
    auto AppendPolyDataFilter = vtkSmartPointer<vtkAppendPolyData>::New();

    MoleculeToAtomBallFilter->SetInputData(Molecule);
    MoleculeToAtomBallFilter->Update();
    MoleculeToBondStickFilter->SetInputData(Molecule);
    MoleculeToBondStickFilter->Update();
    AppendPolyDataFilter->AddInputData(MoleculeToAtomBallFilter->GetOutput());
    AppendPolyDataFilter->AddInputData(MoleculeToBondStickFilter->GetOutput());
    AppendPolyDataFilter->Update();
    return AppendPolyDataFilter->GetOutput();
}
