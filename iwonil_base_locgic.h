#ifndef IWONIL_BASE_LOCGIC_H
#define IWONIL_BASE_LOCGIC_H

#include <QObject>
#include <QMap>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkReply>
#if QT_VERSION < QT_VERSION_CHECK(5,6,0)
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>
#endif
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QWaitCondition>
#include <QMutex>
#include "iwonil_modbus_thread.h"
#include "modbus.h"

#define mb_cycle_count 20625
#define mb_inj_time1 20668
#define mb_inj_time2 20652
#define mb_filling_time 22306
#define mb_cycle_time 20665
#define mb_inj_position 21558
#define mb_inj_pressure 21562
#define mb_suckback_position 19658
#define mb_cuthion_position 22287
#define mb_switch_over_position 22301
#define mb_switch_over_pressure 22302
#define mb_switch_over_speed 22303
#define mb_avg_inj_pre 22284
#define mb_avg_chg_pre 22287
#define mb_inj_speed 22307
#define mb_max_inj_pre 22288
#define mb_max_inj_spd 22313
#define mb_temp1 45058
#define mb_temp2 45059
#define mb_temp3 45060
#define mb_temp4 45061

#define mb_oiltemp1 45065
#define mb_oiltemp2 45063

#define mb_hopertemp1 45064
#define mb_hopertemp2 45062

#define mb_temp1set 43023
#define mb_temp2set 43024
#define mb_temp3set 43025
#define mb_temp4set 43026

#define mb_hopertempset1 43029
#define mb_hopertempset2 43027

#define mb_oiltempset1 43030
#define mb_oiltempset2 43028
      
#define mb_moldtempreal1 36866
#define mb_moldtempreal2 36867
#define mb_moldtempreal3 36868
#define mb_moldtempreal4 36869
#define mb_moldtempreal5 36870
#define mb_moldtempreal6 36871
#define mb_moldtempreal7 36872
#define mb_moldtempreal8 36873
        
#define mb_moldtempset1 36831
#define mb_moldtempset2 36832
#define mb_moldtempset3 36833
#define mb_moldtempset4 36834
#define mb_moldtempset5 36835
#define mb_moldtempset6 36836
#define mb_moldtempset7 36837
#define mb_moldtempset8 36838


class iwonilvalue {
    public:
        QString name;
        QString value;
        iwonilvalue(){

        }
        iwonilvalue(QString name,QString value){
            this->name=name;
            this->value=value;
        }
};


class iwonil_base_locgic : public QObject
{
    Q_OBJECT
public:
    explicit iwonil_base_locgic(QObject *parentmslot,QObject *parent = 0);
    QObject *parentmslot;
    QMap<QString,iwonilvalue *> *datamap; //<name,value>
    bool initflag;
    bool init();
    void loop();
    QSqlDatabase remotedb;
    iwonil_modbus_thread *modbus_thread;
    QWaitCondition waitcondition;
    QMutex mutex;
    QString ip;
    QSqlDatabase iwonildb;
    QSqlDatabase litedb;
    QVector<int> addrlist;

     modbus_t *ctx;

     int typeDB;
     bool queryresult;
     int before_shotcount;
     int current_shotcount;
     void iwonil_base_loop();

signals:

public slots:
     void slot_statue_update(bool statue);
};

#endif // IWONIL_BASE_LOCGIC_H
