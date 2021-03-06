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
#include <ctime>
#include <cstdlib>
#include "recomendator.h"

Recomendator::Recomendator (vector<string> &movies){
  for (unsigned i = 0; i < movies.size(); i++){
    movieList.push_back(new Movie(movies.at(i)));
  }
}
Recomendator::~Recomendator (){
  for (unsigned i = 0; i < movieList.size(); i++){
    delete movieList.at(i);
  }
}
unsigned Recomendator::calculateMeanTime (){
  unsigned meanTime = 0;

  for (unsigned i = 0; i < movieList.size(); i++){
    meanTime += movieList.at(i)->getLength();
  }
  return meanTime/movieList.size();
}

void Recomendator::marathonWithTimeLimit (unsigned timeDisp){
  srand(time(NULL));
  unsigned tries = 0;
  unsigned indexList[3];
  do {
    indexList[0] = rand() % movieList.size();
    do {
      indexList[1] = rand() % movieList.size();
    } while (indexList[1] == indexList[0]);
    do {
      indexList[2] = rand() % movieList.size();
    } while (indexList[2] == indexList[1] || indexList[2] == indexList[0]);

    for (unsigned i = 0; i < 3; i++){
      marathon.push_back(movieList.at(indexList[i]));
    }
    if (marathon.calculateDuration() > timeDisp){
      for (unsigned i = 0; i < 3; i++){
        marathon.pop_back();
      }
      if (++tries > 1000000000){
        cout << "Could not create marathon";
        break;
      }
    }
  } while (marathon.getDuration() > timeDisp);
}

void Recomendator::findThreeBestRated (){
  unsigned i = 0;
  multimap <float, unsigned> scores;
  vector<Movie *>::const_iterator it = movieList.begin();
  multimap <float, unsigned>::iterator itScore = scores.end();

  while(it != movieList.end()){
    scores.insert(pair<float, unsigned>((*it)->getRating(), i));
    i++; it++;
  }
  for (unsigned i = 0; i < 3; i++) {
    marathon.push_back(movieList.at((*--itScore).second));
  }
  marathon.calculateDuration();
}

Marathon Recomendator::getMarathon () const{
  return marathon;
}
