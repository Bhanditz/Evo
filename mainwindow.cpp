#include <QtGui>
#include <QThreadPool>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	game(new Game(this, ui->renderArea)) {
	qDebug() << "MainWindow::MainWindow()";

	ui->setupUi(this);
	ui->actionRestart->setDisabled(true);

	connect(ui->actionStart, SIGNAL(triggered()), this, SLOT(start()));
	connect(ui->actionRestart, SIGNAL(triggered()), this, SLOT(restart()));
	connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
	connect(ui->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

MainWindow::~MainWindow() {
	qDebug() << "MainWindow::~MainWindow()";
	game->quit();
	// QThreadPool hoitaa game:n muistista poistamisen
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
	game->quit();
	delete game;
	game = new Game(this, ui->renderArea);
	start();
}

void MainWindow::about() {
	qDebug() << "MainWindow::about()";
}
