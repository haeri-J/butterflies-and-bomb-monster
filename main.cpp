#include <GL/glut.h>
#include <math.h>

GLfloat time = 0;
GLfloat x = 0, y = 0;//나비의 좌표
GLfloat n = 0;//처음에 발을 멈춰있기 위한 전역변수
GLfloat BX = 0, BY = 0;//bombmonster의 좌표
GLUquadricObj* cyl;

void MySpecial(int key, int X, int Y) {
	n = 1;
	if (key == GLUT_KEY_UP) {
		if (y >= 7.5) {
			y = 7.5;

		}
		else {

			y += 0.5f;
		}
	}
	if (key == GLUT_KEY_DOWN) {

		if (y <= -7.5) {
			y = -7.5;
		}
		else {
			y -= 0.5f;
		}
	}

	if (key == GLUT_KEY_LEFT) {
		if (x <= -7.5) {
			x = -7.5;
		}
		else {
			x -= 0.5f;
		}
	}
	if (key == GLUT_KEY_RIGHT) {
		if (x >= 7.5) {
			x = 7.5;
		}
		else {
			x += 0.5f;

		}
	}
	glutPostRedisplay();
}

void BlueXY() {//BX와 BY가 각각 나비 좌표인 x,y와 같으면 멈춘다.

	if (BY > y) {
		BY -= 0.0025;
	}
	else if (BY < y) {
		BY += 0.0025;
	}
	if (BX > x) {
		BX -= 0.0025;

	}
	else if (BX < x) {
		BX += 0.0025;
	}
	if (BX == x && BY == y) {//각각의 좌표가 같으면 n=0
		n = 0;
	}
}



void MyTimer(int Value) {
	time = time + 4.0f;
	BlueXY();//타이머 콜백함수에 넣어 계속 부른다.
	glutPostRedisplay();
	glutTimerFunc(1, MyTimer, 1);

}
void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(10, 10, 0.1,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);  //시점변환
}


void MyDisplay() {
	cyl = gluNewQuadric();
	gluQuadricDrawStyle(cyl, GLU_FILL);


	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, 500, 500);
	glLoadIdentity();
	gluLookAt(1.5, 0.6, 4, 0, 0, 0, 0, 1, 0);
	glColor3f(1.0, 1.0, 1.0);

	glPushMatrix();//땅바닥(잔디)
	glColor3f(0.7, 0.9, 0.1);
	glTranslatef(0, -6, 0);
	glScalef(50, 0, 50);
	glutSolidCube(0.3);
	glPopMatrix();

	glPushMatrix();//나비
	glColor3f(0.5, 0.4, 0.3);
	glTranslatef(x, -2, y);
	glRotatef(-60, 1, 0, 0);
	gluCylinder(cyl, 0.1, 0.1, 0.3, 20, 5);//몸통
	glPushMatrix();//윗날개
	glColor3f(1.0, 1, 0.0);
	glTranslatef(0.2, 0, 0.25);
	glutSolidSphere(0.1, 5, 20);
	glRotatef(90, 0, 1, 0);
	glRotatef((sin(time * 0.001) * 15) - 45, 1, 0, 0);
	gluCylinder(cyl, 0.1, 0.1, 0.3, 20, 5);
	glPopMatrix();

	glPushMatrix();//아랫날개
	glColor3f(1.0, 1, 0.0);
	glTranslatef(0.2, 0, 0.05);
	glutSolidSphere(0.1, 5, 20);
	glRotatef(90, 0, 1, 0);
	glRotatef((sin(time * 0.001) * 15) - 45, 1, 0, 0);
	gluCylinder(cyl, 0.1, 0.1, 0.3, 20, 5);
	glPopMatrix();

	glPushMatrix();//윗날개
	glColor3f(1.0, 1, 0.0);
	glTranslatef(-0.2, 0, 0.25);
	glutSolidSphere(0.1, 5, 20);
	glRotatef(90, 0, 1, 0);
	glRotatef(-(sin(time * 0.001) * 15) - 135, 1, 0, 0);
	gluCylinder(cyl, 0.1, 0.1, 0.3, 20, 5);
	glPopMatrix();

	glPushMatrix();//아랫날개
	glColor3f(1.0, 1, 0.0);
	glTranslatef(-0.2, 0, 0);
	glutSolidSphere(0.1, 5, 20);
	glRotatef(90, 0, 1, 0);
	glRotatef(-(sin(time * 0.001) * 15) - 135, 1, 0, 0);
	gluCylinder(cyl, 0.1, 0.1, 0.3, 20, 5);
	glPopMatrix();

	glPopMatrix();


	glPushMatrix();//동그란 캐릭터 몸통
	glColor3f(0.1, 0.1, 0.9);
	glTranslatef(BX, -4.7, BY);
	glutSolidSphere(0.8, 20, 20);

	glPushMatrix();//심지
	glColor3f(0.7, 0.7, 0.7);
	glTranslatef(0, 0.8, 0);
	glRotatef(-70, 1, 0, 0);
	gluCylinder(cyl, 0.1, 0.1, 0.3, 20, 5);
	glPopMatrix();

	glPushMatrix();//눈
	glColor3f(1, 1, 1);
	glTranslatef(-0.2, 0, 0.8);
	glutSolidSphere(0.1, 5, 20);
	glPopMatrix();
	glPushMatrix();//눈
	glColor3f(1, 1, 1);
	glTranslatef(0.2, 0, 0.8);
	glutSolidSphere(0.1, 5, 20);
	glPopMatrix();

	glPushMatrix();//다리
	glColor3f(1.0, 0.8, 0.1);
	glTranslatef(0.3, -0.8, -0.2);
	glutSolidSphere(0.1, 5, 20);
	glRotatef(sin(time * 0.001) * n * 60 + 90, 1, 0, 0);//키보드가 눌리면 전역변수 n=1로 바뀐다. 초깃값 0
	gluCylinder(cyl, 0.1, 0.1, 0.3, 20, 5);
	glPushMatrix();//발
	glTranslatef(0, 0, 0.3);
	glutSolidSphere(0.1, 5, 20);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(cyl, 0.1, 0.1, 0.2, 20, 5);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();//다리
	glColor3f(1.0, 0.8, 0.1);
	glTranslatef(-0.4, -0.8, -0.15);
	glutSolidSphere(0.1, 5, 20);
	glRotatef(-sin(time * 0.001) * n * 60 + 90, 1, 0, 0);;//키보드가 눌리면 전역변수 n=1로 바뀐다. 초깃값 0
	gluCylinder(cyl, 0.1, 0.1, 0.2, 20, 5);
	glPushMatrix();//발
	glTranslatef(0, 0, 0.3);
	glutSolidSphere(0.1, 5, 20);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(cyl, 0.1, 0.1, 0.2, 20, 5);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();


	glutSwapBuffers();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Butterflies and Bomb Monsters");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutReshapeFunc(MyReshape);
	glutDisplayFunc(MyDisplay);
	glutTimerFunc(1, MyTimer, 1);
	glutSpecialFunc(MySpecial);

	glutMainLoop();


	return 0;


}