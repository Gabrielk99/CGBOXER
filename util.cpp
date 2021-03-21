#include "util.h"
using namespace tinyxml2;

//Caminha pelos elementos do SVG
void Util :: parsesElements(Arena &arena,Inimigo &inimigo,Jogador &jogador){
    //Pega o primeiro elemento a partir da raiz
    XMLElement* pParam =  root->FirstChildElement();
    //caminha pelos elementos definidos pelo svg
    while(pParam){
        //pega o nome do elemento
        string name = pParam->Name();
        //Verifica se é retangulo,ou circulo
        if(!name.compare("rect")){
            //pega todas as propriedades da arena e constroi
            //o objeto arena
           arena = return_proprieties_Arena(pParam);
        }

        else if(!name.compare("circle")){
            //pega todas as propriedades do jogador e inimigo
            //e define nos parametros inimigo e jogador
            return_proprieties_JogadorOrInimigo(pParam,inimigo,jogador);
        }
        //vai para o proximo elemento
        pParam = pParam->NextSiblingElement();
    }
    //limpa o doc
    doc.Clear();
   
    //pega altura e largura da arena
    GLdouble altura,largura;
    GLfloat x,y;
    arena.obtemAlturaLargura(largura,altura);
    arena.ObtemOrigem(x,y);
    jogador.redefinecy(altura,y);
    inimigo.redefinecy(altura,y);
    
    //pega o centro do inimigo e acha o angulo de direção do jogador ao inimigo
    GLfloat cx, cy;
    inimigo.obtemcXcY(cx,cy);
    jogador.calculeAngleNarizJogador(cx,cy);
    //pega o centro do jogador e acha o angulo de direção do inimigo ao jogador
    jogador.obtemcXcY(cx,cy);
    inimigo.calculeAnlgeNarizInimigo(cx,cy);
}
//Pega as propriedades da arena
Arena Util :: return_proprieties_Arena(XMLElement* pParam){
    GLfloat x,y;
    GLdouble width,height;
    string color;
    //pega o primeiro atributo
    const XMLAttribute* attr = pParam->FirstAttribute();
    //caminha pelos atributos
    while(attr){
            //pega o nome
            string nameAt = attr->Name();
            //verifica qual atributo é e converte para número
            if(!nameAt.compare("x")){
                x =atof(attr->Value());
            }
            else if(!nameAt.compare("y")){
                y = atof(attr->Value());
            }
            else if(!nameAt.compare("width")){
                width = atof(attr->Value());
            }
            else if(!nameAt.compare("height")){
                height = atof(attr->Value());
            }
            else if(!nameAt.compare("fill")){
                color = attr->Value();
            }
           //caminha pelos atributos
            attr = attr->Next();
        }
    //retorna arena
    Arena arena = Arena(x,y,width,height,color);
    return arena;
}
//retorna propriedade de jogador ou inimigo
void Util::return_proprieties_JogadorOrInimigo(XMLElement* pParam,Inimigo &inimigo, Jogador &jogador){
    GLfloat cx;
    GLfloat cy;
    GLfloat radius;

    //pega o primeiro atributo
    const XMLAttribute* attr = pParam->FirstAttribute();
    while (attr)
    {
        // colhe o nome
       string nameAt = attr->Name();
       //confere os atributos e converte para número
       if(!nameAt.compare("cx")){
           cx = atof(attr->Value()); 
       }
       else if(!nameAt.compare("cy")){
           cy = atof(attr->Value());
       }
       else if(!nameAt.compare("r")){
           radius = atof(attr->Value());
       }
       //decide se é inimigo ou jogador
       else if(!nameAt.compare("fill")){
           string color = attr->Value();
           if(!color.compare("red")){
               inimigo =  Inimigo(cx,cy,radius,color);
           }
           else if(!color.compare("green")){
               jogador =  Jogador(cx,cy,radius,color);
           }
       }
       //caminha pelos atributos
       attr = attr->Next();
    }
}
