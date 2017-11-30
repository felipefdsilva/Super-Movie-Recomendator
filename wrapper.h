#ifndef _WRAPPER_H_
#define _WRAPPER_H_	"wrapper.h"

#include <EXTERN.h>
#include <perl.h>
#include <vector>
#include <string>
#include "movie.h"

using namespace std;

class PerlWrapper {
	public:
		PerlWrapper (int *, char ***, char ***);
		~PerlWrapper ();
		void runInterpreterWithPerlFile (char *file);
		void renewFiles ();
		void showMovieByGenre (const char *);
		void retrieveMovieCandidates (const char *,
																	string *,
																	unsigned,
																	vector<Movie *> &);

	private:
		PerlInterpreter *my_perl;
		char *my_argv[2];
};

#endif
