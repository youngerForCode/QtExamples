#ifndef SERIALHELPER_H
#define SERIALHELPER_H

#include <QObject>
#include <QSerialPort>
#include  <QSerialPortInfo>


class SerialHelper : public QObject
{
    Q_OBJECT
public:
    explicit SerialHelper(QObject *parent = nullptr);
    ~SerialHelper();
    // 扫描可用串口
    QStringList scanSerial();
    // 打开串口
    bool openSerial(QString portName, int br,int db, int parity, int sb,int fc);
    QSerialPort *getSerialPort();
    QByteArray readData();
    void writeData(QByteArray &data);
signals:
    void  readDataSignal();
private:
    QSerialPort *_serialPort;
};

#endif // SERIALHELPER_H
