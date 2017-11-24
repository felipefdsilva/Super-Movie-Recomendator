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
#include <cstdlib>

ostream &operator<< (ostream &output, const Movie &movie){
  output << "Title: " << movie.getName()
          << "\nYear: " << movie.getYear()
          << "\nDirector(s): " << movie.getAuthor()
          << "\nSisnopsys: " << movie.mSinopsys
          << "\nLength: " << movie.mLength << " min"
          << "\nRating: " << movie.getRating();

  output << "\nActors: ";
  for (unsigned i = 0; i < movie.mActors.size()-1; i++)
    output << movie.mActors.at(i) << ", ";
  output << movie.mActors.at(movie.mActors.size()-1);

  output << "\nGenres: ";
  for (unsigned i = 0; i < movie.mGenres.size()-1; i++)
    output << movie.mGenres.at(i) << ", ";
  output << movie.mGenres.at(movie.mGenres.size()-1);

  output << endl;

  return output;
}
Movie::Movie (string movie,
              const unsigned sizeOfActors,
              const unsigned sizeOfGenres):
              mActors(sizeOfActors),
              mGenres(sizeOfGenres){

  vector<string> info(9);

  splitString (movie, "\n", info);
  setName (info.at(0));
  setYear (info.at(1));
  setAuthor (info.at(7));
  setSinopsys (info.at(6));
  setLength (info.at(2));
  setActors (info.at(8));
  setGenres (info.at(3));
  setRating (info.at(4), info.at(5));
}
void Movie::splitString (string str, string delimiter, vector<string> &v){
  unsigned i = 0;
  unsigned position = str.find(delimiter);
  while (position < str.size()){
    v.at(i) = str.substr(0, position);
    str = str.erase(0, position+delimiter.size());
    position = str.find(delimiter);
    i++;
  }
  if (str.size()){
    v.at(i) = str.substr(0, str.size());
    v.resize(++i);
  } else {
    v.resize(i);
  }
}
void Movie::setSinopsys (string sinopsys){
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
void Movie::setGenres(string genres){
  splitString(genres, ", ", mGenres);
}
void Movie::getGenres (vector<string> &genres) const {
  genres = mGenres;
}
void Movie::setLength (string length){
  mLength = strtoul(length.c_str(), NULL, 10);
}
unsigned Movie::getLength () const {
  return mLength;
}
void Movie::setRating (string imdb, string metascore){
  mRating = (strtof(imdb.c_str(), NULL) + strtof(metascore.c_str(), NULL)/10) / 2;
}
float Movie::getRating () const {
  return mRating;
}
