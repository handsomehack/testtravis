#ifndef CELLDISPLAYDIALOG_H
#define CELLDISPLAYDIALOG_H
#include <QWidget>
#include <qvector.h>
#include <qhash.h>
class QLineEdit;
class QHBoxLayout;
#define Render_Window  RenderWindow::Get_Instance()
#define Data_Inventory DataInventory::Get_Instance()

namespace Ui {
class CellDisplayDialog;
}

/*
 * Copyright: Group6
 *
 */

///This is a GUI class
///This class is used to display the cells selected by the user
///
///This class also has the ability to check cells' types of a model
class CellDisplayDialog : public QWidget
{
    Q_OBJECT

public:
    ///The constructor of the class
    explicit CellDisplayDialog(QWidget *parent = nullptr);

    ///The destructor of the class
    ~CellDisplayDialog() override;

    ///This method is used to set the available model on the QCombo Box
    ///@param modelAvailable an array contains the available models
    void Set_Model_Available(QVector<QString> &modelAvailable);

    ///This method is used to get the starting cell's ID
    ///@return the ID of the staring cell
    static int Get_StartCellID() { return mStartCellID; };

    ///This method is used to get the ending cell's ID
    ///@return the ID of the ending cell
    static int Get_EndCellID() { return mEndCellID; };

    CellDisplayDialog(const CellDisplayDialog& )= delete;

    CellDisplayDialog& operator=(const CellDisplayDialog& )= delete;


signals:

    ///This signal is used to add item on the MainWindow's TreeWidget
    void TreeWidget_Add_ChildItem(const QString &ItemName);


private:
    ///@attention This is a private method and it's meant to be used internally in this class
    ///This method sets up the signal and slot connection
    void Init_SignalAndSlot();

    ///@attention This is a private method and it's meant to be used internally in this class
    ///This method sets up the GUI appearance
    void SetUp_GUI();

    ///@attention This is a private method and it's meant to be used internally in this class
    ///This method is used to initialize the TableWidget
    void Init_TableWidget();

    ///@attention This is a private method and it's meant to be used internally in this class
    ///This method is used to Map the int to its corresponding string
    ///@note Because the VTK's GetCellType() method returns an integer representation of a cell's type, so this mapping function is used to make the user knows what a cell's type is intuitively
    void Init_CellTypes_Map();

    ///@note This is a private method and it's meant to be used internally in this class
    ///This method is used to reset the ID and type containers, thus allows the tableWidget to be reusable.
    void Clear_IDsAndTypes();



private:

    Ui::CellDisplayDialog *ui;
    QVector<int> mCellIDs;
    QVector<int> mCellTypes;
    QHash<QLineEdit*,QHBoxLayout*>  mEditToLayoutMap;
    QHash<int,QString> mCellTypesMap;
    QLineEdit* mMainValEdit{};
    QLineEdit* mOptionalValEdit{};
    double* mColor;
    static int mStartCellID;
    static int mEndCellID;

};

#endif // CELLDISPLAYDIALOG_H
