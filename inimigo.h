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
//Classe que define o inimigo
class Inimigo: public Boxer
{

private:
    
public:
    Inimigo(GLfloat cx,GLfloat cy, GLfloat radius,string cor):Boxer(cx,cy,radius,cor){
    };
    //permite definir o objeto sem inicializar
    Inimigo(){};
 
    //calcula o angulo do nariz inimigo (direção inicial do inimigo)
    void calculeAnlgeNarizInimigo(GLfloat cxjogador,GLfloat cyjogador){
        GLfloat theta;
        //pega o angulo relativo ao jogador
        retornaAnguloRelativoAoJogador(cxjogador,cyjogador,theta);
        Boxer::defineAngle(theta);
    }
    //calcula o angulo relativo ao jogador
    void retornaAnguloRelativoAoJogador(GLfloat cxjogador,GLfloat cyjogador,GLfloat& theta){
        //retorna o centro do inimigo
        GLfloat cX,cY;
        Boxer::obtemcXcY(cX,cY);
        //calcula a diferença dos centros
        float distx = cxjogador-cX;
        float disty = cyjogador -cY;
        //retorna o angulo
        theta = atan2(disty,distx);
    }
    //calcula a distancia ao jogador
    GLfloat distanceAoJogador(GLfloat cxjogador,GLfloat cyjogador,GLfloat raioJogador){
        //pega o centro do inimigo
        GLfloat cx,cy;
        Boxer::obtemcXcY(cx,cy);
        //calcula a distancia ao jogador
        float distx = cx-cxjogador;
        float disty = cy-cyjogador;
        float dist = sqrt(pow(distx,2)+pow(disty,2));
        return dist;
    }
    //calcula a distancia futura ao jogador
    GLfloat distanceAoJogadorF(GLfloat inc,GLfloat time,GLfloat cxjogador,GLfloat cyjogador,GLfloat raioJogador){
        //obtem o centro do inimgio
        GLfloat cx,cy;
        Boxer::obtemcXcY(cx,cy);
        //calcula o incremento de x e y com base ao movimento circular
        float incx = inc*time*cos(Boxer::returnAngle());
        float incy = inc*time*sin(Boxer::returnAngle());
        //calcula a distancia e retorna
        float distx = (cx+incx)-cxjogador;
        float disty = (cy+incy)-cyjogador;
        float dist = sqrt(pow(distx,2)+pow(disty,2));
        return dist;
    }
};


#endif /* INIMIGO_H */