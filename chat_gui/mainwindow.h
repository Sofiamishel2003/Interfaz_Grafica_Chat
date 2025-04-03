#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void updateUI(bool success);
    

private:
    Ui::MainWindow *ui;
    void onConnectClicked();
    void onListUsers();
    void onChangeStatus();
    void onSendMessage();
    std::string username;
    std::string server_ip;
    std::string chat_name;
    int port;
    int socket_fd;
    int user_status;
};

#endif //