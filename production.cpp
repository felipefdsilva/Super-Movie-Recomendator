/*
* Universidade Federal do Rio de Janeiro
* Departamento de Engenharia Eletrônica e de Computação
* Linguagens de Programação 2017.2
* Professor Miguel Campista
* Autor: Felipe Ferreira da Silva
* Trabalho do Período - Parte 3 (C++)
* Recomendador de Filmes e Maratonas
* Implementação da Classe Production
*/

#include "production.h"

Production::Production (string name, string author, unsigned year):
                        mName(name), mAuthor(author), mYear (year){}
string Production::getName () const{
  return mName;
}
string Production::getAuthor () const{
  return mAuthor;
}
unsigned Production::getYear() const {
  return mYear;
}
