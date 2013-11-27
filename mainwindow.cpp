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

	connect(ui->actionStart,   SIGNAL(triggered()), this, SLOT(start()));
	connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
	connect(ui->actionExit,    SIGNAL(triggered()), qApp, SLOT(quit()));
}

MainWindow::~MainWindow() {
	qDebug() << "MainWindow::~MainWindow()";
	ui->game->stop();
	delete ui;
}

void MainWindow::start() {
	qDebug() << "MainWindow::start()";
	ui->actionStart->setDisabled(true);
	ui->game->run();
}

void MainWindow::about() {
	qDebug() << "MainWindow::about()";
}
