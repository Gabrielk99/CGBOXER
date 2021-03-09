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
    angle+=inc*M_PI/180*time;
}
void Boxer :: Move(GLdouble inc, GLdouble time,GLfloat limesq,GLfloat limdir,
GLfloat cima,GLfloat baixo,GLfloat cxinimigo,GLfloat cyinimigo,GLfloat r){ 
    //começa a função
    float incx = inc*time*cos((angle));
    float incy = inc*time*sin((angle));
    float x_dir,y_cima;
    float x_esq,y_baixo;
    x_dir = cX+radiuS+incx;
    x_esq = cX-radiuS+incx;
    y_cima = cY+radiuS+incy;
    y_baixo = cY-radiuS+incy;
    float  distcx =  (cX+incx)-cxinimigo;
    float distcy = (cY+incy)-cyinimigo;
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
    anglebraco21-=anglebraco21_acc;
    anglebraco22-=anglebraco22_acc;
    anglebraco21_acc=0;
    anglebraco22_acc=0;
}
void Boxer::socoDireito(GLfloat inc){
    float xinicial,yinicial;
    xinicial = (-radiuS+radiuS/6)*cos(angle+M_PI/2);
    yinicial = (-radiuS+radiuS/6)*sin(angle+M_PI/2);
    xinicial = cX+xinicial;
    yinicial = cY+yinicial;

    float bracolength = radiuS+radiuS/2;
    float x = (bracolength-bracolength/16)*cos((anglebraco21+inc)*M_PI/180+M_PI_2+angle);
    float y = (bracolength-bracolength/16)*sin((anglebraco21+inc)*M_PI/180+M_PI_2+angle);
    
    float cotovelox = xinicial+x;
    float cotoveloy = yinicial+y; 

    x = (bracolength)*cos(((anglebraco21+inc)*M_PI/180+(anglebraco22-0.95*inc)*M_PI/180+angle)+M_PI_2);
    y = (bracolength)*sin(((anglebraco21+inc)*M_PI/180+(anglebraco22-0.95*inc)*M_PI/180+angle)+M_PI_2);

    float luvax = cotovelox+x;
    float luvay = cotoveloy+y;

    float distx = cX - luvax;
    float disty = cY - luvay;
    float distT = sqrt(pow(distx,2)+pow(disty,2));
    
    printf("\nluva x %f, luva y %f\n",luvax,luvay);
    printf("\ndist %f imR %f\n",distT,radiusImaginary);

    
    
    if(radiusImaginary>=distT && anglebraco21_acc+inc>=0 && anglebraco22_acc-0.95*inc<=0){
        inc = inc*360/(2*M_PI*radiusImaginary);
        anglebraco21+=inc;
        anglebraco22-=0.95*inc;
        anglebraco21_acc+=inc;
        anglebraco22_acc-=inc*0.95;
    }

}