typedef void (*colorconvert_function)(const ColorSpaceConverter*, const unsigned char *, unsigned char *,const int ,const int );

#if defined USE_MACRO_TEMPLATES
#define NUMBER_OF_SUPPORTED_FORMATS 31
//#define NUMBER_OF_PARAMETER_OPTIONS 2

//first, include the 2-stage include files so that we generate a 2d array of named functions
//static colorconvert_function colorconvert_funcArray[NUMBER_OF_SUPPORTED_FORMATS][NUMBER_OF_SUPPORTED_FORMATS][NUMBER_OF_PARAMETER_OPTIONS];
static colorconvert_function colorconvert_funcArray[NUMBER_OF_SUPPORTED_FORMATS + 1][NUMBER_OF_SUPPORTED_FORMATS];
#include "colorspace_template2.h"

//then, do the same inclusion process run-time to get an array of function pointers
void init_function_table()
{
	#define BUILD_ARRAY
	#include "colorspace_template2.h"
	#undef BUILD_ARRAY
}
#else //if defined USE_MACRO_TEMPLATES
//bypass all of the macro stuff and do the function directly (slow)
//static colorconvert_function colorconvert_funcArray[1][1][1];
static colorconvert_function colorconvert_funcArray[1][1];
#include "colorspace_template5.h"
void init_function_table()
{
	#define BUILD_ARRAY
	#include "colorspace_template5.h"
	#undef BUILD_ARRAY
}
#endif
