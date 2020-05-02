#ifndef CFG_H
#define CFG_H

#include <QString>
#include <QSettings>

class Cfg
{
private:
    QString filename;
    QSettings setting;
public:
    Cfg(QString filename = "config");

    QString wordscapes_ip;
    int wordscapes_port;

    void save_config();
};

#endif // CFG_H
