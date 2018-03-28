/////////////////////////////////////////////////////////////////
//PROGRAMMEURS/ PROGRAMMEUSES : François-Xavier Mousseau et Émilie Seguin
// Programme : Ce programme rentre dans le cadre du projet du
// cours inf 1483 de l’université uqo.ca
// Projet : le projet défini la conception d’un personnage en mouvement.
// main.c : ce programme démontre la cuisse du personnage
//
// date: 11 avril 2018
////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <GL/freeglut.h>
#else
#include <GL/freeglut.h>
#endif

void InitLights() {

}

void Init()
{
	glClearColor(0, 0, 0, 0);
	//glEnable(GL_NORMALIZE);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glShadeModel(GL_SMOOTH);

	InitLights();

	//enable lights
	glEnable(GL_LIGHT0);

	glEnable(GL_LIGHTING);
}


void Cuisse() {

	float size = 0.5;
	glPushMatrix();

	//définir l'object ici
	glBegin(GL_TRIANGLES); 
	/*glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-size, -size, size);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(size, -size, size);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(size, size, size);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-size, size, size);*/
	glEnd();

	glPopMatrix();
}

void Display()
{
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	Cuisse();

	glFlush();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, (GLint)w, (GLint)h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glOrtho(-8.0, 8.0, -8.0, 8.0, -8.0, 8.0);
}

int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Projet 2D/3D : La cuisse");

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);

	Init();

	glutMainLoop();

	return 0;
}


