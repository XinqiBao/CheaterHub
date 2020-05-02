#include "cfg.h"
#include <QSettings>

Cfg::Cfg(QString filename):
    filename(filename),
    setting(filename, QSettings::IniFormat)
{
    setting.beginGroup("wordscapes");
    if(!setting.childKeys().contains("ip"))
        setting.setValue("ip", "127.0.0.1");
    if(!setting.childKeys().contains("port"))
        setting.setValue("port", 2020);
    wordscapes_ip = setting.value("ip").toString();
    wordscapes_port = setting.value("port").toInt();
    setting.endGroup();
}

void Cfg::save_config()
{
    setting.beginGroup("wordscapes");
    setting.setValue("ip", wordscapes_ip);
    setting.setValue("port", wordscapes_port);
    setting.endGroup();
}
