#include <CellDisplayDialog.h>
#include "ui_celldisplaydialog.h"
#include <qlineedit.h>
#include <qlabel.h>
#include <qmessagebox.h>
#include <vtkPolyData.h>
#include <qpushbutton.h>
#include <qcolordialog.h>
#include <DataInventory.h>
#include <FilteringEvent.h>
#include <RenderWindow.h>

int CellDisplayDialog::mStartCellID = 0;
int CellDisplayDialog::mEndCellID = 0;


CellDisplayDialog::CellDisplayDialog(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::CellDisplayDialog),
        mColor(new double[3]) {
    ui->setupUi(this);
    this->SetUp_GUI();
    this->Init_CellTypes_Map();
    this->Init_SignalAndSlot();

    //SET the default color
    mColor[0] = 0;
    mColor[1] = 0;
    mColor[2] = 1;

}

CellDisplayDialog::~CellDisplayDialog() {
    //Because there is dynamic memory allocation in the constructor, so it needs to be deallocated in the destructor, otherwise there will be memory leak
    if (mColor != nullptr) {
        delete[] mColor;
        mColor = nullptr;
    }
    delete ui;
}

void CellDisplayDialog::Set_Model_Available(QVector<QString> &modelAvailable) {

    //init the QCombo Box using the item stored in the array
    for (auto &item : modelAvailable) {
        ui->ModelSelection->addItem(item);
    }

}

void CellDisplayDialog::Init_SignalAndSlot() {

    //this signal and slot hook up allows the the widgets on the UI to be shown dynamically
    //for example if the users choose "is between" option in the combo box , there will be two LineEdits waiting to be filled out by the user
    //if the users choose "is" option , there will be only one LineEdit waiting to be filled out by the user
    //if the users choose "Max" option , there will be no lineEdit waiting to be filled out by the user, because the Maximum Cell's Id will be automatically determined using the VTK's method
    connect(ui->IDSelection, QOverload<const QString &>::of(&QComboBox::currentIndexChanged),
            [this](const QString &text) {

                if (!mEditToLayoutMap.isEmpty()) {
                    QHBoxLayout *RestLayout = mEditToLayoutMap.take(mMainValEdit);
                    while (RestLayout->count() != 0) {
                        QLayoutItem *item = RestLayout->takeAt(0);
                        delete item->widget();
                        delete item;
                    }
                }

                auto layout = qobject_cast<QHBoxLayout *>(ui->frame->layout());
                mMainValEdit = new QLineEdit(ui->frame);
                if (text == "is between") {
                    auto *label = new QLabel("And", ui->frame);
                    mOptionalValEdit = new QLineEdit(ui->frame);
                    layout->insertWidget(0, mMainValEdit);
                    layout->insertWidget(1, label);
                    layout->insertWidget(2, mOptionalValEdit);
                    mEditToLayoutMap.insert(mMainValEdit, layout);

                }
                if (text == "is >=" || text == "is <=" || text == "is") {
                    layout->insertWidget(0, mMainValEdit);
                    mEditToLayoutMap.insert(mMainValEdit, layout);
                }
            });


    //The slot function will get executed when the users click the ExtractSelection button
    connect(ui->ExtractSelection, &QPushButton::clicked, [this]() {

        //when the users only want to extract a single cell
        if (ui->IDSelection->currentText() == "is" && !this->mMainValEdit->text().isEmpty()) {

            //do the validation check
            if (mMainValEdit->text().toInt() < 0 || mMainValEdit->text().toInt() >
                                                    Data_Inventory.Get_Value_From_PolyDataSet(
                                                            ui->ModelSelection->currentText())->GetNumberOfCells() -
                                                    1) {
                QMessageBox::warning(nullptr, "Warning", "Invalid Input");
            } else {
                //do the sources preparation->add data to the inventory->establish the pipeline->reset camera->render
                mStartCellID = mMainValEdit->text().toInt();
                FilteringEvent CellFiltering(ui->ModelSelection->currentText(),
                                             mColor,
                                             FilteringEvent::Mode::CELL_IS
                );
                DataInventory::Add_Data_To_Inventory(CellFiltering);
                RenderWindow::Establish_PipeLine(CellFiltering);
                Render_Window.Reset_Camera("Cell-" + ui->ModelSelection->currentText());
                Render_Window.Render();
                //add item to the treeWidget
                emit this->TreeWidget_Add_ChildItem("Cell-" + ui->ModelSelection->currentText());
            }

        }

            // when the users want the extract a range of cells
        else if (ui->IDSelection->currentText() == "is between" && !this->mMainValEdit->text().isEmpty() &&
                 !this->mOptionalValEdit->text().isEmpty()) {

            if (mMainValEdit->text().toInt() >= mOptionalValEdit->text().toInt()) {
                QMessageBox::warning(nullptr, "Warning", "Invalid Input");
            } else {
                //do the sources preparation->add data to the inventory->establish the pipeline->reset camera->render
                mStartCellID = mMainValEdit->text().toInt();
                mEndCellID = mOptionalValEdit->text().toInt();
                FilteringEvent CellFiltering(ui->ModelSelection->currentText(),
                                             mColor,
                                             FilteringEvent::Mode::CELL_IS_BETWEEN
                );
                DataInventory::Add_Data_To_Inventory(CellFiltering);
                RenderWindow::Establish_PipeLine(CellFiltering);
                Render_Window.Reset_Camera("Cell-" + ui->ModelSelection->currentText());
                Render_Window.Render();
                //add item to the tree widget
                emit this->TreeWidget_Add_ChildItem("Cell-" + ui->ModelSelection->currentText());
            }
        }

            //when the users want to extract all the cells greater than a certain ID
        else if (ui->IDSelection->currentText() == "is >=" && !this->mMainValEdit->text().isEmpty()) {

            if (mMainValEdit->text().toInt() >
                Data_Inventory.Get_Value_From_PolyDataSet(ui->ModelSelection->currentText())->GetNumberOfCells() - 1) {
                QMessageBox::warning(nullptr, "Warning", "Invalid Input");
            } else {
                //do the sources preparation->add data to the inventory->establish the pipeline->reset camera->render
                mStartCellID = mMainValEdit->text().toInt();
                mEndCellID = Data_Inventory.Get_Value_From_PolyDataSet(
                        ui->ModelSelection->currentText())->GetNumberOfCells();
                FilteringEvent CellFiltering(ui->ModelSelection->currentText(),
                                             mColor,
                                             FilteringEvent::Mode::CELL_GREATER_EQUAL_THAN
                );
                DataInventory::Add_Data_To_Inventory(CellFiltering);
                RenderWindow::Establish_PipeLine(CellFiltering);
                Render_Window.Reset_Camera("Cell-" + ui->ModelSelection->currentText());
                Render_Window.Render();
                //add item to the tree widget
                emit this->TreeWidget_Add_ChildItem("Cell-" + ui->ModelSelection->currentText());
            }
        }

            //when the users want to extract all the cells less than a certain ID
        else if (ui->IDSelection->currentText() == "is <=" && !this->mMainValEdit->text().isEmpty()) {

            if (mMainValEdit->text().toInt() < 0) {
                QMessageBox::warning(nullptr, "Warning", "Invalid Input");
            } else {
                //do the sources preparation->add data to the inventory->establish the pipeline->reset camera->render
                mStartCellID = 0;
                mEndCellID = mMainValEdit->text().toInt();
                FilteringEvent CellFiltering(ui->ModelSelection->currentText(),
                                             mColor,
                                             FilteringEvent::Mode::CELL_LESS_EQUAL_THAN
                );
                DataInventory::Add_Data_To_Inventory(CellFiltering);
                RenderWindow::Establish_PipeLine(CellFiltering);
                Render_Window.Reset_Camera("Cell-" + ui->ModelSelection->currentText());
                Render_Window.Render();
                //add item to the treeWidget
                emit this->TreeWidget_Add_ChildItem("Cell-" + ui->ModelSelection->currentText());
            }
        }

            //when the users only want to extract the first cell
        else if (ui->IDSelection->currentText() == "is Min") {
            //do the sources preparation->add data to the inventory->establish the pipeline->reset camera->render
            mStartCellID = 0;
            FilteringEvent CellFiltering(ui->ModelSelection->currentText(),
                                         mColor,
                                         FilteringEvent::Mode::CELL_MIN
            );
            DataInventory::Add_Data_To_Inventory(CellFiltering);
            RenderWindow::Establish_PipeLine(CellFiltering);
            Render_Window.Reset_Camera("Cell-" + ui->ModelSelection->currentText());
            Render_Window.Render();
            //add item to the treeWidget
            emit this->TreeWidget_Add_ChildItem("Cell-" + ui->ModelSelection->currentText());

        }

            //when the users only want to extract the last cell
        else if (ui->IDSelection->currentText() == "is Max") {

            //do the sources preparation->add data to the inventory->establish the pipeline->reset camera->render
            mEndCellID = static_cast<int>(
                    (Data_Inventory.Get_Value_From_PolyDataSet(ui->ModelSelection->currentText())->GetNumberOfCells()) -
                    1);
            FilteringEvent CellFiltering(ui->ModelSelection->currentText(),
                                         mColor,
                                         FilteringEvent::Mode::CELL_MAX
            );
            DataInventory::Add_Data_To_Inventory(CellFiltering);
            RenderWindow::Establish_PipeLine(CellFiltering);
            Render_Window.Reset_Camera("Cell-" + ui->ModelSelection->currentText());
            Render_Window.Render();
            //add item to the treewidget
            emit this->TreeWidget_Add_ChildItem("Cell-" + ui->ModelSelection->currentText());

        } else {

            QMessageBox::warning(nullptr, "Warning", "Invalid Input");
        }


    });

    //This signal and slot hook up is used to display the cells' types
    connect(ui->RunQuery, &QPushButton::clicked, [this]() {

        //when the users only want to know the type of a single cell
        if (ui->IDSelection->currentText() == "is" && !this->mMainValEdit->text().isEmpty()) {
            if (mMainValEdit->text().toInt() < 0 || mMainValEdit->text().toInt() >
                                                    Data_Inventory.Get_Value_From_PolyDataSet(
                                                            ui->ModelSelection->currentText())->GetNumberOfCells() -
                                                    1) {
                QMessageBox::warning(nullptr, "Warning", "Invalid Input");
            } else {
                //clear the previous ID and types stored in the containers->push new data into the containers->Send data to the tableWidget to display
                this->Clear_IDsAndTypes();
                this->mCellIDs.push_back(mMainValEdit->text().toInt());
                this->mCellTypes.push_back(
                        Data_Inventory.Get_Value_From_PolyDataSet(ui->ModelSelection->currentText())->GetCell(
                                mMainValEdit->text().toInt())->GetCellType());
                this->Init_TableWidget();
            }

        }

            //when the users want to know a range of cells' types
        else if (ui->IDSelection->currentText() == "is between" && !this->mMainValEdit->text().isEmpty() &&
                 !this->mOptionalValEdit->text().isEmpty() &&
                 mMainValEdit->text().toInt() < mOptionalValEdit->text().toInt()) {

            if (mMainValEdit->text().toInt() >= mOptionalValEdit->text().toInt()) {
                QMessageBox::warning(nullptr, "Warning", "Invalid Input");
            } else {
                //clear the previous ID and types stored in the containers->push new data into the containers->Send data to the tableWidget to display
                this->Clear_IDsAndTypes();
                for (int i = mMainValEdit->text().toInt(); i < (mOptionalValEdit->text().toInt()) + 1; i++) {
                    mCellIDs.push_back(i);
                    mCellTypes.push_back(
                            Data_Inventory.Get_Value_From_PolyDataSet(ui->ModelSelection->currentText())->GetCell(
                                    i)->GetCellType());

                }
                this->Init_TableWidget();
            }

        }

            //when the users want to know all the cells' types greater than a certain index
        else if (ui->IDSelection->currentText() == "is >=" && !this->mMainValEdit->text().isEmpty()) {
            if (mMainValEdit->text().toInt() >
                Data_Inventory.Get_Value_From_PolyDataSet(ui->ModelSelection->currentText())->GetNumberOfCells() - 1) {
                QMessageBox::warning(nullptr, "Warning", "Invalid Input");
            } else {
                //clear the previous ID and types stored in the containers->push new data into the containers->Send data to the tableWidget to display
                this->Clear_IDsAndTypes();
                for (int i = mMainValEdit->text().toInt(); i < Data_Inventory.Get_Value_From_PolyDataSet(
                        ui->ModelSelection->currentText())->GetNumberOfCells(); i++) {
                    mCellIDs.push_back(i);
                    mCellTypes.push_back(
                            Data_Inventory.Get_Value_From_PolyDataSet(ui->ModelSelection->currentText())->GetCell(
                                    i)->GetCellType());

                }
                this->Init_TableWidget();
            }
        }

            //when the user want to know all the cell's types less than a certain index
        else if (ui->IDSelection->currentText() == "is <=" && !this->mMainValEdit->text().isEmpty()) {
            if (mMainValEdit->text().toInt() < 0) {
                QMessageBox::warning(nullptr, "Warning", "Invalid Input");
            } else {
                //clear the previous ID and types stored in the containers->push new data into the containers->Send data to the tableWidget to display
                this->Clear_IDsAndTypes();
                for (int i = 0; i < (mMainValEdit->text().toInt()) + 1; i++) {
                    mCellIDs.push_back(i);
                    mCellTypes.push_back(
                            Data_Inventory.Get_Value_From_PolyDataSet(ui->ModelSelection->currentText())->GetCell(
                                    i)->GetCellType());

                }
                this->Init_TableWidget();
            }

        }

            //when the users only want to know the type of the first cell
        else if (ui->IDSelection->currentText() == "is Min") {
            //clear the previous ID and types stored in the containers->push new data into the containers->Send data to the tableWidget to display
            this->Clear_IDsAndTypes();
            this->mCellIDs.push_back(0);
            this->mCellTypes.push_back(
                    Data_Inventory.Get_Value_From_PolyDataSet(ui->ModelSelection->currentText())->GetCell(
                            0)->GetCellType());
            this->Init_TableWidget();

        }


            //when the users only want to know the type of the last cell
        else if (ui->IDSelection->currentText() == "is Max") {
            //clear the previous ID and types stored in the containers->push new data into the containers->Send data to the tableWidget to display
            this->Clear_IDsAndTypes();
            this->mCellIDs.push_back(
                    (Data_Inventory.Get_Value_From_PolyDataSet(ui->ModelSelection->currentText())->GetNumberOfCells()) -
                    1);
            this->mCellTypes.push_back(
                    Data_Inventory.Get_Value_From_PolyDataSet(ui->ModelSelection->currentText())->GetCell(
                            (Data_Inventory.Get_Value_From_PolyDataSet(
                                    ui->ModelSelection->currentText())->GetNumberOfCells()) - 1)->GetCellType());
            this->Init_TableWidget();
        } else {

            QMessageBox::warning(nullptr, "Warning", "Invalid Input");
        }


    });

    //this signal and slot hook up is used to hide the dialog
    connect(ui->CloseDialog, &QPushButton::clicked, [this]() {

        this->hide();

    });

    //this signal and slot hook up is used to set the selected cells' color
    connect(ui->SelectColor, &QPushButton::clicked, [this]() {

        QColor color = QColorDialog::getColor(Qt::white, nullptr, "Choose color");
        mColor[0] = static_cast<double>(color.red()) / 255;
        mColor[1] = static_cast<double>(color.green()) / 255;
        mColor[2] = static_cast<double>(color.blue()) / 255;


    });

}


void CellDisplayDialog::SetUp_GUI() {


    this->setFixedSize(570, 440);
    this->setWindowIcon(QIcon(":/Icons/48.png"));
    ui->ModelSelection->setFixedSize(400, 20);
    //set the cells' selection
    QStringList Options = {" ", "is", "is between", "is >=", "is <=", "is Min", "is Max"};
    ui->IDSelection->addItems(Options);

}

void CellDisplayDialog::Init_TableWidget() {

    //Init the TableWidget based on the information stored in the containers
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(this->mCellIDs.size());
    ui->tableWidget->setHorizontalHeaderLabels(QStringList({"Cell ID", "Cell Types"}));
    QStringList Vheader;
    for (int i = 0; i < this->mCellIDs.size(); i++) {
        Vheader << QString::number(i);
    }
    ui->tableWidget->setVerticalHeaderLabels(Vheader);


    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {


        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(mCellIDs[i])));

        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(mCellTypesMap.find(mCellTypes[i]).value()));


    }

}


void CellDisplayDialog::Init_CellTypes_Map() {

    // the integer representation of the types and corresponding string representation mapping
    mCellTypesMap.insert(0, "EMPTY_CELL");
    mCellTypesMap.insert(1, "VERTEX");
    mCellTypesMap.insert(2, "POLY_VERTEX");
    mCellTypesMap.insert(3, "LINE");
    mCellTypesMap.insert(4, "POLY_LINE");
    mCellTypesMap.insert(5, "TRIANGLE");
    mCellTypesMap.insert(6, "TRIANGLE_STRIP");
    mCellTypesMap.insert(7, "POLYGON");
    mCellTypesMap.insert(8, "PIXEL");
    mCellTypesMap.insert(9, "QUAD");
    mCellTypesMap.insert(10, "TETRA");
    mCellTypesMap.insert(11, "VOXEL");
    mCellTypesMap.insert(12, "HEXAHEDRON");
    mCellTypesMap.insert(13, "WEDGE");
    mCellTypesMap.insert(14, "PYRAMID");
    mCellTypesMap.insert(15, "PENTAGONAL_PRISM");
    mCellTypesMap.insert(16, "HEXAGONAL_PRISM");

}

void CellDisplayDialog::Clear_IDsAndTypes() {

    //reset the containers
    this->mCellIDs.clear();
    this->mCellTypes.clear();

}

