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

  string file, ans;
  string parameters[4];
  unsigned numOfParameters = 0;
  vector<Movie *>retrievedMovies;
  unsigned minTime, timeAvaliable;

  PerlWrapper perlWrapper(&argc, &argv, &env);

  perlWrapper.runInterpreterWithPerlFile((char *)"smr.pl");

  if (argc != 2){
    cout << "The options are:" << endl;
    cout << "\"renew database\", \"show file\", \"marathon\"" << endl;
    exit (1);
  }
  if (!strcmp(argv[1], "renew database")){
    perlWrapper.renewFiles();
    return OK;
  }
  if (!strcmp(argv[1], "show file")){
    cout << "What file?" << endl;
    getline(cin, file);
    perlWrapper.showMovieByGenre(file.c_str());
    return OK;
  }
  if (!strcmp(argv[1], "marathon")){
    cout << "What file?" << endl;
    getline(cin, file);
    cout << "Give me some key-words (type \"end\" to stop)" << endl;
    cout << "Examples: name of an actor or director, a year" << endl;
    getline(cin, parameters[numOfParameters]);
    while (numOfParameters < 3 && parameters[numOfParameters].compare("end")){
        numOfParameters++;
        cout << "What else? ";
        getline(cin, parameters[numOfParameters]);
    }
    perlWrapper.retrieveMovieCandidates (file.c_str(), parameters, numOfParameters, retrievedMovies);

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
        cout << (*retrievedMovies.at(i)) << endl;
        return OK;
    }

    cout << "The search returned " <<
            retrievedMovies.size() << " movies" << endl;

    Recomendator recomendator(retrievedMovies);

    cout << "Do you have a time limit? (y/n)" << endl;
    getline(cin, ans);
    while (ans.compare("n") && (ans.compare("y"))){
      cout << "Options are \"y\" or \"n\"" << endl;
      getline(cin, ans);
    }
    if (!ans.compare("y")){
      minTime = recomendator.calculateMeanTime()*3;

      cout << "How much time do you have?" << endl;
      cin >> ans;

      timeAvaliable = strtoul(ans.c_str(), NULL, 10);

      while (timeAvaliable < minTime) {
        cout << "Don't you have at least "<< minTime <<" minutes?" << endl;
        cin >> ans;
        timeAvaliable = strtoul(ans.c_str(), NULL, 10);
      }
      recomendator.marathonWithTimeLimit(timeAvaliable);
    } else if (!ans.compare("n")){
      recomendator.findThreeBestRated();
    }
    cout << "=====================================" << endl;
    cout << "Ok. Here's your marathon:" << endl;
    cout << "=====================================" << endl;
    cout << endl;
    cout << recomendator.getMarathon() << endl;

    cout << "Marathon total time: " << recomendator.getMarathon().getDuration() << " minutes" << endl;
  }
  return OK;
}
