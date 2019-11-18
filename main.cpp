#include "XImage.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	XImage w;
	w.show();
	return a.exec();
}
