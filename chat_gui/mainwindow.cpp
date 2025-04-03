#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtConcurrent>
#include <QMetaObject>
#include <QDebug>
#include "client.h"
#include <cstdint> 
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
    {
        ui->setupUi(this); //
    
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onConnectClicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::onListUsers);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::onHelp);
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


void MainWindow::onHelp() {
    QMessageBox::information(this, "Ayuda del Chat OS", 
        "Ayuda del Chat OS\nBienvenido a Chat OS, una aplicación de mensajería en red donde puedes comunicarte en tiempo real con otros usuarios conectados al mismo servidor.\n"
"\n"
"   * Secciones y botones de la interfaz\n"
"   * Conexión:\n"
"Server IP: Dirección IP del servidor al que deseas conectarte.\n"
"\n"
"Puerto: Puerto en el que escucha el servidor.\n"
"\n"
"   * Usuario: Tu nombre de usuario.\n"
"Conectar: Intenta establecer conexión con el servidor usando los datos anteriores.\n"
"\n"
"   * Nota: No puedes conectarte con el mismo nombre de usuario que otro ya conectado. Si lo haces, la conexión será rechazada.\n"
"   * Configuración:\n"
"   * Status: Cambia tu estado actual. Las opciones disponibles son:\n"
"\n"
"   * Activo: Puedes recibir y enviar mensajes.\n"
"\n"
"   * Ocupado: Estás conectado, pero ocupado.\n"
"\n"
"   * Ausente: No estás disponible momentáneamente.\n"
"\n"
"Desconectado: Aparece como desconectado para los demás.\n"
"\n"
"Ayuda: Muestra esta ventana de ayuda.\n"
"\n"
"Chat:\n"
"Listar: Obtiene la lista actualizada de usuarios conectados y sus estados.\n"
"\n"
"Historial: Recupera los mensajes anteriores con el usuario seleccionado.\n"
"\n"
"Usuarios: Muestra la lista de usuarios disponibles.\n"
"\n"
"Chat: Área donde se muestran los mensajes enviados y recibidos.\n"
"\n"
"Campo de mensaje: Escribe tu mensaje aquí."
"\n"
"Enviar: Envía tu mensaje al usuario seleccionado o al chat general (~).\n"
"\n"
" El nombre del usuario seleccionado aparece en el desplegable al lado del botón \"Historial\". Si seleccionas ~, se envía al chat general.\n"
"\n"
" Buscar Usuario:\n"
"Campo de texto: Escribe el nombre del usuario que deseas buscar.\n"
"\n"
"Buscar: Muestra el estado actual de ese usuario.\n"
"\n"
"Resultado: Aquí aparece el estado del usuario buscado (por ejemplo: Activo, Ocupado... o que no existe).\n"
"\n"
" Consideraciones importantes:\n"
"No se permite más de una conexión simultánea con el mismo nombre de usuario.\n"
"\n"
"Si cierras la aplicación sin desconectarte correctamente, puedes reconectarte con el mismo nombre y recuperar tu sesión.\n"
"\n"
"Todos los mensajes se almacenan localmente mientras el chat esté activo. Puedes verlos con el botón Historial.\n"
"\n"
"La conexión debe ser establecida correctamente para que el chat funcione (debes ver Status conexión: Exitosa).\n"
"\n"
"El estado Desconectado no cierra la conexión: solo oculta tu actividad para otros usuarios.\n");
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

