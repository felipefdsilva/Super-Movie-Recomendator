/*
* Universidade Federal do Rio de Janeiro
* Departamento de Engenharia Eletrônica e de Computação
* Linguagens de Programação 2017.2
* Professor Miguel Campista
* Autor: Felipe Ferreira da Silva
* Trabalho do Período - Parte 3 (C++)
* Recomendador de Filmes e Maratonas
* Declaração da Classe Recomendador
*/

#ifndef _recomendator_H_
#define _recomendator_H_ "recomendator.h"

#include "marathon.h"

class Recomendator {
  public:
    Recomendator(vector<string> &);
    ~Recomendator();
    unsigned calculateMeanTime ();
    void findThreeBestRated ();
    void marathonWithTimeLimit(unsigned);
    Marathon getMarathon () const;

  private:
    vector<Movie *> movieList;
    Marathon marathon;
};

#endif
