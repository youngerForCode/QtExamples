#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    iniUI();
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::iniUI()
{
    QStringList portList = _serialHelper.scanSerial();
    ui->serialPorts->addItems(portList);
    QList<qint32> baudRateList = QSerialPortInfo::standardBaudRates();
                                 /* {QSerialPort::Baud1200, QSerialPort::Baud2400, \
                                 QSerialPort::Baud4800,QSerialPort::Baud9600,
                                 QSerialPort::Baud19200, QSerialPort::Baud38400,
                                  QSerialPort::Baud57600,  QSerialPort::Baud115200};*/
    for(auto elem: baudRateList)
        ui->baudRate->addItem(QString::number(elem));
    QStringList dataBitList = {"Data5", "Data6", "Data7","Data8"};
    QStringList parityList = {"NoParity", "EvenParity", "OddParity","SpaceParity","MarkParity"};
    QStringList stopBitList = {"OneStop", "OneAndHalfStop", "TwoStop"};
    QStringList flowControlList = {"OneStop", "OneAndHalfStop", "TwoStop"};
    ui->dataBit->addItems(dataBitList);
    ui->parityBit->addItems(parityList);
    ui->stopBit->addItems(stopBitList);
    ui->controlFlow->addItems(flowControlList);
}


bool MainWindow::onOpenSerialClicked()
{
    QString portName = ui->serialPorts->currentText();
    int baudRate = ui->baudRate->currentText().toInt();
    int dataBit = ui->dataBit->currentText().toInt();
    int parity = ui->parityBit->currentText().toInt();
    int stopBit = ui->stopBit->currentText().toInt();
    int flowControl = ui->controlFlow->currentText().toInt();
    bool status =  _serialHelper.openSerial(portName,baudRate, dataBit, parity, stopBit, flowControl);
    if(status)
    {
        connect(ui->sendBtn, &QPushButton::clicked, [&](){
            QString text = ui->lineEdit->text();
            ui->textBrowser->append(text);
            QByteArray data = text.toLatin1();
            _serialHelper.writeData(data);
        });
        connect(&_serialHelper, &SerialHelper::readDataSignal, this, &MainWindow::readData);
    }
    return false;
}

void MainWindow::readData()
{
    QByteArray data = _serialHelper.readData();
    ui->textBrowser->append(QString(data));
}

