#include <EXTERN.h>
#include <perl.h>
#include <iostream>
#include <string>

using namespace std;

class perlWrapper {
	public:
		perlWrapper ();
		~perlWrapper ();

		void runInterpreterWithPerlFile (char *file);

	private:
		PerlInterpreter *my_perl;
		char *my_argv[2];
};
