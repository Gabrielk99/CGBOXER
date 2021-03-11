#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>
#include "tinyxml2.h"
#include <string>
#include "arena.h"
#include "jogador.h"
#include "inimigo.h"
using namespace tinyxml2;
using namespace std;
class Util
{
    string svgfilename;
    XMLDocument doc;
    XMLElement*  root;
    XMLError lido;
private:
  
public:
    Util(string filename){
        svgfilename = filename;
        lido = doc.LoadFile(svgfilename.c_str());
        if(lido==XML_SUCCESS){
            root = doc.FirstChildElement("svg");
        }
    }
    Arena  return_proprieties_Arena(XMLElement* pParam);
    void  return_proprieties_JogadorOrInimigo(XMLElement* pParam,Inimigo &inimigo,Jogador &jogador);
    void parsesElements(Arena &arena,Inimigo &inimigo,Jogador &jogador);
   
};






















#endif /* UTIL_H */