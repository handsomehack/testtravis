#ifndef CUSTOMIZEDMODELDIALOG_H
#define CUSTOMIZEDMODELDIALOG_H
#include <QWidget>
#include <memory>
#define Render_Window  RenderWindow::Get_Instance()
#define Data_Inventory DataInventory::Get_Instance()
/*
 * Copyright: Group6
 *
 */


namespace Ui {
class CustomizedModelDialog;
}


///This is GUI class
///This class is used to ask users what kind of cell they want to render and collect vertex information if they prefer defining the vertices by themselves
/// This class is closely related to CustomizedModelRenderingEvent
///@see CustomizedModelRenderingEvent
class CustomizedModelDialog : public QWidget
{
    Q_OBJECT

public:
    ///Constructor of the class
    explicit CustomizedModelDialog(QWidget *parent = nullptr);

    ///destructor of the class
    ~CustomizedModelDialog() override;


    CustomizedModelDialog(const CustomizedModelDialog& )= delete;

    CustomizedModelDialog& operator=(const CustomizedModelDialog& )= delete;

signals:
    ///This signal is used to add item on the MainWindow's TreeWidget
    void TreeWidget_Add_ParentItem(const QString& ModelName);

private:
    ///@attention This is a private method and it's meant to be used internally in this class
    ///This method is used to initialize the Combo Box on the GUI
   void Init_ComboBox();

    ///@attention This is a private method and it's meant to be used internally in this class
    ///This method is used to initialize the TableWidget on the GUI
    ///@param RowCount the number of rows in the tableWidget
   void Init_TableWidget(const int& RowCount);

    ///@attention This is a private method and it's meant to be used internally in this class
    ///This method sets up the signal and slot connection
   void Signal_And_Slot_SetUp();

private:
    Ui::CustomizedModelDialog *ui;
    double* mColor;
};

#endif // CUSTOMIZEDMODELDIALOG_H
