#ifndef DEFINES
#define DEFINES

#include <iostream>
#include <sstream>

/* VISUAL_STUDIO is defined as a preprocessor directive in the Visual Studio build */
/* in visual studio, the following warnings are disabled
 * 4514 "unreferenced inline function has been removed"
 * 4820 "2 bytes padding added after data member"
 * 4710 "function not inlined"
 * 4986
 */
#ifndef VISUAL_STUDIO
#include "R.h"
#include "Rmath.h"
#else
//#ifndef MATHLIB_STANDALONE
//#define MATHLIB_STANDALONE
//#include "Rmath.h"
//#endif
#endif

#ifndef VISUAL_STUDIO
#define PRINT_MACRO Rprintf
#define ERROR_MACRO error
#define WARNING_MACRO warning
#else
#define PRINT_MACRO printf
#define ERROR_MACRO printf
#define WARNING_MACRO printf
#endif

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#endif
