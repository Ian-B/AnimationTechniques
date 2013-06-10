
#include "Obj.h"
#include "Model.h"
#include <string>
using namespace std;

//globals

//body
unsigned int body_tSize, body_vSize, body_nSize;
GLuint* body_triangles;
GLdouble* body_verticies, * body_normals;

//left wing
unsigned int lwing_tSize, lwing_vSize, lwing_nSize;
GLuint* lwing_triangles;
GLdouble* lwing_verticies, * lwing_normals;

//right wing
unsigned int rwing_tSize, rwing_vSize, rwing_nSize;
GLuint* rwing_triangles;
GLdouble* rwing_verticies, * rwing_normals;

bool loaded = false;

void SetupBody()
{
	ifstream* i_file = new ifstream();
	i_file->open("body.obj");
	Model* newModel = new Model(i_file);
	i_file->close();
	//No of triangles
	body_tSize = newModel->tSize;
	//No of verticies
	body_vSize = newModel->vSize;
	//No of normals
	body_nSize = newModel->nSize;
	//triangle array
	body_triangles = newModel->triangles;
	//vertex array
	body_verticies = newModel->verticies;
	//normal array
	body_normals = newModel->normals;
	cout << "Body" << endl;
	cout << "verticies: ";
	cout << (body_vSize/3) << endl;
	cout << "triangles: ";
	cout << (body_tSize/3) << endl;
	cout << "normals: ";
	cout << (body_nSize/3) << endl;
	cout << endl;
}

void SetupLWing()
{
	ifstream* i_file = new ifstream();
	i_file->open("lwing.obj");
	Model* newModel = new Model(i_file);
	i_file->close();
	//No of triangles
	lwing_tSize = newModel->tSize;
	//No of verticies
	lwing_vSize = newModel->vSize;
	//No of normals
	lwing_nSize = newModel->nSize;
	//triangle array
	lwing_triangles = newModel->triangles;
	//vertex array
	lwing_verticies = newModel->verticies;
	//normal array
	lwing_normals = newModel->normals;
	cout << "Left Wing" << endl;
	cout << "verticies: ";
	cout << (lwing_vSize/3) << endl;
	cout << "triangles: ";
	cout << (lwing_tSize/3) << endl;
	cout << "normals: ";
	cout << (lwing_nSize/3) << endl;
	cout << endl;
}

void SetupRWing()
{
	ifstream* i_file = new ifstream();
	i_file->open("rwing.obj");
	Model* newModel = new Model(i_file);
	i_file->close();
	//No of triangles
	rwing_tSize = newModel->tSize;
	//No of verticies
	rwing_vSize = newModel->vSize;
	//No of normals
	rwing_nSize = newModel->nSize;
	//triangle array
	rwing_triangles = newModel->triangles;
	//vertex array
	rwing_verticies = newModel->verticies;
	//normal array
	rwing_normals = newModel->normals;
	cout << "Right Wing" << endl;
	cout << "verticies: ";
	cout << (rwing_vSize/3) << endl;
	cout << "triangles: ";
	cout << (rwing_tSize/3) << endl;
	cout << "normals: ";
	cout << (rwing_nSize/3) << endl;
	cout << endl;
}

Obj::Obj()
{
	SetupBody();
	SetupLWing();
	SetupRWing();
	loaded = true;
}

//
Obj::Obj(ifstream &fin):thetaInc(0.02),direction(1.0){
	if (!loaded)
	{
		Obj();
	}

	fin >> numChildren;
	fin >> linkLength >> theta >> twist >> displacement >> thetaMax >> thetaMin;

	if (numChildren>0){ 
		children = new Obj*[numChildren];
		for(int i=0; i<numChildren; i++)
			children[i] = new Obj(fin);
	}
}

void Obj::traverse(string position){
	glPushMatrix();
	transform();

	if (position == "right")
	{
		drawRWing();
	}
	if (position == "left")
	{
		drawLWing();
	}

	for (int i=0; i<numChildren; i++)
		children[i]->traverse(position);
	glPopMatrix();
}

void Obj::transform(){
		glRotatef(theta,1.0,0.0,0.0);
		glTranslatef(0,0,displacement);
		glTranslatef(linkLength,0.0,0.0);
		glRotatef(twist,1.0,0.0,0.0);
}

void Obj::drawBody(){
	//enable vertex array
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_DOUBLE, 3*sizeof(GLdouble), body_verticies);
	glNormalPointer(GL_DOUBLE, 3*sizeof(GLdouble), body_normals);
	glDrawElements(GL_TRIANGLES, body_tSize, GL_UNSIGNED_INT, body_triangles);
	//disable vertex array
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void Obj::drawLWing(){
	//enable vertex array
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_DOUBLE, 3*sizeof(GLdouble), lwing_verticies);
	glNormalPointer(GL_DOUBLE, 3*sizeof(GLdouble), lwing_normals);
	glDrawElements(GL_TRIANGLES, lwing_tSize, GL_UNSIGNED_INT, lwing_triangles);
	//disable vertex array
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void Obj::drawRWing(){
	//enable vertex array
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_DOUBLE, 3*sizeof(GLdouble), rwing_verticies);
	glNormalPointer(GL_DOUBLE, 3*sizeof(GLdouble), rwing_normals);
	glDrawElements(GL_TRIANGLES, rwing_tSize, GL_UNSIGNED_INT, rwing_triangles);
	//disable vertex array
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void Obj::update(){
	theta = theta + direction*thetaInc;
	if (theta<thetaMin || theta>thetaMax) direction *= -1;

	for (int i=0; i<numChildren; i++)
		children[i]->update();
}
