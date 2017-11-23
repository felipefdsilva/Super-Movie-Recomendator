#include "wrapper.h"

EXTERN_C void xs_init(pTHX) {
    static const char file[] = __FILE__;
    dXSUB_SYS;
    PERL_UNUSED_CONTEXT;

    /* DynaLoader is a special case */
    newXS("DynaLoader::boot_DynaLoader", boot_DynaLoader, file);
}
PerlWrapper::PerlWrapper (){
	PERL_SYS_INIT3 (NULL, NULL, NULL);

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
																					const char **parameters,
																					unsigned numParameters,
																					Marathon &marathon){
	dSP;
	ENTER;
	SAVETMPS;
	PUSHMARK(SP);
	XPUSHs(sv_2mortal(newSVpvf(file)));
	for (unsigned i = 0; i < numParameters; i++){
		XPUSHs(sv_2mortal(newSVpvf(parameters[i])));
	}
	PUTBACK;
	call_pv("moviesSelection", G_ARRAY);
	SPAGAIN;
	STRLEN len;
	unsigned numberOfMovies = POPi;
	char *movie[numberOfMovies];
	for (unsigned i = 0; i <= numberOfMovies; i++){
		movie[i] = SvPV(POPs, len);
		cout << movie[i] << endl;
	}
	PUTBACK;
	FREETMPS;
	LEAVE;
}
