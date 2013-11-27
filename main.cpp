#include "mainwindow.h"
#include <QApplication>

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	MainWindow window;

	window.resize(WINDOW_WIDTH, WINDOW_HEIGHT);
	window.show();

	return app.exec();
}
