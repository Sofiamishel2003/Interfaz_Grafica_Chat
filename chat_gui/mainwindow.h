#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QPushButton *button;
    QGroupBox *groupBox;
    QVBoxLayout *groupLayout;
    QLabel *labels[5]; // Array of labels
};

#endif // MAINWINDOW_H
