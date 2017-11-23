#include <iostream>
#include "wrapper.h"

#define OK      0

using namespace std;

int main (int argc, char **argv) {
  Marathon maratona;

  if (argc != 2){
    cout << "What function?" << endl;
    exit (1);
  }
  PerlWrapper perlWrapper;

  char file[7] = "smr.pl";
  perlWrapper.runInterpreterWithPerlFile(file);

  if (!strcmp(argv[1], "renew"))
    perlWrapper.renewFiles();
  else if (!strcmp(argv[1], "show"))
    perlWrapper.showMovieByGenre("Dados/Drama.html");
  else if (!strcmp(argv[1], "selection")){
    const char *parametros[1] = {"Kubrick"};
    perlWrapper.retrieveMovieCandidates ("Dados/Drama.html", parametros, 1, maratona);
  }
  return OK;
}
