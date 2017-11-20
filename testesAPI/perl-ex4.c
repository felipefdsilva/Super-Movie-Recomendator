/*
* Universidade Federal do Rio de Janeiro
* Escola Politecnica
* Departamento de Eletronica e de Computacao
* Linguagens de Programação - Turma 2017/2
* Prof. Miguel Campista
* Autor: Felipe Ferraira da Silva
*/

#define OK		0

#include <EXTERN.h>
#include <perl.h>

PerlInterpreter *my_perl; /*** The Perl interpreter  ***/

int PerlCalc (int a, int b) {
	dSP;							
	ENTER;							
	SAVETMPS;						
	PUSHMARK(SP);
	XPUSHs(sv_2mortal(newSViv(a)));
	XPUSHs(sv_2mortal(newSViv(b)));
	PUTBACK;
	call_pv("expo", G_SCALAR);
	SPAGAIN;

	int resultado = POPi;
	PUTBACK;
	FREETMPS;
	LEAVE;

	return resultado;
}


int main (int argc, char **argv, char **env){
	char *my_argv[] = {"", "calc.pl"};
	PERL_SYS_INIT3(&argc, &argv, &env);

	my_perl = perl_alloc();
	perl_construct(my_perl);
	PL_exit_flags |= PERL_EXIT_DESTRUCT_END;
	
	perl_parse(my_perl, NULL, 2, my_argv, (char **)NULL);
	perl_run(my_perl);
	
	printf("Resultado: %d\n", PerlCalc(2, 4));

	perl_destruct(my_perl);
	perl_free(my_perl);
	PERL_SYS_TERM();

	return OK;
}
