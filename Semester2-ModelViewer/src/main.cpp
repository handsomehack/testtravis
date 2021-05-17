#include <QtWidgets/QApplication>
#include <MainWindow.h>
#include <QSurfaceFormat>
#include <QVTKOpenGLWidget.h>
#include <vector3d.h>
#include <material.h>



//Implmentation of overloading the << operator to display the vector
ostream& operator<<(ostream& os, vector3D& v)
{

    return os << "v " << v.Index << " " << v.X << " " << v.Y << " " << v.Z; // display the result in [x,y,z] format
}

ostream& operator<<(ostream& os, Material& m)
{

    os << "m " << m.ID << " " << m.Density << " " << m.Colour << " " << m.Name;
    return os;
}



istream& operator>>(istream& is, vector3D& v) {

    is >> v.Index >> v.X >> v.Y >> v.Z;
    return is;
}

istream& operator>>(istream& is, Material& m) {

    is >> m.ID >> m.Density >> m.Colour >> m.Name;
    return is;
}


int main(int argc, char *argv[]) {


    // needed to ensure appropriate OpenGL context is created for VTK rendering.
    QSurfaceFormat::setDefaultFormat( QVTKOpenGLWidget::defaultFormat() );


	QApplication app(argc, argv);

    MainWindow window;

    window.show();

	return app.exec();

}