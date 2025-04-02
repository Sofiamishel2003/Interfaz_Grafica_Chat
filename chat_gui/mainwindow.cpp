#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create a central widget
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Create Button
    button = new QPushButton("Click Me", this);
    mainLayout->addWidget(button);

    // Create GroupBox
    groupBox = new QGroupBox("Labels Box", this);
    groupLayout = new QVBoxLayout(groupBox);

    // Create labels
    for (int i = 0; i < 5; ++i) {
        labels[i] = new QLabel("Label " + QString::number(i + 1), this);
        groupLayout->addWidget(labels[i]);
    }

    groupBox->setLayout(groupLayout);
    mainLayout->addWidget(groupBox);
}

MainWindow::~MainWindow() {}
