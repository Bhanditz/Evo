#include <QtGui>
#include <QThreadPool>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.hpp"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow) {
	qDebug() << "MainWindow::MainWindow()";

	ui->setupUi(this);
	ui->actionRestart->setDisabled(true);
	game = new Game(ui->gamewrapper);


	connect(ui->actionStart,   SIGNAL(triggered()), this, SLOT(start()));
	connect(ui->actionRestart, SIGNAL(triggered()), this, SLOT(restart()));
	connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
	connect(ui->actionExit,    SIGNAL(triggered()), qApp, SLOT(quit()));
}

MainWindow::~MainWindow() {
	qDebug() << "MainWindow::~MainWindow()";
	game->stop();
	delete game;
	delete ui;
}

void MainWindow::start() {
	qDebug() << "MainWindow::start()";
	if (game) {
		ui->actionStart->setDisabled(true);
		ui->actionRestart->setDisabled(false);
		game->run();
	} else {
		qCritical() << "Game not initialized";
	}
}
void MainWindow::restart() {
	game->stop();
	delete game;
	game = new Game(this);
	start();
}

void MainWindow::about() {
	qDebug() << "MainWindow::about()";
}
