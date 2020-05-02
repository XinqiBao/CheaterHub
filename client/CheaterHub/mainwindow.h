#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cfg.h"
#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Cfg& cfg, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Cfg& cfg;
    Ui::MainWindow *ui;
    QTcpSocket *socket;

private slots:
    void select_lineEdit_search();
    void on_btn_socket_clicked();
    void on_socket_msg_receive();
};
#endif // MAINWINDOW_H
