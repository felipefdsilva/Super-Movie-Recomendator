/*
* Universidade Federal do Rio de Janeiro
* Departamento de Engenharia Eletrônica e de Computação
* Linguagens de Programação 2017.2
* Professor Miguel Campista
* Autor: Felipe Ferreira da Silva
* Trabalho do Período - Parte 3 (C++)
* Recomendador de Filmes e Maratonas
* Implementação da Classe Recomendador
*/

#include <map>
#include "recomendator.h"

void Recomendator::findThreeBestRated (const vector<Movie *> &movie, Marathon &marathon){
  unsigned i = 0;
  multimap <float, unsigned> scores;
  vector<Movie *>::const_iterator it = movie.begin();
  multimap <float, unsigned>::iterator itScore = scores.end();

  while(it != movie.end()){
    scores.insert(pair<float, unsigned>((*it)->getRating(), i));
    i++; it++;
  }
  for (unsigned i = 0; i < 3; i++) {
    marathon.push_back(movie.at((*--itScore).second));
  }
}
