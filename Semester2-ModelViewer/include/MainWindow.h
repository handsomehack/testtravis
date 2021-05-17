#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMultiMap>
#include <qmap.h>
#include <qvector.h>
#include <CellDisplayDialog.h>
#include <CustomizedModelDialog.h>
class QTreeWidgetItem;
class QComboBox;
class QAction;
class QLineEdit;
class QCheckBox;
class QSlider;
class QPushButton;
#define Render_Window  RenderWindow::Get_Instance()
#define Data_Inventory DataInventory::Get_Instance()
#define Active_Camera  CameraReaction::Get_Instance()

/*
 * Copyright:Group 6
 */


namespace Ui {
class MainWindow;
}

///This is the MainWindow GUI class
class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    ///constructor of the class
    explicit MainWindow(QWidget *parent = nullptr);

    ///destructor of the class
    ~MainWindow() override;


public slots:
    ///This method is used to add parentItem to the TreeWidget
    ///@param ItemName name of the item
    void TreeWidget_Add_ParentItem(const QString& ItemName);

    ///This method is used to add childItem  to the TreeWidget
    ///@param ItemName name of the item
    void TreeWidget_Add_ChildItem(const QString& ItemName);

private:
    ///@attention This method is used internally of this class
    ///This method is used to initialize the OpenGlWidget
    void Init_OpenGLWindow();

    ///@attention This method is used internally of this class
    ///This method is used to set up the MainWindow appearance
    void SetUp_MainWindow();

    ///@attention This method is used internally of this class
    ///This method is used to set up the Menubar
    void SetUp_Menubar();

    ///@attention This method is used internally of this class
    ///This method is used to set up the Toolbar
    void SetUp_Toolbar();

    ///@attention This method is used internally of this class
    ///This method is used to set up all the signal and slot connections
    void Signal_And_Slot_SetUp();

    ///@attention This method is used internally of this class
    ///This method is used to do the statistic calculation on a model
    ///@param ModelName name of the model
    void Model_Statistic_Calculation(const QString& ModelName);

    ///@attention This method is used internally of this class
    ///This method is used to reset all the lineEdit and LCD widgets
    void Reset_Display_Widgets();





private slots:
    ///@attention This method is used internally of this class
    ///This method is used to create a right-clicked menu when the users right click on an item in the TreeWidget
    void OnCustomContextMenuRequested(const QPoint &pos);

    ///@attention This method is used internally of this class
    ///This method is used to initialize the CellSelection Dialog
    void init_CellDisplay_Dialog();

    ///@attention This method is used internally of this class
    ///This method is used to initialize the customizedCell Dialog
    void init_Customize_Model_Dialog();


private:
    Ui::MainWindow* ui;
    QPushButton* mCustomizedModelButton{};
    QPushButton* mCameraIncrementButton{};
    QPushButton* mCameraDecrementButton{};
    QComboBox* mViewModeComboBox{};
    QAction* mModelColorAction{};
    QAction* mBackgroundColorAction{};
    QAction* mDeleteTreeWidgetItemAction{};
    QLineEdit* mCurrentModelEdit{};
    QSlider* mOpacitySlider{};
    QSlider* mSpecularLightingSlider{};
    QSlider* mDiffuseLightingSlier{};
    QSlider* mAmbientLightingSlider{};
    QCheckBox* mFrontfaceCullingCheckbox{};
    QCheckBox* mBackfaceCullingCheckbox{};
    QCheckBox* mAxesGridCheckbox{};
    QCheckBox* mOrientationAxesCheckbox{};
    QCheckBox* mvtkImplicitPlaneWidget2Checkbox{};
    QCheckBox* mBoxWidgetcCheckbox{};
    QMap<QString, QTreeWidgetItem *> mTreeWidgetParentItems;
    QMultiMap<QString, QString> mTreeWidgetChildItems;
    QString mTreeWidgetCurrentlySelectedItem;
    CellDisplayDialog mCellDisplayDialog;
    CustomizedModelDialog mCustomizedModelDialog;


};

#endif // MAINWINDOW_H
