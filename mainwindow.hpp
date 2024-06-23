#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "tree.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsView *graphicsView;
    QTextEdit *textOutput;
    QVBoxLayout *mainLayout;
    QHBoxLayout *contentLayout;

    void setupUI();
    void setupTree();
    void displayDoubleTree(QGraphicsScene *scene);
    void displayIntTree(QGraphicsScene *scene);
    void displayComplexTree(QGraphicsScene *scene);
    void displayStringTree(QGraphicsScene *scene);

    template<typename T, int K>
    void displayTreeTraversal(const ariel::Tree<T, K>& tree, QGraphicsScene *scene);
};

#endif // MAINWINDOW_HPP