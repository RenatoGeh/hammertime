#ifndef ENV
#define ENV

#ifdef _WIN32
	#define CLEAR "cls"
	#include "winenv.h"
#else
	#define CLEAR "clear"
	#include "stdenv.h"
#endif

#endif