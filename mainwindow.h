#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void ReceiveData();
    void tellMeMore();
    void reconnectTo();

    void r1();
    void r2();
    void off();
    void on();
private:
    Ui::MainWindow *ui;
    QTcpServer *Server;
    QTcpSocket *socket;
    bool getNext=true;
    QByteArray status;
    QMap <QString,QString> toLabel;
};
#endif // MAINWINDOW_H
