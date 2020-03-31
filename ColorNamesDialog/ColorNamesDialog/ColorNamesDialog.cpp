#include "ColorNamesDialog.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtCore/QRegExp>

#include <QtCore/QStringListModel>
#include <QtCore/QSortFilterProxyModel>


ColorNamesDialog::ColorNamesDialog(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	QGridLayout *layout = new QGridLayout;
	QListView *listView = new QListView;
	listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	QLabel *filterLabel = new QLabel("Filter:");
	filterLineEdit = new QLineEdit;
	QLabel *patternLabel = new QLabel("Pattern syntax:");
	syntaxComboBox = new QComboBox();
	syntaxComboBox->addItem(tr("Regular Expression"), QRegExp::RegExp);
	syntaxComboBox->addItem(tr("Wildcard "), QRegExp::Wildcard);
	syntaxComboBox->addItem(tr("Fixed String"), QRegExp::FixedString);
	connect(syntaxComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(reapplyFilter()));
	connect(filterLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(reapplyFilter()));
	layout->addWidget(listView, 0, 0, 1, 2);
	layout->addWidget(filterLabel, 1, 0);
	layout->addWidget(filterLineEdit, 1, 1);
	layout->addWidget(patternLabel, 2, 0);
	layout->addWidget(syntaxComboBox, 2, 1);
	//layout->addWidget(listView, 0, 0, 4, 3);
	//layout->addWidget(filterLabel, 4, 0, 1, 1);
	//layout->addWidget(filterLineEdit, 4, 1, 1, 2);
	//layout->addWidget(patternLabel, 5, 0, 1, 1);
	//layout->addWidget(syntaxComboBox, 5, 1, 1, 2);
	ui.centralWidget->setLayout(layout);

	QStringListModel *sourceModel = new QStringListModel;
	sourceModel->setStringList(QColor::colorNames());
	proxyModel = new QSortFilterProxyModel;
	proxyModel->setSourceModel(sourceModel);
	proxyModel->setFilterKeyColumn(0);

	listView->setModel(proxyModel);
}

void ColorNamesDialog::reapplyFilter()
{
	//QComboBox *syntaxComboBox = static_cast<QComboBox*>(sender());
	QRegExp::PatternSyntax syntax =
		QRegExp::PatternSyntax(syntaxComboBox->itemData(syntaxComboBox->currentIndex()).toInt());
	QRegExp regExp(filterLineEdit->text(), Qt::CaseInsensitive, syntax);
	proxyModel->setFilterRegExp(regExp);
}
