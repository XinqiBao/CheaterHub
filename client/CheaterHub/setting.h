#ifndef SETTING_H
#define SETTING_H

#include "cfg.h"
#include <QDialog>

namespace Ui {
class Setting;
}

class Setting : public QDialog
{
    Q_OBJECT

public:
    explicit Setting(Cfg& cfg, QWidget *parent = nullptr);
    ~Setting();

private:
    Cfg& cfg;
    Ui::Setting *ui;

public slots:
    void update_setting();
};

#endif // SETTING_H
