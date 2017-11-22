/*
* Universidade Federal do Rio de Janeiro
* Departamento de Engenharia Eletrônica e de Computação
* Linguagens de Programação 2017.2
* Professor Miguel Campista
* Autor: Felipe Ferreira da Silva
* Trabalho do Período - Parte 3 (C++)
* Recomendador de Filmes e Maratonas
* Teste para a classe Maratona
*/

#include "movie.h"
#include "marathon.h"

#define OK    0

int main (){
  string actors[3] = {"Mark Hammil", "Harrison Ford", "Chewbacca"};
  string genres[3] = {"Adventure", "Action", "Sci-fi"};
  Movie movie1
  ("Star Wars", "George Lucas", 1978,
  "A long time ago, in a galaxy far, far away...",
  138, 8.8, 7.0, actors, 3, genres, 3);


  string actors2[3] = {"Gal Gadot", "Matt Damon", "Batman"};
  string genres2[3] = {"Adventure", "Action", "Sci-fi"};
  Movie movie2
  ("Mulher Maravilha", "Rob Reiner", 2017,
  "Wonder Woman has to save the world.",
  160, 7.9, 6.9, actors2, 3, genres2, 3);

  string actors3[3] = {"Antonio Banderas", "Salma Hayek", "Quentin Tarantino"};
  string genres3[3] = {"Crime", "Action", "Drama"};
  Movie movie3
  ("A Balada do Pistoleiro", "Robert Rodriguez", 1999,
  "A Mariachi/Outlaw seeks revenge after the death of his wife",
  125, 6.5, 7.0, actors3, 3, genres3, 3);

  Marathon maratona;

  maratona.insert(map<string, Movie *>::value_type(movie1.getName(), &movie1));
  maratona.insert(map<string, Movie *>::value_type(movie2.getName(), &movie2));
  maratona.insert(map<string, Movie *>::value_type(movie3.getName(), &movie3));

  cout << "Duração da maratona: " << maratona.getDuration() << "\n" << endl;

  cout << maratona;

  return OK;
}
