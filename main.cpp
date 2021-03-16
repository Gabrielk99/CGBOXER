#include <stdio.h>
#include "util.h"
#include <string>

//Controle dos incrementos
#define inc_andar 0.15
#define inc_girar 0.15
#define inc_soca1  0.5
#define inc_soca2  0.33
#define max_angle_soca 115
//Criando os as variaveis que guardam as informações necessárias de cada objeto
Arena arena;
Inimigo inimigo;
Jogador jogador;
//Status dos controles
int keyStatus[256];
//Controla angulo dos socos
int soca=0;
//controla o braço a socar
float initialx=0;
//controla movimento inimigo
bool moveI = true;
bool podeGirar = true;
//controla soco do inimigo
float incSocoAcc = 0;
int socoDirection = 0;
bool finalizousoco = false;
//controla fim de jogo
bool fim = false;
using namespace std;
//ImprimePlacar
static char str[1000];
void *font = GLUT_BITMAP_9_BY_15;
void imprimePlacar(GLfloat x,GLfloat y,GLfloat deslocy){
    glColor3f(1,1,1);
    char*tmpStr;
    sprintf(str,"JogadorScore : %d",jogador.returnPontuation());
    glRasterPos2f(x,y);
    tmpStr=str;
    while(*tmpStr){
        glutBitmapCharacter(font,*tmpStr);
        tmpStr++;
    }
    sprintf(str,"InimigoScore : %d",inimigo.returnPontuation());
    glRasterPos2f(x,y-deslocy);
    tmpStr=str;
    while(*tmpStr){
        glutBitmapCharacter(font,*tmpStr);
        tmpStr++;
    }
}
//Imprime Mensagem De Vitoria
void imprimeVitoria(GLfloat x,GLfloat y,int qual,GLfloat R,GLfloat G,GLfloat B){
 glColor3f(R,G,B);
    char*tmpStr;
    if(qual == 1){
        sprintf(str,"PARABENS JOGADOR VENCEU !!!");
    }
    else if(qual ==2){
        sprintf(str," QUE PENA, O INIMIGO VENCEU !!!");
    }
    tmpStr=str;
    float deslocx = glutBitmapLength(font,(const unsigned char*)tmpStr)/2.0f;
    glRasterPos2f(x-deslocx,y);
    while(*tmpStr){
        glutBitmapCharacter(font,*tmpStr);
        tmpStr++;
    }
}
void renderScene(){
    glClear(GL_COLOR_BUFFER_BIT);
    if(arena.validArena())
        arena.Desenha();
    if(jogador.validBoxer()){
        jogador.Desenha();
    }
    if(inimigo.validBoxer()){
        inimigo.Desenha();
    }
    GLdouble largura,altura;
    GLfloat x,y;
    arena.obtemAlturaLargura(largura,altura);
    arena.ObtemOrigem(x,y);
    imprimePlacar(x+largura/12,y+altura/12,altura/18);
    if(fim){
        float xposition,yposition;
        xposition = x+largura/2.0f;
        yposition = y+altura*4/5;
        //Escreve mensagem de vitoria
        if(jogador.validBoxer()){
            imprimeVitoria(xposition,yposition,1,1,1,1);
        }
        else if(inimigo.validBoxer()){
            imprimeVitoria(xposition,yposition,2,1,1,1);
        }
    }
    glutSwapBuffers();
}
void mousePresse(int button,int state,int x,int y){
    if(button==GLUT_LEFT_BUTTON){
        if(state==GLUT_DOWN){
            soca = 1;
            initialx = x;
        }
        else {
            soca=0;
            //Volta braço pra origem
            jogador.resetanglebracdir();
            jogador.resetanglebracesq();
            //reseta x click
            initialx=0;
        }
    }
}
void mouseMotion(int x,int y){
    GLdouble altura,largura;
    arena.obtemAlturaLargura(largura,altura);
    GLfloat cxini,cyini,rini;
    inimigo.obtemcXcY(cxini,cyini);
    inimigo.obtemRaio(rini);
    if(soca && jogador.returnValidSoco() ){
        float atualposition = x-initialx;
        float theta,maxangle;
        maxangle=max_angle_soca;
        theta = maxangle*atualposition/(largura/2); 
        if(atualposition>0 && atualposition<(largura/2)){
            jogador.socoDireito(theta,rini,cxini,cyini);
        }
        if(atualposition<0 && abs(atualposition)<(largura/2)){
            jogador.socoEsquerdo(theta,rini,cxini,cyini);
        }
    }
}
void keyPress(unsigned char key,int x,int y){
    keyStatus[key]=1;
    if(keyStatus[(int)('a')]||keyStatus[(int)('d')]||keyStatus[(int)('w')]
                            ||keyStatus[(int)('s')]){
        jogador.defineValidSoco(false);
    }
    glutPostRedisplay();
}
void keyUp(unsigned char key, int x,int y){
    keyStatus[key]=0;
     if(!keyStatus[(int)('a')] && !keyStatus[(int)('d')] && !keyStatus[(int)('w')]
                              && !keyStatus[(int)('s')]){
        jogador.defineValidSoco(true);
    }
    glutPostRedisplay();
}
void idle(){
    if(!fim){
        //Pega os parametros da arena
        GLfloat x,y;
        GLdouble width,height;
        arena.obtemAlturaLargura(width,height);
        arena.ObtemOrigem(x,y);
        
        //Verifica pontuação
        if(jogador.returnPontuation()==10){
            inimigo.defineValid(false);
            jogador.reposition(x+width/2,y+height/2);
            inimigo.reposition(0,0);
            jogador.resetanglebracdir();
            jogador.resetanglebracesq();
            fim = true;
            
        }
        else if(inimigo.returnPontuation()==10){
            jogador.defineValid(false);
            inimigo.resetanglebracdir();
            inimigo.resetanglebracesq();
            inimigo.reposition(x+width/2,y+height/2);
            jogador.reposition(0,0);
            fim = true;
        }

        //Pega o tempo 
        static GLdouble previousTime = glutGet(GLUT_ELAPSED_TIME);
        GLdouble currentTime,timeDiference;
        currentTime = glutGet(GLUT_ELAPSED_TIME);
        timeDiference = currentTime-previousTime;
        previousTime = currentTime;

        //Realiza os movimentos do jogador
        double inc_giro = inc_girar;
        double inc_anda = inc_andar;
        float limitdireita = x+width;
        float limitesquerda = x;
        float limitcima = y+height;
        float limitbaixo = y;
        GLfloat cxinimigo,cyinimigo,raioinimigo;
        inimigo.obtemcXcY(cxinimigo,cyinimigo);
        inimigo.obtemRaio(raioinimigo);
        if(keyStatus[(int)('a')]){
            jogador.Gira(inc_giro,timeDiference);
        }
        if(keyStatus[(int)('d')]){
            jogador.Gira(-inc_giro,timeDiference);
        }
        if(keyStatus[(int)('w')]){
            jogador.Move(inc_anda,timeDiference,limitesquerda,limitdireita,limitcima,
                            limitbaixo,cxinimigo,cyinimigo,raioinimigo);
            
        }
        if(keyStatus[(int)('s')]){
            jogador.Move(-inc_anda,timeDiference,limitesquerda,limitdireita,
                            limitcima,limitbaixo,cxinimigo,cyinimigo,raioinimigo);
        }



        //Movimento do inimigo
            GLfloat cxjogador,cyjogador;
            jogador.obtemcXcY(cxjogador,cyjogador);
            GLfloat raiojogador;
            jogador.obtemRaio(raiojogador);
            GLfloat theta=0;
            inimigo.retornaAnguloRelativoAoJogador(cxjogador,cyjogador,theta);
            GLfloat anguloAtual = inimigo.returnAngle();
            GLfloat angleDiference = anguloAtual-theta;
            static float oldT = theta;
            GLfloat dist = inimigo.distanceAoJogadorF(inc_anda,timeDiference,cxjogador,cyjogador,raiojogador);
            GLfloat raioI; 
            inimigo.obtemRaioImaginary(raioI);

            if((raioI+raiojogador)<dist){
                inimigo.defineValidSoco(false);
                if((dist-(raioI+raiojogador))>100 || (!keyStatus[(int)('w')] && !keyStatus[(int)('s')]) ){
                    moveI = true;
                }
            }
            else {
                moveI = false;
                inimigo.defineValidSoco(true);
            }
            if(oldT!=theta){
                podeGirar = true;
            }
            if(angleDiference<0 && podeGirar){
                podeGirar = false;
                if((anguloAtual+inc_giro)<theta){
                    inimigo.Gira(inc_giro,timeDiference);
                }
            }
            else if(angleDiference>0 && podeGirar){
                podeGirar = false;
                if((anguloAtual-inc_giro)>theta){
                    inimigo.Gira(-inc_giro,timeDiference);
                }
            }

            //Define a memoria de theta passado
            oldT = theta;
            if(moveI){
                inimigo.Move(inc_anda,timeDiference,limitesquerda,limitdireita,limitcima,limitbaixo,
                            cxjogador,cyjogador,raiojogador);
            }
            //Soca Inimigo
            if(inimigo.returnValidSoco()){
                GLdouble largura,altura;
                arena.obtemAlturaLargura(largura,altura);
                float incsoco = (max_angle_soca)/(360.0f)*timeDiference*1.5;
                
                if(!socoDirection){
                    socoDirection = rand()%2+1;
                }
                switch (socoDirection)
                {
                case 1:
                    if(!finalizousoco && incSocoAcc<max_angle_soca){
                        incSocoAcc+=incsoco;
                        inimigo.socoDireito(incSocoAcc,raiojogador,cxjogador,cyjogador);
                    }
                    else if(incSocoAcc>0) {
                        finalizousoco = true;
                        incSocoAcc-= incsoco;
                        inimigo.socoDireito(incSocoAcc,raiojogador,cxjogador,cyjogador);
                    }
                    else {
                        finalizousoco=false;
                        incSocoAcc = 0;
                        socoDirection = rand()%2+1;
                    }
                    break;
                case 2:
                    if(!finalizousoco && incSocoAcc>-max_angle_soca){
                        incSocoAcc-=incsoco;
                        inimigo.socoEsquerdo(incSocoAcc,raiojogador,cxjogador,cyjogador);
                    }
                    else if(incSocoAcc<0) {
                        finalizousoco = true;
                        incSocoAcc+= incsoco;
                        inimigo.socoEsquerdo(incSocoAcc,raiojogador,cxjogador,cyjogador);
                    }
                    else {
                        incSocoAcc = 0;
                        socoDirection = rand()%2+1;
                        finalizousoco=false;
                    }
                    break;
                default:
                    break;
                }
            }
    }
    glutPostRedisplay();
}
void init(void){
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    GLdouble width,height;
    GLfloat  x,y;
    arena.obtemAlturaLargura(width,height);
    arena.ObtemOrigem(x,y);
    glMatrixMode(GL_PROJECTION);
    glOrtho(x,x+width,y,y+height,-100,100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
int main (int argc, char* argv[]){
    string filename;
    filename = argv[1];
    Util utilidades(filename);
    //Inicializando os objetos
    utilidades.parsesElements(arena,inimigo,jogador);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    //Criando janela
    GLdouble width,height;
    arena.obtemAlturaLargura(width,height);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(150,50);
    glutCreateWindow("Box-Game-CREDS_LIKE");
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyUp);
    glutMouseFunc(mousePresse);
    glutMotionFunc(mouseMotion);
    glutIdleFunc(idle);
    glutDisplayFunc(renderScene);




    init();
    glutMainLoop();
    return 0;
}