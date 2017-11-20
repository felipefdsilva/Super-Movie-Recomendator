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

int main (int argc, char **argv, char **env){
	char *embedding[] = {"", "-e", "0"};

	PERL_SYS_INIT3(&argc, &argv, &env);
	my_perl = perl_alloc();
	perl_construct(my_perl);
	perl_parse(my_perl, NULL, 3, embedding, NULL);
	PL_exit_flags |= PERL_EXIT_DESTRUCT_END;
	perl_run(my_perl);
	
	/*** Trata o $a como um inteiro  ***/
	eval_pv("$a = 3; $a **= 2", TRUE);
	printf("a = %ld\n", SvIV(get_sv("a", 0)));
	/*** Trata $a como um float  ***/
	eval_pv("$a = 3.14; $a **= 2", TRUE);
	printf("a = %f\n", SvNV(get_sv("a", 0)));
	/*** Trata o $a como uma string  ***/
	eval_pv("$a = 'rekcaH lreP rehtonA tsuJ'; $a = reverse($a)", TRUE);
	printf("a = %s\n", SvPV_nolen(get_sv("a", 0)));

	perl_destruct(my_perl);
	perl_free(my_perl);
	PERL_SYS_TERM();

	return OK;
}
