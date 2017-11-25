/*
* Universidade Federal do Rio de Janeiro
* Departamento de Engenharia Eletrônica e de Computação
* Linguagens de Programação 2017.2
* Professor Miguel Campista
* Autor: Felipe Ferreira da Silva
* Trabalho do Período - Parte 3 (C++)
* Recomendador de Filmes e Maratonas
* Função Principal
*/

#include "wrapper.h"
#include "marathon.h"
#include "recomendator.h"

#define OK      0

using namespace std;

int main (int argc, char **argv, char **env) {

 if (argc != 2){
   cout << "What function?" << endl;
   exit (1);
 }
 PerlWrapper perlWrapper(&argc, &argv, &env);

 char file[7] = "smr.pl";
 perlWrapper.runInterpreterWithPerlFile(file);

 if (!strcmp(argv[1], "renew"))
   perlWrapper.renewFiles();

 else if (!strcmp(argv[1], "show"))
   perlWrapper.showMovieByGenre("Dados/Drama.html");

 else if (!strcmp(argv[1], "selection")){
   const unsigned numOfParameters = 1;
   const char *parametros[numOfParameters] = {"Action"};
   vector<Movie *>retrievedMovies;

   perlWrapper.retrieveMovieCandidates ("Dados/Action.html", parametros, numOfParameters, retrievedMovies);

   Marathon marathon;
   Recomendator recomendator;
   recomendator.findThreeBestRated(retrievedMovies, marathon);

   cout << marathon << endl;
 }
 return OK;
}
