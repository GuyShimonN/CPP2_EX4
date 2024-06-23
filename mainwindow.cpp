#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "complex.hpp"
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <functional>
#include <QScreen>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    std::cout << "Setting up UI..." << std::endl;
    ui->setupUi(this);
    std::cout << "UI setup complete." << std::endl;

    std::cout << "Setting up custom UI..." << std::endl;
    setupUI();
    std::cout << "Custom UI setup complete." << std::endl;

    std::cout << "Setting up tree..." << std::endl;
    setupTree();
    std::cout << "Tree setup complete." << std::endl;

    // Ensure the window is a reasonable size
    resize(800, 600);

    // Center the window on the screen
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);

    // Ensure the window is visible
    show();
    raise();
    activateWindow();

    std::cout << "MainWindow construction complete. Window should be visible." << std::endl;
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

    contentLayout->addWidget(graphicsView, 3);
    contentLayout->addWidget(textOutput, 1);

    mainLayout->addLayout(contentLayout);
}

void MainWindow::setupTree()
{
    std::cout << "Starting setupTree()..." << std::endl;
    QApplication::processEvents();

    std::cout << "Creating scene..." << std::endl;
    QGraphicsScene *scene = new QGraphicsScene(this);
    if (!scene) {
        std::cerr << "Failed to create QGraphicsScene!" << std::endl;
        return;
    }
    scene->setSceneRect(0, 0, 2400, 800);
    std::cout << "Scene created successfully." << std::endl;
    QApplication::processEvents();

    try {
        std::cout << "Displaying Double Tree..." << std::endl;
        displayDoubleTree(scene);
        std::cout << "Double Tree displayed." << std::endl;
        QApplication::processEvents();

        std::cout << "Displaying Int Tree..." << std::endl;
        displayIntTree(scene);
        std::cout << "Int Tree displayed." << std::endl;
        QApplication::processEvents();

        std::cout << "Displaying Complex Tree..." << std::endl;
        displayComplexTree(scene);
        std::cout << "Complex Tree displayed." << std::endl;
        QApplication::processEvents();

        std::cout << "Displaying String Tree..." << std::endl;
        displayStringTree(scene);
        std::cout << "String Tree displayed." << std::endl;
        QApplication::processEvents();
    } catch (const std::exception& e) {
        std::cerr << "Exception caught while displaying trees: " << e.what() << std::endl;
    }

    std::cout << "Setting scene to graphicsView..." << std::endl;
    graphicsView->setScene(scene);
    std::cout << "Scene set to graphicsView." << std::endl;
    QApplication::processEvents();

    std::cout << "Fitting scene in view..." << std::endl;
    graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    std::cout << "Scene fitted in view." << std::endl;
    QApplication::processEvents();

    std::cout << "Tree setup complete." << std::endl;
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
            } else if constexpr (std::is_same_v<T, std::string>) {
                output += QString::fromStdString(it->value) + " ";
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
    tree.drawTree(scene, 0);
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
    intTree.drawTree(scene, 600);
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
    complexTree.drawTree(scene, 1200);
    displayTreeTraversal(complexTree, scene);
}

void MainWindow::displayStringTree(QGraphicsScene *scene)
{
    ariel::Tree<std::string> stringTree;
    ariel::Node<std::string>* root = new ariel::Node<std::string>("Root");
    stringTree.add_root(root);

    // Level 1
    ariel::Node<std::string>* child1 = new ariel::Node<std::string>("Child1");
    ariel::Node<std::string>* child2 = new ariel::Node<std::string>("Child2");
    stringTree.add_sub_node(root, child1);
    stringTree.add_sub_node(root, child2);

    // Level 2
    ariel::Node<std::string>* grandchild1 = new ariel::Node<std::string>("GrandChild1");
    ariel::Node<std::string>* grandchild2 = new ariel::Node<std::string>("GrandChild2");
    ariel::Node<std::string>* grandchild3 = new ariel::Node<std::string>("GrandChild3");
    ariel::Node<std::string>* grandchild4 = new ariel::Node<std::string>("GrandChild4");
    stringTree.add_sub_node(child1, grandchild1);
    stringTree.add_sub_node(child1, grandchild2);
    stringTree.add_sub_node(child2, grandchild3);
    stringTree.add_sub_node(child2, grandchild4);

    // Level 3
    ariel::Node<std::string>* greatgrandchild1 = new ariel::Node<std::string>("GreatGrandChild1");
    ariel::Node<std::string>* greatgrandchild2 = new ariel::Node<std::string>("GreatGrandChild2");
    stringTree.add_sub_node(grandchild1, greatgrandchild1);
    stringTree.add_sub_node(grandchild1, greatgrandchild2);

    textOutput->append("\nString Tree:");
    stringTree.drawTree(scene, 1800);
    displayTreeTraversal(stringTree, scene);
}