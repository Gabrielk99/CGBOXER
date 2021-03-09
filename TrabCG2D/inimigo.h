#ifndef INIMIGO_H
#define INIMIGO_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "boxer.h"

using namespace std;
class Inimigo: public Boxer
{

private:
    
public:
    Inimigo(GLfloat cx,GLfloat cy, GLfloat radius,string cor):Boxer(cx,cy,radius,cor){
    };
    Inimigo(){};
    void calculeAnlgeNarizInimigo(GLfloat cxjogador,GLfloat cyjogador){
        GLfloat cX,cY;
        Boxer::obtemcXcY(cX,cY);
        float distx = cxjogador-cX;
        float disty = cyjogador -cY;
        float theta = atan2(disty,distx);
        Boxer::defineAngle(theta);
    }
};






#endif /* INIMIGO_H */