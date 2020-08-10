#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <GL\glut.h>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

double MASS = 100, SIZE = 10, V = 50, angle = 70, G = 9.8, t = 0.0, s = 10;

struct vector3D
{
	double x, y, z;
};

struct vector4D
{
	double matrix[4];
};

struct matrix3D/***/
{
	double matrix[10][10] = { 0 };
};

struct quaternions
{
	double w;
	vector3D v;
};

struct object
{
	vector3D position, v, acceleration, speed = { 0,0,0 };
	double uk;
	int mass, size, angle;
}obj,obj_slide;
double height;
double horizontal;

vector3D P = { 1.0,2.0,3.0 }, Q = { 10.0,10.0,10.0 }, cubepos = {0.0,0.0,10.0};
vector3D crossVector{ 0.0,0.0,0.0 }, plant_N = { 0,0,-1 };
int cube_size = 6;
GLUquadricObj* quadricPtr = gluNewQuadric();
//¦±½u
vector3D P1 = { 0,0,0 }, P2 = { 5,8,3 }, V1{ 1,0,0 }, V2{ -1,0,0 };
//
quaternions q1, q2, q3;

inline vector3D vadd(vector3D v, vector3D u)
{
	vector3D s;
	s.x = v.x + u.x;
	s.y = v.y + u.y;
	s.z = v.z + u.z;
	return s;
}

vector3D vsub(vector3D v, vector3D u)
{
	vector3D s;
	s.x = v.x - u.x;
	s.y = v.y - u.y;
	s.z = v.z - u.z;
	return s;
}

inline vector3D valuemulv(double w, vector3D q)
{
	q.x = q.x*w;
	q.y = q.y*w;
	q.z = q.z*w;
	return q;
}

quaternions addition(quaternions p, quaternions q)
{
	quaternions sum;
	sum.w = p.w + q.w;
	sum.v = vadd(p.v, q.v);
	return sum;
}

quaternions subtraction(quaternions p, quaternions q)
{
	quaternions sub;
	sub.w = p.w - q.w;
	sub.v = vsub(p.v, q.v);
	return sub;
}

double matrixdet(matrix3D m, int n)/***/
{
	double det, ratio;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (j > i)
			{
				ratio = m.matrix[j][i] / m.matrix[i][i];
				for (int k = 0; k < n; k++)
				{
					m.matrix[j][k] -= ratio * m.matrix[i][k];
				}
			}
		}
	}
	det = 1; //storage for determinant
	for (int i = 0; i < n; i++)
		det *= m.matrix[i][i];
	return det;
}

matrix3D matrixinv(matrix3D m, int n)
{
	int i, j, k;
	double ratio, a;
	for (i = 0; i < n; i++)
	{
		for (j = n; j < 2 * n; j++)
		{
			if (i == (j - n))
				m.matrix[i][j] = 1.0;
			else
				m.matrix[i][j] = 0.0;
		}
	}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (i != j) {
				ratio = m.matrix[j][i] / m.matrix[i][i];
				for (k = 0; k < 2 * n; k++)
				{
					m.matrix[j][k] -= ratio * m.matrix[i][k];
				}
			}
		}
	}
	for (i = 0; i < n; i++)
	{
		a = m.matrix[i][i];
		for (j = 0; j < 2 * n; j++)
		{
			m.matrix[i][j] /= a;
		}
	}
	return m;
}

double length(vector3D v)
{
	double leng = 0;
	leng = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
	return leng;
}

vector3D normalize(vector3D v)
{
	double leng = 0;
	leng = length(v);
	if (leng - 0 < 1e-5)
		return v;
	else
	{
		v.x = v.x / leng;
		v.y = v.y / leng;
		v.z = v.z / leng;
		return v;
	}
}

double dot(vector3D v, vector3D u)
{
	double leng = 0;
	leng = v.x*u.x + v.y*u.y + v.z*u.z;
	return leng;
}

vector3D ptov(vector3D v, vector3D u)
{
	vector3D y;
	y.x = v.x - u.x;
	y.y = v.y - u.y;
	y.z = v.z - u.z;
	return y;
}

vector3D cross(vector3D v, vector3D u)
{
	vector3D n;
	n.x = v.y*u.z - v.z*u.y;
	n.y = v.z*u.x - v.x*u.z;
	n.z = v.x*u.y - v.y*u.x;
	return n;
}

double magnitude(quaternions p)
{
	double n;
	n = sqrt(p.w*p.w + length(p.v)*length(p.v));
	return n;
}

quaternions multiplication(quaternions p, quaternions q)
{
	quaternions mul;
	mul.w = p.w*q.w - dot(p.v, q.v);
	mul.v = vadd(vadd(valuemulv(q.w, p.v), valuemulv(p.w, q.v)), cross(p.v, q.v));
	return mul;
}

quaternions normalization(quaternions p)
{
	double f = magnitude(p);
	quaternions s;
	s.w = p.w / f;
	s.v.x = p.v.x / f;
	s.v.y = p.v.y / f;
	s.v.z = p.v.z / f;
	return s;
}

quaternions conjugate(quaternions p)
{
	quaternions q;
	q.w = p.w;
	q.v.x = -p.v.x;
	q.v.y = -p.v.y;
	q.v.z = -p.v.z;
	return q;
}

quaternions inverse(quaternions p)
{
	double f = magnitude(p)*magnitude(p);
	quaternions q = conjugate(p), s;
	s.w = q.w / f;
	s.v.x = q.v.x / f;
	s.v.y = q.v.y / f;
	s.v.z = q.v.z / f;
	return s;
}

quaternions division(quaternions p, quaternions q)
{
	quaternions t;
	double s = p.w / q.w;
	t.w = (s + q.v.x*p.v.x + q.v.y*p.v.y + q.v.z*p.v.z) / (magnitude(q)*magnitude(q));
	t.v.x = (s - q.v.x*p.v.x - q.v.y*p.v.y + q.v.z*p.v.z) / (magnitude(q)*magnitude(q));
	t.v.y = (s + q.v.x*p.v.x - q.v.y*p.v.y - q.v.z*p.v.z) / (magnitude(q)*magnitude(q));
	t.v.z = (s - q.v.x*p.v.x + q.v.y*p.v.y - q.v.z*p.v.z) / (magnitude(q)*magnitude(q));
	return t;
}

void quatout(quaternions p)
{
	cout << p.w << " " << p.v.x << " " << p.v.y << " " << p.v.z << endl;
}

int Collision_Detection(vector3D N, vector3D point1, vector3D point2)
{
	double n = 0;
	point2.z -= cube_size / 2;
	vector3D fn = { -N.x, -N.y, -N.z };
	n = dot(N, point1)+dot(fn, point2);
	return n;
}

double quat_dot(quaternions q1, quaternions q2)
{
	double dotproduct = q1.w*q2.w + dot(q1.v, q2.v);
	return dotproduct;
}

quaternions good(quaternions bb)
{
	double rad = (bb.w * M_PI / 180) / 2;
	bb.w = cos(rad);
	bb.v.x *= sin(rad);
	bb.v.y *= sin(rad);
	bb.v.z *= sin(rad);
	return bb;
}

quaternions Slerp(quaternions q1, quaternions q2, double lambda)
{
	quaternions qr;
	double dotproduct = quat_dot(q1, q2), theta, st, sut, sout, coeff1, coeff2;
	theta = (double)acos(dotproduct);
	if (theta < 0.0)theta = -theta;
	st = (double)sin(theta);
	sut = (double)sin(lambda*theta);
	sout = (double)sin((1 - lambda)*theta);
	coeff1 = sout / st;
	coeff2 = sut / st;
	qr.v = vadd(valuemulv(coeff1, q1.v), valuemulv(coeff2, q2.v));
	qr.w = coeff1*q1.w + coeff2*q2.w;
	qr = normalization(qr);
	return qr;
}

double m[4][4];
void ExportToMatrix(quaternions u, double mat[4][4])
{
	double wx, wy, wz, xx, yy, yz, xy, xz, zz;
	xx = u.v.x * u.v.x;
	xy = u.v.x * u.v.y;
	xz = u.v.x * u.v.z;
	yy = u.v.y * u.v.y;
	zz = u.v.z * u.v.z;
	yz = u.v.y * u.v.z;

	wx = u.w * u.v.x;
	wy = u.w * u.v.y;
	wz = u.w * u.v.z;

	mat[0][0] = 1.0f - 2.0f*(yy + zz);
	mat[1][0] = 2.0f*(xy - wz);
	mat[2][0] = 2.0f*(xz + wy);
	mat[3][0] = 0.0;

	mat[0][1] = 2.0f*(xy + wz);
	mat[1][1] = 1.0f - 2.0f*(xx + zz);
	mat[2][1] = 2.0f*(yz - wx);
	mat[3][1] = 0.0;

	mat[0][2] = 2.0f*(xz - wy);
	mat[1][2] = 2.0f*(yz + wx);
	mat[2][2] = 1.0f - 2.0f*(xx + yy);
	mat[3][2] = 0.0;

	mat[0][3] = 0;
	mat[1][3] = 0;
	mat[2][3] = 0;
	mat[3][3] = 1;
}

vector3D MultiplyPointMatrix(double m[4][4], vector3D p)
{
	vector3D rot;
	rot.x = m[0][0] * p.x + m[0][1] * p.y + m[0][2] * p.z;
	rot.y = m[1][0] * p.x + m[1][1] * p.y + m[1][2] * p.z;
	rot.z = m[2][0] * p.x + m[2][1] * p.y + m[2][2] * p.z;
	return rot;
}

vector3D S[4];
/*vector3D HermiteCurve(vector3D P1, vector3D P2, vector3D V1, vector3D V2)
{
	double M[4][4] = 
	{ { 1,0,-3,2 },
	{ 0,0,3,-2 },
	{ 0,1,-2,1 },
	{ 0,0,-1,1 } };

	vector3D G[4] = { P1, P2, V1, V2 };
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			S[i] = vadd(valuemulv(M[i][j], G[j]), S[i]);
		}
	}
	return ;
}*/

void drawplant()
{
	glLoadIdentity();
	//glTranslatef(2.0f, 0.0f, -5.0f);
	glPushMatrix();
	glBegin(GL_QUADS);
		glVertex3f(20.0, -20.0, 0.0);
		glVertex3f(-20.0, -20.0, 0.0);
		glVertex3f(-20.0, 20.0, 0.0);
		glVertex3f(20.0, 20.0, 0.0);
	glEnd();
	glPopMatrix();

	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, -60.0);
	glVertex3f(0.0, 0.0, 60.0);
	glEnd();
	glPopMatrix();

	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(cubepos.x, cubepos.y, cubepos.z);
	glutSolidCube(cube_size);
	glPopMatrix();
}
double lamb = 0.0;
void IDLE()
{
	
	if(height >= 0)
		t += 0.000001;
	glutPostRedisplay();
}

void drawSlerp()
{
	vector3D aa = { 0,0,1 };
	aa = normalize(aa);
	quaternions bb = { 90, aa };
	bb = good(bb);

	vector3D cc = { 1,0,0 };
	cc = normalize(cc);
	quaternions dd = { 45, cc };
	dd = good(dd);

	glColor3f(0.5, 0.3, 0.1);
	glPushMatrix();
	quaternions qr;
	qr = Slerp(bb, dd, lamb);
	ExportToMatrix(qr, m);
	vector3D point = { 5,5,5 };
	point = MultiplyPointMatrix(m, point);
	//glVertex3f(point.x, point.y, point.z);
	glTranslatef(point.x, point.y, point.z);
	glutSolidCube(1);
	glPopMatrix();
	//glEnd();
}

void drowobj()
{
	double t_temp = t * 1000;
	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
		obj.v.x = V * cos(angle * M_PI / 180);
		obj.v.y = V * sin(angle * M_PI / 180);
		obj.v.z = 0.0;
		height = obj.position.y + ((obj.v.y * t_temp) - (G*t_temp*t_temp / 2));
		horizontal = obj.position.x + obj.v.x*t_temp;
		glTranslatef(horizontal, height - (obj.size / 2), obj.position.z);
		glutSolidCube(obj.size);
		cout << height << endl;
	glPopMatrix();
}

void drow_obj_slide()
{
	glColor3f(0.0, 1.0, 1.0);
	glPushMatrix();
	double temp = max(0.0, 9.8*(sin(obj_slide.angle*M_PI / 180) - obj_slide.uk*cos(obj_slide.angle*M_PI / 180)));
	obj_slide.acceleration = { temp*cos(obj_slide.angle*M_PI / 180),-temp*sin(obj_slide.angle*M_PI / 180),0.0 };
	obj_slide.speed = vadd(obj_slide.speed, valuemulv(t, obj_slide.acceleration));
	obj_slide.position = vadd(obj_slide.position, valuemulv(t, obj_slide.speed));

	glTranslatef(obj_slide.position.x, obj_slide.position.y, obj_slide.position.z);
	glutSolidCube(obj_slide.size);
	glPopMatrix();
}

void mydisplay() {

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	gluQuadricDrawStyle(quadricPtr, GLU_LINE);
	glShadeModel(GL_SMOOTH);
	gluQuadricNormals(quadricPtr, GLU_SMOOTH);

	//drawplant();

	//drawSlerp();

	drowobj();
	drow_obj_slide();


	glFlush();
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-200.0, 200.0, -200.0, 200.0, -200.0, 200.0);
	gluLookAt(1, 1, 90, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	
}

void inputkey(unsigned char key, int x, int y)
{
	vector3D point1 = { 20.0, -20.0, 0.0 };
	
	switch (key)
	{
	case 'w':
		cubepos.z += 1.0;
		if (Collision_Detection(plant_N, point1, cubepos) == 0)
			cubepos.z -= 1.0;
		break;
	case 's':
		cubepos.z -= 1.0;
		if (Collision_Detection(plant_N, point1, cubepos) == 0)
			cubepos.z += 1.0;
		break;
	default:
		break;
	}
	mydisplay();
}


void main(int argc, char** argv) {
	glutInitWindowSize(500, 500);
	glutCreateWindow("simple");
	//crossVector = cross(P, Q);
	//crossVector = normalize(crossVector);
	glutIdleFunc(IDLE);
	glutDisplayFunc(mydisplay);
	glutKeyboardFunc(inputkey);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
	init();

	/*vector3D a = { 20.0, -20.0, 0.0 }, b = { -20.0, -20.0, 0.0 }, c = { -20.0, 20.0, 0.0 };
	vector3D d = cross(ptov(a, b), ptov(b, c));
	//d = normalize(d);
	//cout << d.x << " " << d.y << " "<<d.z;

	vector3D aa = { 0,0,1 };
	aa = normalize(aa);
	quaternions bb = { 90, aa };
	bb = good(bb);

	vector3D cc = { 1,0,0 };
	cc = normalize(cc);
	quaternions dd = { 45, cc };
	dd = good(dd);
	
	quatout(multiplication(bb, dd));
	quatout(inverse(bb));
	quatout(inverse(dd));*/

	obj.position.x = 0, obj.position.y = 0,	obj.position.z = 0;
	obj.mass = MASS;
	obj.size = SIZE;

	obj_slide.position.x = 0, obj_slide.position.y = 0, obj_slide.position.z = 0;
	obj_slide.mass = MASS;
	obj_slide.size = SIZE;
	obj_slide.speed = { s*cos(obj_slide.angle*M_PI / 180),s*sin(obj_slide.angle*M_PI / 180),0 };
	obj_slide.uk = 0.5;
	obj_slide.angle = 45;


	/*vector3D R;
	cout << "P length = " << length(P) << endl;
	cout << "Q length = " << length(Q) << endl;
	R = normalize(P);
	cout << "unit vector of P = " << R.x << "," << R.y << "," << R.z << endl;
	R = normalize(Q);
	cout << "unit vector of Q = " << R.x << "," << R.y << "," << R.z << endl;
	cout << "P.Q = " << dot(normalize(P), normalize(Q)) << endl;
	R = cross(P, Q);
	R = normalize(R);
	cout << "PxQ = " << R.x << "," << R.y << "," << R.z << endl;*/
	/**************///inverse
	/*
	matrix3D x;
	double ratio, a;
	int i, j, k, n;
	cout << "Enter order of matrix: ";
	cin >> n;
	cout << "Enter the matrix: " << endl;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			cin >> x.matrix[i][j];
		}
	}
	if (matrixdet(x, n) - 0 < 1e-6)
		cout << "The matrix has no Inverse" << endl;
	else
	{
		x = matrixinv(x, n);
		cout << "The inverse matrix is: " << endl;
		for (i = 0; i < n; i++)
		{
			for (j = n; j < 2 * n; j++)
			{
				cout << x.matrix[i][j]<<" ";
			}
			cout << endl;
		}
	}*/
	/**************/
	/*double d;//distance point:q,s vector v
	vector3D q{ 10.0, 0.0, -10.0 }, s{ 5.0, 80.0, -5.0 }, v{ 0.0, -1.0, 0.0 };
	d = sqrt((length(ptov(q, s))*length(ptov(q, s))) - ((dot(v, ptov(q, s)))*(dot(v, ptov(q, s))) / (length(v)*length(v))));
	cout <<setprecision(8)<< d << endl;*/
	//drawplant();
	glutMainLoop();

}