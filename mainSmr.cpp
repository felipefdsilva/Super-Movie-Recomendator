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
 string genero;

 if (!strcmp(argv[1], "renew"))
   perlWrapper.renewFiles();

 else if (!strcmp(argv[1], "show"))
   perlWrapper.showMovieByGenre("Dados/Drama.html");

 else if (!strcmp(argv[1], "selection")){
   unsigned timeDisp = 0;
   const unsigned numOfParameters = 1;
   vector<Movie *>retrievedMovies;

   const char *parametros[numOfParameters] = {"Action"};

   perlWrapper.retrieveMovieCandidates ("Dados/Action.html", parametros, numOfParameters, retrievedMovies);

   Recomendator recomendator(retrievedMovies);
   //recomendator.findThreeBestRated();
   unsigned minTime = recomendator.calculateMeanTime()*3;

   while (timeDisp < minTime) {
     cout << "Quanto tempo disponiel?" << endl;
     cin >> timeDisp;
     if (timeDisp < minTime)
      cout << "Muito pouco! Não tem pelo menos "<< minTime <<" minutos?" << endl;
   }
   recomendator.marathonWithTimeLimit(timeDisp);

   cout << recomendator.getMarathon() << endl;
   cout << "Tempo Total de Maratona: " << (recomendator.getMarathon()).getDuration() << " minutos" << endl;
 }
 return OK;
}
