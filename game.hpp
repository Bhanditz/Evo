#ifndef GAME_H
#define GAME_H

#include <QtWidgets>
#include "map.hpp"

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

		Game(QWidget *parent = 0) :
			QWidget(parent),
			mutex(QMutex::NonRecursive),
			painter(this) {
			qDebug() << "Game::Game()";

			keepRunning = false;
			map         = new Map();
			updateTimer = new QTimer(this);

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
			keepRunning = true;
		}
		void updateEvent() {
			if (keepRunning) {
				map->update();
				this->update();
			} else updateTimer->stop();
		}
		void paintEvent(QPaintEvent *) {
			if (!keepRunning) return;
			QFont font("Helvetica");
			painter.begin(this);
			painter.setFont(font);
			for(int i = 0; i < 100; i++)
				painter.drawText(qrand() % this->width(), qrand() % this->height(), "Foobar");
			painter.end();
		}
		void stop() {
			qDebug() << "Game::stop()";
			keepRunning = false;
			updateTimer->stop();
		}
};

#endif // GAME_H
