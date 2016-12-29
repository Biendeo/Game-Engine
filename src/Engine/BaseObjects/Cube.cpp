#include "Cube.h"

#include <Windows.h>
#include <GL/glew.h>
#include <GL/GL.h>

namespace Biendeo::GameOff2016::Engine::BaseObjects {
	Cube::Cube(Engine* engine) : Biendeo::GameOff2016::Engine::GameObject(engine) {

	}

	Cube::~Cube() {

	}

	void Cube::DrawSelf() {
		// TODO: This can be cleaned up much better.
		glEnable(GL_DEPTH_TEST);
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_TRIANGLES);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glEnd();
		glColor3f(1.0f, 1.0f, 0.0f);
		glBegin(GL_TRIANGLES);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glEnd();
		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_TRIANGLES);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glEnd();
		glColor3f(0.0f, 1.0f, 1.0f);
		glBegin(GL_TRIANGLES);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glEnd();
		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_TRIANGLES);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glEnd();
		glColor3f(1.0f, 0.0f, 1.0f);
		glBegin(GL_TRIANGLES);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glEnd();
		glDisable(GL_DEPTH_TEST);
	}
}