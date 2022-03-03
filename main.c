#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chroma_interpolate.h"




int  main()
{
	
	int ret = 0, in_size = 0, out_size = 0;
	unsigned char *in_data = NULL, *out_data = NULL;
	int height = 1280 , width = 720, do_adaptive_interpolator = 0, do_demomode = 0;	
	ColorSpaceConverter  coreconverter;
	FormatDescriptor src_format, dst_format;
	in_data = malloc(height*width * 2);
	out_data = malloc(height*width * 3/2);

	memset(&src_format, 0, sizeof(FormatDescriptor));
	memset(&dst_format, 0 ,sizeof(FormatDescriptor));

	init_colorspaceconverter(&coreconverter, src_format, dst_format, height, width, do_adaptive_interpolator, do_demomode);


	ret = colorspaceconvert(&coreconverter, (unsigned char *)in_data, (unsigned char *)out_data, in_size, out_size);


	return ret;
}

