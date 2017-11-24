/*
* Universidade Federal do Rio de Janeiro
* Departamento de Engenharia Eletrônica e de Computação
* Linguagens de Programação 2017.2
* Professor Miguel Campista
* Autor: Felipe Ferreira da Silva
* Trabalho do Período - Parte 3 (C++)
* Recomendador de Filmes e Maratonas
* Declaração da Classe Movie
*/
#ifndef _MOVIE_H_
#define _MOVIE_H_ "movie.h"

#include <iostream>
#include "production.h"

using namespace std;

class Movie: public Production {
  friend ostream &operator<< (ostream &, const Movie &);

  public:
    Movie (string, const unsigned = 4, const unsigned = 5);

    void splitString (string, string, vector<string> &);

    void setSinopsys (string);
    string getSinopsys () const;

    void setActors (string);
    void getActors (vector<string> &) const;

    void setGenres (string);
    void getGenres (vector<string> &) const;

    void setLength (string);
    unsigned getLength () const;

    void setRating (string, string);
    float getRating () const;

  private:
    string mSinopsys;
    unsigned mLength;
    float mRating;
    vector<string> mActors;
    vector<string> mGenres;
  };

  #endif
