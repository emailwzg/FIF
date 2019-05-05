#include <QtGui/QApplication>
#include "fractionorderif.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FractionOrderIF w;
	w.show();
	return a.exec();
}
