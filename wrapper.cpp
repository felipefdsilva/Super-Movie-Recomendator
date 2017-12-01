/*
* Universidade Federal do Rio de Janeiro
* Departamento de Engenharia Eletrônica e de Computação
* Linguagens de Programação 2017.2
* Professor Miguel Campista
* Autor: Felipe Ferreira da Silva
* Trabalho do Período - Parte 3 (C++)
* Recomendador de Filmes e Maratonas
* Implementação da Classe Wrapper
*/

#include "wrapper.h"

PerlWrapper::PerlWrapper (int *pArgc, char ***pArgv, char ***pEnv){
	PERL_SYS_INIT3 (pArgc, pArgv, pEnv);

	my_perl = perl_alloc();
	perl_construct (my_perl);
	PL_exit_flags |= PERL_EXIT_DESTRUCT_END;
}
PerlWrapper::~PerlWrapper (){
	perl_destruct (my_perl);
	perl_free (my_perl);
	PERL_SYS_TERM ();
}
void PerlWrapper::runInterpreterWithPerlFile (char *file){
	char nd[1] = "";
	my_argv [0] = nd;
	my_argv [1] = file;
	perl_parse (my_perl, xs_init, 0, my_argv, (char **)NULL);
	perl_run(my_perl);
}
void PerlWrapper::renewFiles (){
	dSP;
	PUSHMARK(SP);
	call_pv("getHtmlFiles", G_DISCARD|G_NOARGS);
}
void PerlWrapper::showMovieByGenre (const char *file){
	dSP;
	ENTER;
	SAVETMPS;
	PUSHMARK(SP);
	XPUSHs(sv_2mortal(newSVpvf(file, 20)));
	PUTBACK;
	call_pv("showFile", G_DISCARD);
	FREETMPS;
	LEAVE;
}
void PerlWrapper::retrieveMovieCandidates(const char *file,
																					vector<string> &parameters,
																					vector<string> &selectedMovies){
	unsigned numOfMovies;

	dSP;
	ENTER;
	SAVETMPS;
	PUSHMARK(SP);
	XPUSHs(sv_2mortal(newSVpvf("%s", file)));
	for (unsigned i = 0; i < parameters.size(); i++)
		XPUSHs(sv_2mortal(newSVpvf("%s", parameters.at(i).c_str())));
	PUTBACK;
	call_pv("moviesSelection", G_ARRAY);
	SPAGAIN;
	numOfMovies = POPi;
	for (unsigned i = 0; i < numOfMovies; i++)
		selectedMovies.push_back(POPp);
	PUTBACK;
	FREETMPS;
	LEAVE;
}

EXTERN_C void xs_init(pTHX) {
    static const char file[] = __FILE__;
    dXSUB_SYS;
    PERL_UNUSED_CONTEXT;

    /* DynaLoader is a special case */
    newXS("DynaLoader::boot_DynaLoader", boot_DynaLoader, file);
}
