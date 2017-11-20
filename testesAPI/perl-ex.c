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
	/* inicialização */
	PERL_SYS_INIT3(&argc, &argv, &env);

	/* criação de um interpretador  */
	my_perl = perl_alloc();
	perl_construct(my_perl);
	PL_exit_flags |= PERL_EXIT_DESTRUCT_END;

	/* invocação do perl com argumentos  */
	int perl_argc = 3;
	char *code = "print scalar (localtime).\"\\n\"";
	char *perl_argv [] = {argv[0], "-e", code};
	perl_parse(my_perl, NULL, perl_argc, perl_argv, NULL);
	perl_run(my_perl);

	/* limpeza  */
	perl_destruct(my_perl);
	perl_free(my_perl);

	/* término  */
	PERL_SYS_TERM();

	return OK;
}
