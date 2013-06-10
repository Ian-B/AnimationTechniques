
#include "Obj.h"

ifstream fin("art.txt");
ifstream fin2("art2.txt");
Obj *test = new Obj(fin);
Obj *test2 = new Obj(fin2);

void Init()
{
	GLfloat light_position[] = {1.0,1.0,0.0,1.0};
	GLfloat light_ambient[] = {0.0,0.0,0.0,1.0};
	GLfloat light_diffuse[] = {1.0,1.0,1.0,1.0};
	GLfloat light_specular[] = {1.0,1.0,1.0,1.0};
	GLfloat model_ambient[] = {0.2,0.2,0.2,1.0};
	GLfloat material_specular[] = {1.0,1.0,1.0,1.0};
	GLfloat material_emission[] = {0.0,0.0,0.0,1.0};
	glClearColor(0.5,0.5,0.5,1.0);
	glShadeModel(GL_SMOOTH);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_emission);
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslated(0.0,0.0,-40.0);	
	//glRotatef(185, 0, 1, 0);	
	glColor3f(0.0,0.0,1.0);
	test->drawBody();
	test2->traverse("left");
	test->traverse("right");
	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (w/h), 10, 70);
	glMatrixMode(GL_MODELVIEW);
}

void update(void){
	test->update();
	test2->update();	
	glutPostRedisplay();
}

int main(int argc, char **argv)
{	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(50,100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Assign 2");
	glutIdleFunc(update);
	Init();
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutMainLoop();
}
