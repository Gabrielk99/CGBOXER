#include "boxer.h"
//Desenha circulo (chamado para desenhar a cabeça, a luva e o nariz)
void Boxer :: DesenhaCirc(GLfloat radius,GLfloat R,GLfloat G,GLfloat B){
    //define o centro como 0,0 para realizar rotações em torno do proprio objeto
    float cx,cy = 0.0;
    int num_point = 150;
    glColor3f(R,G,B);
    glBegin(GL_POLYGON);
        //calcula os vertices
        for (int i = 0 ; i < num_point; i++){
            //equação do circulo
            float theta = 2*M_PI/(float(num_point))*(float)i;
            float x = radius*cos(theta);
            float y = radius*sin(theta);
            glVertex3f(cx+x,cy+y,0);
        }
    glEnd();
}
//Desenha retangulo (chamando para desenhar os braços)
void Boxer:: DesenhaRect(GLfloat width,GLfloat height,GLfloat R,GLfloat G,GLfloat B){
    glColor3f(R,G,B);
    glBegin(GL_QUADS);
        //a base do eixo cartesiano é na base do braço 
        //permite rotação em torno da base
        glVertex3f(-width/2,0,0);
        glVertex3f(width/2,0,0);
        glVertex3f(width/2,height,0);
        glVertex3f(-width/2,height,0);
    glEnd();
}
//Desenha braço do personagem
void Boxer:: DesenhaBraco(GLfloat x,GLfloat y,GLfloat width,GLfloat height,GLfloat angle1,GLfloat angle2,GLfloat radius){
    //salva as atuais transformações inserindo uma copia
    glPushMatrix();
        //translada para o primeiro braço
        glTranslatef(x,y,0);
        //realiza rotação
        glRotatef(angle1,0,0,1);
        //desenha o braço
        DesenhaRect(width,height,0.4,0.9,0.1);
        //translada para o segundo braço
        //uma pequena diferença para designer dos personagens
        glTranslatef(0,height-height/16,0);
        //rotaciona o braço
        glRotatef(angle2,0,0,1);
        //desenha o antebraço
        DesenhaRect(width,height,0.4,0.9,0.1);
        //translada de toda altura do braço e desenha a luva
        glTranslatef(0,height,0);
        DesenhaCirc(radius,0.9,0.2,0.3);
    glPopMatrix();
    //romeveu a copia da pilha
}
//desenha nariz
void Boxer:: DesenhaNariz(GLfloat x,GLfloat y,GLfloat radius){
    glPushMatrix();
        glTranslatef(x,y,0);
        DesenhaCirc(radius,0.3,0.4,0.5);
    glPopMatrix();
}
//Desenha todo o personagem
void Boxer :: DesenhaBoxer(GLfloat cx,GLfloat cy,GLfloat radius,string color,GLfloat angle,GLfloat angleb11,
                                GLfloat angleb12,GLfloat angleb21,GLfloat angleb22){
    //Começa desenho
    //copia as atuais transformações e insere na pilha
    glPushMatrix();
        //translada a té a posição do personagem
        glTranslatef(cx,cy,0);
        //rotaciona do angulo de direção
        glRotatef(angle*180/M_PI,0,0,1);
        //desenha o braço esquerdo
        DesenhaBraco(0,(radius-radius/6),radius/4,radius+radius/2,angleb11,angleb12,radius/3);
        //desenha o braço direito
        DesenhaBraco(0,(-radius+radius/6),radius/4,radius+radius/2,angleb21,angleb22,radius/3);
        //desenha o nariz
        DesenhaNariz(radius+(radius/4-radius/6),0,radius/4);
        //decide a cor da cabeça a partir da cor predefinida do persoangem
        if (!color.compare("green")){
            DesenhaCirc(radius,0.43,0.664,0.36);
        }
        if (!color.compare("red")){
            DesenhaCirc(radius,0.9,0.1,0.1);
        }
    //remove do topo da pilha a copia
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
    //calcula os incrementos necessários e o movimento circular
    //com base ao angulo de direção
    float incx = inc*time*cos((angle));
    float incy = inc*time*sin((angle));
    //calcula a posições possíveis maximas da arena
    float x_dir,y_cima;
    float x_esq,y_baixo;
    x_dir = cX+radiuS+incx;
    x_esq = cX-radiuS+incx;
    y_cima = cY+radiuS+incy;
    y_baixo = cY-radiuS+incy;
    //calcula a distancia do personagem ao adversario
    float  distcx =  (cX+incx)-cxadv;
    float distcy = (cY+incy)-cyadv;
    float dist = sqrt(pow(distcx,2)+pow(distcy,2));
    //verifica se está dentro do limite da arena
    if(x_dir< limdir && x_esq> limesq){
        //verifica se esta colidindo com adversario
        if((r+radiusImaginary)<dist){
            cX+=incx;
        }
    }
    if(y_cima<cima && y_baixo>baixo){
        if((r+radiusImaginary)<dist)
            cY+=incy;
    }
}
//reseta os angulos do braço direito
void Boxer:: resetanglebracdir(){
    anglebraco21=anglebraco21_inicial;
    anglebraco22=anglebraco22_inicial;
}
//reseta os angulos do braço esquerdo
void Boxer:: resetanglebracesq(){
    anglebraco11=anglebraco11_inicial;
    anglebraco12=anglebraco12_inicial;
}
//auxiliar de rotacionar um ponto
void rotacionaPT(GLfloat x, GLfloat y, GLfloat theta,GLfloat &xOut,GLfloat &yOut){
    //definição de rotação
    xOut = x*cos(theta)-y*sin(theta);
    yOut = x*sin(theta)+y*cos(theta);

}
//pega a posição da luva
void Boxer:: getGlovesPosition(GLfloat &cx,GLfloat &cy,GLfloat angle1,GLfloat angle2, bool esq=false,bool dir=false){
    /* PARAMETRO
      cx cy --> onde será guardado o centro da luva
      angle1 --> angulo da primeira parte do braço
      angle2 --> angulo da segunda parte do braço
      esq --> se for o braço esquerdo
      dir --> se for o braço direito
    */
    
    // calcula posição da luva para conferir pontuação
    float xinicial,yinicial;
    //tamanho do braço
    float bracolength = radiuS+radiuS/2;
    //verifica o braço e atribui a posição inicial da base de cada braço
    if(dir){
        xinicial = 0 ;
        yinicial = -radiuS+radiuS/6;
    }
    else if(esq){
        xinicial = 0 ;
        yinicial = radiuS-radiuS/6;   
    }
    //acha a posição do ombro
    float ombrox,ombroy;
    rotacionaPT(xinicial,yinicial,angle,ombrox,ombroy);
    ombrox+=cX;
    ombroy+=cY;
    //acha a posição do cotovelo
    float cotovelox ;
    float cotoveloy ;
    rotacionaPT(0,bracolength-bracolength/16,angle+(angle1*M_PI/180),cotovelox,cotoveloy);
    cotovelox+=ombrox;
    cotoveloy+=ombroy;

    //acha a posição final da luva
    float luvax ;
    float luvay ;

    rotacionaPT(0,bracolength,angle+(angle1*M_PI/180)+(angle2*M_PI/180),luvax,luvay);
    luvax+=cotovelox;
    luvay+=cotoveloy;

    cx = luvax;
    cy = luvay;

}
//soco direito
void Boxer::socoDireito(GLfloat inc,GLfloat raioadversario,GLfloat cx,GLfloat cy){
    //calcula se acertou o adversário
    //pega a posição da luva do braço direito
    float luvax,luvay;
    getGlovesPosition(luvax,luvay,anglebraco21_inicial+inc,anglebraco22_inicial-0.75*inc,false,true);
    //calcula a distancia ao adversário
    float distcx = luvax - cx;
    float distcy = luvay - cy;

    float dist = sqrt(pow(distcx,2)+pow(distcy,2));
    //retorna o raio da luva
    float raioluva = radiuS/3;
    //verifica se a luva colidiu com o adversário
    if((raioadversario+raioluva)<(dist)){
        // define os angulos de soco
        anglebraco21=anglebraco21_inicial + inc;
        anglebraco22=anglebraco22_inicial -0.75*inc; 
        //primeira colisão define como valida a pontuação
        pontuationValid=true;
        //define que pode avançar mais uma posição
        avancaUltimaPosixSoco = true;
      
    }
    //se colidiu então 
    else{
        if(avancaUltimaPosixSoco){
            // define os angulos de soco
            anglebraco21=anglebraco21_inicial + inc;
            anglebraco22=anglebraco22_inicial -0.75*inc; 
            avancaUltimaPosixSoco = false;
        }
        //verifica se pode pontuar se sim pontua
       if(pontuationValid){
            pontuation++;
            //define como falso para não pontuar de forma errada
            pontuationValid = false;
        }
    }
   
}
//soco esquerdo
void  Boxer :: socoEsquerdo(GLfloat inc,GLfloat raioadversario,GLfloat cx,GLfloat cy){

    //calcula se acertou o adversário
    //pega a posição da luva do braço esquerdo
    float luvax,luvay;
    getGlovesPosition(luvax,luvay,anglebraco11_inicial+inc,anglebraco12_inicial-0.75*inc,true,false);
    
    //calcula a distancia até o adversário
    float distcx = luvax - cx;
    float distcy = luvay - cy;

    float dist = sqrt(pow(distcx,2)+pow(distcy,2));
    //retorna raio da luva
    float raioluva = radiuS/3;
    //verifica se o soco acertou o adversario
    if((raioadversario+raioluva)<(dist)){
        //define angulo do soco
        anglebraco11 = anglebraco11_inicial + inc;
        anglebraco12 = anglebraco12_inicial - 0.75*inc;
        pontuationValid=true;
        avançaUltimaPosixSoco = true;
    }
    //pontuar quando valido
    else {
        if(avançaUltimaPosixSoco){
            // define os angulos de soco
            anglebraco11=anglebraco11_inicial + inc;
            anglebraco12=anglebraco12_inicial -0.75*inc; 
            avançaUltimaPosixSoco = false;
        }
        if(pontuationValid){
            pontuation++;
            pontuationValid = false;
        }
    }
}