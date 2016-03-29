#include "scanlinezbuffer.h"
#include <QtWidgets/QApplication>
#include <consoleapi.h>

int main(int argc, char *argv[])
{
	///xxx
	if (AllocConsole())
	{
		freopen("CONOUT$", "w", stdout);
	}
	QApplication a(argc, argv);
	ScanlineZbuffer w;
	w.show();
	return a.exec();
}
