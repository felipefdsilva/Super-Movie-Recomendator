#include <EXTERN.h>
#include <perl.h>
#include <iostream>
#include <string>

using namespace std;

//class wrapper
class perlWrapper {
	public:
		perlWrapper ();
		~perlWrapper ();

		void runInterpreterWithPerlFile (char *file);

		int getMathResult (int a, string perlFunc);
		int getInputFileInfo (string inputFile, string perlFunc);

	private:
		PerlInterpreter *my_perl;
		char *my_argv[2];
};
