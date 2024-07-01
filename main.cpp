#include <QApplication>
#include "mainwindow.hpp"
#include <iostream>
#include <QTimer>
#include <QApplication>
#include "mainwindow.hpp"
#include <QApplication>
#include <QDebug>
#include "mainwindow.hpp"

int main(int argc, char *argv[])
{
    qDebug() << "Starting application...";
    QApplication a(argc, argv);
    MainWindow w;
    qDebug() << "MainWindow created.";
    w.show();
    qDebug() << "MainWindow shown.";
    return a.exec();
}
//int main(int argc, char *argv[]) {
//    QApplication app(argc, argv);
//
//    std::cout << "Creating MainWindow..." << std::endl;
//    MainWindow mainWindow;
//    std::cout << "MainWindow created." << std::endl;
//
//    // Add a small delay
//    QTimer::singleShot(100, &mainWindow, &QWidget::show);
//
//    std::cout << "Entering event loop..." << std::endl;
//    return app.exec();
//}
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
