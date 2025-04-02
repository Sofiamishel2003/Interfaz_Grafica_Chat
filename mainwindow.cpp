#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "newwindow.h"  // Incluir la nueva ventana

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // Crear la nueva ventana y mostrarla
    NewWindow *newWindow = new NewWindow();  // Crear la nueva ventana
    newWindow->show();  // Mostrar la nueva ventana
    this->close();  // Cerrar la ventana principal
}

