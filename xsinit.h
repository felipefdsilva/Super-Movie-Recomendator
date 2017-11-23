#ifndef _XSINIT_H_
#define _XSINIT_H_  "xsinit.h"

#include <EXTERN.h>
#include <perl.h>
#include "XSUB.h"

EXTERN_C void xs_init (pTHX);
EXTERN_C void boot_DynaLoader (pTHX_ CV* cv);

#endif
