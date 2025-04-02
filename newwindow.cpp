#include "newwindow.h"
#include <QLabel>

NewWindow::NewWindow(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle("Nueva Ventana");
    setGeometry(100, 100, 400, 300);  // Ajustar la geometría de la ventana

    // Agregar contenido a la nueva ventana, como una etiqueta
    QLabel *label = new QLabel("¡Bienvenido a la nueva ventana!", this);
    label->move(100, 100);  // Establecer la posición de la etiqueta en la ventana
}

NewWindow::~NewWindow()
{
}
