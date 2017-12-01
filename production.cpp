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
#include <iostream>
#include <cstdlib>

void Production::print () const{
  cout << "Title: " << mName << endl
       << "Year: " << mYear << endl
       << "Director(s): " << mAuthor << endl;
}
void Production::setName (string name){
  mName = name;
}
string Production::getName () const{
  return mName;
}
void Production::setAuthor (string author){
  mAuthor = author;
}
string Production::getAuthor () const{
  return mAuthor;
}
void Production::setYear (string year){
  mYear = strtoul(year.c_str(), NULL, 10);
}
unsigned Production::getYear() const {
  return mYear;
}
