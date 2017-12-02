#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->status = "0";

    this->toLabel.insert("0","Status: Desligados");
    this->toLabel.insert("1","Status: Relay 1 ligado");
    this->toLabel.insert("2","Status: Relay 2 ligado");
    this->toLabel.insert("3","Status: Ligados");

    this->Server = new QTcpServer(this);
    this->socket = new QTcpSocket(this);

    this->reconnectTo();

    connect(Server, SIGNAL(newConnection()), this, SLOT(ReceiveData()));
    connect(ui->pbR1,SIGNAL(clicked(bool)),this,SLOT(r1()));
    connect(ui->pbR2,SIGNAL(clicked(bool)),this,SLOT(r2()));
    connect(ui->pbR1R2,SIGNAL(clicked(bool)),this,SLOT(on()));
    connect(ui->pbOff,SIGNAL(clicked(bool)),this,SLOT(off()));
}

void MainWindow::r1()
{
    this->status = "1";
    ui->label->setText(this->toLabel[this->status]);
    //this->getNext = true;
}

void MainWindow::r2()
{
    this->status = "2";
    ui->label->setText(this->toLabel[this->status]);
    //this->getNext = true;
}

void MainWindow::off()
{
    this->status = "0";
    ui->label->setText(this->toLabel[this->status]);
    this->getNext = true;
}

void MainWindow::on()
{
    this->status = "3";
    ui->label->setText(this->toLabel[this->status]);
    this->getNext = true;
}

void MainWindow::tellMeMore()
{
    QByteArray data = socket->readAll();
    if (data.contains("sendMeCommand")){
        socket->write(this->status);
        this->socket->close();
        this->Server->close();
    }
}
void MainWindow::ReceiveData()
{
    if (this->getNext){
        this->socket = Server->nextPendingConnection();
        this->getNext = false;
        connect(socket,SIGNAL(readyRead()),this,SLOT(tellMeMore()));
        connect(socket,SIGNAL(disconnected()),this,SLOT(reconnectTo()));
    }
    if (!socket){
        qDebug() << "saindo em ReceiveData";
        return;
    }
}
void MainWindow::reconnectTo()
{
    this->socket->close();
    this->Server->close();
    this->getNext = true;
    QHostAddress add;
    add.setAddress("192.168.1.7");
    if(!Server->listen(add, 8888)) {
        return;
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
