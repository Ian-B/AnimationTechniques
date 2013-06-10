
#include <fstream>
using namespace std;
#include "GL/glut.h"
#include "GL/glu.h"

class Obj{

public:
	Obj();
	Obj(ifstream &fin);
	void traverse(string position);
	void transform();
	void drawRWing();
	void drawLWing();
	void drawBody();
	void update();

private:
	Obj** children;
	int numChildren;
	GLdouble linkLength;
	GLdouble theta;
	GLdouble twist;
	GLdouble displacement;
	GLdouble thetaMax;
	GLdouble thetaMin;
	GLdouble thetaInc;
	GLdouble direction; 
};
