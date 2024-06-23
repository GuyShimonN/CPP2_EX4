#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "complex.hpp"
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <functional>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupUI();
    setupTree();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);
    contentLayout = new QHBoxLayout();

    graphicsView = new QGraphicsView(this);
    textOutput = new QTextEdit(this);
    textOutput->setReadOnly(true);

    contentLayout->addWidget(graphicsView, 2);  // Give more space to the graph
    contentLayout->addWidget(textOutput, 1);

    mainLayout->addLayout(contentLayout);
}

void MainWindow::setupTree()
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 600, 400);  // Adjust size as needed

    displayDoubleTree(scene);
    displayIntTree(scene);
    displayComplexTree(scene);

    graphicsView->setScene(scene);
    graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

template<typename T, int K>
void MainWindow::displayTreeTraversal(const ariel::Tree<T, K>& tree, QGraphicsScene *scene)
{
    QString output;

    auto appendTraversal = [&](const QString& name, auto begin, auto end) {
        output += name + ": ";
        for (auto it = begin; it != end; ++it) {
            if constexpr (std::is_same_v<T, ariel::Complex>) {
                output += QString::fromStdString(it->value.to_string()) + " ";
            } else {
                output += QString::number(it->value) + " ";
            }
        }
        output += "\n";
    };

    appendTraversal("Pre-order", tree.begin_pre_order(), tree.end_pre_order());
    appendTraversal("Post-order", tree.begin_post_order(), tree.end_post_order());
    appendTraversal("In-order", tree.begin_in_order(), tree.end_in_order());
    appendTraversal("BFS", tree.begin_bfs(), tree.end_bfs());
    appendTraversal("DFS", tree.begin_dfs(), tree.end_dfs());

    textOutput->append(output);
}

void MainWindow::displayDoubleTree(QGraphicsScene *scene)
{
    ariel::Tree<double, 2> tree;
    ariel::Node<double>* root1 = new ariel::Node<double>(1.1);
    tree.add_root(root1);
    ariel::Node<double>* n1 = new ariel::Node<double>(1.2);
    ariel::Node<double>* n2 = new ariel::Node<double>(1.3);
    ariel::Node<double>* n4 = new ariel::Node<double>(1.5);
    ariel::Node<double>* n5 = new ariel::Node<double>(1.6);
    tree.add_sub_node(root1, n1);
    tree.add_sub_node(root1, n2);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n1, n5);

    textOutput->append("Double Tree:");
    tree.drawTree(scene);
    displayTreeTraversal(tree, scene);
}

void MainWindow::displayIntTree(QGraphicsScene *scene)
{
    ariel::Tree<int> intTree;
    ariel::Node<int>* root = new ariel::Node<int>(1);
    intTree.add_root(root);

    ariel::Node<int>* child1 = new ariel::Node<int>(2);
    ariel::Node<int>* child2 = new ariel::Node<int>(3);
    ariel::Node<int>* child3 = new ariel::Node<int>(4);
    ariel::Node<int>* child4 = new ariel::Node<int>(5);
    ariel::Node<int>* child5 = new ariel::Node<int>(6);
    intTree.add_sub_node(root, child1);
    intTree.add_sub_node(root, child2);
    intTree.add_sub_node(child1, child3);
    intTree.add_sub_node(child1, child4);
    intTree.add_sub_node(child2, child5);

    textOutput->append("\nInteger Tree:");
    intTree.drawTree(scene);
    displayTreeTraversal(intTree, scene);
}

void MainWindow::displayComplexTree(QGraphicsScene *scene)
{
    ariel::Tree<ariel::Complex> complexTree;
    ariel::Node<ariel::Complex>* complexRoot = new ariel::Node<ariel::Complex>(ariel::Complex(1, 2));
    complexTree.add_root(complexRoot);

    ariel::Node<ariel::Complex>* complexChild1 = new ariel::Node<ariel::Complex>(ariel::Complex(3, 4));
    ariel::Node<ariel::Complex>* complexChild2 = new ariel::Node<ariel::Complex>(ariel::Complex(5, 6));
    complexTree.add_sub_node(complexRoot, complexChild1);
    complexTree.add_sub_node(complexRoot, complexChild2);

    textOutput->append("\nComplex Tree:");
    complexTree.drawTree(scene);
    displayTreeTraversal(complexTree, scene);
}