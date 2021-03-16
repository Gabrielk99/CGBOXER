#ifndef BOXER_H
#define BOXER_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
class Boxer
{
    GLfloat cX;
    GLfloat cY;
    GLfloat radiuS;
    GLfloat radiusImaginary;
    bool valid = false;
    string color;
    GLfloat angle;
    GLfloat anglebraco11_inicial=45;
    GLfloat anglebraco12_inicial=-135;
    GLfloat anglebraco11=45;
    GLfloat anglebraco12=-135;
    GLfloat anglebraco21_inicial=135;
    GLfloat anglebraco22_inicial=135;
    GLfloat anglebraco21=135;
    GLfloat anglebraco22=135;
    int pontuation = 0;
    bool pontuationValid = true;
    bool socoValid = true;

private:
    void DesenhaCirc(GLfloat radius,GLfloat R,GLfloat G,GLfloat B);
    void DesenhaRect(GLfloat width,GLfloat height,GLfloat R,GLfloat G,GLfloat B);
    void DesenhaBraco(GLfloat x,GLfloat y,GLfloat width,GLfloat height,GLfloat angle1,GLfloat angle2,GLfloat radius);
    void DesenhaNariz(GLfloat x,GLfloat y,GLfloat radius);
    void DesenhaBoxer(GLfloat cx,GLfloat cy,GLfloat radius,string color,GLfloat angle,
                        GLfloat angleb11,GLfloat angleb12,GLfloat angleb2,GLfloat anlgeb22);
public:
    Boxer(GLfloat cx,GLfloat cy,GLfloat radius,string cor){
        cX = cx;
        cY = cy;
        radiuS = radius;
        radiusImaginary = radius*2.25;
        valid = true;
        color = cor;
        
    };
    Boxer(){};
    void Desenha(){
        DesenhaBoxer(cX,cY,radiuS,color,angle,anglebraco11,anglebraco12,anglebraco21,anglebraco22);
    };
    bool validBoxer(){
        return valid;
    }
    void obtemcXcY(GLfloat &cx,GLfloat &cy){
        cx = cX;
        cy = cY;
    }
    void obtemRaio(GLfloat &r){
        r=radiuS;
    }
    void obtemRaioImaginary(GLfloat &r){
        r = radiusImaginary;
    }
    void defineAngle(GLfloat theta){
        angle = theta;
    }
    void Gira(GLdouble inc,GLdouble time);
    void Move(GLdouble inc,GLdouble time,GLfloat limesq,GLfloat limdir,GLfloat cima,GLfloat baixo,
                GLfloat cxadv,GLfloat cyadv,GLfloat r);
    void socoDireito(GLfloat inc,GLfloat raioadversario,GLfloat cx,GLfloat cy);
    void socoEsquerdo(GLfloat inc,GLfloat raioadversario,GLfloat cx,GLfloat cy);
    void resetanglebracdir();
    void resetanglebracesq();
    void getGlovesPosition(GLfloat &cx,GLfloat &cy,GLfloat angle1,GLfloat angle2,bool esq,bool dir);
    void defineValidSoco(bool validade){
        socoValid = validade;
    }
    bool returnValidSoco(){
        return socoValid;
    }
    float returnAngle(){
        return angle;
    }
    void defineValid(bool validade){
        valid = validade;
    }
    int returnPontuation(){
        return pontuation;
    }
    void reposition(GLfloat cx,GLfloat cy){
        cX = cx;
        cY = cy;
        angle =270*M_PI/180;
    }
};


#endif /* BOXER_H*/