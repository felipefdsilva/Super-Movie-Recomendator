/*
* Universidade Federal do Rio de Janeiro
* Departamento de Engenharia Eletrônica e de Computação
* Linguagens de Programação 2017.2
* Professor Miguel Campista
* Autor: Felipe Ferreira da Silva
* Trabalho do Período - Parte 3 (C++)
* Recomendador de Filmes e Maratonas
* Declaração da Classe Production
*/

#ifndef _PRODUCTION_H_
#define _PRODUCTION_H_  "production.h"

#include <string>

using namespace std;

class Production {
  public:
    Production (string, string, unsigned);
    string getName () const;
    string getAuthor () const;
    unsigned getYear() const;
  private:
    string mName, mAuthor;
    unsigned mYear;
};

#endif
