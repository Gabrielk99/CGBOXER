#ifndef ARENA_H
#define ARENA_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
//Classe que define a arena
class Arena
{
    //Origem da arena
    GLfloat gX;
    GLfloat gY;
    //largura e altura
    GLdouble widthA;
    GLdouble heightA;
    //cor da arena
    string colorA;
    //validade da arena
    bool valid=false;

private:
    //funções para desenhar a arena
    void DesenhaRect(GLfloat x, GLfloat y,GLdouble width,GLdouble height,GLfloat R,GLfloat G,GLfloat B);
    void DesenhaArena(GLfloat x, GLfloat y,GLdouble width,GLdouble height,string color);
public:
    //inicializa a arena
    Arena(GLfloat x, GLfloat y,GLdouble width,GLdouble height,string color){
        gX = x;
        gY = y;
        widthA = width;
        heightA = height;
        colorA = color;
        valid = true;
    };
    //permite criar objeto sem inicialização
    Arena(){};
    //desenha a arena
    void Desenha(){
        DesenhaArena(gX,gY,widthA,heightA,colorA);
    };
    //retorna a altura e largura da arena
    void obtemAlturaLargura(GLdouble &width,GLdouble &height){
        width = widthA;
        height = heightA;
    }
    //retorna origem da arena
    void ObtemOrigem(GLfloat &x,GLfloat &y){
        x=gX;
        y=gY;
    }
    //retorna validade da arena
    bool validArena(){
        return valid;
    }
};





#endif /* ARENA_H*/