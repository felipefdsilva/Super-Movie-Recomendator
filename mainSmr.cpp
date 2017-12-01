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

#include "split.h"
#include "wrapper.h"
#include "recomendator.h"

#define OK                    0
#define NOT_ENOUGH_ARGS       1
#define NOT_ENOUGH_TIME       2
#define NOT_VALID_TIME        3

#define MAX_OF_PARAMETERS     3

using namespace std;

int main (int argc, char **argv, char **env) {

  string file, ans;
  string parameters;
  vector<string> vParameters;
  vector<string> retrievedMovies;
  unsigned minTime, timeAvaliable = 0;

  PerlWrapper perlWrapper(&argc, &argv, &env);

  perlWrapper.runInterpreterWithPerlFile((char *)"smr.pl");

  if (argc != 3 && argc != 4){
    cout << "Usage: " << argv[0] << " renew database" << endl
         << "Usage: " << argv[0] << " show <file>" << endl
         << "Usage: " << argv[0] << " marathon <file> [<time limit>]" << endl;
    exit (NOT_ENOUGH_ARGS);
  }
  if (!strcmp(argv[1], "renew") && !strcmp(argv[2], "database")){
    perlWrapper.renewFiles();
    return OK;
  }
  if (!strcmp(argv[1], "show")){
    perlWrapper.showMovieByGenre(argv[2]);
    return OK;
  }
  if (!strcmp(argv[1], "marathon")){
    cout << "Give me some key-words" << endl;
    cout << "Examples: name of an actor or director, a year, a movie genre" << endl;

    getline(cin, parameters);
    splitString(parameters, " ", vParameters);

    perlWrapper.retrieveMovieCandidates (argv[2], vParameters, retrievedMovies);

    if (!retrievedMovies.size()){
      cout << "=====================================" << endl;
      cout << "The search returned no movie" << endl;
      cout << "Cannot elaborate a marathon" << endl;
      cout << "Try a less especific search" << endl;
      cout << "=====================================" << endl;
      cout << endl;
      return OK;
    }

    if (retrievedMovies.size() < 4) {
      cout << "=====================================" << endl;
      cout << "The search returned only a few movies" << endl;
      cout << "Cannot elaborate a marathon" << endl;
      cout << "=====================================" << endl;
      cout << endl;
      for (unsigned i = 0; i < retrievedMovies.size(); i++)
        cout << retrievedMovies.at(i) << endl;
        return OK;
    }

    cout << "The search returned " <<
            retrievedMovies.size() << " movies" << endl;

    Recomendator recomendator(retrievedMovies);

    if (argc == 4){
      timeAvaliable = strtoul(argv[3], NULL, 10);
      if (!timeAvaliable){
        cout << endl;
        cout << "Time limit is not valid: " << argv[3] << " minutes" << endl;
        cout << endl;
        exit(NOT_VALID_TIME);
      }
    }

    minTime = recomendator.calculateMeanTime()*3;

    if (!timeAvaliable){
      recomendator.findThreeBestRated();
    }
    else if (timeAvaliable < minTime){
      cout << endl;
      cout << "Hey, don't you have at least "<< minTime <<" minutes?" << endl;
      cout << endl;
      exit(NOT_ENOUGH_TIME);
    }
    else {
      recomendator.marathonWithTimeLimit(timeAvaliable);
    }

    cout << "=====================================" << endl;
    cout << "Ok. Here's your marathon:" << endl;
    cout << "=====================================" << endl;
    sleep(3);
    cout << endl;
    cout << recomendator.getMarathon();
    cout << "Marathon total time: " << recomendator.getMarathon().getDuration() << " minutes" << endl;
  }
  return OK;
}
