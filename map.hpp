#ifndef MAP_H
#define MAP_H

#include<QPainter>

class Map {
	private:
	public:
		Map() {
			qDebug() << "Map::Map()";
		}
		~Map() {
			qDebug() << "Map::~Map()";
		}
		void update() {

		}
		void draw(QPainter *p) {
			for(int i = 0; i < 100; i++)
				p->drawText(qrand() % p->device()->width(), qrand() % p->device()->height(), "Foobar");
		}
};


#endif // MAP_H
