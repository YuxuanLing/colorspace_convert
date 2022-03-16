#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cutil.h"
#include "chroma_interpolate.h"




int main(int argc, char* argv[])
{
	FILE* fp_in, * fp_out;
	char* inName = NULL, * outName = NULL;
	int frmCoverted = 0, frmToCovert = -1;
	int srcWidth = -1, dstWidth = -1;
	int srcHeight = -1, dstHeight = -1;
	int srcChannel = 4, dstChannel = 4;
	int c = 0;
	int converType = 0;
	int srcStride = -1;
	int dstStride = -1;
	int srcFrmBytes = -1;
	int dstFrmBytes = -1;
	const char* optstring = "?t:w:h:s:a:b:c:f:i:o:";

	struct option opts[] = {
	   {"help", 0, NULL, '?'},
	   {"type", 1, NULL, 't'},
	   {"sW", 1, NULL, 'w'},
	   {"sH", 1, NULL, 'h'},
	   {"sS", 1, NULL, 's'},
	   {"dW", 1, NULL, 'a'},
	   {"dH", 1, NULL, 'b'},
	   {"dS", 1, NULL, 'c'},
	   {"frms", 1, NULL, 'f'},
	   {"input", 1, NULL, 'i'},
	   {"output", 1, NULL, 'o'}
	};


	//while ( (c = getopt(argc, argv, "w:h:f:i:o:t:?")) != -1) {
	while ((c = getopt_long(argc, argv, optstring, opts, NULL)) != -1) {
		switch (c) {
		case '?':
			printf("useage : --type convType --sW srcW --sH srcH --sS srcStride --dW dstW --dH dstH --dS dstStride --frms frames --input inFile --output outFile");
			return 0;
		case 't':
			converType = atoi(optarg);
			break;
		case 'w':
			srcWidth = atoi(optarg);
			break;
		case 'h':
			srcHeight = atoi(optarg);
			break;
		case 's':
			srcStride = atoi(optarg);
			break;
		case 'a':
			dstWidth = atoi(optarg);
			break;
		case 'b':
			dstHeight = atoi(optarg);
			break;
		case 'c':
			dstStride = atoi(optarg);
			break;
		case 'f':
			frmToCovert = atoi(optarg);
			break;
		case 'i':
			inName = optarg;
			break;
		case 'o':
			outName = optarg;
			break;
		default:
			printf("invalid use age \n");
			printf("useage : --type convType --sW srcW --sH srcH --sS srcStride --dW dstW --dH dstH --dS dstStride --frms frames --input inFile --output outFile");
			return -1;
		}
	}


	if (fopen_s(&fp_in, inName, "rb") || fopen_s(&fp_out, outName, "wb"))
	{
		printf("ERROR OPEN INPUT/OUTPUT FILE\n");
		return -1;
	}

	switch (converType)
	{
	case 0:
		//BGRA8888To420P
		srcChannel = 4;
		dstChannel = 3;
		srcFrmBytes = srcStride * srcHeight;
		dstFrmBytes = dstStride * dstHeight * dstChannel / 2;
		break;
	case 1:
		//NV12ToXRGB8888
		srcChannel = 3;
		dstChannel = 4;
		srcFrmBytes = srcStride * srcHeight * srcChannel / 2;
		dstFrmBytes = dstStride * dstHeight * dstChannel;
		break;
	default:
		printf("invalid convert type ,using \n \
                0:    BGRA8888 to NV12 \n \
                1:    NV12 to BGRA8888 \n");

		return -1;
	}

	if (srcWidth <= 0 || srcHeight <= 0 || dstWidth <= 0 || dstHeight <= 0 || srcStride <= 0 || dstStride <= 0 || frmToCovert <= 0)
	{
		printf("INVALID USAGE\n");
		return -1;
	}

	void* src = (void*)malloc(srcFrmBytes);
	void* dst = (void*)malloc(dstFrmBytes);

	if (!src || !dst)
	{
		printf("ERROR TO ALLOC CONVERT MEM\n");
		return -1;
	}

	int ret = 0, do_adaptive_interpolator = 0, do_demomode = 0;	
	ColorSpaceConverter  coreconverter;
	FormatDescriptor src_format, dst_format;

	memset(&src_format, 0, sizeof(FormatDescriptor));
	memset(&dst_format, 0 ,sizeof(FormatDescriptor));

	src_format.colorspace = sRGB_PC;
	src_format.organisation = PACKED;
	src_format.width  = srcWidth;
	src_format.height = srcHeight;
	src_format.stride = srcStride;
	src_format.active_channels = 4;
	src_format.pixel_repeat_period = 1;

	src_format.ch0.byte_offset1 = 2;    //B
	src_format.ch0.mask1 = 0x0000ff00;
	src_format.ch0.offset = 0;
	src_format.ch0.stride = srcStride;

	src_format.ch1.byte_offset1 = 1;    //G
	src_format.ch1.mask1 = 0x00ff0000;
	src_format.ch1.offset = 1;
	src_format.ch1.stride = srcStride;

	src_format.ch2.byte_offset1 = 0;    //R
	src_format.ch2.mask1 = 0xff000000;
	src_format.ch2.offset = 2;
	src_format.ch2.stride = srcStride;

	src_format.ch3.byte_offset1 = 3;    //A
	src_format.ch3.mask1 = 0x000000ff;
	src_format.ch3.offset = 3;
	src_format.ch3.stride = srcStride;

	src_format.active_bpp = 32;
	src_format.total_bpp = 32;

	dst_format.colorspace = BT709;
	dst_format.organisation = PLANAR;
	dst_format.width = dstWidth;
	dst_format.height = dstHeight;
	dst_format.stride = dstStride;
	dst_format.active_channels = 3;
	dst_format.chromalayout.horz_subs_factor = 2;
	dst_format.chromalayout.vert_subs_factor = 2;

	dst_format.ch0.byte_offset1 = 0;    //Y
	dst_format.ch0.mask1 = 0xff000000;
	dst_format.ch0.offset = 0;
	dst_format.ch0.stride = dstStride;

	//for 420P
	dst_format.ch1.byte_offset1 = 1;    //U
	dst_format.ch1.mask1 = 0x00ff0000;
	dst_format.ch1.offset = dstStride*dstHeight;
	dst_format.ch1.stride = dstStride/2;

	dst_format.ch2.byte_offset1 = 2;    //V
	dst_format.ch2.mask1 = 0x0000ff00;
	dst_format.ch2.offset = dstStride * dstHeight + (dstStride /2)*(dstHeight/2);
	dst_format.ch2.stride = dstStride/2;

	dst_format.ch1.byte_offset1 = 1;    //U
	dst_format.ch1.mask1 = 0x00ff0000;
	dst_format.ch1.offset = dstStride * dstHeight;
	dst_format.ch1.stride = dstStride;

	dst_format.ch2.byte_offset1 = 2;    //V
	dst_format.ch2.mask1 = 0x0000ff00;
	dst_format.ch2.offset = dstStride * dstHeight + 1;
	dst_format.ch2.stride = dstStride;

	dst_format.active_bpp = 24;
	dst_format.total_bpp = 24;


	init_colorspaceconverter(&coreconverter, src_format, dst_format, dstHeight, dstWidth, do_adaptive_interpolator, do_demomode);

	while (!feof(fp_in) && frmCoverted < frmToCovert)
	{
		size_t ret = fread_s((void*)src, srcFrmBytes, 1, srcFrmBytes, fp_in);
		if (ret != srcFrmBytes)
		{
			break;
		}
		TRACE_QUERY_START
	    ret = colorspaceconvert(&coreconverter, (unsigned char *)src, (unsigned char *)dst, srcFrmBytes, dstFrmBytes);
		TRACE_QUERY_FROM_LAST("WxH %d x %d Convert Time Elapsed In MS = %f idx=%d \n", srcWidth, srcHeight, elapsedTimeInMS, frmCoverted);

	    frmCoverted++;
	    fwrite(dst, 1, dstFrmBytes, fp_out);
	}

	free(src);
	free(dst);

	fclose(fp_in);
	fclose(fp_out);


	getchar();
	return ret;
}

