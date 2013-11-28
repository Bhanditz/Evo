#ifndef GAME_H
#define GAME_H

#include </usr/include/qt/QtOpenGL/QGLWidget>
#include <GL/glu.h>
#include <GL/glut.h>
#include <QMutex>
#include <QTimer>
#include <QtWidgets>
#include "map.hpp"

class Game : public QGLWidget {
	Q_OBJECT

	private:
		Map *map;
		QMutex mutex;
		bool keepRunning;
		QPainter painter;
		QTimer *updateTimer;

	protected:
		void initializeGL() {
			qDebug() << "Game::initializeGL()";
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClearDepth(1.0);
			glDepthFunc(GL_LESS);
			glEnable(GL_DEPTH_TEST);
			glShadeModel(GL_SMOOTH);
		}
		void resizeGL(int w, int h) {
			qDebug() << QString("Game::resizeGL(%1,%2)").arg(w).arg(h);
			if ( h==0 ) h=1;

			glViewport(0, 0, w, h);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);
			glMatrixMode(GL_MODELVIEW);
		}
		void paintGL() {
			qDebug() << "Game::paintGL()";

			static float rtri = 0.0;
			static float rquad = 0.0;
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
			glLoadIdentity();				// Reset The View

			glTranslatef(-1.5f,0.0f,-6.0f);		// Move Left 1.5 Units And Into The Screen 6.0

			glRotatef(rtri,0.0f,1.0f,0.0f);		// Rotate The Pyramid On The Y axis

			// draw a pyramid (in smooth coloring mode)
			glBegin(GL_POLYGON);				// start drawing a pyramid

			// front face of pyramid
			glColor3f(1.0f,0.0f,0.0f);			// Set The Color To Red
			glVertex3f(0.0f, 1.0f, 0.0f);		        // Top of triangle (front)
			glColor3f(0.0f,1.0f,0.0f);			// Set The Color To Green
			glVertex3f(-1.0f,-1.0f, 1.0f);		// left of triangle (front)
			glColor3f(0.0f,0.0f,1.0f);			// Set The Color To Blue
			glVertex3f(1.0f,-1.0f, 1.0f);		        // right of traingle (front)

			// right face of pyramid
			glColor3f(1.0f,0.0f,0.0f);			// Red
			glVertex3f( 0.0f, 1.0f, 0.0f);		// Top Of Triangle (Right)
			glColor3f(0.0f,0.0f,1.0f);			// Blue
			glVertex3f( 1.0f,-1.0f, 1.0f);		// Left Of Triangle (Right)
			glColor3f(0.0f,1.0f,0.0f);			// Green
			glVertex3f( 1.0f,-1.0f, -1.0f);		// Right Of Triangle (Right)

			// back face of pyramid
			glColor3f(1.0f,0.0f,0.0f);			// Red
			glVertex3f( 0.0f, 1.0f, 0.0f);		// Top Of Triangle (Back)
			glColor3f(0.0f,1.0f,0.0f);			// Green
			glVertex3f( 1.0f,-1.0f, -1.0f);		// Left Of Triangle (Back)
			glColor3f(0.0f,0.0f,1.0f);			// Blue
			glVertex3f(-1.0f,-1.0f, -1.0f);		// Right Of Triangle (Back)

			// left face of pyramid.
			glColor3f(1.0f,0.0f,0.0f);			// Red
			glVertex3f( 0.0f, 1.0f, 0.0f);		// Top Of Triangle (Left)
			glColor3f(0.0f,0.0f,1.0f);			// Blue
			glVertex3f(-1.0f,-1.0f,-1.0f);		// Left Of Triangle (Left)
			glColor3f(0.0f,1.0f,0.0f);			// Green
			glVertex3f(-1.0f,-1.0f, 1.0f);		// Right Of Triangle (Left)

			glEnd();					// Done Drawing The Pyramid

			glLoadIdentity();				// make sure we're no longer rotated.
			glTranslatef(1.5f,0.0f,-7.0f);		// Move Right 3 Units, and back into the screen 7

			glRotatef(rquad,1.0f,1.0f,1.0f);		// Rotate The Cube On X, Y, and Z

			// draw a cube (6 quadrilaterals)
			glBegin(GL_QUADS);				// start drawing the cube.

			// top of cube
			glColor3f(0.0f,1.0f,0.0f);			// Set The Color To Blue
			glVertex3f( 1.0f, 1.0f,-1.0f);		// Top Right Of The Quad (Top)
			glVertex3f(-1.0f, 1.0f,-1.0f);		// Top Left Of The Quad (Top)
			glVertex3f(-1.0f, 1.0f, 1.0f);		// Bottom Left Of The Quad (Top)
			glVertex3f( 1.0f, 1.0f, 1.0f);		// Bottom Right Of The Quad (Top)

			// bottom of cube
			glColor3f(1.0f,0.5f,0.0f);			// Set The Color To Orange
			glVertex3f( 1.0f,-1.0f, 1.0f);		// Top Right Of The Quad (Bottom)
			glVertex3f(-1.0f,-1.0f, 1.0f);		// Top Left Of The Quad (Bottom)
			glVertex3f(-1.0f,-1.0f,-1.0f);		// Bottom Left Of The Quad (Bottom)
			glVertex3f( 1.0f,-1.0f,-1.0f);		// Bottom Right Of The Quad (Bottom)

			// front of cube
			glColor3f(1.0f,0.0f,0.0f);			// Set The Color To Red
			glVertex3f( 1.0f, 1.0f, 1.0f);		// Top Right Of The Quad (Front)
			glVertex3f(-1.0f, 1.0f, 1.0f);		// Top Left Of The Quad (Front)
			glVertex3f(-1.0f,-1.0f, 1.0f);		// Bottom Left Of The Quad (Front)
			glVertex3f( 1.0f,-1.0f, 1.0f);		// Bottom Right Of The Quad (Front)

			// back of cube.
			glColor3f(1.0f,1.0f,0.0f);			// Set The Color To Yellow
			glVertex3f( 1.0f,-1.0f,-1.0f);		// Top Right Of The Quad (Back)
			glVertex3f(-1.0f,-1.0f,-1.0f);		// Top Left Of The Quad (Back)
			glVertex3f(-1.0f, 1.0f,-1.0f);		// Bottom Left Of The Quad (Back)
			glVertex3f( 1.0f, 1.0f,-1.0f);		// Bottom Right Of The Quad (Back)

			// left of cube
			glColor3f(0.0f,0.0f,1.0f);			// Blue
			glVertex3f(-1.0f, 1.0f, 1.0f);		// Top Right Of The Quad (Left)
			glVertex3f(-1.0f, 1.0f,-1.0f);		// Top Left Of The Quad (Left)
			glVertex3f(-1.0f,-1.0f,-1.0f);		// Bottom Left Of The Quad (Left)
			glVertex3f(-1.0f,-1.0f, 1.0f);		// Bottom Right Of The Quad (Left)

			// Right of cube
			glColor3f(1.0f,0.0f,1.0f);			// Set The Color To Violet
			glVertex3f( 1.0f, 1.0f,-1.0f);	        // Top Right Of The Quad (Right)
			glVertex3f( 1.0f, 1.0f, 1.0f);		// Top Left Of The Quad (Right)
			glVertex3f( 1.0f,-1.0f, 1.0f);		// Bottom Left Of The Quad (Right)
			glVertex3f( 1.0f,-1.0f,-1.0f);		// Bottom Right Of The Quad (Right)
			glEnd();					// Done Drawing The Cube

			rtri+=15.0f;					// Increase The Rotation Variable For The Pyramid
			rquad-=15.0f;					// Decrease The Rotation Variable For The Cube

		}

	public:
		Game(QWidget *parent = 0) :
			QGLWidget(parent),
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
			updateTimer->setInterval(30);
			updateTimer->start();
			keepRunning = true;
		}
		void updateEvent() {
			if (keepRunning) {
				map->update();
				this->updateGL();
			} else updateTimer->stop();
		}
		void paintEvent(QPaintEvent *) {
			if (!keepRunning) return;
			painter.begin(this);
			map->draw(&painter);
			painter.end();
		}
		void stop() {
			qDebug() << "Game::stop()";
			keepRunning = false;
			updateTimer->stop();
		}
};

#endif // GAME_H
