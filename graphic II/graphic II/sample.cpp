#include <iostream>
#include <math.h>
#include <GL\glut.h>
#include <vector>

GLUquadricObj* quadricPtr = gluNewQuadric();
float P[3][40][40] = { 0 };
float x = -10, z = 0, Z = -10, a = 8.0, b = 11.0, c = 0.0;
int Pnx = 0, Pny = 0, menu = 10;
bool A = true;
GLfloat ambient[4] = { 0.5, 0.5, 0.5, 1.0 }, angle = 0.0, X = 0, Y = -5;
GLfloat diffuse[4] = { 1.0, 1.0, 0.0, 1.0 };
GLfloat specular[4] = { 1.0, 1.0, 1.0, 1.0 };

struct vector3D{
	float x, y, z;
};

struct vector3D V1 = { 0.0, 0.0, 0.0 }, V2 = { 0.0, 0.0, 0.0 }, V3 = { 0.0, 0.0, 0.0 };
struct vector3D HORV[82][41];

float L(float A, float B)
{
	float a = -2 * pow(A, 2);
	return(pow(1.5, a) * pow(B,4));
}

struct vector3D normale(struct vector3D P1, struct vector3D P2, struct vector3D P3)
{
	float a, b, c;
	a = ((P2.y - P1.y)*(P3.z - P1.z) - (P2.z - P1.z)*(P3.y - P1.y));
	b = ((P2.z - P1.z)*(P3.x - P1.x) - (P2.x - P1.x)*(P3.z - P1.z));
	c = ((P2.x - P1.x)*(P3.y - P1.y) - (P2.y - P1.y)*(P3.x - P1.x));
	struct vector3D k = { a, b, c };
	return k;
}

void pointdraw()
{
	for (float j = Z; j < 10; j += 0.5)
	{
		if (A)
		{
			if (z >= 2.1)
				A = false;
			z += 0.06;
		}
		else
		{
			if (z >= 0)
				z -= 0.06;
			else
				z = 0;
		}
		for (float i = x; i < 10; i += 0.5)
		{
			float B[3] = { i, L(i, z), j };
			for (int k = 0; k < 3; k++)
			{
				P[k][Pnx][Pny] = B[k];
			}
			Pnx++;
			if (Pnx >= 40)
				Pnx = 0;
		}
		Pny++;
	}
}

void drawnormal()
{
	for (int i = 0; i < 39; i++)
	{
		for (int j = 0; j < 39; j++)
		{
			V1.x = P[0][i][j]; V1.y = P[1][i][j]; V1.z = P[2][i][j];
			V2.x = P[0][i + 1][j]; V2.y = P[1][i + 1][j]; V2.z = P[2][i + 1][j];
			V3.x = P[0][i][j + 1]; V3.y = P[1][i][j + 1]; V3.z = P[2][i][j + 1];
			struct vector3D K = normale(V2, V1, V3);
			HORV[2 * i + 2][j + 1] = K;

			V1.x = P[0][i + 1][j + 1]; V1.y = P[1][i + 1][j + 1]; V1.z = P[2][i + 1][j + 1];
			V2.x = P[0][i + 1][j]; V2.y = P[1][i + 1][j]; V2.z = P[2][i + 1][j];
			V3.x = P[0][i][j + 1]; V3.y = P[1][i][j + 1]; V3.z = P[2][i][j + 1];
			K = normale(V1, V2, V3);
			HORV[2 * i + 2][j + 2] = K;
		}
	}
}

struct vector3D P_NORMAL(int u, int v)
{
	int n = 0;
	float AA=0.0, BB=0.0, CC=0.0;
	for (int i = v; i <= v + 1; i++)
	{
		for (int j = u; j <= u + 2; j++)
		{
			if (HORV[i][j].y > 0)
			{
				n++;
				AA += HORV[i][j].x;
				BB += HORV[i][j].y;
				CC += HORV[i][j].z;
			}
		}
		u++;
	}
	AA /= n;
	BB /= n;
	CC /= n;
	struct vector3D SS = { AA, BB, CC };
	return SS;
}

void mydisplay()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	GLfloat light_pos[4] = { a, b, c, 0 };
	glColor3f(1.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glEnable(GL_LIGHT0);
	glPushMatrix();
	glRotatef(angle, 0, 1, 0);
	//glutSolidTeapot(5);
	switch (menu)
	{
		case 10:
			glDisable(GL_LIGHTING);
			glLineWidth(0.2);
			for (int i = 0; i < 39; i++)
			{
				for (int j = 0; j < 39; j++)
				{
					glBegin(GL_LINE_STRIP);
					glVertex3f(P[0][i][j], P[1][i][j], P[2][i][j]);
					glVertex3f(P[0][i + 1][j], P[1][i + 1][j], P[2][i + 1][j]);
					glVertex3f(P[0][i + 1][j + 1], P[1][i + 1][j + 1], P[2][i + 1][j + 1]);
					glVertex3f(P[0][i][j + 1], P[1][i][j + 1], P[2][i][j + 1]);
					glVertex3f(P[0][i][j], P[1][i][j], P[2][i][j]);
					glVertex3f(P[0][i + 1][j + 1], P[1][i + 1][j + 1], P[2][i + 1][j + 1]);
					glEnd();
				}
			}
			break;
		case 11:
			glEnable(GL_LIGHTING);
			for (int i = 0; i < 39; i++)
			{
				for (int j = 0; j < 39; j++)
				{
					glBegin(GL_TRIANGLES);
					V1.x = P[0][i][j]; V1.y = P[1][i][j]; V1.z = P[2][i][j];
					V2.x = P[0][i + 1][j]; V2.y = P[1][i + 1][j]; V2.z = P[2][i + 1][j];
					V3.x = P[0][i][j + 1]; V3.y = P[1][i][j + 1]; V3.z = P[2][i][j + 1];
					struct vector3D K = normale(V2, V1, V3);
					glNormal3f(K.x, K.y, K.z);
					glVertex3f(P[0][i][j], P[1][i][j], P[2][i][j]);
					glVertex3f(P[0][i + 1][j], P[1][i + 1][j], P[2][i + 1][j]);
					glVertex3f(P[0][i][j + 1], P[1][i][j + 1], P[2][i][j + 1]);


					V1.x = P[0][i + 1][j + 1]; V1.y = P[1][i + 1][j + 1]; V1.z = P[2][i + 1][j + 1];
					V2.x = P[0][i + 1][j]; V2.y = P[1][i + 1][j]; V2.z = P[2][i + 1][j];
					V3.x = P[0][i][j + 1]; V3.y = P[1][i][j + 1]; V3.z = P[2][i][j + 1];
					K = normale(V1, V2, V3);
					glNormal3f(K.x, K.y, K.z);
					glVertex3f(P[0][i + 1][j + 1], P[1][i + 1][j + 1], P[2][i + 1][j + 1]);
					glVertex3f(P[0][i + 1][j], P[1][i + 1][j], P[2][i + 1][j]);
					glVertex3f(P[0][i][j + 1], P[1][i][j + 1], P[2][i][j + 1]);
					glEnd();
				}
			}
			break;
		case 12:
			drawnormal();
			glEnable(GL_LIGHTING);
			for (int i = 0; i < 39; i++)
			{
				for (int j = 0; j < 39; j++)
				{
					glBegin(GL_TRIANGLES);
					struct vector3D K = P_NORMAL(i, j);
					glNormal3f(K.x, K.y, K.z);
					glVertex3f(P[0][i][j], P[1][i][j], P[2][i][j]);
					K = P_NORMAL(i + 1, j);
					glNormal3f(K.x, K.y, K.z);
					glVertex3f(P[0][i + 1][j], P[1][i + 1][j], P[2][i + 1][j]);
					K = P_NORMAL(i, j + 1);
					glNormal3f(K.x, K.y, K.z);
					glVertex3f(P[0][i][j + 1], P[1][i][j + 1], P[2][i][j + 1]);

					K = P_NORMAL(i + 1, j + 1);
					glNormal3f(K.x, K.y, K.z);
					glVertex3f(P[0][i + 1][j + 1], P[1][i + 1][j + 1], P[2][i + 1][j + 1]);
					K = P_NORMAL(i + 1, j);
					glNormal3f(K.x, K.y, K.z);
					glVertex3f(P[0][i + 1][j], P[1][i + 1][j], P[2][i + 1][j]);
					K = P_NORMAL(i, j + 1);
					glNormal3f(K.x, K.y, K.z);
					glVertex3f(P[0][i][j + 1], P[1][i][j + 1], P[2][i][j + 1]);
					glEnd();
				}
			}
	}
	glPopMatrix();
	
	glFlush();
}



void IDLE()
{
	angle += 0.05;
	if (angle >= 360)
		angle -= 360;
	glutPostRedisplay();
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-200.0, 200.0, -200.0, 200.0, 50.0, 200.0);
	glOrtho(-20, 20, -20, 30, 0, 100);
	gluLookAt(15, 40, 10, 0, 15, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	gluQuadricDrawStyle(quadricPtr, GLU_FILL);
	glShadeModel(GL_SMOOTH);
	gluQuadricNormals(quadricPtr, GLU_SMOOTH);
}
void processMenuEvents(int option)
{
	if (option == 2)
		exit(1);
}
void subMenuEvents(int option)
{
	switch (option)
	{
	case 10:
		menu = 10;
		break;
	case 11:
		menu = 11;
		break;
	case 12:
		menu = 12;
		break;
	}
}

void createGLUTMenus()
{
	int sub_Menu = glutCreateMenu(subMenuEvents);
	glutAddMenuEntry("wire-frame", 10);
	glutAddMenuEntry("flat", 11);
	glutAddMenuEntry("smooth shading", 12);

	int menu;
	menu = glutCreateMenu(processMenuEvents);
	glutAddSubMenu("µe­·", sub_Menu);
	glutAddMenuEntry("QUIT", 2);

	glutAttachMenu(GLUT_RIGHT_BUTTON);


}

void main(int argc, char** argv)
{
	glutInitWindowSize(700, 700);
	glutCreateWindow("sample");
	glutDisplayFunc(mydisplay);
	glutIdleFunc(IDLE);
	createGLUTMenus();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
	for (int d = 0; d < 82; d++)//normal vector ªì©l
	{
		for (int y = 0; y < 41; y++)
		{
			HORV[d][y].y = -1;
		}
	}
	pointdraw();
	init();

	glutMainLoop();
}