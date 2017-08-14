#include "mainwindow.h"
#include <QApplication>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	std::string files = argv[1];

	MainWindow mainWindow(files);

	mainWindow.show();

	return app.exec();
}