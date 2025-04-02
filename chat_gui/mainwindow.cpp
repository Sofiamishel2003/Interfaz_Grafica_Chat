#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtConcurrent>
#include <QMetaObject>
#include <QDebug>
#include "client.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onConnectClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onConnectClicked() {
    int port_n = 8000;
    std::string server_ip = "3.133.134.47";
    std::string name = "from_frontend";

    // Run in a separate thread
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

void MainWindow::updateUI(bool success) {
    if (success) {
        ui->label_8->setText("Connected!");
    } else {
        ui->label_8->setText("Connection failed.");
    }
}