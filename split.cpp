/*
* Universidade Federal do Rio de Janeiro
* Departamento de Engenharia Eletrônica e de Computação
* Linguagens de Programação 2017.2
* Professor Miguel Campista
* Autor: Felipe Ferreira da Silva
* Trabalho do Período - Parte 3 (C++)
* Recomendador de Filmes e Maratonas
* Implementação da Função Global Split
*/

#include "split.h"

void splitString (string str, string delimiter, vector<string> &v){
  unsigned position = str.find(delimiter);

  while (position < str.size()){
    v.push_back(str.substr(0, position));
    str.erase(0, position+delimiter.size());
    position = str.find(delimiter);
  }
  if (str.size())
    v.push_back(str);
}
