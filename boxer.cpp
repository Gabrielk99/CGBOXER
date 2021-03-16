#include "boxer.h"

void Boxer :: DesenhaCirc(GLfloat radius,GLfloat R,GLfloat G,GLfloat B){
    float cx,cy = 0.0;
    int num_point = 150;
    glColor3f(R,G,B);
    glBegin(GL_POLYGON);
        for (int i = 0 ; i < num_point; i++){
            float theta = 2*M_PI/(float(num_point))*(float)i;
            float x = radius*cos(theta);
            float y = radius*sin(theta);
            glVertex3f(cx+x,cy+y,0);
        }
    glEnd();
}
void Boxer:: DesenhaRect(GLfloat width,GLfloat height,GLfloat R,GLfloat G,GLfloat B){
    glColor3f(R,G,B);
    glBegin(GL_QUADS);
        glVertex3f(-width/2,0,0);
        glVertex3f(width/2,0,0);
        glVertex3f(width/2,height,0);
        glVertex3f(-width/2,height,0);
    glEnd();
}
void Boxer:: DesenhaBraco(GLfloat x,GLfloat y,GLfloat width,GLfloat height,GLfloat angle1,GLfloat angle2,GLfloat radius){
    glPushMatrix();
        glTranslatef(x,y,0);
        glRotatef(angle1,0,0,1);
        DesenhaRect(width,height,0.4,0.9,0.1);
        glTranslatef(0,height-height/16,0);
        glRotatef(angle2,0,0,1);
        DesenhaRect(width,height,0.4,0.9,0.1);
        glTranslatef(0,height,0);
        DesenhaCirc(radius,0.9,0.2,0.3);
    glPopMatrix();
}
void Boxer:: DesenhaNariz(GLfloat x,GLfloat y,GLfloat radius){
    glPushMatrix();
        glTranslatef(x,y,0);
        DesenhaCirc(radius,0.3,0.4,0.5);
    glPopMatrix();
}
void Boxer :: DesenhaBoxer(GLfloat cx,GLfloat cy,GLfloat radius,string color,GLfloat angle,GLfloat angleb11,
                                GLfloat angleb12,GLfloat angleb21,GLfloat angleb22){
    //Começa desenho
    glPushMatrix();
        glTranslatef(cx,cy,0);
        glRotatef(angle*180/M_PI,0,0,1);
        DesenhaBraco(0,(radius-radius/6),radius/4,radius+radius/2,angleb11,angleb12,radius/3);
        DesenhaBraco(0,(-radius+radius/6),radius/4,radius+radius/2,angleb21,angleb22,radius/3);
        DesenhaNariz(radius+(radius/4-radius/6),0,radius/4);
        if (!color.compare("green")){
            DesenhaCirc(radius,0.43,0.664,0.36);
        }
        if (!color.compare("red")){
            DesenhaCirc(radius,0.9,0.1,0.1);
        }
    glPopMatrix();
}
void Boxer :: Gira(GLdouble inc,GLdouble time){
    // reseta o soco
    resetanglebracdir();
    resetanglebracesq();
    
    //gira o boneco
    angle+=inc*M_PI/180*time;
}
void Boxer :: Move(GLdouble inc, GLdouble time,GLfloat limesq,GLfloat limdir,
GLfloat cima,GLfloat baixo,GLfloat cxadv,GLfloat cyadv,GLfloat r){ 
    //reseta o soco
    resetanglebracdir();
    resetanglebracesq();
    
    //começa a função
    float incx = inc*time*cos((angle));
    float incy = inc*time*sin((angle));
    float x_dir,y_cima;
    float x_esq,y_baixo;
    x_dir = cX+radiuS+incx;
    x_esq = cX-radiuS+incx;
    y_cima = cY+radiuS+incy;
    y_baixo = cY-radiuS+incy;
    float  distcx =  (cX+incx)-cxadv;
    float distcy = (cY+incy)-cyadv;
    float dist = sqrt(pow(distcx,2)+pow(distcy,2));
    if(x_dir< limdir && x_esq> limesq){
        if((r+radiusImaginary)<dist){
            cX+=incx;
        }
    }
    if(y_cima<cima && y_baixo>baixo){
        if((r+radiusImaginary)<dist)
            cY+=incy;
    }
}
void Boxer:: resetanglebracdir(){
    anglebraco21=anglebraco21_inicial;
    anglebraco22=anglebraco22_inicial;
}
void Boxer:: resetanglebracesq(){
    anglebraco11=anglebraco11_inicial;
    anglebraco12=anglebraco12_inicial;
}
void rotacionaPT(GLfloat x, GLfloat y, GLfloat theta,GLfloat &xOut,GLfloat &yOut){

    xOut = x*cos(theta)-y*sin(theta);
    yOut = x*sin(theta)+y*cos(theta);

}
void Boxer:: getGlovesPosition(GLfloat &cx,GLfloat &cy,GLfloat angle1,GLfloat angle2, bool esq=false,bool dir=false){
    // calcula posição da luva para conferir pontuação
    float xinicial,yinicial;
    float bracolength = radiuS+radiuS/2;
    if(dir){
        xinicial = 0 ;
        yinicial = -radiuS+radiuS/6;
    }
    else if(esq){
        xinicial = 0 ;
        yinicial = radiuS-radiuS/6;   
    }
    float ombrox,ombroy;
    rotacionaPT(xinicial,yinicial,angle,ombrox,ombroy);
    ombrox+=cX;
    ombroy+=cY;

    float cotovelox ;
    float cotoveloy ;

    rotacionaPT(0,bracolength-bracolength/16,angle+(angle1*M_PI/180),cotovelox,cotoveloy);

    cotovelox+=ombrox;
    cotoveloy+=ombroy;
    float luvax ;
    float luvay ;

    rotacionaPT(0,bracolength,angle+(angle1*M_PI/180)+(angle2*M_PI/180),luvax,luvay);
    luvax+=cotovelox;
    luvay+=cotoveloy;

    cx = luvax;
    cy = luvay;

}
void Boxer::socoDireito(GLfloat inc,GLfloat raioadversario,GLfloat cx,GLfloat cy){
    //calcula se acertou o adversário
    
    float luvax,luvay;
    getGlovesPosition(luvax,luvay,anglebraco21_inicial+inc,anglebraco22_inicial-0.75*inc,false,true);
    
    float distcx = luvax - cx;
    float distcy = luvay - cy;

    float dist = sqrt(pow(distcx,2)+pow(distcy,2));
    float raioluva = radiuS/3;
    if((raioadversario+raioluva)<(dist+3)){
        // define os angulos de soco
        anglebraco21=anglebraco21_inicial + inc;
        anglebraco22=anglebraco22_inicial -0.75*inc; 
        pontuationValid=true;
      
    }
    else{
       if(pontuationValid){
            pontuation++;
            pontuationValid = false;
        }
    }
   
}
void  Boxer :: socoEsquerdo(GLfloat inc,GLfloat raioadversario,GLfloat cx,GLfloat cy){

    //calcula se acertou o adversário
    float luvax,luvay;
    getGlovesPosition(luvax,luvay,anglebraco11_inicial+inc,anglebraco12_inicial-0.75*inc,true,false);
    
    float distcx = luvax - cx;
    float distcy = luvay - cy;

    float dist = sqrt(pow(distcx,2)+pow(distcy,2));
    float raioluva = radiuS/3;
    if((raioadversario+raioluva)<(dist+3)){
        //define angulo do soco
        anglebraco11 = anglebraco11_inicial + inc;
        anglebraco12 = anglebraco12_inicial - 0.75*inc;
        pontuationValid=true;
    }
    else {
      if(pontuationValid){
            pontuation++;
            pontuationValid = false;
        }
    }
}