#include "newwindow.h"
#include "./ui_newwindow.h"
NewWindow::NewWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewWindow)  // Inicialización de la UI de NewWindow
{
    ui->setupUi(this);  // Configura la UI en la ventana
}

NewWindow::~NewWindow()
{
    delete ui;  // Limpieza del objeto UI
}

