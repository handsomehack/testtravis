#ifndef FILEIOEVENT_H
#define FILEIOEVENT_H
#include <QFileInfo>
#include <VTKPipeLine.h>
#include <QString>
#include <vtkSmartPointer.h>
class vtkCMLMoleculeReader;
class vtkJPEGReader;
class vtkPNGReader;
class vtkSTLReader;
class vtkUnstructuredGrid;
class vtkTexture;
class vtkPLYReader;
class vtkOBJReader;
class vtkSTLWriter;
class vtkPLYWriter;
class vtkOBJWriter;
class vtkXMLPolyDataReader;
class vtkXMLUnstructuredGridReader;
class vtkXMLPolyDataWriter;
class vtkXMLUnstructuredGridWriter;
#define Data_Inventory DataInventory::Get_Instance()
#define Render_Window  RenderWindow::Get_Instance()


/*
 * Copyright:Group 6
 */

/// This class is used to handle the file reading and writing events
class FileIOEvent: public VTKPipeLine
{
public:

    ///This enum is used to decide whether users want to read or write a file
    enum class Mode{

        READ,
        WRITE
    };

    ///This enum holds the available file types
    ///vtk accepts lots of file types, but the procedure is totally the same, so here I am gonna provide some types that are commonly used
    enum class FileType{

        STL,
        MOD,
        PLY,
        OBJ,
        CML,
        JPG,
        PNG,
        VTP,
        VTU

    };

    ///constructor of the class
    ///@param FilePath the file path
    ///@param mode read or write the file
    ///@param SourceName this parameter is used when the users want to write data to a file by specifying the name of the source
    explicit FileIOEvent(QString& FilePath, Mode mode, const QString& SourceName=QString());

    ///This method is used to get the base name of a file
    ///for instance a file named girl.stl, then girl is returned
    ///@param FilePath the file path
    ///@return the base name of a file
    QString Get_File_Name(const QString& FilePath);

    ///This method is used to set the source the users what to apply texture on
    ///@param the name of the source
    void Set_Source_To_Apply_Texture_On(const QString& InputSource){mInputSource=InputSource;};


    ///@note This is a reimplemented method
    ///This method contains the procedure from **source** to **mapper**
    void Source_To_Mapper() override;

    ///@note This is a reimplemented method
    ///This method contains the procedure from **Actor** to **Renderer**
    void Actor_To_Renderer() override;


    ///@note This is a reimplemented method
    ///This method is used to set the Actor's properties
    void Set_Actor_Property() override;

    ///@note This is a reimplemented method
    ///This method is used to store the information of an Actor
    void Store_Model_Data() override;


private:

    ///@attention this method is used internally by this class
    ///This method is used to set up the texture transformation
    void Texture_Transformation_SetUp();

    ///@attention this method is used internally by this class
    ///This method is used to write data to a file
    ///@param SourceName the name of the source
    void Write_To_A_File(const QString& SourceName);


private:

    Mode mMode{};
    FileType mFileType{};
    QString mInputSource;
    QString mFilePath;
    QFileInfo mFileInfo;
    vtkSmartPointer<vtkUnstructuredGrid> mUnstructuredGrid;
    vtkSmartPointer<vtkTexture> mTexture;
    vtkSmartPointer<vtkSTLReader> mSTLReader;
    vtkSmartPointer<vtkJPEGReader> mJPGReader;
    vtkSmartPointer<vtkPNGReader> mPNGReader;
    vtkSmartPointer<vtkCMLMoleculeReader> mCMLReader;
    vtkSmartPointer<vtkPLYReader> mPLYReader;
    vtkSmartPointer<vtkOBJReader> mOBJReader;
    vtkSmartPointer<vtkXMLPolyDataReader> mVTPReader;
    vtkSmartPointer<vtkXMLUnstructuredGridReader> mVTUReader;
    vtkSmartPointer<vtkSTLWriter> mSTLWriter;
    vtkSmartPointer<vtkOBJWriter> mOBJWriter;
    vtkSmartPointer<vtkPLYWriter> mPLYWriter;
    vtkSmartPointer<vtkXMLPolyDataWriter> mVTPWriter;
    vtkSmartPointer<vtkXMLUnstructuredGridWriter> mVTUWriter;

};

#endif
