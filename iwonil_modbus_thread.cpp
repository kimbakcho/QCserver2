#include "iwonil_modbus_thread.h"
#include "iwonil_base_locgic.h"
iwonil_modbus_thread::iwonil_modbus_thread(QObject *parent_src)
{
    playflag = true;
    this->parent = parent_src;
    iwonil_base_locgic *parent_des = (iwonil_base_locgic *)parent;
}
void iwonil_modbus_thread::run(){
    iwonil_base_locgic *parent_des = (iwonil_base_locgic *)parent;
    while(playflag){
        parent_des->mutex.lock();
        parent_des->waitcondition.wait(&(parent_des->mutex));
        parent_des->iwonil_base_loop();
        parent_des->mutex.unlock();

    }
}
