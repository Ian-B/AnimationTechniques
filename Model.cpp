
#include "Model.h"
#include <sstream>
#include <algorithm>

using namespace std;
Model::Model(ifstream* inStream):
verticies(0),
vSize(0),
triangles(0),
tSize(0),
normals(0),
nSize(0)
{
	string line;
	vector<GLdouble> tmpVerticies;
	vector<GLuint> tmpFaces;
	vector<GLdouble> tmpNormals;

	while(!inStream->eof())
	{
		getline(*inStream, line);
		string token;
		token.assign(line.c_str(), 2);		

		if (token == "v ")
		{
			readVertex(&tmpVerticies, line);
		}
		if (token == "f ")
		{
			readFace(&tmpFaces, line);
		}
		if (token == "vn")
		{
			readNormal(&tmpNormals, line);
		}
	}
	vSize = tmpVerticies.size();
	verticies = new GLdouble[vSize];
	for (unsigned int i = 0; i<vSize; verticies[i]=tmpVerticies[i], i++);

	tSize = tmpFaces.size();
	triangles = new GLuint[tSize];
	for (unsigned int i = 0; i<tSize; triangles[i]=tmpFaces[i], i++);

	nSize = tmpNormals.size();
	normals = new GLdouble[nSize];
	for (unsigned int i = 0; i<nSize; normals[i]=tmpNormals[i], i++);
}

void Model::readVertex(vector<GLdouble>* tv, string line)
{
	stringstream ss(line, stringstream::in | stringstream::out);

	GLdouble x,y,z;
	char v;
	ss >> v >> x >> y >> z;
	tv->push_back(x);
	tv->push_back(y);
	tv->push_back(z);
}

void Model::readFace(vector<GLuint>* tf, string line)
{
	string faces = line;
	replace(faces.begin(), faces.end(), '/', ' ');

	stringstream ss(faces, stringstream::in | stringstream::out);
	GLint x1,y1,z1,x2,y2,z2,x3,y3,z3;
	char f;
	ss >> f >> x1 >> x2 >> x3 >> y1 >> y2 >> y3 >> z1 >> z2 >> z3;
	tf->push_back(x1);
	tf->push_back(y1);
	tf->push_back(z1);
}

void Model::readNormal(vector<GLdouble>* nv, string line)
{
	stringstream ss(line, stringstream::in | stringstream::out);

	GLdouble x,y,z;
	char v;
	ss >> v >> x >> y >> z;
	nv->push_back(x);
	nv->push_back(y);
	nv->push_back(z);
}

Model::~Model()
{
	if (verticies!=0) delete [] verticies;
	if (triangles!=0) delete [] triangles;
	if (normals!=0) delete [] normals;
}
