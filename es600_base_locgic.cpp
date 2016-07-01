#include "es600_base_locgic.h"
#include "mslotitem.h"
#include <QSqlError>

es600_base_locgic::es600_base_locgic(QObject *parentmslot,QObject *parent) : QObject(parent)
{
    this->parentmslot = parentmslot;
    initflag=false;
    before_shotcount =-1;
    current_shotcount =-1;
}
bool es600_base_locgic::init(){
     mslotitem *parent_item = (mslotitem *)parentmslot; //부모 위젯
     datamap = new QMap<QString,es600value *>;
     ip = parent_item->ip->text();
     litedb = QSqlDatabase::database("localdb");
     QSqlQuery litequery1(litedb);
     litequery1.exec("select * from systemset;");
     litequery1.next();
     if(litequery1.value("remoteservertype").toString().compare("MYSQL")==0){
         es600db = QSqlDatabase::addDatabase("QMYSQL",parent_item->iptext);
         typeDB = MYSQL;
     }else if(litequery1.value("remoteservertype").toString().compare("ODBC")==0){
         es600db = QSqlDatabase::addDatabase("QODBC",parent_item->iptext);
         typeDB = ODBC;
     }
     es600db.setHostName(litequery1.value("remoteserverip").toString());
     es600db.setDatabaseName(litequery1.value("remoteserverdbname").toString());
     es600db.setPort(litequery1.value("remoteserverport").toInt());
     es600db.setUserName(litequery1.value("remoteserverusername").toString());
     es600db.setPassword(litequery1.value("remoteserveruserpassword").toString());

     if(!es600db.open()){
         qDebug()<<"es600 DB not open";

     }else {
        qDebug()<<"es600 DB open";
     }


     addrlist.append(mb_object_count);
     addrlist.append(mb_production_count);
     addrlist.append(mb_run_mode);
     addrlist.append(mb_warning_flag);
     addrlist.append(mb_cabity);

     addrlist.append(mb_temp1_set);
     temp_set_atnumber = addrlist.count()-1;
     addrlist.append(mb_temp2_set);
     addrlist.append(mb_temp3_set);
     addrlist.append(mb_temp4_set);
     addrlist.append(mb_temp5_set);
     addrlist.append(mb_temp6_set);
     addrlist.append(mb_temp7_set);
     addrlist.append(mb_temp8_set);
     addrlist.append(mb_temp9_set);
     addrlist.append(mb_temp10_set);
     addrlist.append(mb_temp11_set);
     addrlist.append(mb_temp12_set);
     addrlist.append(mb_temp13_set);
     addrlist.append(mb_temp14_set);
     addrlist.append(mb_temp15_set);
     addrlist.append(mb_temp16_set);

     addrlist.append(mb_temp1_up);
     temp_up_atnumber = addrlist.count()-1;
     addrlist.append(mb_temp2_up);
     addrlist.append(mb_temp3_up);
     addrlist.append(mb_temp4_up);
     addrlist.append(mb_temp5_up);
     addrlist.append(mb_temp6_up);
     addrlist.append(mb_temp7_up);
     addrlist.append(mb_temp8_up);
     addrlist.append(mb_temp9_up);
     addrlist.append(mb_temp10_up);
     addrlist.append(mb_temp11_up);
     addrlist.append(mb_temp12_up);
     addrlist.append(mb_temp13_up);
     addrlist.append(mb_temp14_up);
     addrlist.append(mb_temp15_up);
     addrlist.append(mb_temp16_up);

     addrlist.append(mb_temp1_down);
     temp_down_atnumber = addrlist.count()-1;
     addrlist.append(mb_temp2_down);
     addrlist.append(mb_temp3_down);
     addrlist.append(mb_temp4_down);
     addrlist.append(mb_temp5_down);
     addrlist.append(mb_temp6_down);
     addrlist.append(mb_temp7_down);
     addrlist.append(mb_temp8_down);
     addrlist.append(mb_temp9_down);
     addrlist.append(mb_temp10_down);
     addrlist.append(mb_temp11_down);
     addrlist.append(mb_temp12_down);
     addrlist.append(mb_temp13_down);
     addrlist.append(mb_temp14_down);
     addrlist.append(mb_temp15_down);
     addrlist.append(mb_temp16_down);

     addrlist.append(mb_temp1_real);
     temp_real_atnumber = addrlist.count()-1;
     addrlist.append(mb_temp2_real);
     addrlist.append(mb_temp3_real);
     addrlist.append(mb_temp4_real);
     addrlist.append(mb_temp5_real);
     addrlist.append(mb_temp6_real);
     addrlist.append(mb_temp7_real);
     addrlist.append(mb_temp8_real);
     addrlist.append(mb_temp9_real);
     addrlist.append(mb_temp10_real);
     addrlist.append(mb_temp11_real);
     addrlist.append(mb_temp12_real);
     addrlist.append(mb_temp13_real);
     addrlist.append(mb_temp14_real);
     addrlist.append(mb_temp15_real);
     addrlist.append(mb_temp16_real);

     addrlist.append(mb_temp1_onoff);
     temp_onoff_atnumber = addrlist.count()-1;
     addrlist.append(mb_temp2_onoff);
     addrlist.append(mb_temp3_onoff);
     addrlist.append(mb_temp4_onoff);
     addrlist.append(mb_temp5_onoff);
     addrlist.append(mb_temp6_onoff);
     addrlist.append(mb_temp7_onoff);
     addrlist.append(mb_temp8_onoff);
     addrlist.append(mb_temp9_onoff);
     addrlist.append(mb_temp10_onoff);
     addrlist.append(mb_temp11_onoff);
     addrlist.append(mb_temp12_onoff);
     addrlist.append(mb_temp13_onoff);
     addrlist.append(mb_temp14_onoff);
     addrlist.append(mb_temp15_onoff);
     addrlist.append(mb_temp16_onoff);

     addrlist.append(mb_actstatus);

     addrlist.append(mb_SHOTDATA_count);
     addrlist.append(mb_currenttotalcount);
     addrlist.append(mb_SHOTDATA_fooldata);
     addrlist.append(mb_SHOTDATA_fillingtime);
     addrlist.append(mb_SHOTDATA_plasticizing_time);
     addrlist.append(mb_SHOTDATA_cycle_time);
     addrlist.append(mb_SHOTDATA_cushion_position);
     addrlist.append(mb_SHOTDATA_plasticizing_position);
     addrlist.append(mb_SHOTDATA_temp1);
     addrlist.append(mb_SHOTDATA_temp2);
     addrlist.append(mb_SHOTDATA_temp3);
     addrlist.append(mb_SHOTDATA_temp4);
     addrlist.append(mb_SHOTDATA_temp5);
     addrlist.append(mb_SHOTDATA_temp6);
     addrlist.append(mb_SHOTDATA_temp7);
     addrlist.append(mb_SHOTDATA_temp8);
     addrlist.append(mb_moldname1);
     addrlist.append(mb_moldname2);
     addrlist.append(mb_moldname3);
     addrlist.append(mb_moldname4);
     addrlist.append(mb_moldname5);

     addrlist.append(mb_injstep);
     addrlist.append(mb_hldstep);

     addrlist.append(mb_injVelocity1);
     addrlist.append(mb_injVelocity2);
     addrlist.append(mb_injVelocity3);
     addrlist.append(mb_injVelocity4);
     addrlist.append(mb_injVelocity5);
     addrlist.append(mb_injVelocity6);
     addrlist.append(mb_injPressure1);
     addrlist.append(mb_injPressure2);
     addrlist.append(mb_injPressure3);
     addrlist.append(mb_injPressure4);
     addrlist.append(mb_injPressure5);
     addrlist.append(mb_injPressure6);
     addrlist.append(mb_injPosition1);
     addrlist.append(mb_injPosition2);
     addrlist.append(mb_injPosition3);
     addrlist.append(mb_injPosition4);
     addrlist.append(mb_injPosition5);
     addrlist.append(mb_injPosition6);

     addrlist.append(mb_injstep);
     addrlist.append(mb_hldstep);

     addrlist.append(mb_injVelocity1);
     addrlist.append(mb_injVelocity2);
     addrlist.append(mb_injVelocity3);
     addrlist.append(mb_injVelocity4);
     addrlist.append(mb_injVelocity5);
     addrlist.append(mb_injVelocity6);

     addrlist.append(mb_injPressure1);
     addrlist.append(mb_injPressure2);
     addrlist.append(mb_injPressure3);
     addrlist.append(mb_injPressure4);
     addrlist.append(mb_injPressure5);
     addrlist.append(mb_injPressure6);

     addrlist.append(mb_injPosition1);
     addrlist.append(mb_injPosition2);
     addrlist.append(mb_injPosition3);
     addrlist.append(mb_injPosition4);
     addrlist.append(mb_injPosition5);
     addrlist.append(mb_injPosition6);

     addrlist.append(mb_hldPressure1);
     addrlist.append(mb_hldPressure2);
     addrlist.append(mb_hldPressure3);

     addrlist.append(mb_hldTime1);
     addrlist.append(mb_hldTime2);
     addrlist.append(mb_hldTime3);

     addrlist.append(mb_hldVel1);
     addrlist.append(mb_hldVel2);
     addrlist.append(mb_hldVel3);

     addrlist.append(mb_chgPosition1);
     addrlist.append(mb_chgPosition2);
     addrlist.append(mb_chgPosition3);
     addrlist.append(mb_chgPosition4);

     addrlist.append(mb_chgSpeed1);
     addrlist.append(mb_chgSpeed2);
     addrlist.append(mb_chgSpeed3);
     addrlist.append(mb_chgSpeed4);

     addrlist.append(mb_backPressure1);
     addrlist.append(mb_backPressure2);
     addrlist.append(mb_backPressure3);
     addrlist.append(mb_backPressure4);

     addrlist.append(mb_suckbackPosition2);

     addrlist.append(mb_suckbackSpeed1);
     addrlist.append(mb_suckbackSpeed2);

     addrlist.append(mb_tempues1);
     addrlist.append(mb_tempues2);
     addrlist.append(mb_tempues3);
     addrlist.append(mb_tempues4);
     addrlist.append(mb_tempues5);
     addrlist.append(mb_tempues6);
     addrlist.append(mb_tempues7);

     addrlist.append(mb_tempset1);
     addrlist.append(mb_tempset2);
     addrlist.append(mb_tempset3);
     addrlist.append(mb_tempset4);
     addrlist.append(mb_tempset5);
     addrlist.append(mb_tempset6);
     addrlist.append(mb_tempset7);
     addrlist.append(mb_oilset);

     addrlist.append(mb_moldtempuse1);
     addrlist.append(mb_moldtempuse2);
     addrlist.append(mb_moldtempuse3);
     addrlist.append(mb_moldtempuse4);
     addrlist.append(mb_moldtempuse5);
     addrlist.append(mb_moldtempuse6);
     addrlist.append(mb_moldtempuse7);
     addrlist.append(mb_moldtempuse8);

    addrlist.append(mb_moldtempset1);
    addrlist.append(mb_moldtempset2);
    addrlist.append(mb_moldtempset3);
    addrlist.append(mb_moldtempset4);
    addrlist.append(mb_moldtempset5);
    addrlist.append(mb_moldtempset6);
    addrlist.append(mb_moldtempset7);
    addrlist.append(mb_moldtempset8);

    addrlist.append(mb_injtime);
    addrlist.append(mb_cooltime);
    addrlist.append(mb_chgtime);



     modbus_thread = new es600_modbus_thread(this);
     modbus_thread->start();

     initflag=true;
     return initflag;

}
void es600_base_locgic::loop(){
    waitcondition.wakeAll();
}
//es600_modbus_thread 에서 현재 함수를 호출한다.
void es600_base_locgic::es600_base_loop(){
    //example
/*
    qDebug()<<"temp1_set="<<datamap->value(QString("%1").arg(mb_temp1_set))->value;
    qDebug()<<"temp2_set="<<datamap->value(QString("%1").arg(mb_temp2_set))->value;
    qDebug()<<"temp3_set="<<datamap->value(QString("%1").arg(mb_temp3_set))->value;
    qDebug()<<"temp4_set="<<datamap->value(QString("%1").arg(mb_temp4_set))->value;
    qDebug()<<"temp5_set="<<datamap->value(QString("%1").arg(mb_temp5_set))->value;
    qDebug()<<"temp6_set="<<datamap->value(QString("%1").arg(mb_temp6_set))->value;
    qDebug()<<"temp7_set="<<datamap->value(QString("%1").arg(mb_temp7_set))->value;
    qDebug()<<"temp8_set="<<datamap->value(QString("%1").arg(mb_temp8_set))->value;
    qDebug()<<"temp9_set="<<datamap->value(QString("%1").arg(mb_temp9_set))->value;
    qDebug()<<"temp10_set="<<datamap->value(QString("%1").arg(mb_temp10_set))->value;
    qDebug()<<"temp11_set="<<datamap->value(QString("%1").arg(mb_temp11_set))->value;
    qDebug()<<"temp12_set="<<datamap->value(QString("%1").arg(mb_temp12_set))->value;
    qDebug()<<"temp13_set="<<datamap->value(QString("%1").arg(mb_temp13_set))->value;
    qDebug()<<"temp14_set="<<datamap->value(QString("%1").arg(mb_temp14_set))->value;
    qDebug()<<"temp15_set="<<datamap->value(QString("%1").arg(mb_temp15_set))->value;
    qDebug()<<"temp16_set="<<datamap->value(QString("%1").arg(mb_temp16_set))->value;
 */
    mslotitem * parent_item = (mslotitem *)parentmslot; //부모 위젯
    QString mancine_name = parent_item->machinename->text();

    QSqlQuery mysqlquery1(es600db);
    if(typeDB == MYSQL){
    QString update_temp = QString("UPDATE `temp_table` SET ");
    QString temp_append ;
    for(int i=1;i<=16;i++){
        if(i == 16){
            temp_append = QString("`temp%1_set`=%2, `temp%1_up`=%3, `temp%1_down`=%4, `temp%1_real`=%5, temp%1_onoff = %6 ")
                               .arg(i)
                               .arg(datamap->value(QString("%1").arg(addrlist.at(temp_set_atnumber+i-1)))->value.toDouble()/10.0)
                               .arg(datamap->value(QString("%1").arg(addrlist.at(temp_up_atnumber+i-1)))->value.toDouble()/10.0)
                               .arg(datamap->value(QString("%1").arg(addrlist.at(temp_down_atnumber+i-1)))->value.toDouble()/10.0)
                               .arg(datamap->value(QString("%1").arg(addrlist.at(temp_real_atnumber+i-1)))->value.toDouble()/10.0)
                               .arg(datamap->value(QString("%1").arg(addrlist.at(temp_onoff_atnumber+i-1)))->value.toDouble()/10.0);

        }else {
         temp_append = QString("`temp%1_set`=%2, `temp%1_up`=%3, `temp%1_down`=%4, `temp%1_real`=%5, temp%1_onoff = %6, ")
                            .arg(i)
                            .arg(datamap->value(QString("%1").arg(addrlist.at(temp_set_atnumber+i-1)))->value.toDouble()/10.0)
                            .arg(datamap->value(QString("%1").arg(addrlist.at(temp_up_atnumber+i-1)))->value.toDouble()/10.0)
                            .arg(datamap->value(QString("%1").arg(addrlist.at(temp_down_atnumber+i-1)))->value.toDouble()/10.0)
                            .arg(datamap->value(QString("%1").arg(addrlist.at(temp_real_atnumber+i-1)))->value.toDouble()/10.0)
                            .arg(datamap->value(QString("%1").arg(addrlist.at(temp_onoff_atnumber+i-1)))->value.toDouble()/10.0);

        }
         update_temp.append(temp_append);
    }
    temp_append = QString("WHERE  `machine_name`=\'%1\'").arg(mancine_name);

    update_temp.append(temp_append);

    queryresult = mysqlquery1.exec(update_temp);
    }else if(typeDB == ODBC){

    }
    current_shotcount = datamap->value(QString("%1").arg(mb_SHOTDATA_count))->value.toInt();
    if(before_shotcount<0){
        before_shotcount = current_shotcount;
        modbus_write_register(ctx,mb_actstatus,0);
    }
    if(before_shotcount!=current_shotcount){
        before_shotcount=current_shotcount;
    int actstatus = datamap->value(QString("%1").arg(mb_actstatus))->value.toInt();
    int fooldata =datamap->value(QString("%1").arg(mb_SHOTDATA_fooldata))->value.toInt();
    double fillingtime = datamap->value(QString("%1").arg(mb_SHOTDATA_fillingtime))->value.toDouble()/100.0;
    double plasticizing_time = datamap->value(QString("%1").arg(mb_SHOTDATA_plasticizing_time))->value.toDouble()/100.0;
    double cycle_time = datamap->value(QString("%1").arg(mb_SHOTDATA_cycle_time))->value.toDouble()/100.0;
    double cushion_position = datamap->value(QString("%1").arg(mb_SHOTDATA_cushion_position))->value.toDouble()/10.0;
    double plasticizing_position = datamap->value(QString("%1").arg(mb_SHOTDATA_plasticizing_position))->value.toDouble()/10.0;
    double temp1=datamap->value(QString("%1").arg(mb_SHOTDATA_temp1))->value.toDouble()/10.0;
    double temp2=datamap->value(QString("%1").arg(mb_SHOTDATA_temp2))->value.toDouble()/10.0;
    double temp3=datamap->value(QString("%1").arg(mb_SHOTDATA_temp3))->value.toDouble()/10.0;
    double temp4=datamap->value(QString("%1").arg(mb_SHOTDATA_temp4))->value.toDouble()/10.0;
    double temp5=datamap->value(QString("%1").arg(mb_SHOTDATA_temp5))->value.toDouble()/10.0;
    double temp6=datamap->value(QString("%1").arg(mb_SHOTDATA_temp6))->value.toDouble()/10.0;
    double temp7=datamap->value(QString("%1").arg(mb_SHOTDATA_temp7))->value.toDouble()/10.0;
    double oil_temp=datamap->value(QString("%1").arg(mb_SHOTDATA_oil_temp))->value.toDouble()/10.0;

    unsigned short moldname1 = datamap->value(QString("%1").arg(mb_moldname1))->value.toShort();
    unsigned short moldname2 = datamap->value(QString("%1").arg(mb_moldname2))->value.toShort();
    unsigned short moldname3 = datamap->value(QString("%1").arg(mb_moldname3))->value.toShort();
    unsigned short moldname4 = datamap->value(QString("%1").arg(mb_moldname4))->value.toShort();
    unsigned short moldname5 = datamap->value(QString("%1").arg(mb_moldname5))->value.toShort();
    QByteArray mold_name;
    mold_name.append((char)(moldname1>>8));
    mold_name.append((char)(moldname1));
    mold_name.append((char)(moldname2>>8));
    mold_name.append((char)(moldname2));
    mold_name.append((char)(moldname3>>8));
    mold_name.append((char)(moldname3));
    mold_name.append((char)(moldname4>>8));
    mold_name.append((char)(moldname4));
    mold_name.append((char)(moldname5>>8));
    mold_name.append((char)(moldname5));
    QString moldname = mold_name;




    actstatus = datamap->value(QString("%1").arg(mb_actstatus))->value.toInt();
    if(actstatus == 1 && before_shotcount){
        current_shotcount = datamap->value(QString("%1").arg(mb_SHOTDATA_count))->value.toInt();
    }
    if(typeDB == MYSQL){

    }else if(typeDB == ODBC){
        QString insertquery = QString("INSERT INTO [shot_data] "
                                      "([Machine_Name]"
                                      ",[Additional_Info_1]"
                                      ",[Additional_Info_2]"
                                      ",[TimeStamp]"
                                      ",[Shot_Number]"
                                      ",[NGmark]"
                                      ",[Injection_Time]"
                                      ",[Filling_Time]"
                                      ",[Plasticizing_Time]"
                                      ",[Cycle_Time]"
                                      ",[Clamp_Close_Time]"
                                      ",[Cushion_Position]"
                                      ",[Switch_Over_Position]"
                                      ",[Plasticizing_Position]"
                                      ",[Clamp_Open_Position]"
                                      ",[Max_Injection_Speed]"
                                      ",[Max_Screw_RPM]"
                                      ",[Average_Screw_RPM]"
                                      ",[Max_Injection_Pressure]"
                                      ",[Max_Switch_Over_Pressure]"
                                      ",[Max_Back_Pressure]"
                                      ",[Average_Back_Pressure]"
                                      ",[Barrel_Temperature_1]"
                                      ",[Barrel_Temperature_2]"
                                      ",[Barrel_Temperature_3]"
                                      ",[Barrel_Temperature_4]"
                                      ",[Barrel_Temperature_5]"
                                      ",[Barrel_Temperature_6]"
                                      ",[Barrel_Temperature_7]"
                                      ",[Hopper_Temperature]"
                                      ",[Mold_Temperature_1]"
                                      ",[Mold_Temperature_2]"
                                      ",[Mold_Temperature_3]"
                                      ",[Mold_Temperature_4]"
                                      ",[Mold_Temperature_5]"
                                      ",[Mold_Temperature_6]"
                                      ",[Mold_Temperature_7]"
                                      ",[Mold_Temperature_8]"
                                      ",[Mold_Temperature_9]"
                                      ",[Mold_Temperature_10]) "
                                "VALUES ("
                                      +QString("'%1'").arg(mancine_name)+","
                                      +QString("'%1'").arg(moldname)+","
                                      +"''"+","
                                      +"\'"+QDate::currentDate().toString("yyyy-MM-dd ")+QTime::currentTime().toString("HH:mm:ss")+"\'"+","
                                      +QString("%1").arg(current_shotcount)+","
                                      +QString("%1").arg(fooldata)+","
                                      +QString("%1").arg(fillingtime)+","
                                      +QString("%1").arg(fillingtime)+","
                                      +QString("%1").arg(plasticizing_time)+","
                                      +QString("%1").arg(cycle_time)+","
                                      +"0.0"+","
                                      +QString("%1").arg(cushion_position)+","
                                      +"0.0"+","
                                      +QString("%1").arg(plasticizing_position)+","
                                      +"0.0"+","
                                      +"0.0"+","
                                      +"0.0"+","
                                      +"0.0"+","
                                      +"0.0"+","
                                      +"0.0"+","
                                      +"0.0"+","
                                      +"0.0"+","
                                      +QString("%1").arg(temp1)+","
                                      +QString("%1").arg(temp2)+","
                                      +QString("%1").arg(temp3)+","
                                      +QString("%1").arg(temp4)+","
                                      +QString("%1").arg(temp5)+","
                                      +QString("%1").arg(temp6)+","
                                      +QString("%1").arg(oil_temp)+","
                                      +QString("%1").arg(temp7)+","
                                      +"0.0"+","
                                      +"0.0"+","
                                      +"0.0"+","
                                      +"0.0"+","
                                      +"0.0"+","
                                      +"0.0"+","
                                      +"0.0"+","
                                      +"0.0"+","
                                      +"0.0"+","
                                      +"0.0)"
                   );
        queryresult = mysqlquery1.exec(insertquery);

        QString Inj_Velocitystr;
        int injstep = datamap->value(QString("%1").arg(mb_injstep))->value.toInt();
        double injVelocity[6];
        for(int i=0;i<6;i++){
            injVelocity[i] = datamap->value(QString("%1").arg(mb_injVelocity1+i*2))->value.toDouble()/100.0;
        }
        if(injstep>0){
            Inj_Velocitystr.append(QString("%1/").arg(injVelocity[0]));
        }else{
            Inj_Velocitystr.append(QString("%1/").arg(0.0));
        }
        if(injstep>1){
            Inj_Velocitystr.append(QString("%1/").arg(injVelocity[1]));
        }else{
            Inj_Velocitystr.append(QString("%1/").arg(0.0));
        }
        if(injstep>2){
            Inj_Velocitystr.append(QString("%1/").arg(injVelocity[2]));
        }else{
            Inj_Velocitystr.append(QString("%1/").arg(0.0));
        }
        if(injstep>3){
            Inj_Velocitystr.append(QString("%1/").arg(injVelocity[3]));
        }else{
            Inj_Velocitystr.append(QString("%1/").arg(0.0));
        }
        if(injstep>4){
            Inj_Velocitystr.append(QString("%1/").arg(injVelocity[4]));
        }else{
            Inj_Velocitystr.append(QString("%1/").arg(0.0));
        }
        if(injstep>5){
            Inj_Velocitystr.append(QString("%1").arg(injVelocity[5]));
        }else{
            Inj_Velocitystr.append(QString("%1").arg(0.0));
        }
        QString injPressurestr;
        double injPressure[6];
        for(int i=0;i<6;i++){
            injPressure[i] = datamap->value(QString("%1").arg(mb_injPressure1+i*2))->value.toDouble();
        }
        if(injstep>0){
            injPressurestr.append(QString("%1/").arg(injPressure[0]));
        }else{
            injPressurestr.append(QString("%1/").arg(0.0));
        }
        if(injstep>1){
            injPressurestr.append(QString("%1/").arg(injPressure[1]));
        }else{
            injPressurestr.append(QString("%1/").arg(0.0));
        }
        if(injstep>2){
            injPressurestr.append(QString("%1/").arg(injPressure[2]));
        }else{
            injPressurestr.append(QString("%1/").arg(0.0));
        }
        if(injstep>3){
            injPressurestr.append(QString("%1/").arg(injPressure[3]));
        }else{
            injPressurestr.append(QString("%1/").arg(0.0));
        }
        if(injstep>4){
            injPressurestr.append(QString("%1/").arg(injPressure[4]));
        }else{
            injPressurestr.append(QString("%1/").arg(0.0));
        }
        if(injstep>5){
            injPressurestr.append(QString("%1").arg(injPressure[5]));
        }else{
            injPressurestr.append(QString("%1").arg(0.0));
        }
        QString injPositionstr;
        double injPosition[6];
        for(int i=0;i<6;i++){
            injPosition[i] = datamap->value(QString("%1").arg(mb_injPosition1+i*2))->value.toDouble()/10.0;
        }
        if(injstep>0){
            injPositionstr.append(QString("%1/").arg(injPosition[0]));
        }else{
            injPositionstr.append(QString("%1/").arg(0.0));
        }
        if(injstep>1){
            injPositionstr.append(QString("%1/").arg(injPosition[1]));
        }else{
            injPositionstr.append(QString("%1/").arg(0.0));
        }
        if(injstep>2){
            injPositionstr.append(QString("%1/").arg(injPosition[2]));
        }else{
            injPositionstr.append(QString("%1/").arg(0.0));
        }
        if(injstep>3){
            injPositionstr.append(QString("%1/").arg(injPosition[3]));
        }else{
            injPositionstr.append(QString("%1/").arg(0.0));
        }
        if(injstep>4){
            injPositionstr.append(QString("%1/").arg(injPosition[4]));
        }else{
            injPositionstr.append(QString("%1/").arg(0.0));
        }
        if(injstep>5){
            injPositionstr.append(QString("%1").arg(injPosition[5]));
        }else{
            injPositionstr.append(QString("%1").arg(0.0));
        }

        int hldstep = datamap->value(QString("%1").arg(mb_hldstep))->value.toInt();
        QString hldPressurestr;
        double hldPressure[3];
        for(int i=0;i<3;i++){
            hldPressure[i] = datamap->value(QString("%1").arg(mb_hldPressure1+i*2))->value.toDouble();
        }
        if(hldstep>0){
            hldPressurestr.append(QString("%1/").arg(hldPressure[0]));
        }else{
            hldPressurestr.append(QString("%1/").arg(0.0));
        }
        if(hldstep>1){
            hldPressurestr.append(QString("%1/").arg(hldPressure[1]));
        }else{
            hldPressurestr.append(QString("%1/").arg(0.0));
        }
        if(hldstep>2){
            hldPressurestr.append(QString("%1/").arg(hldPressure[2]));
        }else{
            hldPressurestr.append(QString("%1").arg(0.0));
        }

        QString hldTimestr;
        double hldTime[3];
        for(int i=0;i<3;i++){
            hldTime[i] = datamap->value(QString("%1").arg(mb_hldTime1+i*2))->value.toDouble();
        }
        if(hldstep>0){
            hldTimestr.append(QString("%1/").arg(hldTime[0]));
        }else{
            hldTimestr.append(QString("%1/").arg(0.0));
        }
        if(hldstep>1){
            hldTimestr.append(QString("%1/").arg(hldTime[1]));
        }else{
            hldTimestr.append(QString("%1/").arg(0.0));
        }
        if(hldstep>2){
            hldTimestr.append(QString("%1/").arg(hldTime[2]));
        }else{
            hldTimestr.append(QString("%1").arg(0.0));
        }

        QString hldVelstr;
        double hldVel[3];
        for(int i=0;i<3;i++){
            hldVel[i] = datamap->value(QString("%1").arg(mb_hldVel1+i*2))->value.toDouble()/100.0;
        }
        if(hldstep>0){
            hldVelstr.append(QString("%1/").arg(hldVel[0]));
        }else{
            hldVelstr.append(QString("%1/").arg(0.0));
        }
        if(hldstep>1){
            hldVelstr.append(QString("%1/").arg(hldVel[1]));
        }else{
            hldVelstr.append(QString("%1/").arg(0.0));
        }
        if(hldstep>2){
            hldVelstr.append(QString("%1/").arg(hldVel[2]));
        }else{
            hldVelstr.append(QString("%1").arg(0.0));
        }

        QString chgPositionstr;
        double chgPosition[4];
        for(int i=0;i<4;i++){
            chgPosition[i] = datamap->value(QString("%1").arg(mb_chgPosition1+i*2))->value.toDouble()/10.0;
        }
        chgPositionstr = QString("%1/%2/%3/%4").arg(chgPosition[0]).arg(chgPosition[1])
                                               .arg(chgPosition[2]).arg(chgPosition[3]);
        QString chgSpeedstr;
        double chgSpeed[4];
        for(int i=0;i<4;i++){
            chgSpeed[i] = datamap->value(QString("%1").arg(mb_chgSpeed1+i*2))->value.toDouble()/100.0;
        }
        chgSpeedstr = QString("%1/%2/%3/%4").arg(chgSpeed[0]).arg(chgSpeed[1])
                                               .arg(chgSpeed[2]).arg(chgSpeed[3]);
        QString backPressurestr;
        double backPressure[4];
        for(int i=0;i<4;i++){
            backPressure[i] = datamap->value(QString("%1").arg(mb_backPressure1+i*2))->value.toDouble();
        }
        backPressurestr = QString("%1/%2/%3/%4").arg(backPressure[0]).arg(backPressure[1])
                                               .arg(backPressure[2]).arg(backPressure[3]);

        QString suckbackPositionstr;
        double suckbackPosition2 = datamap->value(QString("%1").arg(mb_suckbackPosition2))->value.toDouble()/10.0;;
        suckbackPositionstr = QString("%1/%2").arg(0.0).arg(suckbackPosition2);

        QString suckbackSpeedstr;
        double suckbackSpeed1 = datamap->value(QString("%1").arg(mb_suckbackSpeed1))->value.toDouble()/100.0;;
        double suckbackSpeed2 = datamap->value(QString("%1").arg(mb_suckbackSpeed2))->value.toDouble()/100.0;;
        suckbackSpeedstr = QString("%1/%2").arg(suckbackSpeed1).arg(suckbackSpeed2);

        double tempues[7];
        for(int i=0;i<7;i++){
            tempues[i] = datamap->value(QString("%1").arg(mb_tempues1+i*2))->value.toDouble()/10.0;
        }

        QString tempsetstr;
        double tempset[7];
        for(int i=0;i<7;i++){
            tempset[i] = datamap->value(QString("%1").arg(mb_tempset1+i*2))->value.toDouble()/10.0;
        }
        double oilset = datamap->value(QString("%1").arg(mb_oilset))->value.toDouble()/10.0;
        if(tempues[0]){
            tempsetstr.append(QString("%1/").arg(tempset[0]));
        }else{
            tempsetstr.append(QString("%1/").arg(0.0));
        }
        if(tempues[1]){
            tempsetstr.append(QString("%1/").arg(tempset[1]));
        }else{
            tempsetstr.append(QString("%1/").arg(0.0));
        }
        if(tempues[2]){
            tempsetstr.append(QString("%1/").arg(tempset[2]));
        }else{
            tempsetstr.append(QString("%1/").arg(0.0));
        }
        if(tempues[3]){
            tempsetstr.append(QString("%1/").arg(tempset[3]));
        }else{
            tempsetstr.append(QString("%1/").arg(0.0));
        }
        if(tempues[4]){
            tempsetstr.append(QString("%1/").arg(tempset[4]));
        }else{
            tempsetstr.append(QString("%1/").arg(0.0));
        }
        if(tempues[5]){
            tempsetstr.append(QString("%1/").arg(tempset[5]));
        }else{
            tempsetstr.append(QString("%1/").arg(0.0));
        }
        if(tempues[6]){
            tempsetstr.append(QString("%1/").arg(tempset[6]));
        }else{
            tempsetstr.append(QString("%1/").arg(0.0));
        }

        tempsetstr.append(QString("%1").arg(oilset));


        double moldtempuse[8];
        for(int i=0;i<8;i++){
            moldtempuse[i] = datamap->value(QString("%1").arg(mb_moldtempuse1+i*2))->value.toDouble()/10.0;
        }

        QString moldtempstr;
        double moldtempset[8];
        for(int i=0;i<8;i++){
            moldtempset[i] = datamap->value(QString("%1").arg(mb_moldtempset1+i*2))->value.toDouble()/10.0;
        }
        if(moldtempuse[0]){
            moldtempstr.append(QString("%1/").arg(moldtempset[0]));
        }else{
            moldtempstr.append(QString("%1/").arg(0.0));
        }
        if(moldtempuse[1]){
            moldtempstr.append(QString("%1/").arg(moldtempset[1]));
        }else{
            moldtempstr.append(QString("%1/").arg(0.0));
        }
        if(moldtempuse[2]){
            moldtempstr.append(QString("%1/").arg(moldtempset[2]));
        }else{
            moldtempstr.append(QString("%1/").arg(0.0));
        }
        if(moldtempuse[3]){
            moldtempstr.append(QString("%1/").arg(moldtempset[3]));
        }else{
            moldtempstr.append(QString("%1/").arg(0.0));
        }
        if(moldtempuse[4]){
            moldtempstr.append(QString("%1/").arg(moldtempset[4]));
        }else{
            moldtempstr.append(QString("%1/").arg(0.0));
        }
        if(moldtempuse[5]){
            moldtempstr.append(QString("%1/").arg(moldtempset[5]));
        }else{
            moldtempstr.append(QString("%1/").arg(0.0));
        }
        if(moldtempuse[6]){
            moldtempstr.append(QString("%1/").arg(moldtempset[6]));
        }else{
            moldtempstr.append(QString("%1/").arg(0.0));
        }
        if(moldtempuse[7]){
            moldtempstr.append(QString("%1").arg(moldtempset[7]));
        }else{
            moldtempstr.append(QString("%1").arg(0.0));
        }

        QString timerstr;
        double injtime = datamap->value(QString("%1").arg(mb_injtime))->value.toDouble()/10.0;
        double cooltime = datamap->value(QString("%1").arg(mb_cooltime))->value.toDouble()/10.0;
        double chgtime = datamap->value(QString("%1").arg(mb_chgtime))->value.toDouble()/10.0;
        timerstr = QString("%1/%2/%3/%4").arg(injtime).arg(cooltime).arg("0.0").arg(chgtime);



        insertquery =QString("INSERT INTO [shot_data_rec]"
                "([Machine_Name]"
                ",[Additional_Info_1]"
                ",[Additional_Info_2]"
                ",[TimeStamp]"
                ",[Shot_Number]"
                ",[Inj_Velocity]"
                ",[Inj_Pressure]"
                ",[Inj_Position]"
                ",[SOV_Time]"
                ",[SOV_Position]"
                ",[Hld_Pressure]"
                ",[Hld_Time]"
                ",[Hld_Vel]"
                ",[Chg_Position]"
                ",[Chg_Speed]"
                ",[BackPressure]"
                ",[Suckback_Position]"
                ",[Suckback_Speed]"
                ",[Barrel_Temperature]"
                ",[Mold_Temperature]"
                ",[Timer])"
          "VALUES"
                "("
                +QString("'%1'").arg(mancine_name)+","
                +QString("'%1'").arg(moldname)+","
                +"''"+","
                +"\'"+QDate::currentDate().toString("yyyy-MM-dd ")+QTime::currentTime().toString("HH:mm:ss")+"\'"+","
                +QString("%1").arg(current_shotcount)+","
                +"\'"+Inj_Velocitystr+"\'"+","
                +"\'"+injPressurestr+"\'"+","
                +"\'"+injPositionstr+"\'"+","
                +"0.0"+","
                +"0.0"+","
                +"\'"+hldPressurestr+"\'"+","
                +"\'"+hldTimestr+"\'"+","
                +"\'"+hldVelstr+"\'"+","
                +"\'"+chgPositionstr+"\'"+","
                +"\'"+chgSpeedstr+"\'"+","
                +"\'"+backPressurestr+"\'"+","
                +"\'"+suckbackPositionstr+"\'"+","
                +"\'"+suckbackSpeedstr+"\'"+","
                +"\'"+tempsetstr+"\'"+","
                +"\'"+moldtempstr+"\'"+","
                +"\'"+timerstr+"\'"+")"
             );

        queryresult = mysqlquery1.exec(insertquery);
        qDebug()<<mysqlquery1.lastQuery();
        qDebug()<<mysqlquery1.lastError().text();
    }
    }

    if(queryresult){

    }else {
        es600db.open();
        qDebug()<<"es600 false";
    }

}
void es600_base_locgic::slot_statue_update(bool statue){
    mslotitem *parent_item = (mslotitem *)parentmslot; //부모 위젯
    if(statue){
        parent_item->set_connectlabel_text("<img src=\":/icon/icon/play-button16.png\">  connect");
        parent_item->set_status_text("<img src=\":/icon/icon/play-button16.png\">  play");
    }else {
        parent_item->set_connectlabel_text("<img src=\":/icon/icon/light-bulb_red.png\">  disconnect");
        parent_item->set_status_text("<img src=\":/icon/icon/stop.png\">  STOP");
    }
}

