/*
* Universidade Federal do Rio de Janeiro
* Departamento de Engenharia Eletrônica e de Computação
* Linguagens de Programação 2017.2
* Professor Miguel Campista
* Autor: Felipe Ferreira da Silva
* Trabalho do Período - Parte 3 (C++)
* Recomendador de Filmes e Maratonas
* Declaração da Classe Marathon
*/

#ifndef _MARATHON_H_
#define _MARATHON_H_  "marathon.h"

#include <map>
#include <iterator>
#include "movie.h"

class Marathon: public map<string, Movie *> {
  friend ostream &operator<< (ostream &, const Marathon &);

  public:
    Marathon (unsigned = 0);
    void calculateDuration ();
    unsigned getDuration ();

  private:
    unsigned mDuration;
};

#endif
