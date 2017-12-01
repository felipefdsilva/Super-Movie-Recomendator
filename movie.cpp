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
#include "split.h"
#include <cstdlib>

ostream &operator<< (ostream &output, const Movie &movie){
  movie.print();
  return output;
}

Movie::Movie (string movie){

  vector<string> info;

  splitString (movie, "\n", info);

  setName (info.at(0));
  setYear (info.at(1));
  setLength (info.at(2));
  setGenres (info.at(3));
  setRating (info.at(4));
  setSinopsys (info.at(5));
  setAuthor (info.at(6));
  setActors (info.at(7));
}

void Movie::print () const {
  Production::print();

  cout  << "Sisnopsys: " << mSinopsys << endl
        << "Length: " << mLength << " min" << endl
        << "Rating: " << mRating << endl;

  cout << "Actors: ";

    for (unsigned i = 0; i < mActors.size()-1; i++)
      cout << mActors.at(i) << ", ";
    cout << mActors.at(mActors.size()-1) << endl;

    cout << "Genres: ";

    for (unsigned i = 0; i < mGenres.size()-1; i++)
      cout << mGenres.at(i) << ", ";
    cout << mGenres.at(mGenres.size()-1) << endl;

    cout << endl;
}

void Movie::setLength (const string length){
  mLength = strtoul(length.c_str(), NULL, 10);
}

unsigned Movie::getLength () const {
  return mLength;
}

void Movie::setRating (const string imdb){
  mRating = strtof(imdb.c_str(), NULL);
}

float Movie::getRating () const {
  return mRating;
}

void Movie::setGenres(string genres){
  splitString(genres, ", ", mGenres);
}

void Movie::getGenres (vector<string> &genres) const {
  genres = mGenres;
}

void Movie::setSinopsys (const string sinopsys){
  mSinopsys = sinopsys;
}

string Movie::getSinopsys () const {
  return mSinopsys;
}

void Movie::setActors (string actors){
  splitString(actors, ", ", mActors);
}

void Movie::getActors (vector<string> &actors) const {
  actors = mActors;
}
