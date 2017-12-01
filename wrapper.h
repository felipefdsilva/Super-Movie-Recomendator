#ifndef _WRAPPER_H_
#define _WRAPPER_H_	"wrapper.h"

#include <EXTERN.h>
#include <perl.h>
#include <vector>
#include <string>

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

#endif
