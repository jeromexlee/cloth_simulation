#include <GL/glew.h>
#include "OpenGL/gl.h"
#include "GLUT/glut.h" 
#include <math.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/timeb.h>
#include <time.h>
#include "Cloth.h"
#include "animation.h"
#include "skeleton.h"
#include "fowardkinematics.h"
#include "params.h"

using namespace std;

Cloth curtain(6,6,50,50);
Cloth cape(0.4,0.8,10,10);
float bx = 3;
float by = -5;
float bz = 7;
Vector3D ball_pos(bx, by, bz);
float ball_radius = 1;
float angle = 0.0f;
float lx = 0.0f;
float lz = -1.0f;
float x = 0.0f;
float z = 5.0f;
double rate = 5;
float wind_force = -5;
Skeleton skeleton;
FowardKinematics frame;
Animation animator = Animation(&skeleton, &frame);

int flag = 1;

int windowHeight=DEF_WINDOW_HEIGHT;
int windowWidth=DEF_WINDOW_WIDTH;
int windowPosHeight=DEF_WINDOW_POS_H;
int windowPosWidth=DEF_WINDOW_POS_W;
double dim=DEF_DIM;
int th=DEF_TH;
int ph=DEF_PH;
int fov=DEF_FOV;
double asp=DEF_ASP;
double ecX=DEF_ECX;
double ecY=DEF_ECY;
double ecZ=DEF_ECZ;
float white[]={1,1,1,1};
int skybox[6];

static void reverse(void* x,const int n) {
	int k;
	char* ch = (char*) x;
	for (k=0; k< n/2; k++) {
		char tmp = ch[k];
		ch[k] = ch[n-1-k];
		ch[n-1-k] = tmp;
	}
}

unsigned int loadTexBMP(char* file) {
	unsigned int texture;
	FILE* f;
	unsigned short magic;
	unsigned int dx, dy, size; 
	unsigned short nbp, bpp; 
	unsigned char* image;  
	unsigned int k;          
	f = fopen(file,"rb");
	fread(&magic,2,1,f);
	fseek(f,16,SEEK_CUR);
	fread(&dx ,4,1,f);
	fread(&dy ,4,1,f);
	fread(&nbp,2,1,f);
	fread(&bpp,2,1,f);
	fread(&k,4,1,f);
	if (magic==0x424D) {
		reverse(&dx,4);
		reverse(&dy,4);
		reverse(&nbp,2);
		reverse(&bpp,2);
		reverse(&k,4);
	}
	size = 3*dx*dy;
	image = (unsigned char*) malloc(size);
	fseek(f,20,SEEK_CUR);
	fread(image,size,1,f);
	fclose(f);
	for (k=0;k<size;k+=3) {
		unsigned char temp = image[k];
		image[k]   = image[k+2];
		image[k+2] = temp;
	}
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
	glTexImage2D(GL_TEXTURE_2D,0,3,dx,dy,0,GL_RGB,GL_UNSIGNED_BYTE,image);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	free(image);
	return texture;	
}

void initSkybox(void)  {
	skybox[SKY_FRONT] = loadTexBMP("../static/txStormydays_front.bmp");	
	skybox[SKY_RIGHT] = loadTexBMP("../static/txStormydays_right.bmp");
	skybox[SKY_LEFT] = loadTexBMP("../static/txStormydays_left.bmp");
	skybox[SKY_BACK] = loadTexBMP("../static/txStormydays_back.bmp");
	skybox[SKY_UP] = loadTexBMP("../static/txStormydays_up.bmp");
	skybox[SKY_DOWN] = loadTexBMP("../static/txStormydays_down.bmp");
}

void displayInit(void) {
	glClearColor(1,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
}

void displayEye(void) {
	double Ex = -2*dim*Sin(th)*Cos(ph);
	double Ey = +2*dim        *Sin(ph);
	double Ez = +2*dim*Cos(th)*Cos(ph);
	gluLookAt(Ex+ecX,Ey,Ez+ecZ , ecX,ecY,ecZ , 0,Cos(ph),0);
}

void displayProject(double fov, double asp, double dim) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov,asp,dim/16,16*dim);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void displayReshape(int width,int height) {
	asp = (height>0) ? (double)width/height : 1;
	glViewport(0,0, width,height);
	displayProject(fov,asp,dim);
}

void redisplayAll(void) {
	displayProject(fov,asp,dim);
	glutPostRedisplay();
}

void drawSkybox(double D) {
	glColor3fv(white);
	glEnable(GL_TEXTURE_2D);

	/* Sides */
	glBindTexture(GL_TEXTURE_2D,skybox[SKY_RIGHT]);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex3f(-D,-D,-D);
	glTexCoord2f(1,0); glVertex3f(+D,-D,-D);
	glTexCoord2f(1,1); glVertex3f(+D,+D,-D);
	glTexCoord2f(0,1); glVertex3f(-D,+D,-D);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,skybox[SKY_FRONT]);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex3f(+D,-D,-D);
	glTexCoord2f(1,0); glVertex3f(+D,-D,+D);
	glTexCoord2f(1,1); glVertex3f(+D,+D,+D);
	glTexCoord2f(0,1); glVertex3f(+D,+D,-D);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,skybox[SKY_LEFT]);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex3f(+D,-D,+D);
	glTexCoord2f(1,0); glVertex3f(-D,-D,+D);
	glTexCoord2f(1,1); glVertex3f(-D,+D,+D);
	glTexCoord2f(0,1); glVertex3f(+D,+D,+D);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,skybox[SKY_BACK]);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex3f(-D,-D,+D);
	glTexCoord2f(1,0); glVertex3f(-D,-D,-D);
	glTexCoord2f(1,1); glVertex3f(-D,+D,-D);
	glTexCoord2f(0,1); glVertex3f(-D,+D,+D);
	glEnd();

	/* Top and Bottom */
	glBindTexture(GL_TEXTURE_2D,skybox[SKY_UP]);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex3f(-D,+D,-D);
	glTexCoord2f(1,0); glVertex3f(+D,+D,-D);
	glTexCoord2f(1,1); glVertex3f(+D,+D,+D);
	glTexCoord2f(0,1); glVertex3f(-D,+D,+D);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,skybox[SKY_DOWN]);
	glBegin(GL_QUADS);
	glTexCoord2f(1,1); glVertex3f(+D,-D,-D);
	glTexCoord2f(0,1); glVertex3f(-D,-D,-D);
	glTexCoord2f(0,0); glVertex3f(-D,-D,+D);
	glTexCoord2f(1,0); glVertex3f(+D,-D,+D);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void drawScene() {
	drawSkybox(3.5*dim);
}

void init(GLvoid)
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.2f, 0.2f, 0.4f, 0.5f);				
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_COLOR_MATERIAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat lightPos[4] = {-1.0,1.0,0.5,0.0};
	glLightfv(GL_LIGHT0,GL_POSITION,(GLfloat *) &lightPos);
	glEnable(GL_LIGHT1);
	GLfloat lightAmbient1[4] = {0.0,0.0,0.0,0.0};
	GLfloat lightPos1[4] = {1.0,0.0,-0.2,0.0};
	GLfloat lightDiffuse1[4] = {0.5,0.5,0.5,0.0};
	glLightfv(GL_LIGHT1,GL_POSITION,(GLfloat *) &lightPos1);
	glLightfv(GL_LIGHT1,GL_AMBIENT,(GLfloat *) &lightAmbient1);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,(GLfloat *) &lightDiffuse1);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
}

void initVars(char arg) {
	flag = arg - '0';
	frame.setRate(rate);
}

void sceneOne() {
	ball_pos.val[0] = bx;
	ball_pos.val[1] = by;
	ball_pos.val[2] = bz;
	curtain.applyForce(Vector3D(0,-0.2,0)*TIMESTEP_SIZE);
	curtain.applyWindForce(Vector3D(0.5,0,0.2)*TIMESTEP_SIZE);
	curtain.timeStep();
	curtain.updateCollision(ball_pos,ball_radius);
	glTranslatef(-6.5,3,-6.0f);
	glRotatef(25,0,1,0);
	curtain.draw();
	glPushMatrix();
	glTranslatef(ball_pos.val[0],ball_pos.val[1],ball_pos.val[2]);
	glColor3f(0.2f,0.6f,0.8f);
	glutSolidSphere(ball_radius-0.05,50,50);
}

void sceneTwo() {
	rate += 0.007;
	wind_force -= 0.08;
	wind_force = wind_force < -20 ? -20 : wind_force;
	rate = rate > 7 ? 7 : rate;
	frame.setRate(rate);
	cape.applyForce(Vector3D(0,-0.2,0)*TIMESTEP_SIZE);
	cape.applyWindForce(Vector3D(0,0,wind_force)*TIMESTEP_SIZE);
	cape.timeStep();
	animator.update();
	glRotatef(225,0,1,0); 
	glTranslatef(0.75f,1, -1.0f);
	cape.draw();
	glTranslatef(-0.75f,-1, 1.0f);
	glColor3f(.1, .1, .1);
	animator.skeleton->update();
}

void sceneThree() {
	rate += 0.01;
	wind_force -= 0.08;
	frame.setRate(rate);
	cape.applyForce(Vector3D(0,-0.2,0)*TIMESTEP_SIZE);
	cape.applyWindForce(Vector3D(0,0,wind_force)*TIMESTEP_SIZE);
	cape.timeStep();
	animator.update();
	glRotatef(225,0,1,0); 
	glTranslatef(0.75f,1, -1.0f);
	cape.draw();
	glTranslatef(-0.75f,-1, 1.0f);
	glColor3f(.1, .1, .1);
	animator.skeleton->update();
}

void render(void) {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	if (flag == 1) {
		glDisable(GL_LIGHTING);
		displayInit();
		displayEye();
		drawScene();
		glFlush();
		glEnable(GL_LIGHTING);
	} else {
		gluLookAt(x, 1.0f, z,
				  x+lx, 1.0f,  z+lz,
				  0.0f, 1.0f,  0.0f);
		glDisable(GL_LIGHTING);
		glColor3f(0.1f, 0.1f, 0.1f);
		glBegin(GL_QUADS);
			glVertex3f(-100.0f, -5.0f, -100.0f);
			glVertex3f(-100.0f, -5.0f,  100.0f);
			glVertex3f( 100.0f, -5.0f,  100.0f);
			glVertex3f( 100.0f, -5.0f, -100.0f);
		glEnd();
		glEnable(GL_LIGHTING);
	}
	switch (flag) {
	case 1:
		sceneOne();
		break;
	case 2:
		sceneTwo();
		break;
	case 3:
		sceneThree();
		break;
	default:
		break;
	}
	glutSwapBuffers();
	glutPostRedisplay();
}

void changeSize(int w, int h) {
	if (h == 0) { 
		h = 1; 
	}
	float ratio = 1.0 * w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective (FOV, ratio, N_CLIP, F_CLIP);
	glMatrixMode(GL_MODELVIEW);
}

void processNormalKeys( unsigned char key, int x, int y ) {
	switch (key) {
	case 'w':
		bz -= MOVE_STEP;
		z -= MOVE_STEP;
		break;
	case 'a':
		bx -= MOVE_STEP;
		x -= MOVE_STEP;
		break;
	case 's':
		bz += MOVE_STEP;
		z += MOVE_STEP;
		break;
	case 'd':
		bx += MOVE_STEP;
		x += MOVE_STEP;
		break;
	case 'l':
		th += 5;
		break;
	case 'j':
		th -= 5;
		break;
	case 'k':
		ph += 5;
		break;
	case 'i':
		ph -= 5;
		break;
	case '-':
		fov--;
		redisplayAll();
		break;
	case '=':
		fov++;
		redisplayAll();
		break;
	case 27:    
		exit(0);
		break; 
	default: 
		break;
	}
}

void processSpecialKeys(int a_keys, int x, int y ) {
	float fraction = 0.4f;
	switch(a_keys) {
		case GLUT_KEY_LEFT :
			angle -= 0.05f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_RIGHT :
			angle += 0.05f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_UP :
			x += lx * fraction;
			z += lz * fraction;
			break;
		case GLUT_KEY_DOWN :
			x -= lx * fraction;
			z -= lz * fraction;
			break;
	default:
		break;
	}
}

int main (int argc, char** argv) {
	if (argc != 2) {
		std::cout << "Choose the scene in the function argument: /.simulation [1, 2, 3]" << std::endl;
		std::cout << "1. curtain collision with ball" << std::endl;
		std::cout << "2. Running cubeman with cape" << std::endl;
		std::cout << "3. Bonus demo: running cubeman crush" << std::endl;
		return 0;
	}
	glutInit(&argc, argv);
	glutInitWindowPosition(500, 200);
	glutInitWindowSize(960, 720);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); 
	glutCreateWindow("Final Project - Cloth simulation");
	init();
	initVars(argv[1][0]);
	glutDisplayFunc(render);  
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glutIdleFunc(render);
	if (flag == 1) {
		initSkybox();
		redisplayAll();
	}
	glutMainLoop();
	return 1;
}
