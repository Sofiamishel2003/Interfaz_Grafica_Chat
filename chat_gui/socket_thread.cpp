#include <QThread>
#include <QObject>

class SocketThread : public QThread {
    Q_OBJECT
public:
    void run() override {
        connect_socket();  // Run the function in a separate thread
    }
};