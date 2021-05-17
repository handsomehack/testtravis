#include <MainWindow.h>
#include "ui_mainwindow.h"
#include <qfiledialog.h>
#include <vtkRenderer.h>
#include <vtkNamedColors.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <qcombobox.h>
#include <qmessagebox.h>
#include <vtkPolyData.h>
#include <vtkMassProperties.h>
#include <vtkProperty.h>
#include <qtoolbutton.h>
#include <QCheckBox>
#include <qmenu.h>
#include <qaction.h>
#include <qcolordialog.h>
#include <vtkTriangleFilter.h>
#include <CellDisplayDialog.h>
#include <DataInventory.h>
#include <RenderWindow.h>
#include <BuiltInSourceRenderingEvent.h>
#include <FilteringEvent.h>
#include <CameraReaction.h>
#include <FileIOEvent.h>
#include <CustomizedModelRenderingEvent.h>
#include <qpushbutton.h>
#include <QDebug>


MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //call the following methods to set up the MainWindow
    ui->setupUi(this);

    SetUp_MainWindow();

    SetUp_Menubar();

    SetUp_Toolbar();

    Init_OpenGLWindow();

    Signal_And_Slot_SetUp();



}


void MainWindow::Signal_And_Slot_SetUp()
{




    //render a cube when the users click CubeAction
    connect(ui->actionCube, &QAction::triggered, [this]() {
        if (!mTreeWidgetParentItems.contains("Cube")) {
            //do the sources preparation-> establish the pipeline -> store the object data -> set the camera to a good angle -> render -> add render item to the TreeWidget
            BuiltInSourceRenderingEvent CubeRender(BuiltInSourceRenderingEvent::Mode::CUBE_RENDER);
            RenderWindow::Establish_PipeLine(CubeRender);
            DataInventory::Add_Data_To_Inventory(CubeRender);
            Render_Window.Reset_Camera("Cube");
            Render_Window.Render();
            this->TreeWidget_Add_ParentItem("Cube");
        }
        });

    //render a sphere when the users click SphereAction
    connect(ui->actionSphere, &QAction::triggered, [this]() {
        if(!mTreeWidgetParentItems.contains("Sphere")) {
            //do the sources preparation-> establish the pipeline -> store the object data -> set the camera to a good angle -> render -> add render item to the TreeWidget
            BuiltInSourceRenderingEvent SphereRender(BuiltInSourceRenderingEvent::Mode::SPHERE_RENDER);
            RenderWindow::Establish_PipeLine(SphereRender);
            DataInventory::Add_Data_To_Inventory(SphereRender);
            Render_Window.Reset_Camera("Sphere");
            Render_Window.Render();
            this->TreeWidget_Add_ParentItem("Sphere");
        }

        });

    //render a cylinder when the users click CylinderAction
    connect(ui->actionCylinder, &QAction::triggered, [this]() {
        if(!mTreeWidgetParentItems.contains("Cylinder")) {
            //do the sources preparation-> establish the pipeline -> store the object data -> set the camera to a good angle -> render -> add render item to the TreeWidget
            BuiltInSourceRenderingEvent CylinderRender(BuiltInSourceRenderingEvent::Mode::CYLINDER_RENDER);
            RenderWindow::Establish_PipeLine(CylinderRender);
            DataInventory::Add_Data_To_Inventory(CylinderRender);
            Render_Window.Reset_Camera("Cylinder");
            Render_Window.Render();
            this->TreeWidget_Add_ParentItem("Cylinder");
        }
    });

    //render a cone when the users click ConeAction
    connect(ui->actionCone, &QAction::triggered, [this]() {
        if(!mTreeWidgetParentItems.contains("Cone")) {
            //do the sources preparation-> establish the pipeline -> store the object data -> set the camera to a good angle -> render -> add render item to the TreeWidget
            BuiltInSourceRenderingEvent ConeRender(BuiltInSourceRenderingEvent::Mode::CONE_RENDER);
            RenderWindow::Establish_PipeLine(ConeRender);
            DataInventory::Add_Data_To_Inventory(ConeRender);
            Render_Window.Reset_Camera("Cone");
            Render_Window.Render();
            this->TreeWidget_Add_ParentItem("Cone");
        }
        });

    //render a disk when the users click DiskAction
    connect(ui->actionDisk, &QAction::triggered, [this]() {
        if(!mTreeWidgetParentItems.contains("Disk")) {
            //do the sources preparation-> establish the pipeline -> store the object data -> set the camera to a good angle -> render -> add render item to the TreeWidget
            BuiltInSourceRenderingEvent DiskRender(BuiltInSourceRenderingEvent::Mode::DISK_RENDER);
            RenderWindow::Establish_PipeLine(DiskRender);
            DataInventory::Add_Data_To_Inventory(DiskRender);
            Render_Window.Reset_Camera("Disk");
            Render_Window.Render();
            this->TreeWidget_Add_ParentItem("Disk");
        }
        });

    //render a line when the users click LineAction
    connect(ui->actionLine, &QAction::triggered, [this]() {
        if(!mTreeWidgetParentItems.contains("Line")) {
            //do the sources preparation-> establish the pipeline -> store the object data -> set the camera to a good angle -> render -> add render item to the TreeWidget
            BuiltInSourceRenderingEvent LineRender(BuiltInSourceRenderingEvent::Mode::LINE_RENDER);
            RenderWindow::Establish_PipeLine(LineRender);
            DataInventory::Add_Data_To_Inventory(LineRender);
            Render_Window.Reset_Camera("Line");
            Render_Window.Render();
            this->TreeWidget_Add_ParentItem("Line");
        }
    });

    //render a pyramid when the users click PyramidAction
    connect(ui->actionPyramid, &QAction::triggered, [this]() {
        if(!mTreeWidgetParentItems.contains("Pyramid")) {
            //do the sources preparation-> establish the pipeline -> store the object data -> set the camera to a good angle -> render -> add render item to the TreeWidget
            CustomizedModelRenderingEvent PyramidRnder(CustomizedModelRenderingEvent::Mode::PYRAMID_RENDER);
            RenderWindow::Establish_PipeLine(PyramidRnder);
            DataInventory::Add_Data_To_Inventory(PyramidRnder);
            Render_Window.Reset_Camera("Pyramid");
            Render_Window.Render();
            this->TreeWidget_Add_ParentItem("Pyramid");
        }
        });

    //render a hexa when the users click hexaAction
    connect(ui->actionHexahedron, &QAction::triggered, [this]() {
        if(!mTreeWidgetParentItems.contains("Hexahedron")) {
            //do the sources preparation-> establish the pipeline -> store the object data -> set the camera to a good angle -> render -> add render item to the TreeWidget
            CustomizedModelRenderingEvent  HexaRnder(CustomizedModelRenderingEvent::Mode::HEXA_RENDER);
            RenderWindow::Establish_PipeLine(HexaRnder);
            DataInventory::Add_Data_To_Inventory(HexaRnder);
            Render_Window.Reset_Camera("Hexahedron");
            Render_Window.Render();
            this->TreeWidget_Add_ParentItem("Hexahedron");
        }
        });

    //render a tetra when the users click tetraAction
    connect(ui->actionTetrahedron, &QAction::triggered, [this]() {
        if(!mTreeWidgetParentItems.contains("Tetrahedron")) {
            //do the sources preparation-> establish the pipeline -> store the object data -> set the camera to a good angle -> render -> add render item to the TreeWidget
            CustomizedModelRenderingEvent TetraRender(CustomizedModelRenderingEvent::Mode::TETRA_RENDER);
            RenderWindow::Establish_PipeLine(TetraRender);
            DataInventory::Add_Data_To_Inventory(TetraRender);
            Render_Window.Reset_Camera("Tetrahedron");
            Render_Window.Render();
            this->TreeWidget_Add_ParentItem("Tetrahedron");
        }
        });

    //render a arrow when users click  arrowAction
    connect(ui->actionArrow, &QAction::triggered, [this](){
        if(!mTreeWidgetParentItems.contains("Dodecahedron")) {
            //do the sources preparation-> establish the pipeline -> store the object data -> set the camera to a good angle -> render -> add render item to the TreeWidget
            BuiltInSourceRenderingEvent ArrowRender(BuiltInSourceRenderingEvent::Mode::ARROW_RENDER);
            RenderWindow::Establish_PipeLine(ArrowRender);
            DataInventory::Add_Data_To_Inventory(ArrowRender);
            Render_Window.Reset_Camera("Arrow");
            Render_Window.Render();
            this->TreeWidget_Add_ParentItem("Arrow");
        }
    });



    //do the outline filtering when the users click outlineAction
    connect(ui->actionOutLine, &QAction::triggered, [this]() {

        if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {
            //do the sources preparation-> establish the pipeline -> store the object data -> set the camera to a good angle -> render -> add render item to the TreeWidget
            double Color[3] = {0,1,0};
            FilteringEvent OutlineFiltering(mTreeWidgetCurrentlySelectedItem,
                                               Color,
                                               FilteringEvent::Mode::OUTLINE);
            RenderWindow::Establish_PipeLine(OutlineFiltering);
            DataInventory::Add_Data_To_Inventory(OutlineFiltering);
            Render_Window.Reset_Camera("Outline-"+mTreeWidgetCurrentlySelectedItem);
            Render_Window.Render();
            this->TreeWidget_Add_ChildItem("Outline-"+mTreeWidgetCurrentlySelectedItem);

        }
        else
        {
            QMessageBox::warning(this, "Warning", "Please select/click a valid source to filter");
        }
        });


    //do the triangulate filtering when the users click triangulateAction
    connect(ui->actionTriangulate, &QAction::triggered, [this]() {

        if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {
            //do the sources preparation-> establish the pipeline -> store the object data -> set the camera to a good angle -> render -> add render item to the TreeWidget
            double Color[3] = {0,1,0};
            FilteringEvent TriangulateFiltering(mTreeWidgetCurrentlySelectedItem,
                                               Color,
                                               FilteringEvent::Mode::TRIANGULATE);
            RenderWindow::Establish_PipeLine(TriangulateFiltering);
            DataInventory::Add_Data_To_Inventory(TriangulateFiltering);
            Render_Window.Reset_Camera("Triangulate-"+mTreeWidgetCurrentlySelectedItem);
            Render_Window.Render();
            this->TreeWidget_Add_ChildItem("Triangulate-"+mTreeWidgetCurrentlySelectedItem);

        }
        else
        {
            QMessageBox::warning(this, "Warning", "Please select/click a valid source to filter");
        }
        });

    // do the smooth filtering when the users click SmoothAction
    connect(ui->actionSmooth, &QAction::triggered, [this]() {

        if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {
            //do the sources preparation-> establish the pipeline -> store the object data -> set the camera to a good angle -> render -> add render item to the TreeWidget
            double Color[3] = {0,1,0};
            FilteringEvent SmoothFiltering(mTreeWidgetCurrentlySelectedItem,
                                                   Color,
                                                   FilteringEvent::Mode::SMOOTH);
            RenderWindow::Establish_PipeLine(SmoothFiltering);
            DataInventory::Add_Data_To_Inventory(SmoothFiltering);
            Render_Window.Reset_Camera("Smooth-"+mTreeWidgetCurrentlySelectedItem);
            Render_Window.Render();
            this->TreeWidget_Add_ChildItem("Smooth-"+mTreeWidgetCurrentlySelectedItem);

        }
        else
        {
            QMessageBox::warning(this, "Warning", "Please select/click a valid source to filter");
        }
        });

    //do the shrink filtering when the users click ShrinkAction
    connect(ui->actionShrink, &QAction::triggered, [this]() {

        if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {
            //do the sources preparation-> establish the pipeline -> store the object data -> set the camera to a good angle -> render -> add render item to the TreeWidget
            double Color[3] = {0, 1, 0};
            FilteringEvent ShrinkFiltering(mTreeWidgetCurrentlySelectedItem,
                                           Color,
                                           FilteringEvent::Mode::SHRINK);
            RenderWindow::Establish_PipeLine(ShrinkFiltering);
            DataInventory::Add_Data_To_Inventory(ShrinkFiltering);
            Render_Window.Reset_Camera("Shrink-" + mTreeWidgetCurrentlySelectedItem);
            Render_Window.Render();
            this->TreeWidget_Add_ChildItem("Shrink-" + mTreeWidgetCurrentlySelectedItem);

        }
        else
        {
            QMessageBox::warning(this, "Warning", "Please select/click a valid source to filter");
        }
        });

    ///do the clip filtering when the users click ClipAction
    connect(ui->actionClip, &QAction::triggered, [this]() {

        if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {
            //do the sources preparation-> establish the pipeline -> store the object data -> set the camera to a good angle -> render -> add render item to the TreeWidget
            double Color[3] = {0,1,0};
            FilteringEvent ClipFiltering(mTreeWidgetCurrentlySelectedItem,
                                              Color,
                                              FilteringEvent::Mode::CLIP);
            RenderWindow::Establish_PipeLine(ClipFiltering);
            DataInventory::Add_Data_To_Inventory(ClipFiltering);
            Render_Window.Reset_Camera("Clip-"+mTreeWidgetCurrentlySelectedItem);
            Render_Window.Render();
            this->TreeWidget_Add_ChildItem("Clip-"+mTreeWidgetCurrentlySelectedItem);
            this->mvtkImplicitPlaneWidget2Checkbox->setCheckState(Qt::Checked);

        }
        else
        {
            QMessageBox::warning(this, "Warning", "Please select/click a valid source to filter");
        }
        });

    //do the contour filtering when the users click ContourAction
    connect(ui->actionContour, &QAction::triggered, [this]() {

        if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {
            //do the sources preparation-> establish the pipeline -> store the object data -> set the camera to a good angle -> render -> add render item to the TreeWidget
            double Color[3] = {0,1,0};
            FilteringEvent ContourFiltering(mTreeWidgetCurrentlySelectedItem,
                                            Color,
                                            FilteringEvent::Mode::CONTOUR);
            RenderWindow::Establish_PipeLine(ContourFiltering);
            DataInventory::Add_Data_To_Inventory(ContourFiltering);
            Render_Window.Reset_Camera("Contour-"+mTreeWidgetCurrentlySelectedItem);
            Render_Window.Render();
            this->TreeWidget_Add_ChildItem("Contour-"+mTreeWidgetCurrentlySelectedItem);

        }
        else
        {
            QMessageBox::warning(this, "Warning", "Please select/click a valid source to filter");
        }
        });

    //do the Delaunay2D filtering when the users click D2D filtering
    connect(ui->actionDelaunay2D, &QAction::triggered, [this]() {

        if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {
            //do the sources preparation-> establish the pipeline -> store the object data -> set the camera to a good angle -> render -> add render item to the TreeWidget
            double Color[3] = {0,1,0};
            FilteringEvent Delaunay2DFiltering(mTreeWidgetCurrentlySelectedItem,
                                               Color,
                                               FilteringEvent::Mode::DELAUNAY2D);
            RenderWindow::Establish_PipeLine(Delaunay2DFiltering);
            DataInventory::Add_Data_To_Inventory(Delaunay2DFiltering);
            Render_Window.Reset_Camera("Delaunay2D-"+mTreeWidgetCurrentlySelectedItem);
            Render_Window.Render();
            this->TreeWidget_Add_ChildItem("Delaunay2D-"+mTreeWidgetCurrentlySelectedItem);

        }
        else
        {
            QMessageBox::warning(this, "Warning", "Please select/click a valid source to filter");
        }
        });

    //set the model representation mode(e.g. wireframe, surface, etc) when the users interact with the combo Box
    connect(this->mViewModeComboBox, QOverload<int>::of(&QComboBox::activated),
        [this](int index) {

            switch (index) {
                case 0:
                    if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {

                        Data_Inventory.Get_Value_From_ActorSet(
                                mTreeWidgetCurrentlySelectedItem)->GetProperty()->SetEdgeVisibility(false);
                        Data_Inventory.Get_Value_From_ActorSet(
                                mTreeWidgetCurrentlySelectedItem)->GetProperty()->SetRepresentationToSurface();
                        Render_Window.Render();
                    } else {
                        QMessageBox::warning(this, "Warning",
                                             "Please select/click a valid source to filter in the view");
                    }
                    break;
                case 1:

                    if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {

                        Data_Inventory.Get_Value_From_ActorSet(
                                mTreeWidgetCurrentlySelectedItem)->GetProperty()->SetRepresentationToWireframe();
                        Render_Window.Render();
                    } else {
                        QMessageBox::warning(this, "Warning",
                                             "Please select/click a valid source to filter in the view");
                    }
                    break;
                case 2:
                    if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {

                        Data_Inventory.Get_Value_From_ActorSet(
                                mTreeWidgetCurrentlySelectedItem)->GetProperty()->SetRepresentationToPoints();
                        Render_Window.Render();
                    } else {
                        QMessageBox::warning(this, "Warning",
                                             "Please select/click a valid source to filter in the view");
                    }
                    break;

                case 3:
                    if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {

                        Data_Inventory.Get_Value_From_ActorSet(
                                mTreeWidgetCurrentlySelectedItem)->GetProperty()->SetRepresentationToSurface();
                        Data_Inventory.Get_Value_From_ActorSet(
                                mTreeWidgetCurrentlySelectedItem)->GetProperty()->SetEdgeVisibility(true);
                        Data_Inventory.Get_Value_From_ActorSet(
                                mTreeWidgetCurrentlySelectedItem)->GetProperty()->SetEdgeColor(0, 0, 255);
                        Render_Window.Render();
                    } else {
                        QMessageBox::warning(this, "Warning",
                                             "Please select/click a valid source to filter in the view");
                    }
                    break;
            }
        });

    //set the camera to positive X direction
    connect(ui->actionPositiveX, &QAction::triggered, [this]() {

        if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {

            Active_Camera.Adjust_Camera_Position(CameraReaction::Mode::RESET_POSITIVE_X);
            //reset the camera to make sure the model can be seen
            Render_Window.Reset_Camera(mTreeWidgetCurrentlySelectedItem);
            Render_Window.Render();

        }
        else
        {
            QMessageBox::warning(this, "Warning", "Please select/click a source to view in the pipeline");
        }
        });

    //set the camera to negative X direction
    connect(ui->actionNegativeX, &QAction::triggered, [this]() {
        if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {

            Active_Camera.Adjust_Camera_Position(CameraReaction::Mode::RESET_NEGATIVE_X);
            //reset the camera to make sure the model can be seen
            Render_Window.Reset_Camera(mTreeWidgetCurrentlySelectedItem);
            Render_Window.Render();

        }
        else
        {
            QMessageBox::warning(this, "Warning", "Please select/click a source to view in the pipeline");
        }
        });

    //set the camera to positive Y direction
    connect(ui->actionPositiveY, &QAction::triggered, [this]() {
        if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {

            Active_Camera.Adjust_Camera_Position(CameraReaction::Mode::RESET_POSITIVE_Y);
            //reset the camera to make sure the model can be seen
            Render_Window.Reset_Camera(mTreeWidgetCurrentlySelectedItem);
            Render_Window.Render();

        }
        else
        {
            QMessageBox::warning(this, "Warning", "Please select/click a source to view in the pipeline");
        }
        });

    //set the camera to negative Y direction
    connect(ui->actionNegaitiveY, &QAction::triggered, [this]() {
        if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {

            Active_Camera.Adjust_Camera_Position(CameraReaction::Mode::RESET_NEGATIVE_Y);
            //reset the camera to make sure the model can be seen
            Render_Window.Reset_Camera(mTreeWidgetCurrentlySelectedItem);
            Render_Window.Render();


        }
        else
        {
            QMessageBox::warning(this, "Warning", "Please select/click a source to view in the pipeline");
        }
        });

    //set the camera to positive Z direction
    connect(ui->actionPositiveZ, &QAction::triggered, [this]() {
        if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {

            Active_Camera.Adjust_Camera_Position(CameraReaction::Mode::RESET_POSITIVE_Z);
            //reset the camera to make sure the model can be seen
            Render_Window.Reset_Camera(mTreeWidgetCurrentlySelectedItem);
            Render_Window.Render();


        }
        else
        {
            QMessageBox::warning(this, "Warning", "Please select/click a source to view in the pipeline");
        }
        });

    //set the camera to negative z direction
    connect(ui->actionNegaitiveZ, &QAction::triggered, [this]() {
        if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {

            Active_Camera.Adjust_Camera_Position(CameraReaction::Mode::RESET_NEGATIVE_Z);
            //reset the camera to make sure the model can be seen
            Render_Window.Reset_Camera(mTreeWidgetCurrentlySelectedItem);
            Render_Window.Render();


        }
        else
        {
            QMessageBox::warning(this, "Warning", "Please select/click a source to view in the pipeline");
        }
        });

    //rotate the camera 90 clockwise
    connect(ui->actionRotate90degCW, &QAction::triggered, [this]() {
        if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {

            Active_Camera+90;
            Render_Window.Reset_Camera(mTreeWidgetCurrentlySelectedItem);
            Render_Window.Render();


        }
        else
        {
            QMessageBox::warning(this, "Warning", "Please select/click a source to view in the pipeline");
        }
        });

    //rotate the camera 90 degree anti-clockwise
    connect(ui->actionRotate90degCCW, &QAction::triggered, [this]() {
        if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {

            Active_Camera-90;
            Render_Window.Reset_Camera(mTreeWidgetCurrentlySelectedItem);
            Render_Window.Render();

        }
        else
        {
            QMessageBox::warning(this, "Warning", "Please select/click a source to view in the pipeline");
        }
        });

    //rotate the camera 10 degree clockwise
    connect(this->mCameraIncrementButton,&QPushButton::clicked,[this](){

        if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {

            ++Active_Camera;
            Render_Window.Reset_Camera(mTreeWidgetCurrentlySelectedItem);
            Render_Window.Render();

        }
        else
        {
            QMessageBox::warning(this, "Warning", "Please select/click a source to view in the pipeline");
        }
    });

    //rotate the camera 10 degree anti-clockwise
    connect(this->mCameraDecrementButton,&QPushButton::clicked,[this](){

        if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {

            --Active_Camera;
            Render_Window.Reset_Camera(mTreeWidgetCurrentlySelectedItem);
            Render_Window.Render();

        }
        else
        {
            QMessageBox::warning(this, "Warning", "Please select/click a source to view in the pipeline");
        }
    });


    //reset the camera the original position
    connect(ui->ActionResetCamera, &QAction::triggered, [this]() {
        if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {

            Active_Camera.Adjust_Camera_Position(CameraReaction::Mode::RESET_CAMERA);
            Render_Window.Reset_Camera(mTreeWidgetCurrentlySelectedItem);
            Render_Window.Render();


        }
        else
        {
            QMessageBox::warning(this, "Warning", "Please select/click a source to view in the pipeline");
        }
        });

   //change the model's opacity when the users interact withe the slider
    connect(this->mOpacitySlider, QOverload<int>::of(&QSlider::valueChanged), [this](int currentVal) {
        double OpacityFacotr = static_cast<double>(currentVal) / 200;
        if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {

            Data_Inventory.Get_Value_From_ActorSet(mTreeWidgetCurrentlySelectedItem)->GetProperty()->SetOpacity(OpacityFacotr);
            Render_Window.Render();

        }
    });

    //enable or disable the backface culling when the users interact with the checkbox
    connect(this->mBackfaceCullingCheckbox,&QCheckBox::stateChanged,[this](int State){
        if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {
            Data_Inventory.Get_Value_From_ActorSet(mTreeWidgetCurrentlySelectedItem)->GetProperty()->SetBackfaceCulling(State);
            Render_Window.Render();
        }
    });

    //enable or disable the frontface culling when the users interact with the checkbox
    connect(this->mFrontfaceCullingCheckbox, &QCheckBox::stateChanged, [this](int State){
        if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {
            Data_Inventory.Get_Value_From_ActorSet(
                    mTreeWidgetCurrentlySelectedItem)->GetProperty()->SetFrontfaceCulling(State);
            Render_Window.Render();
        }
    });

    //enable or disable the Axis Grid when the users interact with the checkbox
    connect(this->mAxesGridCheckbox,&QCheckBox::clicked,[this](bool state){

        if(mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {
            if (state) {

                Render_Window.Show_Axis_Grid_Actor(mTreeWidgetCurrentlySelectedItem);

            } else {

                Render_Window.Hide_Actor("Axis Grid");

            }
        }
        else
        {
            QMessageBox::warning(this, "Warning", "Please select/click a valid source");
        }

    });

    //enable or disable the orientation axis when the users interact with the checkbox
    connect(this->mOrientationAxesCheckbox,&QCheckBox::clicked,[this](bool state){

        if (state) {

            Render_Window.Show_Orientation_Axes_Actor();

        } else {

            Render_Window.Hide_Orientation_Axes_Actor();

        }

    });

    //enable or disable the clipping plane when the users interact withe the checkbox
    connect(this->mvtkImplicitPlaneWidget2Checkbox,&QCheckBox::clicked,[this](bool state){

        if(mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {
            if (state) {
                double Color[3] = {0,1,0};
                FilteringEvent ClipFiltering(mTreeWidgetCurrentlySelectedItem,
                                             Color,
                                             FilteringEvent::Mode::CLIP);
                RenderWindow::Establish_PipeLine(ClipFiltering);
                DataInventory::Add_Data_To_Inventory(ClipFiltering);
                Render_Window.Reset_Camera("Clip-"+mTreeWidgetCurrentlySelectedItem);
                Render_Window.Render();
                this->TreeWidget_Add_ChildItem("Clip-"+mTreeWidgetCurrentlySelectedItem);;

            } else {

                Render_Window.Hide_Clipping_Plane_Actor();

            }
        }
        else
        {
            QMessageBox::warning(this, "Warning", "Please select/click a valid source to clip");
        }

    });

    //enable or disable the boxWidget when the users interact with the checkbox
    connect(this->mBoxWidgetcCheckbox,&QCheckBox::clicked,[this](bool state){

        if(mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {
            if (state) {

              Render_Window.Show_Box_Widget(mTreeWidgetCurrentlySelectedItem);

            } else {

                Render_Window.Hide_Box_Widget();

            }
        }
        else
        {
            QMessageBox::warning(this, "Warning", "Please select/click a valid source to clip");
        }

    });


    //change the model color when the users click ChangeModelColor Action
    connect(this->mModelColorAction, &QAction::triggered, [this]() {
        QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");
        double Red = static_cast<double>(color.red())/255;
        double Green = static_cast<double>(color.green())/255;
        double Blue = static_cast<double>(color.blue())/255;
        if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {

            Data_Inventory.Get_Value_From_ActorSet(mTreeWidgetCurrentlySelectedItem)->GetProperty()->SetColor(Red, Green, Blue);
            Render_Window.Render();

        }
    });

    //change the renderWindow color when the users click changeBackgroundColor Action
    connect(this->mBackgroundColorAction, &QAction::triggered, [this]() {
        QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");
        double Red = static_cast<double>(color.red())/255;
        double Green = static_cast<double>(color.green())/255;
        double Blue = static_cast<double>(color.blue())/255;
        Render_Window.Set_Window_Background_Color(Red,Green,Blue);
        Render_Window.Render();

    });

    //set the specular lighting effect
    connect(this->mSpecularLightingSlider, QOverload<int>::of(&QSlider::valueChanged), [this](int val){
        double SpecularFacotr = static_cast<double>(val) / 200;
        if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {

            Data_Inventory.Get_Value_From_ActorSet(mTreeWidgetCurrentlySelectedItem)->GetProperty()->SetSpecular(SpecularFacotr);
            Render_Window.Render();

        }
    });

    //set the diffuse lighting effect
    connect(this->mDiffuseLightingSlier, QOverload<int>::of(&QSlider::valueChanged), [this](int val){
        double DiffuseFacotr = static_cast<double>(val) / 200;
        if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {

            Data_Inventory.Get_Value_From_ActorSet(mTreeWidgetCurrentlySelectedItem)->GetProperty()->SetDiffuse(DiffuseFacotr);
            Render_Window.Render();

        }
    });


    //set the Ambient lighting effect
    connect(this->mAmbientLightingSlider, QOverload<int>::of(&QSlider::valueChanged), [this](int val){
        double AmbientFacotr = static_cast<double>(val) / 200;
        if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {

            Data_Inventory.Get_Value_From_ActorSet(mTreeWidgetCurrentlySelectedItem)->GetProperty()->SetAmbient(AmbientFacotr);
            Render_Window.Render();

        }
    });

    //open the fileDialog and read the file
    connect(ui->actionFileOpen, &QAction::triggered, [this]() {
         //get the file path
         QString Filepath = QFileDialog::getOpenFileName(this, tr("Open File"), "./",
                                                         tr("MOD file (*.mod)"
                                                            ";;STL file(*.stl)"
                                                            ";;CML file(*.cml)"
                                                            ";;PLY file(*.ply)"
                                                            ";;OBJ file(*.obj)"
                                                            ";;VTP file(*.vtp)"
                                                            ";;VTU file(*.vtu)")
                                                         );

         if(!Filepath.isEmpty()) {
             //read data from the file -> establish the pipeline -> store the object data -> set the camera to a good angle -> render -> add render item to the TreeWidget
             FileIOEvent LoadFile(Filepath, FileIOEvent::Mode::READ);
             RenderWindow::Establish_PipeLine(LoadFile);
             DataInventory::Add_Data_To_Inventory(LoadFile);
             Render_Window.Reset_Camera(LoadFile.Get_File_Name(Filepath));
             Render_Window.Render();
             this->TreeWidget_Add_ParentItem(LoadFile.Get_File_Name(Filepath));
         }
        });

    //open the fileDialog and write to a file
    connect(ui->actionFileSave, &QAction::triggered, [this](){
        //get the file path
        QString Filepath = QFileDialog::getOpenFileName(this, tr("Open File"), "./",
                                                        tr("STL file(*.stl)"
                                                           ";;PLY file(*.ply)"
                                                           ";;OBJ file(*.obj)"
                                                           ";;VTP file(*.vtp)"
                                                           ";;VTU file(*.vtu)")
        );

        if(!Filepath.isEmpty()) {
            //write the data
            FileIOEvent LoadFile(Filepath, FileIOEvent::Mode::WRITE,mTreeWidgetCurrentlySelectedItem);
        }

    });

    //apply texture from a jpg or png file to the model
    connect(ui->actionTexture, &QAction::triggered, [this](){

        if (mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {

            QString Filepath = QFileDialog::getOpenFileName(this, tr("Open File"), "./", tr("Texture Files (*.jpg *.png)"));
            if(!Filepath.isEmpty()) {
                //load the texture and text the model to apply texture onto
                FileIOEvent LoadFile(Filepath, FileIOEvent::Mode::READ);
                LoadFile.Set_Source_To_Apply_Texture_On(mTreeWidgetCurrentlySelectedItem);
                RenderWindow::Establish_PipeLine(LoadFile);
                DataInventory::Add_Data_To_Inventory(LoadFile);
                Render_Window.Reset_Camera(LoadFile.Get_File_Name(Filepath)+"-"+mTreeWidgetCurrentlySelectedItem);
                Render_Window.Render();
                this->TreeWidget_Add_ChildItem(LoadFile.Get_File_Name(Filepath)+"-"+mTreeWidgetCurrentlySelectedItem);
            }

        }
        else
        {
            QMessageBox::warning(this, "Warning", "Please select/click a source to apply texture on");
        }
        });

    //hide or show the model when the users uncheck or check the checkbox in front of the TreeWidgetItem
    connect(ui->treeWidget, &QTreeWidget::itemClicked, [this](QTreeWidgetItem* item, int column) {

        mTreeWidgetCurrentlySelectedItem = QString(item->text(0));
        if (item->checkState(column) == Qt::Unchecked) {

            Render_Window.Hide_Actor(mTreeWidgetCurrentlySelectedItem);

        }
        if (item->checkState(column) == Qt::Checked) {

            Render_Window.Show_Actor(mTreeWidgetCurrentlySelectedItem);
            mCurrentModelEdit->setText(item->text(0));

        }

    });

    //Display the model and its statistic calculation when the users click on an item
    connect(ui->treeWidget, &QTreeWidget::itemPressed,[this](QTreeWidgetItem* item, int column){

        mTreeWidgetCurrentlySelectedItem = QString(item->text(0));
        if(mTreeWidgetParentItems.contains(mTreeWidgetCurrentlySelectedItem)) {
            mCurrentModelEdit->setText(item->text(0));
            this->Model_Statistic_Calculation(item->text(0));
        }

    });



    //open the right-clicked menu when the users right click on an item in the treeWidget
    connect(ui->treeWidget, &QWidget::customContextMenuRequested,this,&MainWindow::OnCustomContextMenuRequested);

    //open the CellSelection Dialog when the users click the pushbutton
    connect(ui->pushButton_DisplayCell, &QPushButton::clicked, this, &MainWindow::init_CellDisplay_Dialog);

    //add childItem in the treeWidget
    connect(&mCellDisplayDialog, &CellDisplayDialog::TreeWidget_Add_ChildItem, this, &MainWindow::TreeWidget_Add_ChildItem);

    //open the customizedModel Dialog when the users click the pushbutton
    connect(this->mCustomizedModelButton, &QPushButton::clicked, this, &MainWindow::init_Customize_Model_Dialog);

    //add childItem in the treeWidget
    connect(&mCustomizedModelDialog, &CustomizedModelDialog::TreeWidget_Add_ParentItem, this, &MainWindow::TreeWidget_Add_ParentItem);


}



void MainWindow::TreeWidget_Add_ParentItem(const QString &ItemName) {
    //add parentItem in the treeWidget
    auto* Parent = new QTreeWidgetItem(ui->treeWidget);
    Parent->setText(0, ItemName);
    Parent->setCheckState(0, Qt::Checked);
    Parent->setExpanded(true);
    mTreeWidgetParentItems.insert(ItemName, Parent);
    mCurrentModelEdit->setText(ItemName);
    mTreeWidgetCurrentlySelectedItem = ItemName;
    Model_Statistic_Calculation(ItemName);

}

void MainWindow::TreeWidget_Add_ChildItem(const QString &ItemName) {

    //add childItem based on the paraentItem in the treeWidget
    auto* Child = new QTreeWidgetItem(mTreeWidgetParentItems.value(ItemName.section('-',1,1)));
    Child->setText(0, ItemName);
    Child->setCheckState(0, Qt::Checked);
    this->mTreeWidgetChildItems.insert(ItemName.section('-',1,1),ItemName);

}



void MainWindow::OnCustomContextMenuRequested(const QPoint& pos)
{
    //create right-clicked menu for use to delete the model or apply filter on it
    auto *RightClickMenu = new QMenu(this);
    mDeleteTreeWidgetItemAction = new QAction("Delete", this);
    auto *FiltersMenu = RightClickMenu->addMenu("Add Filters");
    FiltersMenu->addAction(ui->actionShrink);
    FiltersMenu->addAction(ui->actionOutLine);
    FiltersMenu->addAction(ui->actionSmooth);
    FiltersMenu->addAction(ui->actionTriangulate);
    FiltersMenu->addAction(ui->actionDelaunay2D);
    FiltersMenu->addAction(ui->actionClip);
    FiltersMenu->addAction(ui->actionContour);
    RightClickMenu->addAction(mDeleteTreeWidgetItemAction);
    auto rightClickItem = RightClickMenu->exec(QCursor::pos());
    if (rightClickItem != nullptr) {
        //if the users want to delete an treeWidgetItem
        if (rightClickItem->text().contains("Delete")) {

            QTreeWidgetItem *SelectedItem = nullptr;
            SelectedItem = ui->treeWidget->itemAt(pos);
            //check the item needs to be deleted is a parentItem or childItem
            if (this->mTreeWidgetParentItems.contains(SelectedItem->text(0))) {
                 //check if the item needs to be deleted has any children
                if (SelectedItem->childCount() != 0) {
                    //delete all the children and data associated with them stored in the inventory
                    QList<QTreeWidgetItem *> children = SelectedItem->takeChildren();
                    for (auto child : children) {

                            if(child->text(0).contains("Clip")){
                                 Render_Window.Hide_Clipping_Plane_Actor();
                                 this->mvtkImplicitPlaneWidget2Checkbox->setCheckState(Qt::Unchecked);
                            }
                            Render_Window.Remove_Actor(child->text(0));
                            Data_Inventory.BoundSet_Pop_Back(child->text(0));
                            delete child;

                    }
                    Render_Window.Remove_Actor(SelectedItem->text(0));
                    Data_Inventory.BoundSet_Pop_Back(SelectedItem->text(0));
                    Data_Inventory.PolyDataSet_Pop_Back(SelectedItem->text(0));
                    this->mTreeWidgetParentItems.remove(SelectedItem->text(0));
                    this->mTreeWidgetChildItems.remove(SelectedItem->text(0));
                    delete SelectedItem;
                    this->Reset_Display_Widgets();
                } else {
                    //if the item needs to be deleted does not have any children, then just delete itself and remove data associated with it  from the inventory
                    Render_Window.Remove_Actor(SelectedItem->text(0));
                    Data_Inventory.BoundSet_Pop_Back(SelectedItem->text(0));
                    Data_Inventory.PolyDataSet_Pop_Back(SelectedItem->text(0));
                    this->mTreeWidgetParentItems.remove(SelectedItem->text(0));
                    delete SelectedItem;
                    this->Reset_Display_Widgets();
                }
            } else {
                //delete the item when the item is a child item
                //delete the clipping object is a bit different, so the procedure is a bit different
                if(SelectedItem->text(0).contains("Clip")){
                    Render_Window.Hide_Clipping_Plane_Actor();
                    this->mvtkImplicitPlaneWidget2Checkbox->setCheckState(Qt::Unchecked);
                }
                Render_Window.Remove_Actor(SelectedItem->text(0));
                Data_Inventory.BoundSet_Pop_Back(SelectedItem->text(0));
                this->mTreeWidgetChildItems.remove(SelectedItem->parent()->text(0),SelectedItem->text(0));
                delete SelectedItem;
            }

        }
    }

}


void MainWindow::SetUp_Toolbar()
{
    //trivial toolBar set up
    mCameraIncrementButton = new QPushButton("++", nullptr);
    mCameraDecrementButton = new QPushButton("--", nullptr);
    mCameraIncrementButton->setFixedSize(40,20);
    mCameraDecrementButton->setFixedSize(40,20);
    ui->toolBar_FirstRow->addWidget(mCameraIncrementButton);
    ui->toolBar_FirstRow->addWidget(mCameraDecrementButton);
    ui->toolBar_FirstRow->addSeparator();
    ui->toolBar_FirstRow->addAction(ui->actionCube);
    ui->toolBar_FirstRow->addAction(ui->actionCone);
    ui->toolBar_FirstRow->addAction(ui->actionCylinder);
    ui->toolBar_FirstRow->addAction(ui->actionSphere);
    ui->toolBar_FirstRow->addAction(ui->actionDisk);
    ui->toolBar_FirstRow->addAction(ui->actionHexahedron);
    ui->toolBar_FirstRow->addAction(ui->actionTetrahedron);
    ui->toolBar_FirstRow->addAction(ui->actionPyramid);
    ui->toolBar_FirstRow->addAction(ui->actionArrow);
    ui->toolBar_FirstRow->addSeparator();


    mCustomizedModelButton = new QPushButton("Click", nullptr);
    mCustomizedModelButton->setFixedSize(50,30);
    auto QLabel1= new QLabel("Customize Model: ");
    QFont Font1= QLabel1->font();
    Font1.setBold(true);
    Font1.setPointSize(7);
    QLabel1->setFont(Font1);
    ui->toolBar_FirstRow->addWidget(QLabel1);
    ui->toolBar_FirstRow->addWidget(mCustomizedModelButton);

    mViewModeComboBox = new QComboBox();
    mViewModeComboBox->setFixedSize(140, 20);
    ui->toolBar_SecondRow->addWidget(mViewModeComboBox);
    mViewModeComboBox->addItem("Surface");
    mViewModeComboBox->addItem("Wireframe");
    mViewModeComboBox->addItem("Points");
    mViewModeComboBox->addItem("Surface With Edges");
    mViewModeComboBox->addItem("Cells");

    auto* Palette = new QToolButton();
    Palette->setIcon(QIcon(":/Icons/pqPalette.svg"));
    auto* ColorMenu = new QMenu(this);
    mModelColorAction = new QAction(this);
    mBackgroundColorAction = new QAction(this);
    mModelColorAction->setText("Model Color");
    mBackgroundColorAction->setText("Background Color");
    ColorMenu->addAction(mModelColorAction);
    ColorMenu->addAction(mBackgroundColorAction);
    Palette->setMenu(ColorMenu);
    Palette->setPopupMode(QToolButton::InstantPopup);
    ui->toolBar_SecondRow->addWidget(Palette);

    ui->toolBar_SecondRow->addSeparator();
    auto QLabel2= new QLabel("Current Model:");
    QFont Font2= QLabel2->font();
    Font2.setBold(true);
    Font2.setPointSize(7);
    QLabel2->setFont(Font2);
    ui->toolBar_SecondRow->addWidget(QLabel2);
    mCurrentModelEdit = new QLineEdit(this);
    mCurrentModelEdit->setReadOnly(true);
    mCurrentModelEdit->setFixedSize(160, 25);
    ui->toolBar_SecondRow->addWidget(mCurrentModelEdit);


    ui->toolBar_SecondRow->addSeparator();
    auto QLabel3= new QLabel("Opacity:");
    QLabel3->setFont(Font2);
    ui->toolBar_SecondRow->addWidget(QLabel3);
    mOpacitySlider = new QSlider(Qt::Horizontal);
    mOpacitySlider->setFixedSize(170,15);
    ui->toolBar_SecondRow->addWidget(mOpacitySlider);
    ui->toolBar_SecondRow->addSeparator();


    mBackfaceCullingCheckbox = new QCheckBox("Backface Culling");
    mBackfaceCullingCheckbox->setFixedSize(150,20);
    mBackfaceCullingCheckbox->setFont(Font2);
    ui->toolBar_SecondRow->addWidget(mBackfaceCullingCheckbox);


    ui->toolBar_SecondRow->addSeparator();
    mFrontfaceCullingCheckbox= new QCheckBox("Frontface Culling");
    mFrontfaceCullingCheckbox->setFixedSize(150,20);
    mFrontfaceCullingCheckbox->setFont(Font2);
    ui->toolBar_SecondRow->addWidget(mFrontfaceCullingCheckbox);

    ui->toolBar_SecondRow->addSeparator();
    mAxesGridCheckbox = new QCheckBox("Axes Grid");
    mAxesGridCheckbox->setFixedSize(100,20);
    mAxesGridCheckbox->setFont(Font2);
    ui->toolBar_ThirdRow->addWidget(mAxesGridCheckbox);


    mOrientationAxesCheckbox= new QCheckBox("Orientation Axes visibility");
    mOrientationAxesCheckbox->setCheckState(Qt::Checked);
    mOrientationAxesCheckbox->setFixedSize(120,20);
    mOrientationAxesCheckbox->setFont(Font2);
    ui->toolBar_SecondRow->addWidget(mOrientationAxesCheckbox);

    ui->toolBar_ThirdRow->addSeparator();
    mvtkImplicitPlaneWidget2Checkbox= new QCheckBox("Enable Clipping Plane Widget");
    mvtkImplicitPlaneWidget2Checkbox->setFixedSize(200,30);
    mvtkImplicitPlaneWidget2Checkbox->setFont(Font2);
    ui->toolBar_ThirdRow->addWidget(mvtkImplicitPlaneWidget2Checkbox);

    ui->toolBar_ThirdRow->addSeparator();
    mBoxWidgetcCheckbox= new QCheckBox("Enable Box Widget");
    mBoxWidgetcCheckbox->setFixedSize(140,30);
    mBoxWidgetcCheckbox->setFont(Font2);
    ui->toolBar_ThirdRow->addWidget(mBoxWidgetcCheckbox);
    ui->toolBar_ThirdRow->addSeparator();


    auto QLabel4= new QLabel("Specular Lighting:");
    QLabel4->setFont(Font2);
    ui->toolBar_ThirdRow->addWidget(QLabel4);
    mSpecularLightingSlider = new QSlider(Qt::Horizontal);
    mSpecularLightingSlider->setFixedSize(140, 15);
    ui->toolBar_ThirdRow->addWidget(mSpecularLightingSlider);
    ui->toolBar_ThirdRow->addSeparator();



    auto QLabel5 = new QLabel("Diffuse Lighting:");
    QLabel5->setFont(Font2);
    ui->toolBar_ThirdRow->addWidget(QLabel5);
    mDiffuseLightingSlier = new QSlider(Qt::Horizontal);
    mDiffuseLightingSlier->setFixedSize(140, 15);
    ui->toolBar_ThirdRow->addWidget(mDiffuseLightingSlier);
    ui->toolBar_ThirdRow->addSeparator();


    auto QLabel6 = new QLabel("Ambient Lighting:");
    QLabel5->setFont(Font2);
    ui->toolBar_ThirdRow->addWidget(QLabel6);
    mAmbientLightingSlider = new QSlider(Qt::Horizontal);
    mAmbientLightingSlider->setFixedSize(140, 15);
    ui->toolBar_ThirdRow->addWidget(mAmbientLightingSlider);




}


void MainWindow::SetUp_Menubar()
{
    //trivial menuBar set up
    auto* SourceGroup = new QActionGroup(this);
    SourceGroup->setExclusionPolicy(QActionGroup::ExclusionPolicy::ExclusiveOptional);
    SourceGroup->addAction(ui->actionCube);
    SourceGroup->addAction(ui->actionSphere);
    SourceGroup->addAction(ui->actionCylinder);
    SourceGroup->addAction(ui->actionCone);
    SourceGroup->addAction(ui->actionDisk);
    SourceGroup->addAction(ui->actionLine);
    SourceGroup->addAction(ui->actionHexahedron);
    SourceGroup->addAction(ui->actionPyramid);
    SourceGroup->addAction(ui->actionTetrahedron);

    auto* ViewGroup = new QActionGroup(this);
    ViewGroup->setExclusionPolicy(QActionGroup::ExclusionPolicy::ExclusiveOptional);
    ViewGroup->addAction(ui->actionPositiveX);
    ViewGroup->addAction(ui->actionNegativeX);
    ViewGroup->addAction(ui->actionPositiveY);
    ViewGroup->addAction(ui->actionNegaitiveY);
    ViewGroup->addAction(ui->actionPositiveZ);
    ViewGroup->addAction(ui->actionPositiveZ);
    ViewGroup->addAction(ui->actionRotate90degCW);
    ViewGroup->addAction(ui->actionRotate90degCCW);
    ViewGroup->addAction(ui->ActionResetCamera);

}

void MainWindow::SetUp_MainWindow()
{
    //MainWindow set up
    this->setFixedSize(1200, 850);
    this->setWindowIcon(QIcon(":/Icons/48.png"));

}


void MainWindow::Init_OpenGLWindow()
{

    // init RendererWindow
    ui->openGLWidget->SetRenderWindow(Render_Window.Get_RenderWindow());
    ui->openGLWidget->GetRenderWindow()->AddRenderer(Render_Window.Get_Renderer());


    // init Renderer
    auto color= vtkSmartPointer<vtkNamedColors>::New();
    Render_Window.Get_Renderer()->SetActiveCamera(Active_Camera.Get_Camera());
    Render_Window.Get_Renderer()->SetBackground(color->GetColor3d("Black").GetData());
    Render_Window.Init_Axes_Actor();


}



void MainWindow::Model_Statistic_Calculation(const QString& ModelName)
{
    //extract statistic information from a model
    ui->lcdNumber_Cells->setMode(QLCDNumber::Dec);
    ui->lcdNumber_Points->setMode(QLCDNumber::Dec);
    int  NumOfCells = Data_Inventory.Get_Value_From_PolyDataSet(ModelName)->GetNumberOfCells();
    int NumOfPoints = Data_Inventory.Get_Value_From_PolyDataSet(ModelName)->GetNumberOfPoints();
    ui->lcdNumber_Cells->display(NumOfCells);
    ui->lcdNumber_Points->display(NumOfPoints);
    auto Center =Data_Inventory.Get_Value_From_PolyDataSet(ModelName)->GetCenter();
    ui->Center_X->setText(QString::number(Center[0]));
    ui->Center_Y->setText(QString::number(Center[1]));
    ui->Center_Z->setText(QString::number(Center[2]));
    auto Mass = vtkSmartPointer<vtkMassProperties>::New();
    auto Triangulate = vtkSmartPointer<vtkTriangleFilter>::New();
    Triangulate->SetInputData(Data_Inventory.Get_Value_From_PolyDataSet(ModelName));
    Mass->SetInputConnection(Triangulate->GetOutputPort());
    ui->lineEdit_Mass->setText(QString::number(Mass->GetVolume()));


}


void MainWindow::init_CellDisplay_Dialog()
{   //init the cellSelection Dialog
    if(!this->mTreeWidgetParentItems.isEmpty()) {

        mCellDisplayDialog.setWindowModality(Qt::ApplicationModal);

        QVector<QString> ModelLists;
        auto i = this->mTreeWidgetParentItems.constBegin();
        while (i != this->mTreeWidgetParentItems.constEnd()) {
            ModelLists.push_back(i.key());
            ++i;
        }

        mCellDisplayDialog.Set_Model_Available(ModelLists);
        mCellDisplayDialog.show();
    }
    else{
        QMessageBox::information(nullptr,"Infor","No Source found !");
    }
}

void MainWindow::init_Customize_Model_Dialog() {
    //init the customizedCell Dialog
    mCustomizedModelDialog.setWindowModality(Qt::ApplicationModal);
    mCustomizedModelDialog.show();

}

void MainWindow::Reset_Display_Widgets() {
    //reset display edit and lcd
    this->mCurrentModelEdit->setText("");
    ui->lcdNumber_Cells->display(0);
    ui->lcdNumber_Points->display(0);
    ui->Center_Z->setText("");
    ui->Center_Y->setText("");
    ui->Center_X->setText("");
    ui->lineEdit_Mass->setText("");
}






