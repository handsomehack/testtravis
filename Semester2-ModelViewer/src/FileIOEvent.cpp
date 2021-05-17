#include <FileIOEvent.h>
#include <vtkSTLReader.h>
#include <vtkJPEGReader.h>
#include <vtkPNGReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <RenderWindow.h>
#include <vtkProperty.h>
#include <DataInventory.h>
#include <model.h>
#include <vtkUnstructuredGrid.h>
#include <vtkDataSetMapper.h>
#include <FilteringEvent.h>
#include <vtkTexture.h>
#include <vtkTextureMapToPlane.h>
#include <vtkPolyDataNormals.h>
#include <vtkTransformTextureCoords.h>
#include <vtkImageData.h>
#include <vtkCMLMoleculeReader.h>
#include <vtkMoleculeMapper.h>
#include <vtkMolecule.h>
#include <vtkPLYReader.h>
#include <vtkOBJReader.h>
#include <vtkSTLWriter.h>
#include <vtkPLYWriter.h>
#include <vtkOBJWriter.h>
#include <vtkXMLPolyDataReader.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkUnsignedCharArray.h>
#include <qcolor.h>
#include <vtkCellData.h>
#include <qdebug.h>

FileIOEvent::FileIOEvent(QString &FilePath,Mode mode,const QString& SourceName):mFilePath(std::move(FilePath)),mMode(mode){

    //this method contains two steps:
    //step 1 : do the postfix detection to identify the file type
    //step 2 : allocate memory to the mapper and actor according to the file type
    mFileInfo.setFile(mFilePath);
    switch (this->mMode) {

        case Mode::READ:
            if(mFileInfo.suffix()=="stl")
            {
                mFileType=FileType::STL;
                mActor=vtkSmartPointer<vtkActor>::New();
                mPolyDataMapper=vtkSmartPointer<vtkPolyDataMapper>::New();
            }
            if(mFileInfo.suffix() == "mod")
            {
                mFileType=FileType::MOD;
                mActor=vtkSmartPointer<vtkActor>::New();
                mDataSetMapper=vtkSmartPointer<vtkDataSetMapper>::New();
            }
            if(mFileInfo.suffix() == "ply")
            {

                mFileType=FileType::PLY;
                mActor=vtkSmartPointer<vtkActor>::New();
                mPolyDataMapper=vtkSmartPointer<vtkPolyDataMapper>::New();

            }
            if(mFileInfo.suffix() == "obj")
            {

                mFileType=FileType::OBJ;
                mActor=vtkSmartPointer<vtkActor>::New();
                mPolyDataMapper=vtkSmartPointer<vtkPolyDataMapper>::New();

            }
            if(mFileInfo.suffix()=="png") {

                mFileType=FileType::PNG;
                mActor=vtkSmartPointer<vtkActor>::New();
                mPolyDataMapper=vtkSmartPointer<vtkPolyDataMapper>::New();
            }
            if(mFileInfo.suffix()=="jpg"){

                mFileType=FileType::JPG;
                mActor=vtkSmartPointer<vtkActor>::New();
                mPolyDataMapper=vtkSmartPointer<vtkPolyDataMapper>::New();
            }
            if(mFileInfo.suffix()=="cml"){

                mFileType=FileType::CML;
                mActor=vtkSmartPointer<vtkActor>::New();
                mMoleculeMapper=vtkSmartPointer<vtkMoleculeMapper>::New();
            }
            if(mFileInfo.suffix() =="vtp"){

                mFileType=FileType::VTP;
                mActor=vtkSmartPointer<vtkActor>::New();
                mPolyDataMapper=vtkSmartPointer<vtkPolyDataMapper>::New();
            }
            if(mFileInfo.suffix()=="vtu"){

                mFileType=FileType::VTU;
                mActor=vtkSmartPointer<vtkActor>::New();
                mDataSetMapper=vtkSmartPointer<vtkDataSetMapper>::New();
            }


            break;

        //when user want to write data to a file, then call Write_To_A_File() function to handle the event
        case Mode::WRITE:
            this->Write_To_A_File(SourceName);
            break;

    }


}

void FileIOEvent::Source_To_Mapper() {

    //except for MOD file is a bit different , the procedures of reading the other types of files are basically identical, which
    //simply are reader->Mapper
    switch (this->mFileType) {

        case FileType::STL: {
            mSTLReader = vtkSmartPointer<vtkSTLReader>::New();
            mSTLReader->SetFileName(mFilePath.toStdString().c_str());
            mSTLReader->Update();
            mPolyDataMapper->SetInputConnection(mSTLReader->GetOutputPort());
            break;
        }
        case FileType::MOD: {
            Model m1;
            m1.Read_from_A_file(mFilePath.toStdString());

            //load all the points based on the information in the file
            auto vtk_points = vtkSmartPointer<vtkPoints>::New();
            for (auto i = 0; i < m1.get_vertex_num(); i++) {

                vtk_points->InsertNextPoint(m1.points[i].get_X(), m1.points[i].get_Y(), m1.points[i].get_Z());
            }

            //allocate memory to UGrid and load all the points onto the UGrid
            mUnstructuredGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
            mUnstructuredGrid->SetPoints(vtk_points);

            //construct cells based on the information given in the file and the points on the UGrid
            for (auto i = 0; i < m1.get_Cell_num(); i++) {

                //event for rendering tetrahedron
                if (m1.get_cell_type(i) == 't') {

                    vtkIdType ptIds[] = {m1.Cells[i]->cell_vertices[0].get_ID(), m1.Cells[i]->cell_vertices[1].get_ID(),
                                         m1.Cells[i]->cell_vertices[2].get_ID(),
                                         m1.Cells[i]->cell_vertices[3].get_ID()};
                    mUnstructuredGrid->InsertNextCell(VTK_TETRA, 4, ptIds);
                }

                //event for rendering pyramid
                if (m1.get_cell_type(i) == 'p') {

                    vtkIdType ptIds[] = {m1.Cells[i]->cell_vertices[0].get_ID(), m1.Cells[i]->cell_vertices[1].get_ID(),
                                         m1.Cells[i]->cell_vertices[2].get_ID(), m1.Cells[i]->cell_vertices[3].get_ID(),
                                         m1.Cells[i]->cell_vertices[4].get_ID(),
                                         m1.Cells[i]->cell_vertices[5].get_ID()};
                    mUnstructuredGrid->InsertNextCell(VTK_PYRAMID, 5, ptIds);
                }

                //event for rendering hexahedron
                if (m1.get_cell_type(i) == 'h') {

                    vtkIdType ptIds[] = {m1.Cells[i]->cell_vertices[0].get_ID(), m1.Cells[i]->cell_vertices[1].get_ID(),
                                         m1.Cells[i]->cell_vertices[2].get_ID(), m1.Cells[i]->cell_vertices[3].get_ID(),
                                         m1.Cells[i]->cell_vertices[4].get_ID(), m1.Cells[i]->cell_vertices[5].get_ID(),
                                         m1.Cells[i]->cell_vertices[6].get_ID(),
                                         m1.Cells[i]->cell_vertices[7].get_ID()};
                    mUnstructuredGrid->InsertNextCell(VTK_HEXAHEDRON, 8, ptIds);
                }
            }

            //after loading all the cells onto the uGrid , then load the color of each cell
            vtkSmartPointer<vtkUnsignedCharArray> cellData = vtkSmartPointer<vtkUnsignedCharArray>::New();
            cellData->SetNumberOfComponents(3);
            cellData->SetNumberOfTuples(mUnstructuredGrid->GetNumberOfCells());
            for (int i = 0; i < mUnstructuredGrid->GetNumberOfCells(); i++) {
                //load color code from the material class
                QColor CellColor(QString('#').append(m1.Cells[i]->M->get_Colour().c_str()));
                float rgb[3];
                rgb[0] = static_cast<float>(CellColor.red());
                rgb[1] = static_cast<float>(CellColor.green());
                rgb[2] = static_cast<float>(CellColor.blue());
                cellData->InsertTuple(i, rgb);

            }
            //set the color of each cell
            mUnstructuredGrid->GetCellData()->SetScalars(cellData);
            //set mapper
            mDataSetMapper->SetInputData(mUnstructuredGrid);
            break;
        }

        case FileType::PLY:{
            mPLYReader = vtkSmartPointer<vtkPLYReader>::New();
            mPLYReader->SetFileName(mFilePath.toStdString().c_str());
            mPLYReader->Update();
            mPolyDataMapper->SetInputConnection(mPLYReader->GetOutputPort());
            break;
        }

        case FileType::OBJ:{

            mOBJReader = vtkSmartPointer<vtkOBJReader>::New();
            mOBJReader->SetFileName(mFilePath.toStdString().c_str());
            mOBJReader->Update();
            mPolyDataMapper->SetInputConnection(mOBJReader->GetOutputPort());
            break;

        }

        case FileType::JPG: {
            mJPGReader = vtkSmartPointer<vtkJPEGReader>::New();
            mJPGReader->SetFileName(mFilePath.toStdString().c_str());
            mJPGReader->Update();
            mTexture = vtkSmartPointer<vtkTexture>::New();
            mTexture->SetInputConnection(mJPGReader->GetOutputPort());
            mTexture->InterpolateOn();
            this->Texture_Transformation_SetUp();
            break;
        }
        case FileType::PNG: {
            mPNGReader = vtkSmartPointer<vtkPNGReader>::New();
            mPNGReader->SetFileName(mFilePath.toStdString().c_str());
            mPNGReader->Update();
            mTexture = vtkSmartPointer<vtkTexture>::New();
            mTexture->SetInputConnection(mPNGReader->GetOutputPort());
            mTexture->InterpolateOn();
            this->Texture_Transformation_SetUp();
            break;
        }
        case FileType::CML: {
            mCMLReader = vtkSmartPointer<vtkCMLMoleculeReader>::New();
            mCMLReader->SetFileName(mFilePath.toStdString().c_str());
            mCMLReader->Update();
            mMoleculeMapper->SetInputConnection(mCMLReader->GetOutputPort());
            mMoleculeMapper->UseBallAndStickSettings();
            break;
        }
        case FileType::VTP:{
            mVTPReader = vtkSmartPointer<vtkXMLPolyDataReader>::New();
            mVTPReader->SetFileName(mFilePath.toStdString().c_str());
            mVTPReader->Update();
            mPolyDataMapper->SetInputConnection(mVTPReader->GetOutputPort());
            break;

        }
        case FileType::VTU:{
            mVTUReader = vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
            mVTUReader->SetFileName(mFilePath.toStdString().c_str());
            mVTUReader->Update();
            mDataSetMapper->SetInputConnection(mVTUReader->GetOutputPort());
            mDataSetMapper->ScalarVisibilityOff();
            break;

        }

    }

}

void FileIOEvent::Actor_To_Renderer() {
    //This method basically contains 3 steps:
    //step 1: establish the connection between the Actor and the Mapper
    //step 2: set the Actor's properties
    //step 3: Add the Actor to the scene
    switch (this->mFileType) {

        case FileType::MOD:
            mActor->SetMapper(mDataSetMapper);
            break;

        case FileType::VTU:
            mActor->SetMapper(mDataSetMapper);
            break;

        case FileType::CML:
            mActor->SetMapper(mMoleculeMapper);
            break;

        default:
            mActor->SetMapper(mPolyDataMapper);
    }
    this->Set_Actor_Property();
    Render_Window.Add_Actor(mActor);

}


void FileIOEvent::Set_Actor_Property() {

    //set actor's properties based on the file type
    switch (this->mFileType) {

        case FileType::JPG:
            mActor->SetTexture(mTexture);
            break;
        case FileType::PNG:
            mActor->SetTexture(mTexture);
            break;
        case FileType::MOD:
            break;
        case FileType::CML:
            mActor->GetProperty()->SetDiffuse(0.7);
            mActor->GetProperty()->SetSpecular(0.5);
            mActor->GetProperty()->SetSpecularPower(20.0);
        default:
            mActor->GetProperty()->SetColor(1,0,0);

    }


}


void FileIOEvent::Store_Model_Data() {

    //This method contains 3 steps:
    //step 1: push the Bounding information associated with actor to the Map container
    //step 2: push the PolyData associated with the actor to the Map container
    //step 3: push the Actor to the Map container
    //for the CML file used in chemical area, need to convert the molecules and bonds to PolyData because most of the filter in vtk takes polydata as input source from my experiences, therefore this procedure is necessary if users want to do further filtering
    //for the MOD and VTU files, need to convert the ugrid to polydata and the reason is the same as above
    switch (this->mFileType) {

        case FileType::STL:
            Data_Inventory.BoundSet_Push_Back(Get_File_Name(mFilePath), mSTLReader->GetOutput()->GetBounds());
            Data_Inventory.PolyDataSet_Push_Back(Get_File_Name(mFilePath),mSTLReader->GetOutput());
            Data_Inventory.ActorSet_Push_Back(Get_File_Name(mFilePath), mActor);
            break;
        case FileType::MOD:
            Data_Inventory.BoundSet_Push_Back(Get_File_Name(mFilePath), mUnstructuredGrid->GetBounds());
            Data_Inventory.PolyDataSet_Push_Back(Get_File_Name(mFilePath),FilteringEvent::UGrid_To_PolyData(mUnstructuredGrid));
            Data_Inventory.ActorSet_Push_Back(Get_File_Name(mFilePath), mActor);
            break;

        case FileType::PLY:
            Data_Inventory.BoundSet_Push_Back(Get_File_Name(mFilePath), mPLYReader->GetOutput()->GetBounds());
            Data_Inventory.PolyDataSet_Push_Back(Get_File_Name(mFilePath),mPLYReader->GetOutput());
            Data_Inventory.ActorSet_Push_Back(Get_File_Name(mFilePath), mActor);
            break;

        case FileType::OBJ:
            Data_Inventory.BoundSet_Push_Back(Get_File_Name(mFilePath), mOBJReader->GetOutput()->GetBounds());
            Data_Inventory.PolyDataSet_Push_Back(Get_File_Name(mFilePath),mOBJReader->GetOutput());
            Data_Inventory.ActorSet_Push_Back(Get_File_Name(mFilePath), mActor);
            break;

        case FileType::JPG:
            Data_Inventory.BoundSet_Push_Back(Get_File_Name(mFilePath)+"-"+mInputSource, mJPGReader->GetOutput()->GetBounds());
            Data_Inventory.ActorSet_Push_Back(Get_File_Name(mFilePath)+"-"+mInputSource, mActor);
            break;

        case FileType::PNG:
            Data_Inventory.BoundSet_Push_Back(Get_File_Name(mFilePath)+"-"+mInputSource, mPNGReader->GetOutput()->GetBounds());
            Data_Inventory.ActorSet_Push_Back(Get_File_Name(mFilePath)+"-"+mInputSource, mActor);
            break;

        case FileType::CML:
            Data_Inventory.BoundSet_Push_Back(Get_File_Name(mFilePath), mCMLReader->GetOutput()->GetBounds());
            Data_Inventory.PolyDataSet_Push_Back(Get_File_Name(mFilePath),FilteringEvent::Molecule_To_PolyData(mCMLReader->GetOutput()));
            Data_Inventory.ActorSet_Push_Back(Get_File_Name(mFilePath), mActor);
            break;

        case FileType::VTU:
            Data_Inventory.BoundSet_Push_Back(Get_File_Name(mFilePath), mVTUReader->GetOutput()->GetBounds());
            Data_Inventory.PolyDataSet_Push_Back(Get_File_Name(mFilePath),FilteringEvent::UGrid_To_PolyData(mVTUReader->GetOutput()));
            Data_Inventory.ActorSet_Push_Back(Get_File_Name(mFilePath), mActor);
            break;

        case FileType::VTP:
            Data_Inventory.BoundSet_Push_Back(Get_File_Name(mFilePath), mVTPReader->GetOutput()->GetBounds());
            Data_Inventory.PolyDataSet_Push_Back(Get_File_Name(mFilePath),mVTPReader->GetOutput());
            Data_Inventory.ActorSet_Push_Back(Get_File_Name(mFilePath), mActor);
            break;

    }

}



QString FileIOEvent::Get_File_Name(const QString &FilePath) {

    return mFileInfo.baseName();
}

void FileIOEvent::Texture_Transformation_SetUp() {
    //set up texture transformation
    auto PolyDataNormal= vtkSmartPointer<vtkPolyDataNormals>::New();
    PolyDataNormal->SetInputData(Data_Inventory.Get_Value_From_PolyDataSet(mInputSource));
    auto TexturePlane = vtkSmartPointer<vtkTextureMapToPlane>::New();
    TexturePlane->SetInputConnection(PolyDataNormal->GetOutputPort());
    auto TransformTextureCoords = vtkSmartPointer<vtkTransformTextureCoords>::New();
    TransformTextureCoords->SetInputConnection(TexturePlane->GetOutputPort());
    TransformTextureCoords->SetScale(1, 1, 1);
    mPolyDataMapper->SetInputConnection(TransformTextureCoords->GetOutputPort());

}

void FileIOEvent::Write_To_A_File(const QString &SourceName) {

    //allocate memory to the writer based on the type of file the users want to write to
    //set the file you want to write to-> set input data of the writer -> write
    if(mFileInfo.suffix()=="stl"){

        mSTLWriter=vtkSmartPointer<vtkSTLWriter>::New();
        mSTLWriter->SetFileName(mFilePath.toStdString().c_str());
        mSTLWriter->SetInputData(Data_Inventory.Get_Value_From_PolyDataSet(SourceName));
        mSTLWriter->Write();

    }

    if(mFileInfo.suffix()=="ply"){

        mPLYWriter=vtkSmartPointer<vtkPLYWriter>::New();
        mPLYWriter->SetFileName(mFilePath.toStdString().c_str());
        mPLYWriter->SetInputData(Data_Inventory.Get_Value_From_PolyDataSet(SourceName));
        mPLYWriter->Write();

    }

    if(mFileInfo.suffix()=="obj"){

        mOBJWriter=vtkSmartPointer<vtkOBJWriter>::New();
        mOBJWriter->SetFileName(mFilePath.toStdString().c_str());
        mOBJWriter->SetInputData(Data_Inventory.Get_Value_From_PolyDataSet(SourceName));
        mOBJWriter->Write();

    }

    if(mFileInfo.suffix()=="vtu"){

        mVTUWriter= vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
        mVTUWriter->SetFileName(mFilePath.toStdString().c_str());
        mVTUWriter->SetInputData(Data_Inventory.Get_Value_From_PolyDataSet(SourceName));
        mVTUWriter->Write();

    }

    if(mFileInfo.suffix()=="vtp"){

        mVTPWriter= vtkSmartPointer<vtkXMLPolyDataWriter>::New();
        mVTPWriter->SetFileName(mFilePath.toStdString().c_str());
        mVTPWriter->SetInputData(Data_Inventory.Get_Value_From_PolyDataSet(SourceName));
        mVTPWriter->Write();

    }

}





