#include "iwonilsetup_popup.h"
#include "ui_iwonilsetup_popup.h"
#include <QSqlError>

iwonilsetup_popup::iwonilsetup_popup(QString machinename, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::iwonilsetup_popup)
{
    ui->setupUi(this);
    this->machinename = machinename;
    disconnect(ui->oliselectbox,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_oliselectbox_currentIndexChanged(QString)));
    disconnect(ui->hoperselectbox,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_hoperselectbox_currentIndexChanged(QString)));
    ui->oliselectbox->addItem("6");
    ui->oliselectbox->addItem("8");
    ui->hoperselectbox->addItem("5");
    ui->hoperselectbox->addItem("7");
    remotedb = QSqlDatabase::database("remotedb");
    QSqlQuery remotequery(remotedb);
    remotequery.exec(QString("select iwonilhoper,iwoniloil from Systeminfo where machine_name = '%1'").arg(machinename));
    remotequery.next();
    ui->oliselectbox->setCurrentText(remotequery.value("iwoniloil").toString());
    ui->hoperselectbox->setCurrentText(remotequery.value("iwonilhoper").toString());
    connect(ui->oliselectbox,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_oliselectbox_currentIndexChanged(QString)));
    connect(ui->hoperselectbox,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_hoperselectbox_currentIndexChanged(QString)));

}

iwonilsetup_popup::~iwonilsetup_popup()
{
    delete ui;
}

void iwonilsetup_popup::on_oliselectbox_currentIndexChanged(const QString &arg1)
{
     QSqlQuery remotequery(remotedb);
     remotequery.exec(QString("update Systeminfo set iwoniloil = %1 where machine_name = '%2'").arg(arg1).arg(machinename));


}

void iwonilsetup_popup::on_hoperselectbox_currentIndexChanged(const QString &arg1)
{
    QSqlQuery remotequery(remotedb);
    remotequery.exec(QString("update Systeminfo set iwonilhoper = %1 where machine_name = '%2'").arg(arg1).arg(machinename));

}

void iwonilsetup_popup::on_buttonBox_accepted()
{
    this->deleteLater();
}

void iwonilsetup_popup::on_buttonBox_rejected()
{
    this->deleteLater();
}
