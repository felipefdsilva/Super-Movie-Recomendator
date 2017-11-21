/*
* Universidade Federal do Rio de Janeiro
* Departamento de Engenharia Eletrônica e de Computação
* Linguagens de Programação 2017.2
* Professor Miguel Campista
* Autor: Felipe Ferreira da Silva
* Trabalho do Período - Parte 3 (C++)
* Recomendador de Filmes e Maratonas
* Implementação da Classe Movie
*/

#include "movie.h"

ostream &operator<< (ostream &output, const Movie &movie){
  output << "Title: " << movie.getName ()
          << "\nYear: " << movie.getYear ()
          << "\nDirector: " << movie.getAuthor ()
          << "\nSisnopsys: " << movie.mSinopsys
          << "\nLength: " << movie.mLength
          << "\nRating: " << movie.mRating
          << endl;

  output << "Actors: ";
  for (unsigned i = 0; i < movie.mActors.size(); i++){
    output << movie.mActors.at(i) << ", ";
  }
  output << endl;

  output << "Genres: ";
  for (unsigned i = 0; i < movie.mGenres.size(); i++){
    output << movie.mGenres.at(i) << ", ";
  }
  output << endl;

  return output;
}

Movie::Movie (string movieName, string director, unsigned year,
string sinopsys, unsigned length, float rating,
string *actors, unsigned sizeActors,
string *genres, unsigned sizeGenres):
Production(movieName, director, year),
mSinopsys(sinopsys), mLength(length), mRating(rating) {

  for (unsigned i = 0; i < sizeActors; i++){
    mActors.push_back(actors[i]);
  }
  for (unsigned i = 0; i < sizeGenres; i++){
    mGenres.push_back(genres[i]);
  }
}
string Movie::getSinopsys () const {
  return mSinopsys;
}
void Movie::getActors (vector <string> &actors) const {
  actors = mActors;
}
void Movie::getGenres (vector <string> &genres) const {
  genres = mGenres;
}
unsigned Movie::getLength () const {
  return mLength;
}
float Movie::getRating () const {
  return mRating;
}
