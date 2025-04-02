#ifndef NEWWINDOW2_H
#define NEWWINDOW2_H

#include <QWidget>  // Necesario para que NewWindow herede de QWidget

QT_BEGIN_NAMESPACE
namespace Ui {
class NewWindow;  // Declaración de la clase UI correspondiente a NewWindow
}
QT_END_NAMESPACE

class NewWindow : public QWidget
{
    Q_OBJECT

public:
    explicit NewWindow(QWidget *parent = nullptr);  // Constructor
    ~NewWindow();  // Destructor

private:
    Ui::NewWindow *ui;  // Puntero al objeto de la UI de NewWindow
};

#endif // NEWWINDOW2_H


