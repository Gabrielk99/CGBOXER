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
        GLfloat theta;
        retornaAnguloRelativoAoJogador(cxjogador,cyjogador,theta);
        Boxer::defineAngle(theta);
    }
    void retornaAnguloRelativoAoJogador(GLfloat cxjogador,GLfloat cyjogador,GLfloat& theta){
        GLfloat cX,cY;
        Boxer::obtemcXcY(cX,cY);
        float distx = cxjogador-cX;
        float disty = cyjogador -cY;
        theta = atan2(disty,distx);
    }
    GLfloat distanceAoJogador(GLfloat cxjogador,GLfloat cyjogador,GLfloat raioJogador){
        GLfloat cx,cy;
        Boxer::obtemcXcY(cx,cy);
        float distx = cx-cxjogador;
        float disty = cy-cyjogador;
        float dist = sqrt(pow(distx,2)+pow(disty,2));
        return dist;
    }
    GLfloat distanceAoJogadorF(GLfloat inc,GLfloat time,GLfloat cxjogador,GLfloat cyjogador,GLfloat raioJogador){
        GLfloat cx,cy;
        Boxer::obtemcXcY(cx,cy);
        float incx = inc*time*cos(Boxer::returnAngle());
        float incy = inc*time*sin(Boxer::returnAngle());
        float distx = (cx+incx)-cxjogador;
        float disty = (cy+incy)-cyjogador;
        float dist = sqrt(pow(distx,2)+pow(disty,2));
        return dist;
    }
};


#endif /* INIMIGO_H */