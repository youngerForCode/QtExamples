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
	void dragEnterEvent(QDragEnterEvent *event);//��ĳ�������϶�����ǰ�Ĵ��ڲ���
	void dropEvent(QDropEvent *event);// �ڴ��ڲ�������ĳ������

private:
	bool readFile(const QString &fileName);
	Ui::MainWindowClass *ui;
	QTextEdit *textEdit;
};