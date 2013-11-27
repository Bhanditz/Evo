#include <QtGui>
#include <QThreadPool>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	game(new Game(ui->centralWidget)) {
	qDebug() << "MainWindow::MainWindow()";

	ui->setupUi(this);

	connect(ui->actionStart, SIGNAL(triggered()), this, SLOT(start()));
	connect(ui->actionRestart, SIGNAL(triggered()), this, SLOT(restart()));
	connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
	connect(ui->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));

	ui->actionRestart->setDisabled(true);
}

MainWindow::~MainWindow() {
	qDebug() << "MainWindow::~MainWindow()";
	delete game;
	delete ui;
}

void MainWindow::start() {
	qDebug() << "MainWindow::start()";
	if (game) QThreadPool::globalInstance()->start(game);
	ui->actionStart->setDisabled(true);
	ui->actionRestart->setDisabled(false);
}
void MainWindow::restart() {
	delete game;
	game = new Game();
}

void MainWindow::about() {
	qDebug() << "MainWindow::about()";

}
