#include <stdio.h>
#include "util.h"
#include <string>

//Controle dos incrementos
#define inc_andar 0.15
#define inc_girar 0.15
#define inc_soca1  0.5
#define inc_soca2  0.33
//Criando os as variaveis que guardam as informações necessárias de cada objeto
Arena arena;
Inimigo inimigo;
Jogador jogador;
//Status dos controles
int keyStatus[256] ;
//Controla angulo dos socos
int soca=0;
//controla o braço a socar
float initialx=0;
float oldx = 0;
using namespace std;

void renderScene(){
    glClear(GL_COLOR_BUFFER_BIT);
    if(arena.validArena())
        arena.Desenha();
    if(jogador.validBoxer()){
        jogador.Desenha();
    }
    if(inimigo.validBoxer()){
        GLfloat cxjogador,cyjogador;
        inimigo.Desenha();
    }

    glutSwapBuffers();
}
void mousePresse(int button,int state,int x,int y){
    if(button==GLUT_LEFT_BUTTON){
        if(state==GLUT_DOWN){
            soca = 1;
            oldx = x;
            initialx = x;
        }
        else {
            soca=0;
            //Volta braço pra origem
            jogador.resetanglebracdir();
            //reseta x click
            oldx=0;
            initialx=0;
        }
    }
}
void mouseMotion(int x,int y){
    GLdouble altura,largura;
    arena.obtemAlturaLargura(largura,altura);
    if(soca){
        float atualposition = x-initialx;
        if(atualposition>0 && atualposition<largura/2){
            float dx= x-oldx;
            jogador.socoDireito(dx);
        }
        oldx = x;
    }
}
void keyPress(unsigned char key,int x,int y){
    keyStatus[key]=1;
    glutPostRedisplay();
}
void keyUp(unsigned char key, int x,int y){
    keyStatus[key]=0;
    glutPostRedisplay();
}
void idle(){
    static GLdouble previousTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble currentTime,timeDiference;
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    timeDiference = currentTime-previousTime;
    previousTime = currentTime;
    double inc_giro = inc_girar;
    double inc_anda = inc_andar;
    GLfloat x,y;
    GLdouble width,height;
    arena.obtemAlturaLargura(width,height);
    arena.ObtemOrigem(x,y);
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
    //Define callbacks
    glutDisplayFunc(renderScene);




    init();
    glutMainLoop();
    return 0;
}