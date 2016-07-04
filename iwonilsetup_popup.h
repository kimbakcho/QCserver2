#ifndef IWONILSETUP_POPUP_H
#define IWONILSETUP_POPUP_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
namespace Ui {
class iwonilsetup_popup;
}

class iwonilsetup_popup : public QDialog
{
    Q_OBJECT

public:
    explicit iwonilsetup_popup(QString machinename,QWidget *parent = 0);
    QSqlDatabase remotedb;
    QString machinename;
    ~iwonilsetup_popup();

private slots:
    void on_oliselectbox_currentIndexChanged(const QString &arg1);

    void on_hoperselectbox_currentIndexChanged(const QString &arg1);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::iwonilsetup_popup *ui;
};

#endif // IWONILSETUP_POPUP_H
