#include "arena.h"

//Desenha o retangulo 
void Arena::DesenhaRect(GLfloat x,GLfloat y,GLdouble width,GLdouble height,GLfloat R,GLfloat G,GLfloat B){
    glColor3f(R,G,B);
    glBegin(GL_QUADS);
        //vertices baseados a partir da origem + tamanho e altura da arena
        glVertex3f(x,y,0);
        glVertex3f(x+width,y,0);
        glVertex3f(x+width,y+height,0);
        glVertex3f(x,y+height,0);
    glEnd();
}
//desenha a arena
void Arena::DesenhaArena(GLfloat x, GLfloat y,GLdouble width,GLdouble height,string color){
    //não possui transformações não precisa de glPushMatrix()
    //desenha retangulo
    DesenhaRect(x,y,width,height,0,0,1);
}