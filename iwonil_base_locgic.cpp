#include "iwonil_base_locgic.h"
#include "mslotitem.h"
#include <QSqlError>

iwonil_base_locgic::iwonil_base_locgic(QObject *parentmslot,QObject *parent) : QObject(parent)
{
    this->parentmslot = parentmslot;
    initflag=false;
    before_shotcount =-1;
    current_shotcount =-1;
}
bool iwonil_base_locgic::init(){
    mslotitem *parent_item = (mslotitem *)parentmslot; //부모 위젯
    datamap = new QMap<QString,iwonilvalue *>;
    ip = parent_item->ip->text();
    litedb = QSqlDatabase::database("localdb");
    QSqlQuery litequery1(litedb);
    litequery1.exec("select * from systemset;");
    litequery1.next();
    if(litequery1.value("remoteservertype").toString().compare("MYSQL")==0){
        iwonildb = QSqlDatabase::addDatabase("QMYSQL",parent_item->iptext);
        typeDB = MYSQL;
    }else if(litequery1.value("remoteservertype").toString().compare("ODBC")==0){
        iwonildb = QSqlDatabase::addDatabase("QODBC",parent_item->iptext);
        typeDB = ODBC;
    }
    iwonildb.setHostName(litequery1.value("remoteserverip").toString());
    iwonildb.setDatabaseName(litequery1.value("remoteserverdbname").toString());
    iwonildb.setPort(litequery1.value("remoteserverport").toInt());
    iwonildb.setUserName(litequery1.value("remoteserverusername").toString());
    iwonildb.setPassword(litequery1.value("remoteserveruserpassword").toString());

    if(!iwonildb.open()){
        qDebug()<<"iwonil DB not open";

    }else {
       qDebug()<<"iwonil DB open";
    }

    addrlist.append(mb_cycle_count);
    addrlist.append(mb_inj_time1);
    addrlist.append(mb_inj_time2);
    addrlist.append(mb_filling_time);
    addrlist.append(mb_cycle_time);
    addrlist.append(mb_inj_position);
    addrlist.append(mb_inj_pressure);
    addrlist.append(mb_suckback_position);
    addrlist.append(mb_cuthion_position);
    addrlist.append(mb_switch_over_position);
    addrlist.append(mb_switch_over_pressure);
    addrlist.append(mb_switch_over_speed);
    addrlist.append(mb_avg_inj_pre);
    addrlist.append(mb_avg_chg_pre);
    addrlist.append(mb_inj_speed);
    addrlist.append(mb_max_inj_pre);
    addrlist.append(mb_max_inj_spd);

    addrlist.append(mb_temp1);
    addrlist.append(mb_temp2);
    addrlist.append(mb_temp3);
    addrlist.append(mb_temp4);

    addrlist.append(mb_oiltemp1);
    addrlist.append(mb_oiltemp2);

    addrlist.append(mb_hopertemp1);
    addrlist.append(mb_hopertemp2);

    addrlist.append(mb_temp1set);
    addrlist.append(mb_temp2set);
    addrlist.append(mb_temp3set);
    addrlist.append(mb_temp4set);

    addrlist.append(mb_hopertempset1);
    addrlist.append(mb_hopertempset2);

    addrlist.append(mb_oiltempset1);
    addrlist.append(mb_oiltempset2);
                    
    addrlist.append(mb_moldtempreal1);
    addrlist.append(mb_moldtempreal2);
    addrlist.append(mb_moldtempreal3);
    addrlist.append(mb_moldtempreal4);
    addrlist.append(mb_moldtempreal5);
    addrlist.append(mb_moldtempreal6);
    addrlist.append(mb_moldtempreal7);
    addrlist.append(mb_moldtempreal8);
                  
    addrlist.append(mb_moldtempset1);
    addrlist.append(mb_moldtempset2);
    addrlist.append(mb_moldtempset3);
    addrlist.append(mb_moldtempset4);
    addrlist.append(mb_moldtempset5);
    addrlist.append(mb_moldtempset6);
    addrlist.append(mb_moldtempset7);
    addrlist.append(mb_moldtempset8);




    modbus_thread = new iwonil_modbus_thread(this);
    modbus_thread->start();
    initflag=true;
    return initflag;
}
void iwonil_base_locgic::loop(){
    waitcondition.wakeAll();
}

void iwonil_base_locgic::iwonil_base_loop(){
    mslotitem * parent_item = (mslotitem *)parentmslot; //부모 위젯
    QString mancine_name = parent_item->machinename->text();
    QSqlQuery mysqlquery1(iwonildb);
    int cycle_count =datamap->value(QString("%1").arg(mb_cycle_count))->value.toInt();
    double inj_time1 = datamap->value(QString("%1").arg(mb_inj_time1))->value.toDouble()/100.0;
    double inj_time2 = datamap->value(QString("%1").arg(mb_inj_time2))->value.toDouble()/100.0;
    double filling_time = datamap->value(QString("%1").arg(mb_filling_time))->value.toDouble()/100.0;
    double cycle_time = datamap->value(QString("%1").arg(mb_cycle_time))->value.toDouble()/100.0;
    double inj_position = datamap->value(QString("%1").arg(mb_inj_position))->value.toDouble()/10.0;
    double inj_pressure = datamap->value(QString("%1").arg(mb_inj_pressure))->value.toDouble()/10.0;
    double suckback_position = datamap->value(QString("%1").arg(mb_inj_pressure))->value.toDouble()/10.0;
    double cuthion_position =  datamap->value(QString("%1").arg(mb_cuthion_position))->value.toDouble()/10.0;
    double switch_over_position =  datamap->value(QString("%1").arg(mb_switch_over_position))->value.toDouble()/10.0;
    double switch_over_pressure = datamap->value(QString("%1").arg(mb_switch_over_pressure))->value.toDouble()/10.0;
    double switch_over_speed = datamap->value(QString("%1").arg(mb_switch_over_speed))->value.toDouble()/10.0;
    double avg_inj_pre = datamap->value(QString("%1").arg(mb_avg_inj_pre))->value.toDouble()/10.0;
    double avg_chg_pre = datamap->value(QString("%1").arg(mb_avg_chg_pre))->value.toDouble()/10.0;
    double inj_speed = datamap->value(QString("%1").arg(mb_inj_speed))->value.toDouble()/10.0;
    double max_inj_pre = datamap->value(QString("%1").arg(mb_max_inj_pre))->value.toDouble()/10.0;
    double max_inj_spd = datamap->value(QString("%1").arg(mb_max_inj_spd))->value.toDouble()/10.0;
    double temp1 = datamap->value(QString("%1").arg(mb_temp1))->value.toDouble();
    double temp2 = datamap->value(QString("%1").arg(mb_temp2))->value.toDouble();
    double temp3 = datamap->value(QString("%1").arg(mb_temp3))->value.toDouble();
    double temp4 = datamap->value(QString("%1").arg(mb_temp4))->value.toDouble();
    mysqlquery1.exec(QString("select iwoniloil,iwonilhoper from Systeminfo where machine_name = '%1'").arg(mancine_name));

    mysqlquery1.next();
    double oiltemp1 = datamap->value(QString("%1").arg(mb_oiltemp1))->value.toDouble();
    double oiltemp2 = datamap->value(QString("%1").arg(mb_oiltemp2))->value.toDouble();
    double oiltemp;
    if(mysqlquery1.value("iwoniloil").toInt() == 6){
        oiltemp = oiltemp2;
    }else if(mysqlquery1.value("iwoniloil").toInt() == 8){
        oiltemp = oiltemp1;
    }

    double hopertemp1 =  datamap->value(QString("%1").arg(mb_hopertemp1))->value.toDouble();
    double hopertemp2 =  datamap->value(QString("%1").arg(mb_hopertemp2))->value.toDouble();
    double hopertemp;
    if(mysqlquery1.value("iwonilhoper").toInt() == 5){
        hopertemp = hopertemp2;
    }else if(mysqlquery1.value("iwonilhoper").toInt() == 7){
        hopertemp = hopertemp1;
    }

    double temp1set = datamap->value(QString("%1").arg(mb_temp1set))->value.toDouble();
    double temp2set = datamap->value(QString("%1").arg(mb_temp2set))->value.toDouble();
    double temp3set = datamap->value(QString("%1").arg(mb_temp3set))->value.toDouble();
    double temp4set = datamap->value(QString("%1").arg(mb_temp4set))->value.toDouble();

    double hopertempset1 = datamap->value(QString("%1").arg(mb_hopertempset1))->value.toDouble();
    double hopertempset2 = datamap->value(QString("%1").arg(mb_hopertempset2))->value.toDouble();
    double hopertempset;

    if(mysqlquery1.value("iwonilhoper").toInt() == 5){
        hopertempset = hopertempset2;
    }else if(mysqlquery1.value("iwonilhoper").toInt() == 7){
        hopertempset = hopertempset1;
    }

    double oiltempset1 = datamap->value(QString("%1").arg(mb_oiltempset1))->value.toDouble();
    double oiltempset2 = datamap->value(QString("%1").arg(mb_oiltempset2))->value.toDouble();
    double oiltempset;

    if(mysqlquery1.value("iwoniloil").toInt() == 6){
        oiltempset = oiltempset2;
    }else if(mysqlquery1.value("iwoniloil").toInt() == 8){
        oiltempset = oiltempset1;
    }

    double moldtempreal1 = datamap->value(QString("%1").arg(mb_moldtempreal1))->value.toDouble();
    double moldtempreal2 = datamap->value(QString("%1").arg(mb_moldtempreal2))->value.toDouble();
    double moldtempreal3 = datamap->value(QString("%1").arg(mb_moldtempreal3))->value.toDouble();
    double moldtempreal4 = datamap->value(QString("%1").arg(mb_moldtempreal4))->value.toDouble();
    double moldtempreal5 = datamap->value(QString("%1").arg(mb_moldtempreal5))->value.toDouble();
    double moldtempreal6 = datamap->value(QString("%1").arg(mb_moldtempreal6))->value.toDouble();
    double moldtempreal7 = datamap->value(QString("%1").arg(mb_moldtempreal7))->value.toDouble();
    double moldtempreal8 = datamap->value(QString("%1").arg(mb_moldtempreal8))->value.toDouble();

    double mmoldtempset1 = datamap->value(QString("%1").arg(mb_moldtempset1))->value.toDouble();
    double mmoldtempset2 = datamap->value(QString("%1").arg(mb_moldtempset2))->value.toDouble();
    double mmoldtempset3 = datamap->value(QString("%1").arg(mb_moldtempset3))->value.toDouble();
    double mmoldtempset4 = datamap->value(QString("%1").arg(mb_moldtempset4))->value.toDouble();
    double mmoldtempset5 = datamap->value(QString("%1").arg(mb_moldtempset5))->value.toDouble();
    double mmoldtempset6 = datamap->value(QString("%1").arg(mb_moldtempset6))->value.toDouble();
    double mmoldtempset7 = datamap->value(QString("%1").arg(mb_moldtempset7))->value.toDouble();
    double mmoldtempset8 = datamap->value(QString("%1").arg(mb_moldtempset8))->value.toDouble();
    current_shotcount = cycle_count;
    if(before_shotcount<=0){
        before_shotcount = current_shotcount;
    }
    if(before_shotcount!=current_shotcount){
        before_shotcount=current_shotcount;
    if(typeDB == MYSQL){

    }else if(typeDB == ODBC){
        QString insertquery = QString("INSERT INTO iwonil_shot_data"
                                      "([machine_name]"
                                      ",[shot_date]"
                                      ",[shot_time]"
                                      ",[cycle_count]"
                                      ",[inj_time1]"
                                      ",[inj_time2]"
                                      ",[filling_time]"
                                      ",[cycle_time]"
                                      ",[inj_position]"
                                      ",[inj_pressure]"
                                      ",[suckback_position]"
                                      ",[cuthion_position]"
                                      ",[switch_over_position]"
                                      ",[switch_over_pressure]"
                                      ",[switch_over_speed]"
                                      ",[avg_inj_pre]"
                                      ",[avg_chg_pre]"
                                      ",[inj_speed]"
                                      ",[max_inj_pre]"
                                      ",[max_inj_spd]"
                                      ",[temp1]"
                                      ",[temp2]"
                                      ",[temp3]"
                                      ",[temp4]"
                                      ",[hopertemp]"
                                      ",[oiltemp]"
                                      ",[humidity]"
                                      ",[temp1set]"
                                      ",[temp2set]"
                                      ",[temp3set]"
                                      ",[temp4set]"
                                      ",[hopersettemp]"
                                      ",[oilsettemp]"
                                      ",[moldtemp_high]"
                                      ",[moldtemp_leftdown]"
                                      ",[moldtemp_rightdown]"
                                      ",[moldtempreal1]"
                                      ",[moldtempreal2]"
                                      ",[moldtempreal3]"
                                      ",[moldtempreal4]"
                                      ",[moldtempreal5]"
                                      ",[moldtempreal6]"
                                      ",[moldtempreal7]"
                                      ",[moldtempreal8]"
                                      ",[moldtempset1]"
                                      ",[moldtempset2]"
                                      ",[moldtempset3]"
                                      ",[moldtempset4]"
                                      ",[moldtempset5]"
                                      ",[moldtempset6]"
                                      ",[moldtempset7]"
                                      ",[moldtempset8])"
                                "VALUES("
                                      +QString("'%1'").arg(mancine_name)+","
                                      +"\'"+QDate::currentDate().toString("yyyy-MM-dd")+"\'"+","
                                      +"\'"+QTime::currentTime().toString("HH:mm:ss")+"\'"+","
                                      +QString("%1").arg(cycle_count)+","
                                      +QString("%1").arg(inj_time1)+","
                                      +QString("%1").arg(inj_time2)+","
                                      +QString("%1").arg(filling_time)+","
                                      +QString("%1").arg(cycle_time)+","
                                      +QString("%1").arg(inj_position)+","
                                      +QString("%1").arg(inj_pressure)+","
                                      +QString("%1").arg(suckback_position)+","
                                      +QString("%1").arg(cuthion_position)+","
                                      +QString("%1").arg(switch_over_position)+","
                                      +QString("%1").arg(switch_over_pressure)+","
                                      +QString("%1").arg(switch_over_speed)+","
                                      +QString("%1").arg(avg_inj_pre)+","
                                      +QString("%1").arg(avg_chg_pre)+","
                                      +QString("%1").arg(inj_speed)+","
                                      +QString("%1").arg(max_inj_pre)+","
                                      +QString("%1").arg(max_inj_spd)+","
                                      +QString("%1").arg(temp1)+","
                                      +QString("%1").arg(temp2)+","
                                      +QString("%1").arg(temp3)+","
                                      +QString("%1").arg(temp4)+","
                                      +QString("%1").arg(hopertemp)+","
                                      +QString("%1").arg(oiltemp)+","
                                      +QString("%1").arg("0")+","
                                      +QString("%1").arg(temp1set)+","
                                      +QString("%1").arg(temp2set)+","
                                      +QString("%1").arg(temp3set)+","
                                      +QString("%1").arg(temp4set)+","
                                      +QString("%1").arg(hopertempset)+","
                                      +QString("%1").arg(oiltempset)+","
                                      +QString("%1").arg("0")+","
                                      +QString("%1").arg("0")+","
                                      +QString("%1").arg("0")+","
                                      +QString("%1").arg(moldtempreal1)+","
                                      +QString("%1").arg(moldtempreal2)+","
                                      +QString("%1").arg(moldtempreal3)+","
                                      +QString("%1").arg(moldtempreal4)+","
                                      +QString("%1").arg(moldtempreal5)+","
                                      +QString("%1").arg(moldtempreal6)+","
                                      +QString("%1").arg(moldtempreal7)+","
                                      +QString("%1").arg(moldtempreal8)+","
                                      +QString("%1").arg(mmoldtempset1)+","
                                      +QString("%1").arg(mmoldtempset2)+","
                                      +QString("%1").arg(mmoldtempset3)+","
                                      +QString("%1").arg(mmoldtempset4)+","
                                      +QString("%1").arg(mmoldtempset5)+","
                                      +QString("%1").arg(mmoldtempset6)+","
                                      +QString("%1").arg(mmoldtempset7)+","
                                      +QString("%1").arg(mmoldtempset8)+")"
                                      );

        mysqlquery1.exec(insertquery);

        }
    }


}

void iwonil_base_locgic::slot_statue_update(bool statue){
    mslotitem *parent_item = (mslotitem *)parentmslot; //부모 위젯
    if(statue){
        parent_item->set_connectlabel_text("<img src=\":/icon/icon/play-button16.png\">  connect");
        parent_item->set_status_text("<img src=\":/icon/icon/play-button16.png\">  play");
    }else {
        parent_item->set_connectlabel_text("<img src=\":/icon/icon/light-bulb_red.png\">  disconnect");
        parent_item->set_status_text("<img src=\":/icon/icon/stop.png\">  STOP");
    }
}
