#ifndef JOGADOR_H
#define JOGADOR_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "boxer.h"
using namespace std;
class Jogador : public Boxer
{

private:

public:
    Jogador(GLfloat cx,GLfloat cy,GLfloat radius,string cor):Boxer(cx,cy,radius,cor){
    };
    Jogador(){};
    void calculeAngleNarizJogador(GLfloat cxinimigo,GLfloat cyinimigo){
       GLfloat cX,cY;
       Boxer::obtemcXcY(cX,cY);
       float distx = cxinimigo-cX;
       float disty = cyinimigo-cY;
       float theta = atan2(disty,distx);
       Boxer::defineAngle(theta);
    }
};


#endif /* JOGADOR_H */