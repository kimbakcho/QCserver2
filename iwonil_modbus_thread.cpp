#include "iwonil_modbus_thread.h"
#include "iwonil_base_locgic.h"
iwonil_modbus_thread::iwonil_modbus_thread(QObject *parent_src)
{
    playflag = true;
    this->parent = parent_src;
    iwonil_base_locgic *parent_des = (iwonil_base_locgic *)parent;
    parent_des->ctx = modbus_new_tcp(parent_des->ip.toLocal8Bit(),502);
    modbus_set_slave(parent_des->ctx,255);
    connect(this,SIGNAL(sig_statue_update(bool)),parent_des,SLOT(slot_statue_update(bool)));
}
void iwonil_modbus_thread::run(){
    iwonil_base_locgic *parent_des = (iwonil_base_locgic *)parent;
    while(playflag){
        parent_des->mutex.lock();
        parent_des->waitcondition.wait(&(parent_des->mutex));
        for(int i=0;i<parent_des->addrlist.count();i++){
            if(modbus_read_registers(parent_des->ctx,parent_des->addrlist.at(i),2,reg) == -1){
                if(modbus_connect(parent_des->ctx) == -1){
                    qDebug()<<parent_des->ip<<"="<<"modbus connect fail";
                     emit sig_statue_update(false);
                }else {
                     emit sig_statue_update(true);
                }
                QString addr = QString("%1").arg(parent_des->addrlist.at(i));
                if(!parent_des->datamap->contains(addr)){
                      parent_des->datamap->insert(addr,new iwonilvalue(addr,QString("%1").arg(0)));
                }else{
                       iwonilvalue *tempvalue = parent_des->datamap->value(addr);
                       tempvalue->value = QString("%1").arg(0);
                }
              }else {
                  emit sig_statue_update(true);
                  QString addr = QString("%1").arg(parent_des->addrlist.at(i));
                  if(!parent_des->datamap->contains(addr)){
                        parent_des->datamap->insert(addr,new iwonilvalue(addr,QString("%1").arg(reg[0])));
                  }else{
                         iwonilvalue *tempvalue = parent_des->datamap->value(addr);
                         tempvalue->value = QString("%1").arg(reg[0]);
                  }
              }
        }

        parent_des->iwonil_base_loop();
        parent_des->mutex.unlock();

    }
}
