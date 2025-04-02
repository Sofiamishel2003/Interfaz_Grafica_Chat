#ifndef NEWWINDOW_H
#define NEWWINDOW_H

#include <QWidget>

class NewWindow : public QWidget
{
    Q_OBJECT

public:
    explicit NewWindow(QWidget *parent = nullptr);
    ~NewWindow();

private:
         // Aquí puedes declarar elementos adicionales si es necesario
};

#endif // NEWWINDOW_H

