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

#include <iterator>
#include "marathon.h"

ostream &operator<< (ostream &output, const Marathon &marathon){
  for (unsigned i = 0; i < marathon.size(); ++i){
    output << (*marathon.at(i)) << endl;
  }
  return output;
}

Marathon::Marathon (unsigned duration){
  mDuration = duration;
}

unsigned Marathon::calculateDuration (){
  vector<Movie *>::iterator it = begin();

  if (size() == 0)
    return 0;

  mDuration = 0;

  while (it != end()){
    mDuration += (*it)->getLength();
    it++;
  }
  return mDuration;
}

unsigned Marathon::getDuration () {
  return mDuration;
}
