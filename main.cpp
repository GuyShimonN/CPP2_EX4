#include <QApplication>
#include "mainwindow.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
//
//cd /home/guy/CLionProjects/CPP_EX4
//        rm -rf cmake-build-debug
//        mkdir cmake-build-debug
//        cd cmake-build-debug
//        cmake -G Ninja ..
//ninja

//
//cd /home/guy/CLionProjects/CPP_EX4/cmake-build-debug
//        ninja
//./TreeVisualization
