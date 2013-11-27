#ifndef GAME_H
#define GAME_H

#include <QtWidgets>
#include "map.h"

class Game : public QWidget, public QRunnable {
	private:
		Map *map;
		QMutex mutex;
		bool keepRunning;
		QPainter painter;
	public:

		Game(QWidget *parent = 0) : QWidget(parent), QRunnable() {
			qDebug() << "Game::Game()";
			map = new Map();
			keepRunning = true;
		}
		~Game() {
			qDebug() << "Game::~Game()";
			if (map) {
				delete map;
			}
		}
		void run() {
			qDebug() << "Game::run()";
			while(keepRunning) {
				map->update();
			}
		}
		void paintEvent(QPaintEvent *) {
			qDebug() << "Game::paintEvent()";
			painter.begin(this);
			painter.setFont(QFont("Arial", 30));
			painter.drawText(rect(), Qt::AlignCenter, "Fooobar");
			painter.setPen(QPen(Qt::black, 3));
			for (int j = 0; j < 60; ++j) {
				if ((j % 5) != 0)
					painter.drawLine(92, 0, 96, 0);
				painter.rotate(6.0);
			}
			painter.end();
		}
		void quit() {
			this->keepRunning = false;
		}
};

#endif // GAME_H
