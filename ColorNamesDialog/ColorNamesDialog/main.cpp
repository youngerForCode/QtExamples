#include "ColorNamesDialog.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ColorNamesDialog w;
	w.show();
	return a.exec();
}
