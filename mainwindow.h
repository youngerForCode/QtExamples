#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Serialhelper.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void iniUI();
private  slots:
    // 打开串口
    bool onOpenSerialClicked();
    void readData();
private:
    Ui::MainWindow *ui;
    SerialHelper _serialHelper;
};
#endif // MAINWINDOW_H
