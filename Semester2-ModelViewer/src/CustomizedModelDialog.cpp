#include "CustomizedModelDialog.h"
#include "ui_CustomizedModelDialog.h"
#include <qcolordialog.h>
#include <qvector.h>
#include <vector3d.h>
#include <CustomizedModelRenderingEvent.h>
#include <DataInventory.h>
#include <RenderWindow.h>
#include <qdebug.h>


CustomizedModelDialog::CustomizedModelDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomizedModelDialog),
    mColor(new double[3])
{
    ui->setupUi(this);
    this->Signal_And_Slot_SetUp();
    this->Init_ComboBox();

    //SET the default color
    mColor[0]=0;
    mColor[1]=0;
    mColor[2]=1;
}

CustomizedModelDialog::~CustomizedModelDialog()
{
    //deallocate the allocated memory in the constructor
    if(mColor!= nullptr){
        delete[] mColor;
        mColor = nullptr;
    }
    delete ui;
}

void CustomizedModelDialog::Signal_And_Slot_SetUp() {

    //This signal and slot hook up is used to establish relationship between combo Box and treeWidget
    //for instance, if the user choose triangle to render, then there will be 3 rows waiting users to fill out in the tableWidget
    //if the user choose quad to render, then there will be 4 rows waiting users to fill out in the tableWidget
    connect(ui->CellType_comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this](int index){
                switch (index) {
                    case 1:
                        this->Init_TableWidget(8);
                        break;

                    case 2:
                        this->Init_TableWidget(6);
                        break;

                    case 3:
                        this->Init_TableWidget(5);
                        break;

                    case 4:
                        this->Init_TableWidget(4);
                        break;

                    case 5:
                        this->Init_TableWidget(4);
                        break;

                    case 6:
                        this->Init_TableWidget(3);
                        break;

                    case 7:
                        this->Init_TableWidget(2);
                        break;
                }

    });


    //This signal and slot hook up is used to render the cell after users has provided vertex information in the tableWidget
    connect(ui->Render_Btn,&QPushButton::clicked, [this](){

        //collect vertex information that users put in the tableWidget
        QVector<vector3D> VertexList;
        QVector<double> Coordinates;
        for(int CurrentRow=0 ; CurrentRow<ui->tableWidget->rowCount();CurrentRow++){

            Coordinates.clear();
            for(int CurrentColumn=0; CurrentColumn<ui->tableWidget->columnCount();CurrentColumn++) {

                if (!ui->tableWidget->item(CurrentRow, CurrentColumn)->text().isEmpty()) {
                    Coordinates.push_back(ui->tableWidget->item(CurrentRow, CurrentColumn)->text().toDouble());
                }
            }

          VertexList.push_back(vector3D(CurrentRow,Coordinates[0],Coordinates[1],Coordinates[2]));

        }

        //do the cell rendering
        if(ui->CellType_comboBox->currentIndex()==1){

            //sending vertex information->establish the PipeLine->add data to the inventory->reset camera->render the cell
           if(!(Data_Inventory=="VTK_HEXAHEDRON")) {
               CustomizedModelRenderingEvent CustomizedModel(CustomizedModelRenderingEvent::Mode::USER_DEFINED_RENDER,
                                                             CustomizedModelRenderingEvent::CellType::VTK_HEXAHEDRON,
                                                             mColor,
                                                             VertexList);
               RenderWindow::Establish_PipeLine(CustomizedModel);
               DataInventory::Add_Data_To_Inventory(CustomizedModel);
               Render_Window.Reset_Camera("VTK_HEXAHEDRON");
               Render_Window.Render();
               this->TreeWidget_Add_ParentItem("VTK_HEXAHEDRON");
           }

        }

        if(ui->CellType_comboBox->currentIndex()==2){

            //sending vertex information->establish the PipeLine->add data to the inventory->reset camera->render the cell
            if(!(Data_Inventory=="VTK_POLYGON")) {
                CustomizedModelRenderingEvent CustomizedModel(CustomizedModelRenderingEvent::Mode::USER_DEFINED_RENDER,
                                                              CustomizedModelRenderingEvent::CellType::VTK_POLYGON,
                                                              mColor,
                                                              VertexList);
                RenderWindow::Establish_PipeLine(CustomizedModel);
                DataInventory::Add_Data_To_Inventory(CustomizedModel);
                Render_Window.Reset_Camera("VTK_POLYGON");
                Render_Window.Render();
                this->TreeWidget_Add_ParentItem("VTK_POLYGON");
            }
        }


        if(ui->CellType_comboBox->currentIndex()==3){

            //sending vertex information->establish the PipeLine->add data to the inventory->reset camera->render the cell
            if(!(Data_Inventory=="VTK_PYRAMID")) {
                CustomizedModelRenderingEvent CustomizedModel(CustomizedModelRenderingEvent::Mode::USER_DEFINED_RENDER,
                                                              CustomizedModelRenderingEvent::CellType::VTK_PYRAMID,
                                                              mColor,
                                                              VertexList);
                RenderWindow::Establish_PipeLine(CustomizedModel);
                DataInventory::Add_Data_To_Inventory(CustomizedModel);
                Render_Window.Reset_Camera("VTK_PYRAMID");
                Render_Window.Render();
                this->TreeWidget_Add_ParentItem("VTK_PYRAMID");
            }

        }


        if(ui->CellType_comboBox->currentIndex()==4){

            //sending vertex information->establish the PipeLine->add data to the inventory->reset camera->render the cell
            if(!(Data_Inventory=="VTK_TETRA")) {
                CustomizedModelRenderingEvent CustomizedModel(CustomizedModelRenderingEvent::Mode::USER_DEFINED_RENDER,
                                                              CustomizedModelRenderingEvent::CellType::VTK_TETRA,
                                                              mColor,
                                                              VertexList);
                RenderWindow::Establish_PipeLine(CustomizedModel);
                DataInventory::Add_Data_To_Inventory(CustomizedModel);
                Render_Window.Reset_Camera("VTK_TETRA");
                Render_Window.Render();
                this->TreeWidget_Add_ParentItem("VTK_TETRA");
            }

        }


        if(ui->CellType_comboBox->currentIndex()==5){

            //sending vertex information->establish the PipeLine->add data to the inventory->reset camera->render the cell
            if (!(Data_Inventory == "VTK_QUAD")) {
                CustomizedModelRenderingEvent CustomizedModel(CustomizedModelRenderingEvent::Mode::USER_DEFINED_RENDER,
                                                              CustomizedModelRenderingEvent::CellType::VTK_QUAD,
                                                              mColor,
                                                              VertexList);
                RenderWindow::Establish_PipeLine(CustomizedModel);
                DataInventory::Add_Data_To_Inventory(CustomizedModel);
                Render_Window.Reset_Camera("VTK_QUAD");
                Render_Window.Render();
                this->TreeWidget_Add_ParentItem("VTK_QUAD");
            }
        }

        if(ui->CellType_comboBox->currentIndex()==6){

            //sending vertex information->establish the PipeLine->add data to the inventory->reset camera->render the cell
            if (!(Data_Inventory == "VTK_TRIANGLE")) {
                CustomizedModelRenderingEvent CustomizedModel(CustomizedModelRenderingEvent::Mode::USER_DEFINED_RENDER,
                                                              CustomizedModelRenderingEvent::CellType::VTK_TRIANGLE,
                                                              mColor,
                                                              VertexList);
                RenderWindow::Establish_PipeLine(CustomizedModel);
                DataInventory::Add_Data_To_Inventory(CustomizedModel);
                Render_Window.Reset_Camera("VTK_TRIANGLE");
                Render_Window.Render();
                this->TreeWidget_Add_ParentItem("VTK_TRIANGLE");
            }

        }

        if(ui->CellType_comboBox->currentIndex()==7){

            //sending vertex information->establish the PipeLine->add data to the inventory->reset camera->render the cell
            if (!(Data_Inventory == "VTK_LINE")) {
                CustomizedModelRenderingEvent CustomizedModel(CustomizedModelRenderingEvent::Mode::USER_DEFINED_RENDER,
                                                              CustomizedModelRenderingEvent::CellType::VTK_LINE,
                                                              mColor,
                                                              VertexList);
                RenderWindow::Establish_PipeLine(CustomizedModel);
                DataInventory::Add_Data_To_Inventory(CustomizedModel);
                Render_Window.Reset_Camera("VTK_LINE");
                Render_Window.Render();
                this->TreeWidget_Add_ParentItem("VTK_LINE");
            }
        }

    });


    connect(ui->SetColor_Btn, &QPushButton::clicked, [this](){
        //let users choose the cell color they want
        QColor color = QColorDialog::getColor(Qt::white, nullptr, "Choose color");
        mColor[0] = static_cast<double>(color.red())/255;
        mColor[1] = static_cast<double>(color.green())/255;
        mColor[2] = static_cast<double>(color.blue())/255;

    });


    //close the dialog when the close button is clicked
    connect(ui->Close_Btn,&QPushButton::clicked,[this]{
       this->close();
    });


}


void CustomizedModelDialog::Init_ComboBox() {

    //add available cells' names to the combo Box
    QStringList ComboBoxItems = {" ", "VTK_HEXAHEDRON", "VTK_POLYGON", "VTK_PYRAMID", "VTK_TETRA", "VTK_QUAD",
                                 "VTK_TRIANGLE", "VTK_LINE"};
    ui->CellType_comboBox->addItems(ComboBoxItems);

}

void CustomizedModelDialog::Init_TableWidget(const int& RowCount) {

    //init table widget
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(RowCount);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList({"X", "Y", "Z"}));

}

