#include "setting.h"
#include "ui_setting.h"
#include <QString>
#include <QDebug>

Setting::Setting(Cfg& cfg, QWidget *parent) :
    QDialog(parent),
    cfg(cfg),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    ui->le_wordscapes_ip->setText(cfg.wordscapes_ip);
    ui->le_wordscapes_port->setText(QString::number(cfg.wordscapes_port));

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &Setting::update_setting);
}

Setting::~Setting()
{
    delete ui;
}

void Setting::update_setting()
{
    cfg.wordscapes_ip = ui->le_wordscapes_ip->text();
    cfg.wordscapes_port = ui->le_wordscapes_port->text().toInt();

    cfg.save_config();
}
