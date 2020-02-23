#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

protected:
	void dragEnterEvent(QDragEnterEvent *event);//将某个对象拖动到当前的窗口部件
	void dropEvent(QDropEvent *event);// 在窗口部件放下某个对象

private:
	bool readFile(const QString &fileName);
	Ui::MainWindowClass *ui;
	QTextEdit *textEdit;
};