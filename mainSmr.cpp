#include <iostream>
#include <string>
#include <iterator>
#include "wrapper.h"
#include "movie.h"

#define OK      0

using namespace std;

int main (int argc, char **argv, char **env) {

 vector<string>retrievedMovies;

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
   const char *parametros[1] = {"Kubrick"};
   perlWrapper.retrieveMovieCandidates ("Dados/Drama.html",
                                         parametros,
                                         1,
                                         retrievedMovies);
   Movie movie1 (retrievedMovies.at(0));
   Movie movie2 (retrievedMovies.at(1));
   cout << movie1 << endl;
   cout << movie2 << endl;
 }
 return OK;
}
