#include "util.h"
using namespace tinyxml2;

void Util :: parsesElements(Arena &arena,Inimigo &inimigo,Jogador &jogador){
    XMLElement* pParam =  root->FirstChildElement();
    while(pParam){
        string name = pParam->Name();
        
        if(!name.compare("rect")){
           arena = return_proprieties_Arena(pParam);
        }
        else if(!name.compare("circle")){
            return_proprieties_JogadorOrInimigo(pParam,inimigo,jogador);
        }
        pParam = pParam->NextSiblingElement();
    }
    doc.Clear();
    GLfloat cx, cy;
    inimigo.obtemcXcY(cx,cy);
    jogador.calculeAngleNarizJogador(cx,cy);
    jogador.obtemcXcY(cx,cy);
    inimigo.calculeAnlgeNarizInimigo(cx,cy);
}
Arena Util :: return_proprieties_Arena(XMLElement* pParam){
    GLfloat x,y;
    GLdouble width,height;
    string color;
    const XMLAttribute* attr = pParam->FirstAttribute();
    while(attr){
            string nameAt = attr->Name();
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
            attr = attr->Next();
        }
    Arena arena = Arena(x,y,width,height,color);
    return arena;
}
void Util::return_proprieties_JogadorOrInimigo(XMLElement* pParam,Inimigo &inimigo, Jogador &jogador){
    GLfloat cx;
    GLfloat cy;
    GLfloat radius;

    const XMLAttribute* attr = pParam->FirstAttribute();
    while (attr)
    {
       string nameAt = attr->Name();
       if(!nameAt.compare("cx")){
           cx = atof(attr->Value()); 
       }
       else if(!nameAt.compare("cy")){
           cy = atof(attr->Value());
       }
       else if(!nameAt.compare("r")){
           radius = atof(attr->Value());
       }
       else if(!nameAt.compare("fill")){
           string color = attr->Value();
           if(!color.compare("red")){
               inimigo =  Inimigo(cx,cy,radius,color);
           }
           else if(!color.compare("green")){
               jogador =  Jogador(cx,cy,radius,color);
           }
       }
       attr = attr->Next();
    }
}
