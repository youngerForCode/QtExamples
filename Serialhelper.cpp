#include "Serialhelper.h"

SerialHelper::SerialHelper(QObject *parent) : QObject(parent)
{
    _serialPort = new QSerialPort;
}

SerialHelper::~SerialHelper()
{
    _serialPort->clear();
    _serialPort->close();
}


// 扫描可用串口
QStringList SerialHelper::scanSerial()
{
    QStringList serialStrList;

    // 读取串口信息
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        _serialPort->setPort(info);
        // 判断端口能否以读写方式打开
        if(_serialPort->open(QIODevice::ReadWrite))
        {
            serialStrList.append(_serialPort->portName());
            _serialPort->close(); // 然后自动关闭等待人为开启（通过"打开串口按钮"）
        }
    }

    return serialStrList;
}

bool SerialHelper::openSerial(QString portName, int br,int db, int parity, int sb,int fc)
{
    QSerialPort::BaudRate brE = QSerialPort::BaudRate(br);
    QSerialPort::DataBits dbE = QSerialPort::DataBits(db);
    QSerialPort::Parity parityE = QSerialPort::Parity(parity);
    QSerialPort::StopBits sbE = QSerialPort::StopBits(sb);
    QSerialPort::FlowControl fcE = QSerialPort::FlowControl(fc);

    // 设置串口名
    _serialPort->setPortName(portName);
    //  打开串口（读写方式）
    if(_serialPort->open(QIODevice::ReadWrite))
    {
        _serialPort->setBaudRate(brE);// 设置波特率(默认为115200)
        _serialPort->setDataBits(dbE);// 设置数据位(数据位为8位)
        _serialPort->setParity(parityE);// 设置校验位(无校验位)
        _serialPort->setStopBits(sbE);// 设置停止位(停止位为1)
        _serialPort->setFlowControl(fcE); // 设置流控制(无数据流控制)

        // 当下位机中有数据发送过来时就会触发这个信号，以提示其它类对象
        connect(_serialPort, SIGNAL(readyRead()), this, SIGNAL(readDataSignal()));
        return true;
    }

}

QByteArray SerialHelper::readData()
{
    return _serialPort->readAll();
}

void SerialHelper::writeData(QByteArray &data)
{
    _serialPort->write(data);
}
