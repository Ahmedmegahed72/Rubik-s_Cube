#define GLUT_DISABLE_ATEXIT_HACK
#define STB_IMAGE_IMPLEMENTATION  
#include <iostream>
#include <gl/stb_image.h>
#include <gl/glut.h>
#include <string>
#include <sstream>

using namespace std;

unsigned int texture;
int width, height, nrChannels;
unsigned char* dataa = NULL;
const int screenWidth = 640;
const int screenHeight = 480;
void load(int imgnum);

class wcPt3D		// definition of Point3 class
{
public:
	float x, y, z;

	wcPt3D()			// default constructor
	{
		x = 0.0; y = 0.0; z = 0.0;
	}
	wcPt3D(float x0, float y0, float z0)
	{
		x = x0; y = y0; z = z0;
	}

};

class Face
{
public:
	enum color { RED, ORANGE, BLUE, WHITE, YELLOW, GREEN };
	Face(color c) : face{ {c,c,c}, {c,c,c}, {c,c,c} } {}	// constructor
	color face[3][3];
	void draw()
	{
		glBegin(GL_QUADS);
		//00
		set_color(face[0][0]);
		glVertex3f(-.25 - .5, -.25 + 1, 1.0);
		glVertex3f(.25 - .5, -.25 + 1, 1.0);
		glVertex3f(.25 - .5, .25 + 1, 1.0);
		glVertex3f(-.25 - .5, .25 + 1, 1.0);

		//01
		set_color(face[0][1]);
		glVertex3f(-.25, -.25 + 1, 1.0);
		glVertex3f(.25, -.25 + 1, 1.0);
		glVertex3f(.25, .25 + 1, 1.0);
		glVertex3f(-.25, .25 + 1, 1.0);

		//02
		set_color(face[0][2]);
		glVertex3f(-.25 + .5, -.25 + 1, 1.0);
		glVertex3f(.25 + .5, -.25 + 1, 1.0);
		glVertex3f(.25 + .5, .25 + 1, 1.0);
		glVertex3f(-.25 + .5, .25 + 1, 1.0);

		//03
		set_color(face[1][0]);
		glVertex3f(-.25 - .5, -.25 + .5, 1.0);
		glVertex3f(.25 - .5, -.25 + .5, 1.0);
		glVertex3f(.25 - .5, .25 + .5, 1.0);
		glVertex3f(-.25 - .5, .25 + .5, 1.0);

		//04
		set_color(face[1][1]);
		glVertex3f(-.25, -.25 + .5, 1.0);
		glVertex3f(.25, -.25 + .5, 1.0);
		glVertex3f(.25, .25 + .5, 1.0);
		glVertex3f(-.25, .25 + .5, 1.0);

		//05
		set_color(face[1][2]);
		glVertex3f(-.25 + .5, -.25 + .5, 1.0);
		glVertex3f(.25 + .5, -.25 + .5, 1.0);
		glVertex3f(.25 + .5, .25 + .5, 1.0);
		glVertex3f(-.25 + .5, .25 + .5, 1.0);

		//06
		set_color(face[2][0]);
		glVertex3f(-.25 - .5, -.25, 1.0);
		glVertex3f(.25 - .5, -.25, 1.0);
		glVertex3f(.25 - .5, .25, 1.0);
		glVertex3f(-.25 - .5, .25, 1.0);

		//07
		set_color(face[2][1]);
		glVertex3f(-.25, -.25, 1.0);
		glVertex3f(.25, -.25, 1.0);
		glVertex3f(.25, .25, 1.0);
		glVertex3f(-.25, .25, 1.0);

		//08
		set_color(face[2][2]);
		glVertex3f(-.25 + .5, -.25, 1.0);
		glVertex3f(.25 + .5, -.25, 1.0);
		glVertex3f(.25 + .5, .25, 1.0);
		glVertex3f(-.25 + .5, .25, 1.0);
		glEnd();
		draw_border();
	}

private:

	void set_color(color c)
	{
		switch (c)
		{
		case RED: glColor3f(1.0, 0.0, 0.0); break;
		case ORANGE: glColor3f(1.0, 0.5, 0.0); break;
		case BLUE: glColor3f(0.0, 0.0, 1.0); break;
		case GREEN: glColor3f(0.0, 1.0, 0.0); break;
		case WHITE: glColor3f(1.0, 1.0, 1.0); break;
		case YELLOW: glColor3f(1.0, 1.0, 0.0); break;
		default: cout << "Error: invalid value for color\n"; break;
		}
	}

	void draw_border()
	{
		glColor3f(0.0, 0.0, 0.0);
		glLineWidth(3.5);
		glBegin(GL_LINE_LOOP);
		//00
		glVertex3f(-.25 - .5, -.25 + 1, 1.0);
		glVertex3f(.25 - .5, -.25 + 1, 1.0);
		glVertex3f(.25 - .5, .25 + 1, 1.0);
		glVertex3f(-.25 - .5, .25 + 1, 1.0);
		glEnd();
		glBegin(GL_LINE_LOOP);
		//01
		glVertex3f(-.25, -.25 + 1, 1.0);
		glVertex3f(.25, -.25 + 1, 1.0);
		glVertex3f(.25, .25 + 1, 1.0);
		glVertex3f(-.25, .25 + 1, 1.0);
		glEnd();
		glBegin(GL_LINE_LOOP);
		//02
		glVertex3f(-.25 + .5, -.25 + 1, 1.0);
		glVertex3f(.25 + .5, -.25 + 1, 1.0);
		glVertex3f(.25 + .5, .25 + 1, 1.0);
		glVertex3f(-.25 + .5, .25 + 1, 1.0);
		glEnd();
		glBegin(GL_LINE_LOOP);
		//03
		glVertex3f(-.25 - .5, -.25 + .5, 1.0);
		glVertex3f(.25 - .5, -.25 + .5, 1.0);
		glVertex3f(.25 - .5, .25 + .5, 1.0);
		glVertex3f(-.25 - .5, .25 + .5, 1.0);
		glEnd();
		glBegin(GL_LINE_LOOP);
		//04
		glVertex3f(-.25, -.25 + .5, 1.0);
		glVertex3f(.25, -.25 + .5, 1.0);
		glVertex3f(.25, .25 + .5, 1.0);
		glVertex3f(-.25, .25 + .5, 1.0);
		glEnd();
		glBegin(GL_LINE_LOOP);
		//05
		glVertex3f(-.25 + .5, -.25 + .5, 1.0);
		glVertex3f(.25 + .5, -.25 + .5, 1.0);
		glVertex3f(.25 + .5, .25 + .5, 1.0);
		glVertex3f(-.25 + .5, .25 + .5, 1.0);
		glEnd();
		glBegin(GL_LINE_LOOP);
		//06
		glVertex3f(-.25 - .5, -.25, 1.0);
		glVertex3f(.25 - .5, -.25, 1.0);
		glVertex3f(.25 - .5, .25, 1.0);
		glVertex3f(-.25 - .5, .25, 1.0);
		glEnd();
		glBegin(GL_LINE_LOOP);
		//07
		glVertex3f(-.25, -.25, 1.0);
		glVertex3f(.25, -.25, 1.0);
		glVertex3f(.25, .25, 1.0);
		glVertex3f(-.25, .25, 1.0);
		glEnd();
		glBegin(GL_LINE_LOOP);
		//08
		glVertex3f(-.25 + .5, -.25, 1.0);
		glVertex3f(.25 + .5, -.25, 1.0);
		glVertex3f(.25 + .5, .25, 1.0);
		glVertex3f(-.25 + .5, .25, 1.0);
		glEnd();
		glFlush();
	}
};

class Cube
{
public:
	Cube() :
		front(Face::RED), back(Face::ORANGE), left(Face::GREEN),
		right(Face::BLUE), top(Face::WHITE), bottom(Face::YELLOW) {}

	void draw()
	{
		// DRAW FRONT FACE
		glPushMatrix();
		cout << "Front: \n";
		front.draw();

		// DRAW RIGHT FACE
		glRotated(90, 0, 1, 0);
		glPushMatrix();
		//glRotated(180, 0, 1, 0);
		glTranslated(-.25, 0, -.25);
		cout << "Right: \n";
		right.draw();
		glPopMatrix();

		// DRAW BACK FACE
		glRotated(90, 0, 1, 0);
		glPushMatrix();
		glRotated(0, 0, 0, 1);
		glRotated(180, 0, 1, 0);
		glTranslated(0, 0, -1.5);
		cout << "Back: \n";
		back.draw();
		glPopMatrix();

		//DRAW LEFT FACE
		glRotated(90, 0, 1, 0);
		glPushMatrix();
		glTranslated(.25, 0, -.25);
		cout << "Left: \n";
		left.draw();
		glPopMatrix();

		// DRAW TOP FACE
		glRotated(-90, 1, 0, 0);
		glRotated(90, 0, 0, 1);
		glPushMatrix();
		glRotated(180, 1, 0, 0);
		glRotated(180, 0, 1, 0);
		glRotated(180, 0, 0, 1);
		glTranslated(0, -.75, 0.25);
		cout << "Top: \n";
		top.draw();
		glPopMatrix();

		// DRAW BOTTOM FACE
		glPushMatrix();
		glRotated(180, 0, 1, 0);
		glRotated(180, 0, 0, 1);
		glTranslated(0, -.25, -.75);
		cout << "Bottom: \n";
		bottom.draw();
		glPopMatrix();
		glPopMatrix();
	}

	void w()
	{
		cout << "\n UP TURN \n";
		Face::color temp[3];
		Face::color temp2[3][3];

		temp[0] = right.face[0][0];
		temp[1] = right.face[0][1];
		temp[2] = right.face[0][2];

		right.face[0][0] = back.face[0][0];
		right.face[0][1] = back.face[0][1];
		right.face[0][2] = back.face[0][2];

		back.face[0][0] = left.face[0][0];
		back.face[0][1] = left.face[0][1];
		back.face[0][2] = left.face[0][2];

		left.face[0][0] = front.face[0][0];
		left.face[0][1] = front.face[0][1];
		left.face[0][2] = front.face[0][2];

		front.face[0][0] = temp[0];
		front.face[0][1] = temp[1];
		front.face[0][2] = temp[2];

		temp2[0][0] = top.face[2][0];
		temp2[0][1] = top.face[1][0];
		temp2[0][2] = top.face[0][0];
		temp2[1][0] = top.face[2][1];
		temp2[1][1] = top.face[1][1];
		temp2[1][2] = top.face[0][1];
		temp2[2][0] = top.face[2][2];
		temp2[2][1] = top.face[1][2];
		temp2[2][2] = top.face[0][2];

		top.face[0][0] = temp2[0][0];
		top.face[0][1] = temp2[0][1];
		top.face[0][2] = temp2[0][2];
		top.face[1][0] = temp2[1][0];
		top.face[1][2] = temp2[1][2];
		top.face[2][0] = temp2[2][0];
		top.face[2][1] = temp2[2][1];
		top.face[2][2] = temp2[2][2];
	}

	void q()
	{
		Face::color temp[3];
		Face::color temp2[3][3];

		temp[0] = right.face[2][0];
		temp[1] = right.face[2][1];
		temp[2] = right.face[2][2];

		right.face[2][0] = front.face[2][0];
		right.face[2][1] = front.face[2][1];
		right.face[2][2] = front.face[2][2];

		front.face[2][0] = left.face[2][0];
		front.face[2][1] = left.face[2][1];
		front.face[2][2] = left.face[2][2];

		left.face[2][0] = back.face[2][0];
		left.face[2][1] = back.face[2][1];
		left.face[2][2] = back.face[2][2];

		back.face[2][0] = temp[0];
		back.face[2][1] = temp[1];
		back.face[2][2] = temp[2];

		temp2[0][0] = bottom.face[2][0];
		temp2[0][1] = bottom.face[1][0];
		temp2[0][2] = bottom.face[0][0];
		temp2[1][0] = bottom.face[2][1];
		temp2[1][1] = bottom.face[1][1];
		temp2[1][2] = bottom.face[0][1];
		temp2[2][0] = bottom.face[2][2];
		temp2[2][1] = bottom.face[1][2];
		temp2[2][2] = bottom.face[0][2];

		bottom.face[0][0] = temp2[0][0];
		bottom.face[0][1] = temp2[0][1];
		bottom.face[0][2] = temp2[0][2];
		bottom.face[1][0] = temp2[1][0];
		bottom.face[1][2] = temp2[1][2];
		bottom.face[2][0] = temp2[2][0];
		bottom.face[2][1] = temp2[2][1];
		bottom.face[2][2] = temp2[2][2];
	}

	void s()
	{
		cout << "\n RIGHT TURN \n";
		Face::color temp[3];
		Face::color temp2[3][3];

		//ALMOST POSITIVE THIS IS RIGHT
		temp[0] = bottom.face[0][2];
		temp[1] = bottom.face[1][2];
		temp[2] = bottom.face[2][2];

		bottom.face[0][2] = back.face[2][0];
		bottom.face[1][2] = back.face[1][0];
		bottom.face[2][2] = back.face[0][0];

		back.face[2][0] = top.face[0][2];
		back.face[1][0] = top.face[1][2];
		back.face[0][0] = top.face[2][2];

		top.face[0][2] = front.face[0][2];
		top.face[1][2] = front.face[1][2];
		top.face[2][2] = front.face[2][2];

		front.face[0][2] = temp[0];
		front.face[1][2] = temp[1];
		front.face[2][2] = temp[2];

		temp2[0][0] = right.face[2][0];
		temp2[0][1] = right.face[1][0];
		temp2[0][2] = right.face[0][0];
		temp2[1][0] = right.face[2][1];
		temp2[1][1] = right.face[1][1];
		temp2[1][2] = right.face[0][1];
		temp2[2][0] = right.face[2][2];
		temp2[2][1] = right.face[1][2];
		temp2[2][2] = right.face[0][2];

		right.face[0][0] = temp2[0][0];
		right.face[0][1] = temp2[0][1];
		right.face[0][2] = temp2[0][2];
		right.face[1][0] = temp2[1][0];
		right.face[1][2] = temp2[1][2];
		right.face[2][0] = temp2[2][0];
		right.face[2][1] = temp2[2][1];
		right.face[2][2] = temp2[2][2];
	}

	void a()
	{
		Face::color temp[3];
		Face::color temp2[3][3];

		temp[0] = front.face[0][0];
		temp[1] = front.face[1][0];
		temp[2] = front.face[2][0];

		front.face[0][0] = top.face[0][0];
		front.face[1][0] = top.face[1][0];
		front.face[2][0] = top.face[2][0];

		top.face[0][0] = back.face[2][2];
		top.face[1][0] = back.face[1][2];
		top.face[2][0] = back.face[0][2];

		back.face[2][2] = bottom.face[0][0];
		back.face[1][2] = bottom.face[1][0];
		back.face[0][2] = bottom.face[2][0];

		bottom.face[0][0] = temp[0];
		bottom.face[1][0] = temp[1];
		bottom.face[2][0] = temp[2];

		temp2[0][0] = left.face[2][0];
		temp2[0][1] = left.face[1][0];
		temp2[0][2] = left.face[0][0];
		temp2[1][0] = left.face[2][1];
		temp2[1][1] = left.face[1][1];
		temp2[1][2] = left.face[0][1];
		temp2[2][0] = left.face[2][2];
		temp2[2][1] = left.face[1][2];
		temp2[2][2] = left.face[0][2];

		left.face[0][0] = temp2[0][0];
		left.face[0][1] = temp2[0][1];
		left.face[0][2] = temp2[0][2];
		left.face[1][0] = temp2[1][0];
		left.face[1][2] = temp2[1][2];
		left.face[2][0] = temp2[2][0];
		left.face[2][1] = temp2[2][1];
		left.face[2][2] = temp2[2][2];

	}

	void f()
	{
		Face::color temp[3];
		Face::color temp2[3][3];
		temp[0] = right.face[0][0];
		temp[1] = right.face[1][0];
		temp[2] = right.face[2][0];

		right.face[0][0] = top.face[2][0];
		right.face[1][0] = top.face[2][1];
		right.face[2][0] = top.face[2][2];

		top.face[2][0] = left.face[2][2];
		top.face[2][1] = left.face[1][2];
		top.face[2][2] = left.face[0][2];

		left.face[2][2] = bottom.face[0][2];
		left.face[1][2] = bottom.face[0][1];
		left.face[0][2] = bottom.face[0][0];

		bottom.face[0][0] = temp[2];
		bottom.face[0][1] = temp[1];
		bottom.face[0][2] = temp[0];

		temp2[0][0] = front.face[2][0];
		temp2[0][1] = front.face[1][0];
		temp2[0][2] = front.face[0][0];
		temp2[1][0] = front.face[2][1];
		temp2[1][1] = front.face[1][1];
		temp2[1][2] = front.face[0][1];
		temp2[2][0] = front.face[2][2];
		temp2[2][1] = front.face[1][2];
		temp2[2][2] = front.face[0][2];

		front.face[0][0] = temp2[0][0];
		front.face[0][1] = temp2[0][1];
		front.face[0][2] = temp2[0][2];
		front.face[1][0] = temp2[1][0];
		front.face[1][2] = temp2[1][2];
		front.face[2][0] = temp2[2][0];
		front.face[2][1] = temp2[2][1];
		front.face[2][2] = temp2[2][2];
	}

	void flip_up()
	{
		Face::color temp[3][3];
		Face::color temp2[3][3];

		temp[0][0] = top.face[0][0];
		temp[0][1] = top.face[0][1];
		temp[0][2] = top.face[0][2];
		temp[1][0] = top.face[1][0];
		temp[1][1] = top.face[1][1];
		temp[1][2] = top.face[1][2];
		temp[2][0] = top.face[2][0];
		temp[2][1] = top.face[2][1];
		temp[2][2] = top.face[2][2];

		top.face[0][0] = front.face[0][0];
		top.face[0][1] = front.face[0][1];
		top.face[0][2] = front.face[0][2];
		top.face[1][0] = front.face[1][0];
		top.face[1][1] = front.face[1][1];
		top.face[1][2] = front.face[1][2];
		top.face[2][0] = front.face[2][0];
		top.face[2][1] = front.face[2][1];
		top.face[2][2] = front.face[2][2];

		front.face[0][0] = bottom.face[0][0];
		front.face[0][1] = bottom.face[0][1];
		front.face[0][2] = bottom.face[0][2];
		front.face[1][0] = bottom.face[1][0];
		front.face[1][1] = bottom.face[1][1];
		front.face[1][2] = bottom.face[1][2];
		front.face[2][0] = bottom.face[2][0];
		front.face[2][1] = bottom.face[2][1];
		front.face[2][2] = bottom.face[2][2];

		bottom.face[0][0] = back.face[2][2];
		bottom.face[0][1] = back.face[2][1];
		bottom.face[0][2] = back.face[2][0];
		bottom.face[1][0] = back.face[1][2];
		bottom.face[1][1] = back.face[1][1];
		bottom.face[1][2] = back.face[1][0];
		bottom.face[2][0] = back.face[0][2];
		bottom.face[2][1] = back.face[0][1];
		bottom.face[2][2] = back.face[0][0];

		back.face[0][0] = temp[2][2];
		back.face[0][1] = temp[2][1];
		back.face[0][2] = temp[2][0];
		back.face[1][0] = temp[1][2];
		back.face[1][1] = temp[1][1];
		back.face[1][2] = temp[1][0];
		back.face[2][0] = temp[0][2];
		back.face[2][1] = temp[0][1];
		back.face[2][2] = temp[0][0];

		// SHIFT LEFT FACE
		for (int i = 0; i < 3; ++i)
		{
			temp2[0][0] = left.face[2][0];
			temp2[0][1] = left.face[1][0];
			temp2[0][2] = left.face[0][0];
			temp2[1][0] = left.face[2][1];
			temp2[1][1] = left.face[1][1];
			temp2[1][2] = left.face[0][1];
			temp2[2][0] = left.face[2][2];
			temp2[2][1] = left.face[1][2];
			temp2[2][2] = left.face[0][2];

			left.face[0][0] = temp2[0][0];
			left.face[0][1] = temp2[0][1];
			left.face[0][2] = temp2[0][2];
			left.face[1][0] = temp2[1][0];
			left.face[1][2] = temp2[1][2];
			left.face[2][0] = temp2[2][0];
			left.face[2][1] = temp2[2][1];
			left.face[2][2] = temp2[2][2];
		}

		//SHIFT RIGHT FACE
		temp2[0][0] = right.face[2][0];
		temp2[0][1] = right.face[1][0];
		temp2[0][2] = right.face[0][0];
		temp2[1][0] = right.face[2][1];
		temp2[1][1] = right.face[1][1];
		temp2[1][2] = right.face[0][1];
		temp2[2][0] = right.face[2][2];
		temp2[2][1] = right.face[1][2];
		temp2[2][2] = right.face[0][2];

		right.face[0][0] = temp2[0][0];
		right.face[0][1] = temp2[0][1];
		right.face[0][2] = temp2[0][2];
		right.face[1][0] = temp2[1][0];
		right.face[1][2] = temp2[1][2];
		right.face[2][0] = temp2[2][0];
		right.face[2][1] = temp2[2][1];
		right.face[2][2] = temp2[2][2];
	}

	void flip_down()
	{
		flip_up();
		flip_up();
		flip_up();
	}

	void rotate_clockwise()
	{
		Face::color temp[3][3];
		Face::color temp2[3][3];

		temp[0][0] = front.face[0][0];
		temp[0][1] = front.face[0][1];
		temp[0][2] = front.face[0][2];
		temp[1][0] = front.face[1][0];
		temp[1][1] = front.face[1][1];
		temp[1][2] = front.face[1][2];
		temp[2][0] = front.face[2][0];
		temp[2][1] = front.face[2][1];
		temp[2][2] = front.face[2][2];

		front.face[0][0] = right.face[0][0];
		front.face[0][1] = right.face[0][1];
		front.face[0][2] = right.face[0][2];
		front.face[1][0] = right.face[1][0];
		front.face[1][1] = right.face[1][1];
		front.face[1][2] = right.face[1][2];
		front.face[2][0] = right.face[2][0];
		front.face[2][1] = right.face[2][1];
		front.face[2][2] = right.face[2][2];

		right.face[0][0] = back.face[0][0];
		right.face[0][1] = back.face[0][1];
		right.face[0][2] = back.face[0][2];
		right.face[1][0] = back.face[1][0];
		right.face[1][1] = back.face[1][1];
		right.face[1][2] = back.face[1][2];
		right.face[2][0] = back.face[2][0];
		right.face[2][1] = back.face[2][1];
		right.face[2][2] = back.face[2][2];

		back.face[0][0] = left.face[0][0];
		back.face[0][1] = left.face[0][1];
		back.face[0][2] = left.face[0][2];
		back.face[1][0] = left.face[1][0];
		back.face[1][1] = left.face[1][1];
		back.face[1][2] = left.face[1][2];
		back.face[2][0] = left.face[2][0];
		back.face[2][1] = left.face[2][1];
		back.face[2][2] = left.face[2][2];

		left.face[0][0] = temp[0][0];
		left.face[0][1] = temp[0][1];
		left.face[0][2] = temp[0][2];
		left.face[1][0] = temp[1][0];
		left.face[1][1] = temp[1][1];
		left.face[1][2] = temp[1][2];
		left.face[2][0] = temp[2][0];
		left.face[2][1] = temp[2][1];
		left.face[2][2] = temp[2][2];

		//ROTATE TOP FACE
		temp2[0][0] = top.face[2][0];
		temp2[0][1] = top.face[1][0];
		temp2[0][2] = top.face[0][0];
		temp2[1][0] = top.face[2][1];
		temp2[1][1] = top.face[1][1];
		temp2[1][2] = top.face[0][1];
		temp2[2][0] = top.face[2][2];
		temp2[2][1] = top.face[1][2];
		temp2[2][2] = top.face[0][2];

		top.face[0][0] = temp2[0][0];
		top.face[0][1] = temp2[0][1];
		top.face[0][2] = temp2[0][2];
		top.face[1][0] = temp2[1][0];
		top.face[1][2] = temp2[1][2];
		top.face[2][0] = temp2[2][0];
		top.face[2][1] = temp2[2][1];
		top.face[2][2] = temp2[2][2];

		//ROTATE BOTTOM 
		for (int i = 0; i < 3; ++i)
		{
			temp2[0][0] = bottom.face[2][0];
			temp2[0][1] = bottom.face[1][0];
			temp2[0][2] = bottom.face[0][0];
			temp2[1][0] = bottom.face[2][1];
			temp2[1][1] = bottom.face[1][1];
			temp2[1][2] = bottom.face[0][1];
			temp2[2][0] = bottom.face[2][2];
			temp2[2][1] = bottom.face[1][2];
			temp2[2][2] = bottom.face[0][2];

			bottom.face[0][0] = temp2[0][0];
			bottom.face[0][1] = temp2[0][1];
			bottom.face[0][2] = temp2[0][2];
			bottom.face[1][0] = temp2[1][0];
			bottom.face[1][2] = temp2[1][2];
			bottom.face[2][0] = temp2[2][0];
			bottom.face[2][1] = temp2[2][1];
			bottom.face[2][2] = temp2[2][2];
		}
	}

	void rotate_counter_clockwise()
	{
		rotate_clockwise();
		rotate_clockwise();
		rotate_clockwise();
	}

private:
	Face front, back, left, right, top, bottom;
};

Cube cube;

wcPt3D eye0(1.0, 1.0, 2.0);
wcPt3D eye = eye0;
wcPt3D lookAt0(0.0, 0.0, 0.0);
wcPt3D lookAt = lookAt0;
wcPt3D up(0.0, 1.0, 0.0);

GLdouble windowHeight = 2.0;
GLfloat angle = 90.0;

void init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glClearColor(1.0, 1.0, 1.0, 0.0);	//  Set display window color to white
	//glClearColor(1.0, 1.0, 1.0, 0.0);	//  Set display window color to black
}

void myDisplay(void)
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);


	double winHt = windowHeight;
	double aspect = float(screenWidth) / float(screenHeight);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-winHt * aspect, winHt * aspect, -winHt, winHt, 0.5, 100.0);
	gluLookAt(eye.x, eye.y, eye.z, //position of x, y, z
		lookAt.x, lookAt.y, lookAt.z, // right or lift
		up.x, up.y, up.z); // up or down
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	cube.draw();
	load(1);
	glBegin(GL_QUADS);

	glColor3f(1, 1, 1);     // Green
	glTexCoord2d(2.0f, 0.0f);
	glVertex3f(4.0f, -.27, -3.0f);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(-8.0f, -.27, -3.0f);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(-8.0f, -.27, 3.0f);
	glTexCoord2d(2.0f, 1.0f);
	glVertex3f(4.0f, -.27, 3.0f);
	glEnd();
	glFlush();
}

void reshapeFcn(int newWidth, int newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)newWidth, 0.0, (GLdouble)newHeight);
	glClear(GL_COLOR_BUFFER_BIT);
}

void mySpecialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
		eye.x -= 0.125;
	else if (key == GLUT_KEY_RIGHT)
		eye.x += 0.125;
	else if (key == GLUT_KEY_UP)
		eye.y += 0.125;
	else if (key == GLUT_KEY_DOWN)
		eye.y -= 0.125;
	else if (key == GLUT_KEY_PAGE_DOWN)
		eye.z -= 0.125;
	else if (key == GLUT_KEY_PAGE_UP)
		eye.z += 0.125;
	else if (key == GLUT_KEY_HOME)
	{
		eye = eye0;
	}

	glutPostRedisplay();
}

void myKeyboard(unsigned char key, int x, int y)
{
	if (key == 'w' || key == 'W')
	{
		cube.w();
		myDisplay();
	}

	else if (key == 'q' || key == 'Q')
	{
		cube.q();
		myDisplay();
	}

	else if (key == 'a' || key == 'A')
	{
		cube.a();
		myDisplay();
	}

	else if (key == 's' || key == 'S')
	{
		cube.s();
		myDisplay();
	}

	else if (key == 'z' || key == 'Z')
	{
		cube.rotate_clockwise();
		myDisplay();
	}

	else if (key == 'x' || key == 'X')
	{
		cube.rotate_counter_clockwise();
		myDisplay();
	}
	else if (key == 'c' || key == 'C')
	{
		cube.flip_down();
		myDisplay();
	}

	else if (key == 'v' || key == 'V')
	{
		cube.flip_up();
		myDisplay();
	}

	else if (key == 'f' || key == 'F')
	{
		cube.f();
		myDisplay();
	}

	glutPostRedisplay();
}
void load(int imgnum) {
	if (imgnum == 1) {

		dataa = stbi_load("wall.bmp", &width, &height, &nrChannels, 0);
		if (dataa)
		{
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, dataa);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(dataa);
	}
}




void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(screenWidth, screenHeight);
	glutCreateWindow("Simple Cube");
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(reshapeFcn);
	glutSpecialFunc(mySpecialKeyboard);
	glutKeyboardFunc(myKeyboard);
	init();
	glutMainLoop();
}
