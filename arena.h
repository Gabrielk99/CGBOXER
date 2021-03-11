#ifndef ARENA_H
#define ARENA_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
class Arena
{
    GLfloat gX;
    GLfloat gY;
    GLdouble widthA;
    GLdouble heightA;
    string colorA;
    bool valid=false;

private:
    void DesenhaRect(GLfloat x, GLfloat y,GLdouble width,GLdouble height,GLfloat R,GLfloat G,GLfloat B);
    void DesenhaArena(GLfloat x, GLfloat y,GLdouble width,GLdouble height,string color);
public:
    Arena(GLfloat x, GLfloat y,GLdouble width,GLdouble height,string color){
        gX = x;
        gY = y;
        widthA = width;
        heightA = height;
        colorA = color;
        valid = true;
    };
    Arena(){};
    void Desenha(){
        DesenhaArena(gX,gY,widthA,heightA,colorA);
    };
    void obtemAlturaLargura(GLdouble &width,GLdouble &height){
        width = widthA;
        height = heightA;
    }
    void ObtemOrigem(GLfloat &x,GLfloat &y){
        x=gX;
        y=gY;
    }
    void imprime(){
        printf("%f,%f",gX,gY);
    }
    bool validArena(){
        return valid;
    }
};





#endif /* ARENA_H*/