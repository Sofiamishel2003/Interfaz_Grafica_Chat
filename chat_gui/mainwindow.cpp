#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtConcurrent>
#include <QMetaObject>
#include <QDebug>
#include "client.h"
#include <cstdint> 

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
    {
        ui->setupUi(this); //
    
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onConnectClicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::onListUsers);
        // Mandar mensaje
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::onSendMessage);
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &MainWindow::onChangeStatus);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateUI(bool success) {
    if (success) {
        ui->label_8->setText("Connected!");
        ui->label_8->setStyleSheet("color: green;");
    } else {
        ui->label_8->setText("Connection failed.");
        ui->label_8->setStyleSheet("color: red;");
    }
}

void MainWindow::onSendMessage(){
    QString mssg = ui->lineEdit_4->text();
    QString dest = ui->lineEdit_6->text();
    send_message(socket_fd, username.c_str(),dest.toStdString().c_str(), mssg.toStdString().c_str());
}

void MainWindow::onChangeStatus(){
    QString selected_status = ui->comboBox->currentText();
    int new_stat = -1;
    if (selected_status == "Activo") {
        new_stat = 1;
    } else if (selected_status == "Inactivo") {
        new_stat = 0;
    }
    qDebug() << "Staus: " << new_stat ;
    if (new_stat!=-1){
        if (new_stat!= user_status){
            user_status = new_stat;
            change_status(socket_fd, username.c_str(), user_status);
        }
    }
}


void MainWindow::onListUsers(){
    uint8_t frame[1024] = {0};
    list_users(socket_fd, frame);
    for (int i = 0; i < 1024; ++i) {
        qDebug() << "Byte" << i << ": " << frame[i];
    }
}

void MainWindow::onConnectClicked() {
    QString port_str = ui->lineEdit_2->text();


    server_ip = ui->lineEdit->text().toStdString();
    username = ui->lineEdit_3->text().toStdString();
    bool ok;
    port = port_str.toInt(&ok); 
    if (!ok || port <= 0) {
        // If the conversion failed or the port is invalid, handle the error
        qDebug() << "Invalid port!";
        return;
    }
    QtConcurrent::run([=]() {
        qDebug() << "Connecting to server...";
        int sock = connect_socket(port, server_ip.c_str(), username.c_str());
        socket_fd = sock;

        // Use QMetaObject::invokeMethod to update UI safely
        if (sock >= 0) {
            QMetaObject::invokeMethod(this, "updateUI", Qt::QueuedConnection, Q_ARG(bool, true));
            user_status = 1;
        } else {
            QMetaObject::invokeMethod(this, "updateUI", Qt::QueuedConnection, Q_ARG(bool, false));
        }
    });
}

