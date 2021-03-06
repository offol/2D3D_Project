/////////////////////////////////////////////////////////////////
//PROGRAMMEURS/ PROGRAMMEUSES : François-Xavier Mousseau et Émilie Seguin
// Programme : Ce programme rentre dans le cadre du projet du
// cours inf 1483 de l’université uqo.ca
// Projet : le projet défini la conception d’un personnage en mouvement.
// main.c : ce programme démontre la cuisse du personnage
//
// date: 11 avril 2018
////////////////////////////////////////////////////////////////

/* Chose à faire
1- Un parallélépipède.
2- Texturer (encore
bon d’avoir une
texture d’une
cuisse !
3- Mouvement pendule
de 30 degrés selon
l’axe x en haut de
l’avant-bras*/
#include <iostream>
#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "imageloader.h"
#include <Math.h>

#ifdef __APPLE__
#include <GL/freeglut.h>
#else
#include <GL/freeglut.h>
#endif

char titre[] = "Projet 2D/3D La cuisse";
GLfloat angleCube = 0.0f;
double angleCubed = 0;
int refreshMills = 15;
bool state = false;

// Data read from the header of the BMP file
unsigned char header[54]; // Each BMP file begins by a 54-bytes header
unsigned int dataPos;     // Position in the file where the actual data begins
unsigned int width, height;
unsigned int imageSize;   // = width*height*3
						  // Actual RGB data
unsigned char * data;

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
											 //Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
		0,                            //0 for now
		GL_RGB,                       //Format OpenGL uses for image
		image->width, image->height,  //Width and height
		0,                            //The border of the image
		GL_RGB, //GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
						  //as unsigned numbers
		image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

GLuint _textureId; //The id of the texture

void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	glClearDepth(1.0f);                  
	glEnable(GL_DEPTH_TEST);  
	glDepthFunc(GL_LEQUAL);   
	glShadeModel(GL_SMOOTH);  
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	Image* image = loadBMP("Image/Jeans_Texture.bmp");
	//IvyTexture // duck // texture 
	_textureId = loadTexture(image);
	delete image;
}

void cuisse() {

	glPushMatrix();

	glTranslatef(0.0f, 0.0f, -7.0f);

	glRotatef(45, 1.0, 0, 0);
	glRotatef(45, 0.0, 1.0, 0);
	glRotatef(angleCube, 1.0f, 0.0f, 0.0f); //animation

	glTranslatef(0.0f, -2.0f, 0.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBegin(GL_QUADS);
	// Face du haut (y = 1.0f)

	glVertex3f(0.5f, 2.0f, -0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, 2.0f, -0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f, 2.0f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 2.0f, 0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glEnd();

	glBegin(GL_QUADS);
	// Face du bas (y = -1.0f)

	glVertex3f(0.5f, -2.0f, 0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -2.0f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f, -2.0f, -0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, -2.0f, -0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glEnd();

	glBegin(GL_QUADS);
	// Face du devant  (z = 1.0f)

	glVertex3f(0.5f, 2.0f, 0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, 2.0f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f, -2.0f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, -2.0f, 0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glEnd();

	glBegin(GL_QUADS);
	// Face de derrière (z = -1.0f)

	glVertex3f(0.5f, -2.0f, -0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -2.0f, -0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f, 2.0f, -0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 2.0f, -0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glEnd();

	glBegin(GL_QUADS);
	// Face gauche(x = -1.0f)

	glVertex3f(-0.5f, 2.0f, 0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, 2.0f, -0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f, -2.0f, -0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5f, -2.0f, 0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glEnd();

	glBegin(GL_QUADS);
	// Face droite (x = 1.0f)

	glVertex3f(0.5f, 2.0f, -0.5f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, 2.0f, 0.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -2.0f, 0.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, -2.0f, -0.5f);
	glTexCoord2f(0.0f, 1.0f);
	glEnd();

	glutSwapBuffers();

	if (state == true) {
		angleCube += 0.15f;
		angleCubed += 0.15;
	}
	else if(state == false) {
		angleCube -= 0.15f;
		angleCubed -= 0.15;
	}

	if (angleCubed <= -30.0) {
		state = true;
		printf("true");
	}
	else if (angleCubed >= 0.0) {
		state = false;
		printf("false");
	}

	glPopMatrix();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW);     
	glLoadIdentity();

	cuisse();
}

void timer(int value) {
	glutPostRedisplay();   
	glutTimerFunc(refreshMills, timer, 0);
}

void reshape(GLsizei width, GLsizei height) { 
									
	if (height == 0)
	{
		height = 1;
	}

	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();            
								 
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);         
	glutInitDisplayMode(GLUT_DOUBLE); 
	glutInitWindowSize(640, 480);  
	glutInitWindowPosition(50, 50); 
	glutCreateWindow(titre);         
	glutDisplayFunc(display);      
	glutReshapeFunc(reshape);

	init();    
	glutTimerFunc(0, timer, 0);
	glutMainLoop();              
	return 0;
}


