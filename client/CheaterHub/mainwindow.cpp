#include "mainwindow.h"
#include "setting.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <thread>
#include <QSettings>
#include <QAction>
#include <QDialog>

MainWindow::MainWindow(Cfg& cfg, QWidget *parent)
    : QMainWindow(parent)
    , cfg(cfg)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket();

    //Disable tab switching for several controls
    ui->tabWidget->setFocusPolicy(Qt::NoFocus);
    ui->btn_socket->setFocusPolicy(Qt::NoFocus);
    ui->list_result->setFocusPolicy(Qt::NoFocus);

    connect(ui->actionConfig, &QAction::triggered, this, [=]()
    {
        Setting setting_form(this->cfg);
        setting_form.exec();
    });
    connect(ui->lineEdit_given, &QLineEdit::returnPressed, this, &MainWindow::select_lineEdit_search);
    connect(ui->lineEdit_search, &QLineEdit::returnPressed, ui->btn_socket, &QPushButton::click);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::on_socket_msg_receive);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->socket;
}

void MainWindow::on_btn_socket_clicked()
{
    socket->connectToHost(cfg.wordscapes_ip, cfg.wordscapes_port);
    QString msg(ui->lineEdit_given->text() + ";" + ui->lineEdit_search->text());
    socket->write(msg.toUtf8());
    qDebug() << "Msg send: " << msg;

    ui->list_result->clear();
    select_lineEdit_search();
}

void MainWindow::on_socket_msg_receive()
{
    QByteArray buffer = socket->readAll();
    ui->list_result->addItems(QString(buffer).split(';'));
    qDebug() << buffer;
}

void MainWindow::select_lineEdit_search()
{
    ui->lineEdit_search->setFocus();
    ui->lineEdit_search->selectAll();
}
