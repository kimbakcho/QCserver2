#ifndef IWONIL_MODBUS_THREAD_H
#define IWONIL_MODBUS_THREAD_H

#include <QObject>
#include <QThread>
class iwonil_modbus_thread : public QThread
{
    Q_OBJECT
public:
    explicit iwonil_modbus_thread(QObject *parent_src);
    bool playflag;
    QObject *parent;
    quint16 reg[10];

private:
    void run();

signals:
     void sig_statue_update(bool statue);

public slots:
};

#endif // IWONIL_MODBUS_THREAD_H
