/*
* Universidade Federal do Rio de Janeiro
* Departamento de Engenharia Eletrônica e de Computação
* Linguagens de Programação 2017.2
* Professor Miguel Campista
* Autor: Felipe Ferreira da Silva
* Trabalho do Período - Parte 3 (C++)
* Recomendador de Filmes e Maratonas
* Implementação da Classe Marathon
*/

#include "marathon.h"

ostream &operator<< (ostream &output, const Marathon &marathon){
  map<string, Movie *>::const_iterator it = marathon.begin();

  while(it != marathon.end()){
    cout << (*it->second) << endl;
    it++;
  }
}

Marathon::Marathon (unsigned duration){
  mDuration = duration;
}
void Marathon::calculateDuration (){
  map<string, Movie *>::iterator it = begin();
  while (it != end()){
    mDuration += (*it).second->getLength();
    it++;
  }
}
unsigned Marathon::getDuration () {
  calculateDuration();
  return mDuration;
}
