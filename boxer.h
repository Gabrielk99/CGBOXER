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
//Classe que define o objeto boxeador
class Boxer
{
    //centro e raio do boxeador
    GLfloat cX;
    GLfloat cY;
    GLfloat radiuS;
    //raio imaginario
    GLfloat radiusImaginary;
    //booleano de se o boxeador existe
    bool valid = false;
    //identificador de cor (jogador ou inimigo)
    string color;
    //identificador de angulo de direção
    GLfloat angle;
    //identificadores de angulos iniciais do braço esquerdo
    GLfloat anglebraco11_inicial=45;
    GLfloat anglebraco12_inicial=-135;
    //identificadores de angulos atuais do braço esquerdo
    GLfloat anglebraco11=45;
    GLfloat anglebraco12=-135;
    //identificadores de angulos iniciais do braço direito
    GLfloat anglebraco21_inicial=135;
    GLfloat anglebraco22_inicial=135;
    //identificadores de angulo atuais do braço direito
    GLfloat anglebraco21=135;
    GLfloat anglebraco22=135;
    //pontuação
    int pontuation = 0;
    //se a pontuação é valida de calcular
    bool pontuationValid = true;
    //se o jogador pode socar
    bool socoValid = true;
    //apenas um roubo, quero que o soco colida com o personagem
    //sem atravessar a cabeça, se eu deixa fluir a posição futura ao menos
    //uma vez, o soco colide sem atravessar e sem não encostar
    bool avancaUltimaPosixSoco = true;

private:
    //auxiliares de desenho do personagem
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
        //proporção ao raio definido para o personagem
        radiusImaginary = radius*2.25;
        valid = true;
        color = cor;
        
    };
    //auxiliar para poder criar a classe vazia
    Boxer(){};
    //chama a função desenha 
    void Desenha(){
        DesenhaBoxer(cX,cY,radiuS,color,angle,anglebraco11,anglebraco12,anglebraco21,anglebraco22);
    };
    //retorna validade de existencia
    bool validBoxer(){
        return valid;
    }
    //retorna o centro do personagem
    void obtemcXcY(GLfloat &cx,GLfloat &cy){
        cx = cX;
        cy = cY;
    }
    //retorna o raio do personagem
    void obtemRaio(GLfloat &r){
        r=radiuS;
    }
    //retorna o raio imaginario do personagem (limitador)
    void obtemRaioImaginary(GLfloat &r){
        r = radiusImaginary;
    }
    //define o angulo do personagem
    void defineAngle(GLfloat theta){
        angle = theta;
    }
    // redefine o cy do personagem para o eixo ideal
    void redefinecy(GLdouble altura,GLfloat y){
        cY= y+(altura+y)-cY;
    }
    //funções de movimento e soco
    void Gira(GLdouble inc,GLdouble time);
    void Move(GLdouble inc,GLdouble time,GLfloat limesq,GLfloat limdir,GLfloat cima,GLfloat baixo,
                GLfloat cxadv,GLfloat cyadv,GLfloat r);
    void socoDireito(GLfloat inc,GLfloat raioadversario,GLfloat cx,GLfloat cy);
    void socoEsquerdo(GLfloat inc,GLfloat raioadversario,GLfloat cx,GLfloat cy);
    void resetanglebracdir();
    void resetanglebracesq();
    //retorna posição da luva
    void getGlovesPosition(GLfloat &cx,GLfloat &cy,GLfloat angle1,GLfloat angle2,bool esq,bool dir);
    //define a validade do soco (pode socar ou não socar)
    void defineValidSoco(bool validade){
        socoValid = validade;
    }
    //retorna se o soco é valido
    bool returnValidSoco(){
        return socoValid;
    }
    //retorna o angulo de direção do personagem
    float returnAngle(){
        return angle;
    }
    //define a validade do personagem
    void defineValid(bool validade){
        valid = validade;
    }
    //retorna a pontuação
    int returnPontuation(){
        return pontuation;
    }
    //reposiciona o personagem (finalização do jogo)
    void reposition(GLfloat cx,GLfloat cy){
        cX = cx;
        cY = cy;
        angle =270*M_PI/180;
    }
};


#endif /* BOXER_H*/