/*
* Universidade Federal do Rio de Janeiro
* Departamento de Engenharia Eletrônica e de Computação
* Linguagens de Programação 2017.2
* Professor Miguel Campista
* Autor: Felipe Ferreira da Silva
* Trabalho do Período - Parte 3 (C++)
* Recomendador de Filmes e Maratonas
* Teste para a classe Movie
*/

#include "movie.h"

#define OK    0

int main (){
  string actors[3] = {"Mark Hammil", "Harrison Ford", "Chewbacca"};
  string genres[3] = {"Adventure", "Action", "Scifi"};
  Movie movie
  ("Star Wars", "George Lucas", 1978,
  "A long time ago, in a galaxy far, far away...",
  138, 8.8, actors, 3, genres, 3);

  cout << movie;

  return OK;
}
