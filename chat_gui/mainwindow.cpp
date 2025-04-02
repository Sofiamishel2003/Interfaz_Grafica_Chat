#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtConcurrent>
#include <QMetaObject>
#include <QDebug>
#include "client.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
    {
        ui->setupUi(this); //
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onConnectClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateUI(bool success) {
    if (success) {
        ui->label_8->setText("Connected!");
    } else {
        ui->label_8->setText("Connection failed.");
    }
}

void MainWindow::onConnectClicked() {

    QString ip = ui->lineEdit->text(); 
    QString port_str = ui->lineEdit_2->text();
    QString username = ui->lineEdit_3->text();


    std::string server_ip = ip.toStdString();
    std::string name = username.toStdString();
    bool ok;
    int port_n = port_str.toInt(&ok); 
    if (!ok || port_n <= 0) {
        // If the conversion failed or the port is invalid, handle the error
        qDebug() << "Invalid port!";
        return;
    }
    QtConcurrent::run([=]() {
        qDebug() << "Connecting to server...";
        int sock = connect_socket(port_n, server_ip.c_str(), name.c_str());

        // Use QMetaObject::invokeMethod to update UI safely
        if (sock >= 0) {
            QMetaObject::invokeMethod(this, "updateUI", Qt::QueuedConnection, Q_ARG(bool, true));
        } else {
            QMetaObject::invokeMethod(this, "updateUI", Qt::QueuedConnection, Q_ARG(bool, false));
        }
    });
}

