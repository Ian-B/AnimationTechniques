
#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <fstream>
#include <vector>

#include "GL/glut.h"
using namespace std;
class Model
{
public:

	GLdouble *verticies;
	unsigned int vSize;
	GLuint *triangles;
	unsigned int tSize;
	GLdouble *normals;
	unsigned int nSize;
	Model(ifstream* inStream);	
	virtual ~Model();

protected:
private:
	void readVertex(vector<GLdouble>*, string);
	void readFace(vector<GLuint>*, string);
	void readNormal(vector<GLdouble>*, string);
};

#endif // MODEL_H