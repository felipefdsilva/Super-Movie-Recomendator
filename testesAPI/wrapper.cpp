#include <EXTERN.h>
#include <perl.h>
#include <iostream>
#include <string>

using namespace std;

perlWrapper::perlWrapper (){
	PERL_SYS_INIT3 (NULL, NULL, NULL);

	my_perl = perl_alloc();
	perl_construct (my_perl);
	PL_exit_flags |= PERL_EXIT_DESTRUCT_END;
}

perlWrapper::~perlWrapper (){
	perl_destruct (my_perl);
	perl_free (my_perl);
	PERL_SYS_TERM ();
}

void perlWrapper::runInterpreterWithPerlFile (char *file){
	my_argv [0] = "";
	my_argv [1] = file;
	perl_parse (my_perl, 0, 2, my_argv, (char **)NULL);
	perl_run(my_perl);
}

int perlWrapper::getMathResult (int a, string perlFunc){
	dSP;
	ENTER;
	SAVETMPS;
	PUSHMARK (SP);
	XPUSHs (sv_2mortal(newSViv(valor)));
	PUTBACK;
	call_pv (perlFunc.c_str(), GSCALAR);
	SPAGAIN;

	int resultado = POPi;
	PUTBACK;
	FREETMPS;
	LEAVE;

	return resultado;
}
int perlWrapper::getInputFileInfo (string inputFile, string perlFunc){
	dSP;
	ENTER;
	SAVETMPS;
	PUSHMARK (SP);
	XPUSHs (sv_2mortal (newSVpv(inputFile.c_str (), inputFile.legth ())));
	PUTBACK;
	call_pv (perlFunc.c_str(), G_SCALAR);
	SPAGAIN;

	int resultado = POPi;
	PUTBACK;
	FREETMPS;
	LEAVE;

	return resultado;
}
