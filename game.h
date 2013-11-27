#ifndef GAME_H
#define GAME_H

#include <QtWidgets>
#include "map.h"

class Game : public QWidget {
	Q_OBJECT

	private:
		Map *map;
		QMutex mutex;
		bool keepRunning;
		QPainter painter;
		QWidget *renderArea;
		QTimer *updateTimer;
	public:

		Game(QWidget *parent, QWidget *renderArea) :
			QWidget(parent),
			mutex(QMutex::NonRecursive) {
			qDebug() << "Game::Game()";

			map         = new Map();
			keepRunning = true;
			updateTimer = new QTimer(this);
			this->renderArea = renderArea;
		}
		~Game() {
			qDebug() << "Game::~Game()";
			if (map) {
				delete map;
			}
		}

	public slots:
		void run() {
			qDebug() << "Game::run()";
			connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateEvent()));
			updateTimer->start(20);
		}
		void updateEvent() {
			qDebug() << "Game::updateEvent()";
			map->update();
			this->update();

			if ( keepRunning == false ) updateTimer->stop();
		}
		void paintEvent(QPaintEvent *) {
			static int f = 0;
			f++;
			qDebug() << QString("Game::paintEvent(): %1").arg(f);
			painter.begin(this);
			painter.drawText(f%this->width(), f%this->height(), "Foobar");
			painter.end();
		}
		void quit() {
			qDebug() << "Game::quit()";
			updateTimer->stop();
		}
};

#endif // GAME_H
