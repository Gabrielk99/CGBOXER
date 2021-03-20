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
bool IAactive = false;
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
    //define cor branca
    glColor3f(1,1,1);
    char*tmpStr;
    //escreve a mensagem de score do jogador
    sprintf(str,"JogadorScore : %d",jogador.returnPontuation());
    //coloca na posição 
    glRasterPos2f(x,y);
    //passa para o ponteiro
    tmpStr=str;
    //imprime a mensagem na tela
    while(*tmpStr){
        glutBitmapCharacter(font,*tmpStr);
        tmpStr++;
    }
    //escreve mensagem de score do inimigo
    sprintf(str,"InimigoScore : %d",inimigo.returnPontuation());
    //coloca a posição correta
    glRasterPos2f(x,y-deslocy);
    tmpStr=str;
    while(*tmpStr){
        glutBitmapCharacter(font,*tmpStr);
        tmpStr++;
    }
}
//Imprime Mensagem De Vitoria
void imprimeVitoria(GLfloat x,GLfloat y,int qual,GLfloat R,GLfloat G,GLfloat B){
    //define a cor da mensagem
    glColor3f(R,G,B);
    char*tmpStr;
    // escolhe se quem ganhou foi jogador ou inimigo
    if(qual == 1){
        sprintf(str,"PARABENS JOGADOR VENCEU !!!");
    }
    else if(qual ==2){
        sprintf(str," QUE PENA, O INIMIGO VENCEU !!!");
    }
    tmpStr=str;
    // mensagem fica no meio da tela, calcula o tamanho da mensagem
    // para deslocar metade para esquerda do meio e metade para a direita
    float deslocx = glutBitmapLength(font,(const unsigned char*)tmpStr)/2.0f;
    glRasterPos2f(x-deslocx,y);
    while(*tmpStr){
        glutBitmapCharacter(font,*tmpStr);
        tmpStr++;
    }
}
//Imprime mensagem de ativação da IA
void imprimeActiveIA(GLfloat x,GLfloat y,GLfloat deslocy){
    glColor3f(1,1,1);
    char*tmpStr;
    //escreve mensagem de ativar a IA
    sprintf(str,"Aperte 1 para ativar a IA");
    tmpStr=str;
    //desloca a metade do tamanho da palavra 
    float deslocx = glutBitmapLength(font,(const unsigned char*)tmpStr)/2.0f;
    glRasterPos2f(x-deslocx,y);

    while(*tmpStr){
        glutBitmapCharacter(font,*tmpStr);
        tmpStr++;
    }
    //escreve mensagem de desativar a IA
    sprintf(str,"Aperte 1 para desativar a IA");
    tmpStr=str;
    glRasterPos2f(x-deslocx,y-deslocy);
    while(*tmpStr){
        glutBitmapCharacter(font,*tmpStr);
        tmpStr++;
    }
}
//CallBack de renderizar a cena
void renderScene(){
    //limpa os pixels
    glClear(GL_COLOR_BUFFER_BIT);
    //verifica a existencia da arena
    if(arena.validArena()){
        arena.Desenha();
    }
    //verifica se existe jogador
    if(jogador.validBoxer()){
        jogador.Desenha();
    }
    //verifica se existe inimigo
    if(inimigo.validBoxer()){
        inimigo.Desenha();
    }
    //define variáveis para capturar os 
    //parametros da arena
    GLdouble largura,altura;
    GLfloat x,y;
    arena.obtemAlturaLargura(largura,altura);
    arena.ObtemOrigem(x,y);
    //imprime placar do jogo
    imprimePlacar(x+largura/12,y+altura/12,altura/18);
    //verifica se o jogo finalizou
    if(fim){
        //define as posições da mensagem de vitoria
        float xposition,yposition;
        xposition = x+largura/2.0f;
        yposition = y+altura*4/5;
        //Escreve mensagem de vitoria
        //Se o jogador for valido ele é o campeão
        if(jogador.validBoxer()){
            imprimeVitoria(xposition,yposition,1,1,1,1);
        }
        //Se não o inimigo que é
        else if(inimigo.validBoxer()){
            imprimeVitoria(xposition,yposition,2,1,1,1);
        }
    }
    //se o jogo ainda n terminou mensagem de ativar a IA
    else {
        imprimeActiveIA(x+largura*4/5,y+altura/12,altura/18);
    }
    //troca as janelas 
    glutSwapBuffers();
}
//Callback de pressionar o botão do mouse
void mousePresse(int button,int state,int x,int y){
    //verifica se o evento foi do botão esquerdo
    if(button==GLUT_LEFT_BUTTON){
        // se tiver abaixado o botão inicializa que vai socar
        if(state==GLUT_DOWN){
            soca = 1;
            initialx = x;
        }
        //se o botão for solto reseta o soco
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
//Callback de movimentar o mouse
void mouseMotion(int x,int y){
    //obtem os parametros da arena
    GLdouble altura,largura;
    arena.obtemAlturaLargura(largura,altura);
    //obtem os parametros do inimigo
    GLfloat cxini,cyini,rini;
    inimigo.obtemcXcY(cxini,cyini);
    inimigo.obtemRaio(rini);
    //verifica se está ativado o movimento de soco e se 
    //o personagem pode socar
    if(soca && jogador.returnValidSoco() ){
        //pega a atual posição em x baseado no primeiro x  de click e o x atual
        float atualposition = x-initialx;
        float theta,maxangle;
        //pega o maximo angulo de soco
        maxangle=max_angle_soca;
        //calcula o angulo atual com base a posição atual
        theta = maxangle*atualposition/(largura/2); 
        //se for > 0 significa que é o braço direito
        //só pode ir ate largura/2 
        if(atualposition>0 && atualposition<(largura/2)){
            jogador.socoDireito(theta,rini,cxini,cyini);
        }
        //se for < 0 é o braço esquerdo
        if(atualposition<0 && abs(atualposition)<(largura/2)){
            jogador.socoEsquerdo(theta,rini,cxini,cyini);
        }
    }
}
//callback de teclado
void keyPress(unsigned char key,int x,int y){
   //sempre que pressionar uma tecla será atribuido 1
   //as suas variaveis de estado
   keyStatus[key]=1;
   //se qualquer uma das teclas de movimento for pressionada 
   //o jogador não pode socar
    if(keyStatus[(int)('a')]||keyStatus[(int)('d')]||keyStatus[(int)('w')]
                            ||keyStatus[(int)('s')]){
        jogador.defineValidSoco(false);
    }
    //se pressionado 1 ativa a IA 
    //ou desativa a IA
    if(keyStatus[(int)('1')]){
        if(!IAactive){
            IAactive = true;
        }
        else IAactive = false;
    }
    //redesenha a tela
    glutPostRedisplay();
}
//callback de teclado
void keyUp(unsigned char key, int x,int y){
    //se soltado a tecla atribui 0 a variável
    //de estado
    keyStatus[key]=0;
    //verifica se todas as teclas são soltas 
    // se sim o jogador está parado e pode socar
     if(!keyStatus[(int)('a')] && !keyStatus[(int)('d')] && !keyStatus[(int)('w')]
                              && !keyStatus[(int)('s')]){
        jogador.defineValidSoco(true);
    }
    glutPostRedisplay();
}
//Callback de idle sempre chamado pelo sistema
void idle(){
    //se o jogo ainda não acabou
    if(!fim){
        //Pega os parametros da arena
        GLfloat x,y;
        GLdouble width,height;
        arena.obtemAlturaLargura(width,height);
        arena.ObtemOrigem(x,y);
        
        //Verifica pontuação
        if(jogador.returnPontuation()==10){
            //reseta e redefine posição 
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
        //define parametros de colisão com a arena
        float limitdireita = x+width;
        float limitesquerda = x;
        float limitcima = y+height;
        float limitbaixo = y;
        //define parametros de colisão com o inimigo
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

        //Se a IA tiver ativada
        if(IAactive){
            //Movimento do inimigo
            //parametros de colisão do jogador
            GLfloat cxjogador,cyjogador;
            jogador.obtemcXcY(cxjogador,cyjogador);
            GLfloat raiojogador;
            jogador.obtemRaio(raiojogador);
            //define o anculo em relação ao jogador
            GLfloat theta=0;
            inimigo.retornaAnguloRelativoAoJogador(cxjogador,cyjogador,theta);
            //calcula a diferença de angulo entre o atual e o anterior
            GLfloat anguloAtual = inimigo.returnAngle();
            GLfloat angleDiference = theta-anguloAtual;
            //calcula a distancia do inimigo ao jogador
            GLfloat dist = inimigo.distanceAoJogadorF(inc_anda,timeDiference,cxjogador,cyjogador,raiojogador);
            //pega raio imaginario do inimigo para tratar colisão
            GLfloat raioI; 
            inimigo.obtemRaioImaginary(raioI);
            //decide se o inimigo pode mover ou socar
            if((raioI+raiojogador)<dist){
                //se não houve colisão movimenta-se
                inimigo.defineValidSoco(false);
               //Se o jogador tiver a uma distancia segura de 100 pixels
               //ativa o movimento do inimigo
               //o inimigo vai movimentar quando o jogador não andar para frente e para tras
                if((dist-(raioI+raiojogador))>100 || (!keyStatus[(int)('w')] && !keyStatus[(int)('s')]) ){
                    moveI = true;
                }
            }
            //se houve colisão o inimigo chegou ao jogador
            //é hora de atacar
            else {
                moveI = false;
                inimigo.defineValidSoco(true);
            }
            //calculando o angulo compensador
            angleDiference = atan2(sin(angleDiference),cos(angleDiference));
            //transformando em radianos pois theta e angulo atual ta em radianos
            float inc_giro_r = inc_giro*M_PI/180;
            //se o angulo que compensa girar é negativo
            //decrementa o angulo atual
            if(angleDiference<0){
                if(anguloAtual-inc_giro_r*timeDiference>(anguloAtual+angleDiference)){
                    inimigo.Gira(-inc_giro,timeDiference);
                }
            } 
            //se não incrementa
            else if (angleDiference>0){
                if(anguloAtual+inc_giro_r*timeDiference<(anguloAtual+angleDiference)){
                    inimigo.Gira(inc_giro,timeDiference);
                }
            }
            //se o nimigo pode mover, então mova-se
            if(moveI){
                inimigo.Move(inc_anda,timeDiference,limitesquerda,limitdireita,limitcima,limitbaixo,
                            cxjogador,cyjogador,raiojogador);
            }
            //Soca Inimigo
            if(inimigo.returnValidSoco()){
                GLdouble largura,altura;
                arena.obtemAlturaLargura(largura,altura);
                float incsoco = (max_angle_soca)/(360.0f)*timeDiference*1.5;
                
                //socoDirection começa como zero
                //sorteia para decidir o primeiro braço a socar  
                if(!socoDirection){
                    socoDirection = rand()%2+1;
                }
                //ação de soco para 2 casos diferentes
                switch (socoDirection)
                {
                //se for o braço direito
                case 1:
                    //enquanto não tiver finalizado o soco e o angulo de soco
                    // for menor que o max permitido
                    if(!finalizousoco && incSocoAcc<max_angle_soca){
                        incSocoAcc+=incsoco;
                        inimigo.socoDireito(incSocoAcc,raiojogador,cxjogador,cyjogador);
                        if(incSocoAcc>=max_angle_soca){
                            finalizousoco=true;
                        }
                    }
                    //enquanto incSocoAcc for maior do que zero
                    //retorne o soco para a posição inicial
                    //decrementando o acumulador
                    else if(incSocoAcc>0 && finalizousoco) {
                        incSocoAcc-= incsoco;
                        inimigo.socoDireito(incSocoAcc,raiojogador,cxjogador,cyjogador);
                    }
                    //quando retornado sorteie novamente o braço
                    //resete as variaveis de estados
                    else {
                        finalizousoco=false;
                        incSocoAcc = 0;
                        socoDirection = rand()%2+1;
                    }
                    break;
                //Se for o braço esquerdo
                case 2:
                    //Mesma situação enquanto não finalizar o soco
                    // e enquanto for maior que o -angulo maximo
                    if(!finalizousoco && incSocoAcc>-max_angle_soca){
                        incSocoAcc-=incsoco;
                        inimigo.socoEsquerdo(incSocoAcc,raiojogador,cxjogador,cyjogador);
                        if(incSocoAcc<=-max_angle_soca){
                            finalizousoco=true;
                        }
                    }
                    //incrementa para retornar a posição original
                    else if(incSocoAcc<0 && finalizousoco) {
                        incSocoAcc+= incsoco;
                        inimigo.socoEsquerdo(incSocoAcc,raiojogador,cxjogador,cyjogador);
                    }
                    //reseta e sorteia quando terminado o movimento de soco
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
    }
    glutPostRedisplay();
}
//inicializa o sistema gráfico
void init(void){
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    //obtem os parametros da arena
    GLdouble width,height;
    GLfloat  x,y;
    arena.obtemAlturaLargura(width,height);
    arena.ObtemOrigem(x,y);
    //inicializa a camera de visualização
    glMatrixMode(GL_PROJECTION);
    //define a origem sempre a partir da origem
    //da arena
    glOrtho(x,x+width,y,y+height,-100,100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
//função principal
int main (int argc, char* argv[]){
    //pega o nome do arquivo
    string filename;
    filename = argv[1];
    Util utilidades(filename);
    //Inicializando os objetos arena,inimigo e jogador
    utilidades.parsesElements(arena,inimigo,jogador);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    //Criando janela
    GLdouble width,height;
    arena.obtemAlturaLargura(width,height);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(150,50);
    glutCreateWindow("Box-Game-CREDS_LIKE");
    //Instanciando as callbacks
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