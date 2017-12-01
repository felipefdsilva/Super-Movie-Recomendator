/*
* Universidade Federal do Rio de Janeiro
* Departamento de Engenharia Eletrônica e de Computação
* Linguagens de Programação 2017.2
* Professor Miguel Campista
* Autor: Felipe Ferreira da Silva
* Trabalho do Período - Parte 3 (C++)
* Recomendador de Filmes e Maratonas
* Definição da Classe Wrapper
*/

#ifndef _WRAPPER_H_
#define _WRAPPER_H_	"wrapper.h"

#include <EXTERN.h>
#include <perl.h>
#include <vector>
#include <string>
#include "XSUB.h"

using namespace std;

class PerlWrapper {
	public:
		PerlWrapper (int *, char ***, char ***);
		~PerlWrapper ();
		void runInterpreterWithPerlFile (char *);
		void renewFiles ();
		void showMovieByGenre (const char *);
		void retrieveMovieCandidates (const char *, vector<string> &, vector<string> &);

	private:
		PerlInterpreter *my_perl;
		char *my_argv[2];
};

EXTERN_C void xs_init (pTHX);
EXTERN_C void boot_DynaLoader (pTHX_ CV* cv);

#endif
