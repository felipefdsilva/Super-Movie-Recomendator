#ifndef _WRAPPER_H_
#define _WRAPPER_H_	"wrapper.h"

#include <EXTERN.h>
#include <perl.h>
#include "XSUB.h"
#include "marathon.h"

using namespace std;

EXTERN_C void xs_init (pTHX);
EXTERN_C void boot_DynaLoader (pTHX_ CV* cv);

class PerlWrapper {
	public:
		PerlWrapper ();
		~PerlWrapper ();
		void runInterpreterWithPerlFile (char *file);
		void renewFiles ();
		void showMovieByGenre (const char *);
		void retrieveMovieCandidates (const char *,
																	const char **,
																	unsigned,
																	Marathon &);

	private:
		PerlInterpreter *my_perl;
		char *my_argv[2];
};

#endif
