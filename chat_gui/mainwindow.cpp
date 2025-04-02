#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this); // This is where the UI elements from the .ui file are initialized
}

MainWindow::~MainWindow()
{
    delete ui;
}
