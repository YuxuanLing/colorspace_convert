//#if (defined USE_MACRO_TEMPLATES)
	#define STRINGIFY(aString) #aString
	#define STRINGIFY2(aString) STRINGIFY(aString)
	#define glue3a(name1, name2, name3) (name1 ## name2 ## name3)
	#define glue3(name1, name2, name3) glue3a(name1, name2, name3)
	//#define glue4a(name1, name2, name3, name4) (name1 ## name2 ## name3 ## name4)
	//#define glue4(name1, name2, name3, name4) glue4a(name1, name2, name3, name4)
	#define TO_STRING _to_
	//#define FUNCTION_NAME glue4(SRC_NAME, TO_STRING, DST_NAME, PARAMETER_NAME)
	#define FUNCTION_NAME glue3(SRC_NAME, TO_STRING, DST_NAME)
#if (defined USE_MACRO_TEMPLATES)	
	#if defined(BUILD_ARRAY)
		//colorconvert_funcArray[SRC_FUNCTION_INDEX][DST_FUNCTION_INDEX][PAR_INDEX] = &FUNCTION_NAME;
		colorconvert_funcArray[SRC_FUNCTION_INDEX][DST_FUNCTION_INDEX] = &FUNCTION_NAME;
	#else
		//#pragma message ( "FUNCTION_NAME: " STRINGIFY2( FUNCTION_NAME ) )
		//#pragma message ( "SRC_FUNCTION_INDEX: " STRINGIFY2( SRC_FUNCTION_INDEX ) )
		//#pragma message ( "DST_FUNCTION_INDEX: " STRINGIFY2( DST_FUNCTION_INDEX ) )
		//#if ((defined DST_PACKED) && (defined DST_4CHANNELS) && (defined DST_PIXELPERIOD1) && (defined DST_RGB) && (defined SRC_PLANAR) && (defined SRC_3CHANNELS) && (defined SRC_420) && (defined SRC_YUV601) && (defined NO_ADAPTIVE_INTERPOLATION))
		//skipping the test for 4 channels for now todo: update SSE_functions accordingly !!
		#if ((defined DST_32BPP) && (defined DST_PACKED) && (defined DST_PIXELPERIOD1) && (defined DST_RGB) && (defined SRC_PLANAR) && (defined SRC_3CHANNELS) && (defined SRC_420) && (defined SRC_YUV601) && (defined NO_ADAPTIVE_INTERPOLATION))
			#include "SSEx_functions.h"
		//#elif ((defined DST_PLANAR)&& (defined DST_3CHANNELS) && (defined DST_420) && (defined DST_YUV601) && (defined SRC_PACKED) && (defined SRC_3CHANNELS) && (defined SRC_PIXELPERIOD2) && (defined SRC_422) && (defined SRC_YUV601) && (defined SRC_16BPP) && ((SRC_CH0_BYTEPOS_0 == 0)) && ((SRC_CH0_BYTEPOS_1 == 0))&& ((SRC_CH1_BYTEPOS_0 == 1))&& ((SRC_CH2_BYTEPOS_1 == 1)))
		#elif ((defined DST_PLANAR)&& (defined DST_3CHANNELS) && (defined DST_420) && (defined DST_YUV601) && (defined SRC_PACKED) && (defined SRC_3CHANNELS) && (defined SRC_PIXELPERIOD2) && (defined SRC_422) && (defined SRC_YUV601) && (defined SRC_16BPP))
			#include "SSEx_functions.h"
		#else
			#include "colorspace_template6.h"
		#endif
	#endif
#else //fall-back to regular (slow) functionality
//#else //fall-back to regular (slow) functionality
#if defined(BUILD_ARRAY)
	//colorconvert_funcArray[0][0][0] = &FUNCTION_NAME;
	colorconvert_funcArray[0][0] = &FUNCTION_NAME;
#else
	#include "regular_function.h"
#endif
//#endif
#endif
