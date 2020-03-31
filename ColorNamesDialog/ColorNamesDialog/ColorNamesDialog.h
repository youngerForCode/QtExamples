#pragma once
#include <QtGui/QtGui>
#include <QtWidgets/QMainWindow>
#include "ui_ColorNamesDialog.h"

class ColorNamesDialog : public QMainWindow
{
	Q_OBJECT

public:
	ColorNamesDialog(QWidget *parent = Q_NULLPTR);
public slots:
	void reapplyFilter();
private:
	Ui::ColorNamesDialogClass ui;
	QSortFilterProxyModel *proxyModel;
	QLineEdit *filterLineEdit;
	QComboBox *syntaxComboBox;
};
