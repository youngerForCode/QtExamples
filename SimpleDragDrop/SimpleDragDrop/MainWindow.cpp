#include "MainWindow.h"
#include "QtGui"


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui->setupUi(this);

	textEdit = new QTextEdit;
	setCentralWidget(textEdit);

	textEdit->setAcceptDrops(false);
	setAcceptDrops(true);

	setWindowTitle(tr("Text Editor"));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat("text/uri-list"))
	{
		event->acceptProposedAction();
	}
}

void MainWindow::dropEvent(QDropEvent *event)
{
	QList<QUrl> urls = event->mimeData()->urls();
	if (urls.empty())
		return;
	auto fileName = urls.first().toLocalFile();
	if (fileName.isEmpty())
		return;
	if (readFile(fileName))
	{
		setWindowTitle(tr("%1-%2").arg(fileName)
			.arg(tr("Drag file")));
	}
}

bool MainWindow::readFile(const QString &fileName)
{
	if (fileName.isEmpty())
		return false;
	QFile file(fileName);
	if (file.open(QIODevice::ReadOnly))
	{
		QString data = file.readAll();
		textEdit->append(data);
		file.close();
	}
	return true;
}
