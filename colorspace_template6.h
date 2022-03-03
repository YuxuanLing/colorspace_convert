#pragma warning (disable:177)
#pragma warning (disable:193)

//MACROS FOR WRITING PACKED FORMATS
//rgba32
#define WRITE_ONE_PACKED_PIXEL_0123(ptr1, ch0, ch1, ch2, ch3)\
	*((ptr1)) = (ch0);\
	*((ptr1)+1) = (ch1);\
	*((ptr1)+2) = (ch2);\
	*((ptr1)+3) = (ch3);

//argb32
#define WRITE_ONE_PACKED_PIXEL_3012(ptr1, ch0, ch1, ch2, ch3)\
	*((ptr1)) = (ch3);\
	*((ptr1)+1) = (ch0);\
	*((ptr1)+2) = (ch1);\
	*((ptr1)+3) = (ch2);

//bgra32
#define WRITE_ONE_PACKED_PIXEL_2103(ptr1, ch0, ch1, ch2, ch3)\
	*((ptr1)) = (ch2);\
	*((ptr1)+1) = (ch1);\
	*((ptr1)+2) = (ch0);\
	*((ptr1)+3) = (ch3);

//abgr32
#define WRITE_ONE_PACKED_PIXEL_3210(ptr1, ch0, ch1, ch2, ch3)\
	*((ptr1)) = (ch3);\
	*((ptr1)+1) = (ch2);\
	*((ptr1)+2) = (ch1);\
	*((ptr1)+3) = (ch0);

//rgbx32
#define WRITE_ONE_PACKED_PIXEL_012x(ptr1, ch0, ch1, ch2, ch3)\
	*((ptr1)) = (ch0);\
	*((ptr1)+1) = (ch1);\
	*((ptr1)+2) = (ch2);

//xrgb32
#define WRITE_ONE_PACKED_PIXEL_x012(ptr1, ch0, ch1, ch2, ch3)\
	*((ptr1)+1) = (ch0);\
	*((ptr1)+2) = (ch1);\
	*((ptr1)+3) = (ch2);

//bgrx32
#define WRITE_ONE_PACKED_PIXEL_210x(ptr1, ch0, ch1, ch2, ch3)\
	*((ptr1)) = (ch2);\
	*((ptr1)+1) = (ch1);\
	*((ptr1)+2) = (ch0);

//xbgr32
#define WRITE_ONE_PACKED_PIXEL_x210(ptr1, ch0, ch1, ch2, ch3)\
	*((ptr1)+1) = (ch2);\
	*((ptr1)+2) = (ch1);\
	*((ptr1)+3) = (ch0);

//rgb24
#define WRITE_ONE_PACKED_PIXEL_012(ptr1, ch0, ch1, ch2, ch3)\
	*((ptr1)) = (ch0);\
	*((ptr1)+1) = (ch1);\
	*((ptr1)+2) = (ch2);

//rgb24
#define WRITE_ONE_PACKED_PIXEL_210(ptr1, ch0, ch1, ch2, ch3)\
	*((ptr1)) = (ch2);\
	*((ptr1)+1) = (ch1);\
	*((ptr1)+2) = (ch0);

//yuyv
#define WRITE_TWO_PACKED_PIXELS_01_02(ptr1, ptr2, ch0_1, ch1_1, ch2_1, ch3_1, ch0_2, ch1_2, ch2_2, ch3_2)\
	*((ptr1)) = (ch0_1);\
	*((ptr1)+1) = (ch1_1);\
	*((ptr2)) = (ch0_2);\
	*((ptr2)+1) = (ch2_2);

//yvyu
#define WRITE_TWO_PACKED_PIXELS_02_01(ptr1, ptr2, ch0_1, ch1_1, ch2_1, ch3_1, ch0_2, ch1_2, ch2_2, ch3_2)\
	*((ptr1)) = (ch0_1);\
	*((ptr1)+1) = (ch2_1);\
	*((ptr2)) = (ch0_2);\
	*((ptr2)+1) = (ch1_2);

//uyvy
#define WRITE_TWO_PACKED_PIXELS_10_20(ptr1, ptr2, ch0_1, ch1_1, ch2_1, ch3_1, ch0_2, ch1_2, ch2_2, ch3_2)\
	*((ptr1)) = (ch1_1);\
	*((ptr1)+1) = (ch0_1);\
	*((ptr2)) = (ch2_2);\
	*((ptr2)+1) = (ch0_2);

//vyuy
#define WRITE_TWO_PACKED_PIXELS_20_10(ptr1, ptr2, ch0_1, ch1_1, ch2_1, ch3_1, ch0_2, ch1_2, ch2_2, ch3_2)\
	*((ptr1)) = (ch2_1);\
	*((ptr1)+1) = (ch0_1);\
	*((ptr2)) = (ch2_1);\
	*((ptr2)+1) = (ch0_2);

//MACROS FOR READING PACKED FORMATS
//rgba32
#define READ_ONE_PACKED_PIXEL_0123(ptr1, ch0, ch1, ch2, ch3)\
	(ch0) = *((ptr1));\
	(ch1) = *((ptr1)+1);\
	(ch2) = *((ptr1)+2);\
	(ch3) = *((ptr1)+3);

//argb32
#define READ_ONE_PACKED_PIXEL_3012(ptr1, ch0, ch1, ch2, ch3)\
	(ch3) = *((ptr1));\
	(ch0) = *((ptr1)+1);\
	(ch1) = *((ptr1)+2);\
	(ch2) = *((ptr1)+3);

//bgra32
#define READ_ONE_PACKED_PIXEL_2103(ptr1, ch0, ch1, ch2, ch3)\
	(ch2) = *((ptr1));\
	(ch1) = *((ptr1)+1);\
	(ch0) = *((ptr1)+2);\
	(ch3) = *((ptr1)+3);

//abgr32
#define READ_ONE_PACKED_PIXEL_3210(ptr1, ch0, ch1, ch2, ch3)\
	(ch3) = *((ptr1));\
	(ch2) = *((ptr1)+1);\
	(ch1) = *((ptr1)+2);\
	(ch0) = *((ptr1)+3);

//rgbx32
#define READ_ONE_PACKED_PIXEL_012x(ptr1, ch0, ch1, ch2, ch3)\
	(ch0) = *((ptr1));\
	(ch1) = *((ptr1)+1);\
	(ch2) = *((ptr1)+2);

//xrgb32
#define READ_ONE_PACKED_PIXEL_x012(ptr1, ch0, ch1, ch2, ch3)\
	(ch0) = *((ptr1)+1);\
	(ch1) = *((ptr1)+2);\
	(ch2) = *((ptr1)+3);

//bgrx32
#define READ_ONE_PACKED_PIXEL_210x(ptr1, ch0, ch1, ch2, ch3)\
	(ch2) = *((ptr1));\
	(ch1) = *((ptr1)+1);\
	(ch0) = *((ptr1)+2);

//xbgr32
#define READ_ONE_PACKED_PIXEL_x210(ptr1, ch0, ch1, ch2, ch3)\
	(ch2) = *((ptr1)+1);\
	(ch1) = *((ptr1)+2);\
	(ch0) = *((ptr1)+3);

//rgb24
#define READ_ONE_PACKED_PIXEL_012(ptr1, ch0, ch1, ch2, ch3)\
	(ch0) = *((ptr1));\
	(ch1)= *((ptr1)+1);\
	(ch2) = *((ptr1)+2);

//rgb24
#define READ_ONE_PACKED_PIXEL_210(ptr1, ch0, ch1, ch2, ch3)\
	(ch2) = *((ptr1));\
	(ch1) = *((ptr1)+1);\
	 (ch0) = *((ptr1)+2);

//yuyv
#define READ_TWO_PACKED_PIXELS_01_02(ptr1, ptr2, ch0_1, ch1_1, ch2_1, ch3_1, ch0_2, ch1_2, ch2_2, ch3_2)\
	(ch0_1) = *((ptr1));\
	(ch1_1) = *((ptr1)+1);\
	(ch0_2) = *((ptr2));\
	(ch2_2) = *((ptr2)+1);

//yvyu
#define READ_TWO_PACKED_PIXELS_02_01(ptr1, ptr2, ch0_1, ch1_1, ch2_1, ch3_1, ch0_2, ch1_2, ch2_2, ch3_2)\
	(ch0_1) = *((ptr1));\
	(ch2_1) = *((ptr1)+1);\
	(ch0_2) = *((ptr2));\
	(ch1_2) = *((ptr2)+1);

//uyvy
#define READ_TWO_PACKED_PIXELS_10_20(ptr1, ptr2, ch0_1, ch1_1, ch2_1, ch3_1, ch0_2, ch1_2, ch2_2, ch3_2)\
	(ch1_1) = *((ptr1));\
	(ch0_1) = *((ptr1)+1);\
	(ch2_2) = *((ptr2));\
	(ch0_2) = *((ptr2)+1);

//vyuy
#define READ_TWO_PACKED_PIXELS_20_10(ptr1, ptr2, ch0_1, ch1_1, ch2_1, ch3_1, ch0_2, ch1_2, ch2_2, ch3_2)\
	(ch2_1) = *((ptr1));\
	(ch0_1) = *((ptr1)+1);\
	(ch2_1) = *((ptr2));\
	(ch0_2) = *((ptr2)+1);

void FUNCTION_NAME
(const ColorSpaceConverter *colorconverter, const unsigned char *in_data, unsigned char *out_data, const int in_size, const int out_size)
{
//	int ret;
  unsigned char ch0_0[4] = {0, 0, 0, 0};
  unsigned char ch1_0[4] = {0, 0, 0, 0};
  unsigned char ch2_0[4] = {0, 0, 0, 0};
  unsigned char ch3_0[4] = {0, 0, 0, 0};
  unsigned char ch0_1[4] = {0, 0, 0, 0};
  unsigned char ch1_1[4] = {0, 0, 0, 0};
  unsigned char ch2_1[4] = {0, 0, 0, 0};
  unsigned char ch3_1[4] = {0, 0, 0, 0};
  int line = 0;
  int pix = 0;

#if defined(DST_4CHANNELS)
	const unsigned char alpha_dummy = 0xff;
#endif
#if defined(DST_PLANAR)
	const int dst_ch0_offset		=	colorconverter->dst_format.ch0.offset;
	const int dst_ch1_offset		=	colorconverter->dst_format.ch1.offset;
	const int dst_ch2_offset		=	colorconverter->dst_format.ch2.offset;
	const int dst_ch0_stride		=	colorconverter->dst_format.ch0.stride;
	const int dst_ch1_stride		=	colorconverter->dst_format.ch1.stride;
	const int dst_ch2_stride		=	colorconverter->dst_format.ch2.stride;
#endif
	const int dst_stride			=	colorconverter->dst_format.stride;
#if defined(SRC_PLANAR)
	const int src_ch0_stride		=	colorconverter->src_format.ch0.stride;
	const int src_ch0_offset		=	colorconverter->src_format.ch0.offset;
	const int src_ch1_stride		=	colorconverter->src_format.ch1.stride;
	const int src_ch1_offset		=	colorconverter->src_format.ch1.offset;
	const int src_ch2_stride		=	colorconverter->src_format.ch2.stride;
	const int src_ch2_offset		=	colorconverter->src_format.ch2.offset;
#endif
	const int src_stride			=	colorconverter->src_format.stride;
	const int src_total_byte_pr_pixel = colorconverter->src_format.total_bpp/8;
	const int dst_total_byte_pr_pixel = colorconverter->dst_format.total_bpp/8;
	const int height = colorconverter->height;
	const int width = colorconverter->width;
#if defined (DO_ADAPTIVE_INTERPOLATION)
	const int bAdaptiveIntDemomode = 1;
#endif

  if (in_size && out_size)
  {
    //FIXME: temporary hack to get rid of warnings.
  }

  assert(colorconverter->isInit);
//	ret = 0;
	{		
#ifdef __INTEL_COMPILER
		__assume_aligned(in_data,8);
		__assume_aligned(out_data,64);
#pragma ivdep
#pragma loop count (720)
#pragma vector nontemporal
#endif
		for (line = 0; line < height; line+=2)
		{
#ifdef __INTEL_COMPILER
#pragma ivdep
#pragma loop count (1280)
#endif
//#pragma unroll(8)
			for (pix = 0; pix < width; pix+=2)
			{
#if defined(SRC_PACKED)
				//if (colorconverter->src_format.organisation == PACKED)
				{
					int line1 = line*src_stride;
					int line2 = ((line + 1)*src_stride);
					int pix1 = pix*src_total_byte_pr_pixel;
					int pix2 = (pix + 1)*src_total_byte_pr_pixel;
//#if (defined (SRC_4CHANNELS) && defined (DST_4CHANNELS))//we have to propagate alpha channel through
//					READ_ONE_PACKED_PIXEL_0123	((in_data+line1+pix1), ch0_0[0], ch1_0[0], ch2_0[0], ch3_0[0]);//line 1,3,5...
//					READ_ONE_PACKED_PIXEL_0123	((in_data+line1+pix2), ch0_0[1], ch1_0[1], ch2_0[1], ch3_0[1]);					
//					READ_ONE_PACKED_PIXEL_0123	((in_data+line2+pix1), ch0_0[2], ch1_0[2], ch2_0[2], ch3_0[2]);//line 2,4,6...
//					READ_ONE_PACKED_PIXEL_0123	((in_data+line2+pix2), ch0_0[3], ch1_0[3], ch2_0[3], ch3_0[3]);
//#else
//					READ_ONE_PACKED_PIXEL_0123	((in_data+line1+pix1), ch0_0[0], ch1_0[0], ch2_0[0]);//line 1,3,5...
//					READ_ONE_PACKED_PIXEL_0123	((in_data+line1+pix2), ch0_0[1], ch1_0[1], ch2_0[1]);					
//					READ_ONE_PACKED_PIXEL_0123	((in_data+line2+pix1), ch0_0[2], ch1_0[2], ch2_0[2]);//line 2,4,6...
//					READ_ONE_PACKED_PIXEL_0123	((in_data+line2+pix2), ch0_0[3], ch1_0[3], ch2_0[3]);
//#endif
#if (( SRC_CH0_BYTEPOS_0 == 0 ) && ( SRC_CH1_BYTEPOS_0 == 1 ) && ( SRC_CH2_BYTEPOS_0 == 2 ) && ( SRC_CH3_BYTEPOS_0 == 3 ))//rgba32
					READ_ONE_PACKED_PIXEL_0123	((in_data+line1+pix1), ch0_0[0], ch1_0[0], ch2_0[0], ch3_0[0]);//line 1,3,5...
					READ_ONE_PACKED_PIXEL_0123	((in_data+line1+pix2), ch0_0[1], ch1_0[1], ch2_0[1], ch3_0[1]);					
					READ_ONE_PACKED_PIXEL_0123	((in_data+line2+pix1), ch0_0[2], ch1_0[2], ch2_0[2], ch3_0[2]);//line 2,4,6...
					READ_ONE_PACKED_PIXEL_0123	((in_data+line2+pix2), ch0_0[3], ch1_0[3], ch2_0[3], ch3_0[3]);
#elif (( SRC_CH0_BYTEPOS_0 == 1 ) && ( SRC_CH1_BYTEPOS_0 == 2 ) && ( SRC_CH2_BYTEPOS_0 == 3 ) && ( SRC_CH3_BYTEPOS_0 == 0 ))//argb32
					READ_ONE_PACKED_PIXEL_3012	((in_data+line1+pix1), ch0_0[0], ch1_0[0], ch2_0[0], ch3_0[0]);//line 1,3,5...
					READ_ONE_PACKED_PIXEL_3012	((in_data+line1+pix2), ch0_0[1], ch1_0[1], ch2_0[1], ch3_0[1]);	
					READ_ONE_PACKED_PIXEL_3012	((in_data+line2+pix1), ch0_0[2], ch1_0[2], ch2_0[2], ch3_0[2]);//line 2,4,6...
					READ_ONE_PACKED_PIXEL_3012	((in_data+line2+pix2), ch0_0[3], ch1_0[3], ch2_0[3], ch3_0[3]);
#elif (( SRC_CH0_BYTEPOS_0 == 2 ) && ( SRC_CH1_BYTEPOS_0 == 1 ) && ( SRC_CH2_BYTEPOS_0 == 0 ) && ( SRC_CH3_BYTEPOS_0 == 3 ))//bgra32
					READ_ONE_PACKED_PIXEL_2103	((in_data+line1+pix1), ch0_0[0], ch1_0[0], ch2_0[0], ch3_0[0]);//line 1,3,5...
					READ_ONE_PACKED_PIXEL_2103	((in_data+line1+pix2), ch0_0[1], ch1_0[1], ch2_0[1], ch3_0[1]);	
					READ_ONE_PACKED_PIXEL_2103	((in_data+line2+pix1), ch0_0[2], ch1_0[2], ch2_0[2], ch3_0[2]);//line 2,4,6...
					READ_ONE_PACKED_PIXEL_2103	((in_data+line2+pix2), ch0_0[3], ch1_0[3], ch2_0[3], ch3_0[3]);
#elif (( SRC_CH0_BYTEPOS_0 == 3 ) && ( SRC_CH1_BYTEPOS_0 == 2 ) && ( SRC_CH2_BYTEPOS_0 == 1 ) && ( SRC_CH3_BYTEPOS_0 == 0 ))//abgr32
					READ_ONE_PACKED_PIXEL_3210	((in_data+line1+pix1), ch0_0[0], ch1_0[0], ch2_0[0], ch3_0[0]);//line 1,3,5...
					READ_ONE_PACKED_PIXEL_3210	((in_data+line1+pix2), ch0_0[1], ch1_0[1], ch2_0[1], ch3_0[1]);	
					READ_ONE_PACKED_PIXEL_3210	((in_data+line2+pix1), ch0_0[2], ch1_0[2], ch2_0[2], ch3_0[2]);//line 2,4,6...
					READ_ONE_PACKED_PIXEL_3210	((in_data+line2+pix2), ch0_0[3], ch1_0[3], ch2_0[3], ch3_0[3]);
#elif (( SRC_CH0_BYTEPOS_0 == 0 ) && ( SRC_CH1_BYTEPOS_0 == 1 ) && ( SRC_CH2_BYTEPOS_0 == 2 ))//rgb24
					READ_ONE_PACKED_PIXEL_012	((in_data+line1+pix1), ch0_0[0], ch1_0[0], ch2_0[0], ch3_0[0]);//line 1,3,5...
					READ_ONE_PACKED_PIXEL_012	((in_data+line1+pix2), ch0_0[1], ch1_0[1], ch2_0[1], ch3_0[1]);	
					READ_ONE_PACKED_PIXEL_012	((in_data+line2+pix1), ch0_0[2], ch1_0[2], ch2_0[2], ch3_0[2]);//line 2,4,6...
					READ_ONE_PACKED_PIXEL_012	((in_data+line2+pix2), ch0_0[3], ch1_0[3], ch2_0[3], ch3_0[3]);
#elif (( SRC_CH0_BYTEPOS_0 == 2 ) && ( SRC_CH1_BYTEPOS_0 == 1 ) && ( SRC_CH2_BYTEPOS_0 == 0 ))//bgr24
					READ_ONE_PACKED_PIXEL_210	((in_data+line1+pix1), ch0_0[0], ch1_0[0], ch2_0[0], ch3_0[0]);//line 1,3,5...
					READ_ONE_PACKED_PIXEL_210	((in_data+line1+pix2), ch0_0[1], ch1_0[1], ch2_0[1], ch3_0[1]);	
					READ_ONE_PACKED_PIXEL_210	((in_data+line2+pix1), ch0_0[2], ch1_0[2], ch2_0[2], ch3_0[2]);//line 2,4,6...
					READ_ONE_PACKED_PIXEL_210	((in_data+line2+pix2), ch0_0[3], ch1_0[3], ch2_0[3], ch3_0[3]);
//rgbx32 formats are not needed as rgb24 formats will do the same?
//packed yuv formats
#elif (( SRC_CH0_BYTEPOS_0 == 0 ) && ( SRC_CH1_BYTEPOS_0 == 1 ) && ( SRC_CH0_BYTEPOS_1 == 0 ) && ( SRC_CH2_BYTEPOS_1 == 1 ))//yuyv
					READ_TWO_PACKED_PIXELS_01_02	((in_data+line1+pix1), (in_data+line1+pix2),  ch0_0[0], ch1_0[0], ch2_0[0], ch3_0[0], ch0_0[1], ch1_0[1], ch2_0[1], ch3_0[1]);//line 1,3,5...
					READ_TWO_PACKED_PIXELS_01_02	((in_data+line2+pix1), (in_data+line2+pix2), ch0_0[2], ch1_0[2], ch2_0[2], ch3_0[2], ch0_0[3], ch1_0[3], ch2_0[3], ch3_0[3]);//line 2,4,6...
#elif (( SRC_CH0_BYTEPOS_0 == 0 ) && ( SRC_CH2_BYTEPOS_0 == 1 ) && ( SRC_CH0_BYTEPOS_1 == 0 ) && ( SRC_CH1_BYTEPOS_1 == 1 ))//yvyu
					READ_TWO_PACKED_PIXELS_02_01	((in_data+line1+pix1), (in_data+line1+pix2),  ch0_0[0], ch1_0[0], ch2_0[0], lock_and_play [0], ch0_0[1], ch1_0[1], ch2_0[1], lock_and_play [1]);//line 1,3,5...
					READ_TWO_PACKED_PIXELS_02_01	((in_data+line2+pix1), (in_data+line2+pix2), ch0_0[2], ch1_0[2], ch2_0[2], ch3_0[2], ch0_0[3], ch1_0[3], ch2_0[3], ch3_0[3]);//line 2,4,6...
#elif (( SRC_CH0_BYTEPOS_0 == 1 ) && ( SRC_CH1_BYTEPOS_0 == 0 ) && ( SRC_CH0_BYTEPOS_1 == 1 ) && ( SRC_CH2_BYTEPOS_1 == 0 ))//uyvy
					READ_TWO_PACKED_PIXELS_10_20	((in_data+line1+pix1), (in_data+line1+pix2),  ch0_0[0], ch1_0[0], ch2_0[0], ch3_0[0], ch0_0[1], ch1_0[1], ch2_0[1], ch3_0[1]);//line 1,3,5...
					READ_TWO_PACKED_PIXELS_10_20	((in_data+line2+pix1), (in_data+line2+pix2), ch0_0[2], ch1_0[2], ch2_0[2], ch3_0[2], ch0_0[3], ch1_0[3], ch2_0[3], ch3_0[3]);//line 2,4,6...
#elif (( SRC_CH0_BYTEPOS_0 == 1 ) && ( SRC_CH2_BYTEPOS_0 == 0 ) && ( SRC_CH0_BYTEPOS_1 == 1 ) && ( SRC_CH1_BYTEPOS_1 == 0 ))//vyuy
					READ_TWO_PACKED_PIXELS_20_10	((in_data+line1+pix1), (in_data+line1+pix2),  ch0_0[0], ch1_0[0], ch2_0[0], ch3_0[0], ch0_0[1], ch1_0[1], ch2_0[1], ch3_0[1]);//line 1,3,5...
					READ_TWO_PACKED_PIXELS_20_10	((in_data+line2+pix1), (in_data+line2+pix2), ch0_0[2], ch1_0[2], ch2_0[2], ch3_0[2], ch0_0[3], ch1_0[3], ch2_0[3], ch3_0[3]);//line 2,4,6...
#endif//#if (( SRC_CH0_BYTEPOS_0 == 0 ) && ( SRC_CH1_BYTEPOS_0 == 1 ) && ( SRC_CH2_BYTEPOS_0 == 2 ) && ( SRC_CH3_BYTEPOS_0 == 3 ))//rgba32
#if defined(SRC_422)
					//either (ch1_0[0], ch1_0[2],ch2_0[1], ch2_0[3]) or (ch1_0[1], ch1_0[2],ch2_0[1], ch2_0[3]) contains sane data
					//as the READ_TWO_PACKED_PIXELS macro does not do interpolation.
#if !defined(SRC_CH1_BYTEPOS_0)
					ch1_0[0] = ch1_0[1];
					ch1_0[2] = ch1_0[3];
#elif !defined (SRC_CH1_BYTEPOS_1)
					ch1_0[1] = ch1_0[0];
					ch1_0[3] = ch1_0[2];
#endif
#if !defined (SRC_CH2_BYTEPOS_0)
					ch2_0[0] = ch2_0[1];
					ch2_0[2] = ch2_0[3];
#elif !defined (SRC_CH2_BYTEPOS_1)
					ch2_0[1] = ch2_0[0];
					ch2_0[3] = ch2_0[2];
#endif
#endif//defined(SRC_422)
				}
#elif defined(SRC_PLANAR)
				//else//planar format
				{
					int line_0_1 = (line *src_ch0_stride + pix);
					int line_0_2 = ((line + 1) * src_ch0_stride +pix);
					ch0_0[0] = *(in_data + src_ch0_offset + line_0_1);
					ch0_0[1] = *(in_data + src_ch0_offset + line_0_1 + 1);
					ch0_0[2] = *(in_data + src_ch0_offset + line_0_2);
					ch0_0[3] = *(in_data + src_ch0_offset + line_0_2 + 1);
#if defined (SRC_4CHANNELS)
					//if (colorconverter->src_format.active_channels == 4)
					{
						int src_ch3_offset = colorconverter->src_format.ch3.offset;
						ch3_0[0] = *(in_data + src_ch3_offset + line_0_1);
						ch3_0[1] = *(in_data + src_ch3_offset + line_0_1 + 1);
						ch3_0[2] = *(in_data + src_ch3_offset + line_0_2);
						ch3_0[3] = *(in_data + src_ch3_offset + line_0_2 + 1);
					}
#endif//if defined (SRC_3CHANNELS)
#if defined (SRC_444)
					//if (colorconverter->src_format.chromalayout.horz_subs_factor == 1
					//	&&colorconverter->src_format.chromalayout.vert_subs_factor == 1)///4:4:4
					{
						ch1_0[0] = *(in_data + src_ch1_offset + line_0_1);
						ch1_0[1] = *(in_data + src_ch1_offset + line_0_1 + 1);
						ch1_0[2] = *(in_data + src_ch1_offset + line_0_2);
						ch1_0[3] = *(in_data + src_ch1_offset + line_0_2 + 1);
						ch2_0[0] = *(in_data + src_ch2_offset + line_0_1);
						ch2_0[1] = *(in_data + src_ch2_offset + line_0_1 + 1);
						ch2_0[2] = *(in_data + src_ch2_offset + line_0_2);
						ch2_0[3] = *(in_data + src_ch2_offset + line_0_2 + 1);
					}
#elif defined (SRC_422)
					//else if (colorconverter->src_format.chromalayout.horz_subs_factor == 2 
					//	&& colorconverter->src_format.chromalayout.vert_subs_factor == 1)//4:2:2
					{
						int line_1_0 = (line * src_ch1_stride) + (pix >> 1);
						int line_1_1 = (line * src_ch1_stride) + (pix >> 1);
						ch1_0[0] = ch1_0[1] = *(in_data + src_ch1_offset + line_1_0);
						ch1_0[2] = ch1_0[3] = *(in_data + src_ch1_offset + line_1_1);
						ch2_0[0] = ch2_0[1] = *(in_data + src_ch2_offset + line_1_0);
						ch2_0[2] = ch2_0[3] = *(in_data + src_ch2_offset + line_1_1);
					}
#elif defined (SRC_420)
					//else if (colorconverter->src_format.chromalayout.horz_subs_factor == 2 
					//	&& colorconverter->src_format.chromalayout.vert_subs_factor == 2)//4:2:0
					{
					int line_1 = ((line >> 1) * src_ch1_stride) + (pix >> 1);
					ch1_0[0] = ch1_0[1] = ch1_0[2] = ch1_0[3] = *(in_data + src_ch1_offset + line_1);
					ch2_0[0] = ch2_0[1] = ch2_0[2] = ch2_0[3] = *(in_data + src_ch2_offset + line_1);
#if defined DO_ADAPTIVE_INTERPOLATION
						//if  (colorconverter->bDoAdaptiveInterpolation)
						{
							if (line > 1 && line < (height - 1) && pix > 1 && pix < (width - 1))//can only process if we have a valid 6x6/3x3 area
							{
								luma_adaptive_interp_block(
									line,//current line in full-resolution array
									pix,//current pixel in full-resolution array
									(in_data + colorconverter->src_format.ch0.offset), //full-res Y
									src_ch0_stride, //full-res Y
									(in_data + colorconverter->src_format.ch1.offset), //decimated U
									src_ch1_stride, //decimated U
									(in_data + colorconverter->src_format.ch2.offset), //decimated V
									src_ch2_stride, //decimated V
									&ch1_0[0], //interpolated U
									&ch1_0[1], //interpolated U
									&ch1_0[2], //interpolated U
									&ch1_0[3], //interpolated U
									&ch2_0[0], //interpolated V
									&ch2_0[1], //interpolated V
									&ch2_0[2], //interpolated V
									&ch2_0[3], //interpolated V
									colorconverter->bAdaptiveIntDemomode //process half frame only?
									);
							}
						}
#endif//if defined DO_ADAPTIVE_INTERPOLATION
					}
#endif//defined (SRC_444/422/420)
				}
#endif// defined(SRC_PACKED/SRC_PLANAR)
				//we should now have 2x2 full-resolution pixels in 3(4) channels located in buffer 0
#if (((defined SRC_YUV601) && (defined DST_YUV709)) || ((defined SRC_YUV601) && (defined DST_RGB)) || ((defined SRC_RGB) && (defined DST_YUV601)) || ((defined SRC_RGB) && (defined DST_YUV709)) || ((defined SRC_YUV709) && (defined DST_YUV601)) || ((defined SRC_YUV709) && (defined DST_RGB)))  
	#if ((defined SRC_YUV601) && (defined DST_RGB))
		#define IN_OFFSET_0 16
		#define IN_OFFSET_1 128
		#define IN_OFFSET_2 128

		#define MATRIX_0_TO_0 37
		#define MATRIX_1_TO_0 0
		#define MATRIX_2_TO_0 51

		#define MATRIX_0_TO_1 37
		#define MATRIX_1_TO_1 -13
		#define MATRIX_2_TO_1 -26

		#define MATRIX_0_TO_2 37
		#define MATRIX_1_TO_2 65
		#define MATRIX_2_TO_2 0

		#define OUT_OFFSET_0 16
		#define OUT_OFFSET_1 16
		#define OUT_OFFSET_2 16

		#define EXPONENT 5

		#define OUT_CH0_CLIP_LO 0
		#define OUT_CH0_CLIP_HI 255
		#define OUT_CH1_CLIP_LO 0
		#define OUT_CH1_CLIP_HI 255
		#define OUT_CH2_CLIP_LO 0
		#define OUT_CH2_CLIP_HI 255

	#elif ((defined SRC_RGB) && (defined DST_YUV601))
		#define IN_OFFSET_0 0 
		#define IN_OFFSET_1 0
		#define IN_OFFSET_2 0

		#define MATRIX_0_TO_0 33
		#define MATRIX_1_TO_0 65
		#define MATRIX_2_TO_0 13

		#define MATRIX_0_TO_1 -19
		#define MATRIX_1_TO_1 -37
		#define MATRIX_2_TO_1 56

		#define MATRIX_0_TO_2 56
		#define MATRIX_1_TO_2 -47
		#define MATRIX_2_TO_2 -9

		#define OUT_OFFSET_0 2112
		#define OUT_OFFSET_1 16448
		#define OUT_OFFSET_2 16448

		#define EXPONENT 7

		#define OUT_CH0_CLIP_LO 16
		#define OUT_CH0_CLIP_HI 235
		#define OUT_CH1_CLIP_LO 16
		#define OUT_CH1_CLIP_HI 240
		#define OUT_CH2_CLIP_LO 16
		#define OUT_CH2_CLIP_HI 240
	#elif ((defined SRC_YUV709) && (defined DST_RGB))
		#define IN_OFFSET_0 16 
		#define IN_OFFSET_1 128
		#define IN_OFFSET_2 128

		#define MATRIX_0_TO_0 37
		#define MATRIX_1_TO_0 0
		#define MATRIX_2_TO_0 57

		#define MATRIX_0_TO_1 37
		#define MATRIX_1_TO_1 -7
		#define MATRIX_2_TO_1 -17

		#define MATRIX_0_TO_2 37
		#define MATRIX_1_TO_2 68
		#define MATRIX_2_TO_2 0

		#define OUT_OFFSET_0 16
		#define OUT_OFFSET_1 16
		#define OUT_OFFSET_2 16

		#define EXPONENT 5

		#define OUT_CH0_CLIP_LO 0
		#define OUT_CH0_CLIP_HI 255
		#define OUT_CH1_CLIP_LO 0
		#define OUT_CH1_CLIP_HI 255
		#define OUT_CH2_CLIP_LO 0
		#define OUT_CH2_CLIP_HI 255	
	#elif ((defined SRC_RGB)) && ((defined DST_YUV709))
		#define IN_OFFSET_0 0 
		#define IN_OFFSET_1 0
		#define IN_OFFSET_2 0

		#define MATRIX_0_TO_0 23
		#define MATRIX_1_TO_0 79
		#define MATRIX_2_TO_0 8

		#define MATRIX_0_TO_1 -13
		#define MATRIX_1_TO_1 -43
		#define MATRIX_2_TO_1 56

		#define MATRIX_0_TO_2 56
		#define MATRIX_1_TO_2 -51
		#define MATRIX_2_TO_2 -5

		#define OUT_OFFSET_0 2112
		#define OUT_OFFSET_1 16448
		#define OUT_OFFSET_2 16448

		#define EXPONENT 7

		#define OUT_CH0_CLIP_LO 16
		#define OUT_CH0_CLIP_HI 235
		#define OUT_CH1_CLIP_LO 16
		#define OUT_CH1_CLIP_HI 240
		#define OUT_CH2_CLIP_LO 16
		#define OUT_CH2_CLIP_HI 240
	#elif ((defined SRC_YUV709) && (defined DST_YUV601))
		#define IN_OFFSET_0 16 
		#define IN_OFFSET_1 128
		#define IN_OFFSET_2 128

		#define MATRIX_0_TO_0 64
		#define MATRIX_1_TO_0 6
		#define MATRIX_2_TO_0 12

		#define MATRIX_0_TO_1 0
		#define MATRIX_1_TO_1 63
		#define MATRIX_2_TO_1 -7

		#define MATRIX_0_TO_2 0
		#define MATRIX_1_TO_2 -5
		#define MATRIX_2_TO_2 63

		#define OUT_OFFSET_0 1056
		#define OUT_OFFSET_1 8224
		#define OUT_OFFSET_2 8224

		#define EXPONENT 6

		#define OUT_CH0_CLIP_LO 16
		#define OUT_CH0_CLIP_HI 235
		#define OUT_CH1_CLIP_LO 16
		#define OUT_CH1_CLIP_HI 240
		#define OUT_CH2_CLIP_LO 16
		#define OUT_CH2_CLIP_HI 240
	#elif ((defined SRC_YUV601) && (defined DST_YUV709))
		#define IN_OFFSET_0 16 
		#define IN_OFFSET_1 128
		#define IN_OFFSET_2 128

		#define MATRIX_0_TO_0 128
		#define MATRIX_1_TO_0 -15
		#define MATRIX_2_TO_0 -27

		#define MATRIX_0_TO_1 0
		#define MATRIX_1_TO_1 130
		#define MATRIX_2_TO_1 15

		#define MATRIX_0_TO_2 0
		#define MATRIX_1_TO_2 10
		#define MATRIX_2_TO_2 131

		#define OUT_OFFSET_0 2112
		#define OUT_OFFSET_1 16448
		#define OUT_OFFSET_2 16448

		#define EXPONENT 7

		#define OUT_CH0_CLIP_LO 16
		#define OUT_CH0_CLIP_HI 235
		#define OUT_CH1_CLIP_LO 16
		#define OUT_CH1_CLIP_HI 240
		#define OUT_CH2_CLIP_LO 16
		#define OUT_CH2_CLIP_HI 240
	/*#else //for debugging only!!
		#define IN_OFFSET_0 16 
		#define IN_OFFSET_1 128
		#define IN_OFFSET_2 128

		#define MATRIX_0_TO_0 128
		#define MATRIX_1_TO_0 0
		#define MATRIX_2_TO_0 0

		#define MATRIX_0_TO_1 0
		#define MATRIX_1_TO_1 128
		#define MATRIX_2_TO_1 0

		#define MATRIX_0_TO_2 0
		#define MATRIX_1_TO_2 0
		#define MATRIX_2_TO_2 128

		#define OUT_OFFSET_0 2112
		#define OUT_OFFSET_1 16448
		#define OUT_OFFSET_2 16448

		#define EXPONENT 7

		#define OUT_CH0_CLIP_LO 16
		#define OUT_CH0_CLIP_HI 235
		#define OUT_CH1_CLIP_LO 16
		#define OUT_CH1_CLIP_HI 240
		#define OUT_CH2_CLIP_LO 16
		#define OUT_CH2_CLIP_HI 240*/
	#endif
				//if (colorconverter->src_format.colorspace != colorconverter->dst_format.colorspace)
				{
				int calc;
				int localpix;
				for (localpix = 0; localpix < 4; localpix++)
				{
					const int in_0_norm = ((int)(ch0_0)[localpix] - IN_OFFSET_0);
					const int in_1_norm = ((int)(ch1_0)[localpix] - IN_OFFSET_1);
					const int in_2_norm = ((int)(ch2_0)[localpix] - IN_OFFSET_2);
					calc = 0;
					calc += MATRIX_0_TO_0 * in_0_norm;
					calc += MATRIX_1_TO_0 * in_1_norm;
					calc += MATRIX_2_TO_0 * in_2_norm;
					calc += OUT_OFFSET_0;
					calc  = calc >> EXPONENT;
					(ch0_1)[localpix] = (unsigned char)(calc < OUT_CH0_CLIP_LO ? OUT_CH0_CLIP_LO : (calc > OUT_CH0_CLIP_HI ? OUT_CH0_CLIP_HI : calc));
					calc = 0;
					calc += MATRIX_0_TO_1 * in_0_norm;
					calc += MATRIX_1_TO_1 * in_1_norm;
					calc += MATRIX_2_TO_1 * in_2_norm;
					calc += OUT_OFFSET_1;
					calc  = calc >> EXPONENT;
					(ch1_1)[localpix] = (unsigned char)(calc < OUT_CH1_CLIP_LO ? OUT_CH1_CLIP_LO : (calc > OUT_CH1_CLIP_HI ? OUT_CH1_CLIP_HI : calc));
					calc = 0;
					calc += MATRIX_0_TO_2 * in_0_norm;
					calc += MATRIX_1_TO_2 * in_1_norm;
					calc += MATRIX_2_TO_2 * in_2_norm;
					calc += OUT_OFFSET_2;
					calc  = calc >> EXPONENT;
					(ch2_1)[localpix] = (unsigned char)(calc < OUT_CH2_CLIP_LO ? OUT_CH2_CLIP_LO : (calc > OUT_CH2_CLIP_HI ? OUT_CH2_CLIP_HI : calc));
				}
	#undef IN_OFFSET_0
	#undef IN_OFFSET_1
	#undef IN_OFFSET_2
	#undef MATRIX_0_TO_0
	#undef MATRIX_1_TO_0
	#undef MATRIX_2_TO_0
	#undef MATRIX_0_TO_1
	#undef MATRIX_1_TO_1
	#undef MATRIX_2_TO_1
	#undef MATRIX_0_TO_2
	#undef MATRIX_1_TO_2
	#undef MATRIX_2_TO_2
	#undef OUT_OFFSET_0
	#undef OUT_OFFSET_1
	#undef OUT_OFFSET_2
	#undef EXPONENT
	#undef OUT_CH0_CLIP_LO
	#undef OUT_CH0_CLIP_HI
	#undef OUT_CH1_CLIP_LO
	#undef OUT_CH1_CLIP_HI
	#undef OUT_CH2_CLIP_LO
	#undef OUT_CH2_CLIP_HI
				}
				//}
				//copy from buffer 0 to buffer 1 if no colorspace conversion
#else
				//else
				{
					ch0_1[0] = ch0_0[0];
					ch0_1[1] = ch0_0[1];
					ch0_1[2] = ch0_0[2];
					ch0_1[3] = ch0_0[3];
					ch1_1[0] = ch1_0[0];
					ch1_1[1] = ch1_0[1];
					ch1_1[2] = ch1_0[2];
					ch1_1[3] = ch1_0[3];
					ch2_1[0] = ch2_0[0];
					ch2_1[1] = ch2_0[1];
					ch2_1[2] = ch2_0[2];
					ch2_1[3] = ch2_0[3];
				}
#endif//#if (defined SRC_YUV601) && (defined DST_YUV709) || (defined SRC_YUV601) && (defined DST_RGB) || (defined SRC_RGB) && (defined DST_YUV601) || (defined SRC_RGB) && (defined DST_YUV709) || (defined SRC_YUV709) && (defined DST_YUV601) || (defined SRC_YUV709) && (defined DST_RGB)  */
				//alpha channel not used in colorspace conversion anyways
				//so copy it if it is used in both input and output
				//set it to a safe value if only used in output
#if (defined (SRC_4CHANNELS) && defined (DST_4CHANNELS))
				//if (colorconverter->src_format.active_channels == 4
				//	&& colorconverter->dst_format.active_channels == 4)
				{
					ch3_1[0] = ch3_0[0];
					ch3_1[1] = ch3_0[1];
					ch3_1[2] = ch3_0[2];
					ch3_1[3] = ch3_0[3];
				}
#elif (defined (SRC_3CHANNELS) && defined (DST_4CHANNELS))
				//else if (colorconverter->dst_format.active_channels == 3
				//	&& colorconverter->dst_format.active_channels == 4)
				{
					ch3_1[0] = alpha_dummy;
					ch3_1[1] = alpha_dummy;
					ch3_1[2] = alpha_dummy;
					ch3_1[3] = alpha_dummy;
				}
#endif//(defined (SRC_4CHANNELS) && defined (DST_4CHANNELS))
				//We should now have 2x2 pixels in the desired destination colorspace and desired number of channels
				//will do decimation and packing.
#if (defined DST_444)
#endif
#if (defined DST_422)
					ch1_0[0] = (unsigned char)((ch1_1[0] + ch1_1[1]) >> 1);
					ch1_0[2] = (unsigned char)((ch1_1[2] + ch1_1[3]) >> 1);
					ch2_0[0] = (unsigned char)((ch2_1[0] + ch2_1[1]) >> 1);
					ch2_0[2] = (unsigned char)((ch2_1[2] + ch2_1[3]) >> 1);
					ch1_1[0] = ch1_1[1] = ch1_0[0];//we dont really need to copy decimated values into both chx_1[0] and chx_1[1], but it makes life a little easier for the storing part
					ch1_1[2] = ch1_1[3] = ch1_0[2];
					ch2_1[0] = ch2_1[1] = ch2_0[0];
					ch2_1[2] = ch2_1[3] = ch2_0[2];
#endif
#if (defined DST_420)
					ch1_0[0] = (unsigned char)((ch1_1[0] + ch1_1[1] + ch1_1[2] + ch1_1[3]) >> 2);
					ch2_0[0] = (unsigned char)((ch2_1[0] + ch2_1[1] + ch2_1[2] + ch2_1[3]) >> 2);
					ch1_1[0] = ch1_1[1] = ch1_1[2] = ch1_1[3] = ch1_0[0];//we dont really need to copy decimated values into both chx_1[0] through chx_1[3], but it makes life a little easier for the storing part
					ch2_1[0] = ch2_1[1] = ch2_1[2] = ch2_1[3] = ch2_0[0];
#endif
#if (defined DST_PACKED)
				//if (colorconverter->dst_format.organisation == PACKED)
				{
					int line1 = line*dst_stride;
					int line2 = ((line + 1)*dst_stride);
					int pix1 = pix*dst_total_byte_pr_pixel;
					int pix2 = (pix + 1)*dst_total_byte_pr_pixel;
#if (( DST_CH0_BYTEPOS_0 == 0 ) && ( DST_CH1_BYTEPOS_0 == 1 ) && ( DST_CH2_BYTEPOS_0 == 2 ) && ( DST_CH3_BYTEPOS_0 == 3 ))//rgba32
					WRITE_ONE_PACKED_PIXEL_0123	((out_data+line1+pix1), ch0_1[0], ch1_1[0], ch2_1[0], ch3_1[0]);//line 1,3,5...
					WRITE_ONE_PACKED_PIXEL_0123	((out_data+line1+pix2), ch0_1[1], ch1_1[1], ch2_1[1], ch3_1[1]);					
					WRITE_ONE_PACKED_PIXEL_0123	((out_data+line2+pix1), ch0_1[2], ch1_1[2], ch2_1[2], ch3_1[2]);//line 2,4,6...
					WRITE_ONE_PACKED_PIXEL_0123	((out_data+line2+pix2), ch0_1[3], ch1_1[3], ch2_1[3], ch3_1[3]);
#elif (( DST_CH0_BYTEPOS_0 == 1 ) && ( DST_CH1_BYTEPOS_0 == 2 ) && ( DST_CH2_BYTEPOS_0 == 3 ) && ( DST_CH3_BYTEPOS_0 == 0 ))//argb32
					WRITE_ONE_PACKED_PIXEL_3012	((out_data+line1+pix1), ch0_1[0], ch1_1[0], ch2_1[0], ch3_1[0]);//line 1,3,5...
					WRITE_ONE_PACKED_PIXEL_3012	((out_data+line1+pix2), ch0_1[1], ch1_1[1], ch2_1[1], ch3_1[1]);	
					WRITE_ONE_PACKED_PIXEL_3012	((out_data+line2+pix1), ch0_1[2], ch1_1[2], ch2_1[2], ch3_1[2]);//line 2,4,6...
					WRITE_ONE_PACKED_PIXEL_3012	((out_data+line2+pix2), ch0_1[3], ch1_1[3], ch2_1[3], ch3_1[3]);
#elif (( DST_CH0_BYTEPOS_0 == 2 ) && ( DST_CH1_BYTEPOS_0 == 1 ) && ( DST_CH2_BYTEPOS_0 == 0 ) && ( DST_CH3_BYTEPOS_0 == 3 ))//bgra32
					WRITE_ONE_PACKED_PIXEL_2103	((out_data+line1+pix1), ch0_1[0], ch1_1[0], ch2_1[0], ch3_1[0]);//line 1,3,5...
					WRITE_ONE_PACKED_PIXEL_2103	((out_data+line1+pix2), ch0_1[1], ch1_1[1], ch2_1[1], ch3_1[1]);	
					WRITE_ONE_PACKED_PIXEL_2103	((out_data+line2+pix1), ch0_1[2], ch1_1[2], ch2_1[2], ch3_1[2]);//line 2,4,6...
					WRITE_ONE_PACKED_PIXEL_2103	((out_data+line2+pix2), ch0_1[3], ch1_1[3], ch2_1[3], ch3_1[3]);
#elif (( DST_CH0_BYTEPOS_0 == 3 ) && ( DST_CH1_BYTEPOS_0 == 2 ) && ( DST_CH2_BYTEPOS_0 == 1 ) && ( DST_CH3_BYTEPOS_0 == 0 ))//abgr32
					WRITE_ONE_PACKED_PIXEL_3210	((out_data+line1+pix1), ch0_1[0], ch1_1[0], ch2_1[0], ch3_1[0]);//line 1,3,5...
					WRITE_ONE_PACKED_PIXEL_3210	((out_data+line1+pix2), ch0_1[1], ch1_1[1], ch2_1[1], ch3_1[1]);	
					WRITE_ONE_PACKED_PIXEL_3210	((out_data+line2+pix1), ch0_1[2], ch1_1[2], ch2_1[2], ch3_1[2]);//line 2,4,6...
					WRITE_ONE_PACKED_PIXEL_3210	((out_data+line2+pix2), ch0_1[3], ch1_1[3], ch2_1[3], ch3_1[3]);
#elif (( DST_CH0_BYTEPOS_0 == 0 ) && ( DST_CH1_BYTEPOS_0 == 1 ) && ( DST_CH2_BYTEPOS_0 == 2 ))//rgb24
					WRITE_ONE_PACKED_PIXEL_012	((out_data+line1+pix1), ch0_1[0], ch1_1[0], ch2_1[0], ch3_1[0]);//line 1,3,5...
					WRITE_ONE_PACKED_PIXEL_012	((out_data+line1+pix2), ch0_1[1], ch1_1[1], ch2_1[1], ch3_1[1]);	
					WRITE_ONE_PACKED_PIXEL_012	((out_data+line2+pix1), ch0_1[2], ch1_1[2], ch2_1[2], ch3_1[2]);//line 2,4,6...
					WRITE_ONE_PACKED_PIXEL_012	((out_data+line2+pix2), ch0_1[3], ch1_1[3], ch2_1[3], ch3_1[3]);
#elif (( DST_CH0_BYTEPOS_0 == 2 ) && ( DST_CH1_BYTEPOS_0 == 1 ) && ( DST_CH2_BYTEPOS_0 == 0 ))//bgr24
					WRITE_ONE_PACKED_PIXEL_210	((out_data+line1+pix1), ch0_1[0], ch1_1[0], ch2_1[0], ch3_1[0]);//line 1,3,5...
					WRITE_ONE_PACKED_PIXEL_210	((out_data+line1+pix2), ch0_1[1], ch1_1[1], ch2_1[1], ch3_1[1]);	
					WRITE_ONE_PACKED_PIXEL_210	((out_data+line2+pix1), ch0_1[2], ch1_1[2], ch2_1[2], ch3_1[2]);//line 2,4,6...
					WRITE_ONE_PACKED_PIXEL_210	((out_data+line2+pix2), ch0_1[3], ch1_1[3], ch2_1[3], ch3_1[3]);
//rgbx32 formats are not needed as rgb24 formats will do the same?
//packed yuv formats
#elif (( DST_CH0_BYTEPOS_0 == 0 ) && ( DST_CH1_BYTEPOS_0 == 1 ) && ( DST_CH0_BYTEPOS_1 == 0 ) && ( DST_CH2_BYTEPOS_1 == 1 ))//yuyv
					WRITE_TWO_PACKED_PIXELS_01_02	((out_data+line1+pix1), (out_data+line1+pix2),  ch0_1[0], ch1_1[0], ch2_1[0], ch3_1[0], ch0_1[1], ch1_1[1], ch2_1[1], ch3_1[1]);//line 1,3,5...
					WRITE_TWO_PACKED_PIXELS_01_02	((out_data+line2+pix1), (out_data+line2+pix2), ch0_1[2], ch1_1[2], ch2_1[2], ch3_1[2], ch0_1[3], ch1_1[3], ch2_1[3], ch3_1[3]);//line 2,4,6...
#elif (( DST_CH0_BYTEPOS_0 == 0 ) && ( DST_CH2_BYTEPOS_0 == 1 ) && ( DST_CH0_BYTEPOS_1 == 0 ) && ( DST_CH1_BYTEPOS_1 == 1 ))//yvyu
					WRITE_TWO_PACKED_PIXELS_02_01	((out_data+line1+pix1), (out_data+line1+pix2),  ch0_1[0], ch1_1[0], ch2_1[0], ch3_1[0], ch0_1[1], ch1_1[1], ch2_1[1], ch3_1[1]);//line 1,3,5...
					WRITE_TWO_PACKED_PIXELS_02_01	((out_data+line2+pix1), (out_data+line2+pix2), ch0_1[2], ch1_1[2], ch2_1[2], ch3_1[2], ch0_1[3], ch1_1[3], ch2_1[3], ch3_1[3]);//line 2,4,6...
#elif (( DST_CH0_BYTEPOS_0 == 1 ) && ( DST_CH1_BYTEPOS_0 == 0 ) && ( DST_CH0_BYTEPOS_1 == 1 ) && ( DST_CH2_BYTEPOS_1 == 0 ))//uyvy
					WRITE_TWO_PACKED_PIXELS_10_20	((out_data+line1+pix1), (out_data+line1+pix2),  ch0_1[0], ch1_1[0], ch2_1[0], ch3_1[0], ch0_1[1], ch1_1[1], ch2_1[1], ch3_1[1]);//line 1,3,5...
					WRITE_TWO_PACKED_PIXELS_10_20	((out_data+line2+pix1), (out_data+line2+pix2), ch0_1[2], ch1_1[2], ch2_1[2], ch3_1[2], ch0_1[3], ch1_1[3], ch2_1[3], ch3_1[3]);//line 2,4,6...
#elif (( DST_CH0_BYTEPOS_0 == 1 ) && ( DST_CH2_BYTEPOS_0 == 0 ) && ( DST_CH0_BYTEPOS_1 == 1 ) && ( DST_CH1_BYTEPOS_1 == 0 ))//vyuy
					WRITE_TWO_PACKED_PIXELS_20_10	((out_data+line1+pix1), (out_data+line1+pix2),  ch0_1[0], ch1_1[0], ch2_1[0], ch3_1[0], ch0_1[1], ch1_1[1], ch2_1[1], ch3_1[1]);//line 1,3,5...
					WRITE_TWO_PACKED_PIXELS_20_10	((out_data+line2+pix1), (out_data+line2+pix2), ch0_1[2], ch1_1[2], ch2_1[2], ch3_1[2], ch0_1[3], ch1_1[3], ch2_1[3], ch3_1[3]);//line 2,4,6...
#endif//(( DST_CH0_BYTEPOS_0 == 0 ) && ( DST_CH1_BYTEPOS_0 == 1 ) && ( DST_CH2_BYTEPOS_0 == 2 ) && ( DST_CH3_BYTEPOS_0 == 3 ))//rgba32
				}
#elif (defined DST_PLANAR)
				//else//planar format
				{
					int line_0_1 = (line *dst_ch0_stride + pix);
					int line_0_2 = ((line + 1) * dst_ch0_stride +pix);
					*(out_data + dst_ch0_offset + line_0_1)		=	ch0_1[0];
					*(out_data + dst_ch0_offset + line_0_1 + 1)	=	ch0_1[1];
					*(out_data + dst_ch0_offset + line_0_2)		=	ch0_1[2];
					*(out_data + dst_ch0_offset + line_0_2 + 1)	=	ch0_1[3];
#if (defined DST_4CHANNELS)
					//if (colorconverter->dst_format.active_channels == 4)
					{
						int dst_ch3_offset = colorconverter->dst_format.ch3.offset;
						*(out_data + dst_ch3_offset + line_0_1)		=	ch3_1[0];
						*(out_data + dst_ch3_offset + line_0_1 + 1)	=	ch3_1[1];
						*(out_data + dst_ch3_offset + line_0_2)		=	ch3_1[2];
						*(out_data + dst_ch3_offset + line_0_2 + 1)	=	ch3_1[3];
					}
#endif//#if defined (DST_4CHANNELS)
#if (defined DST_444)
					//if (colorconverter->dst_format.chromalayout.horz_subs_factor == 1
					//	&&colorconverter->dst_format.chromalayout.vert_subs_factor == 1)///4:4:4
					{
						int line_1 = ((line    ) * dst_ch1_stride) + (pix >> 1);
						int line_2 = ((line + 1) * dst_ch1_stride) + (pix >> 1);
						*(out_data + dst_ch1_offset + line_1 + pix)		= ch1_1[0];
						*(out_data + dst_ch1_offset + line_1 + pix + 1)	= ch1_1[1];
						*(out_data + dst_ch1_offset + line_2 + pix)		= ch1_1[2];
						*(out_data + dst_ch1_offset + line_2 + pix + 1) = ch1_1[3];

						*(out_data + dst_ch2_offset + line_1 + pix)		= ch2_1[0];
						*(out_data + dst_ch2_offset + line_1 + pix + 1)	= ch2_1[1];
						*(out_data + dst_ch2_offset + line_2 + pix)		= ch2_1[2];
						*(out_data + dst_ch2_offset + line_2 + pix + 1) = ch2_1[3];
					}
#elif (defined DST_422)
					//else if (colorconverter->dst_format.chromalayout.horz_subs_factor == 2 
					//	&& colorconverter->dst_format.chromalayout.vert_subs_factor == 1)//4:2:2
					{
						int line_1 = ((line    ) * dst_ch1_stride) + (pix >> 1);
						int line_2 = ((line + 1) * dst_ch1_stride) + (pix >> 1);
						*(out_data + dst_ch1_offset + line_1) = ch1_1[0];//(ch1_1[0] + ch1_1[1]) >> 1;
						*(out_data + dst_ch1_offset + line_2) = ch1_1[2];//(ch1_1[2] + ch1_1[3]) >> 1;
						*(out_data + dst_ch2_offset + line_1) = ch2_1[0];//(ch2_1[0] + ch2_1[1]) >> 1;
						*(out_data + dst_ch2_offset + line_2) = ch2_1[2];//(ch2_1[2] + ch2_1[3]) >> 1;
					}
#elif (defined DST_420)
					//else if (colorconverter->dst_format.chromalayout.horz_subs_factor == 2 
					//	&& colorconverter->dst_format.chromalayout.vert_subs_factor == 2)//4:2:0
					{
						int line_1 = ((line >> 1) * dst_ch1_stride) + (pix >> 1);
						*(out_data + dst_ch1_offset + line_1) = ch1_1[0];//(ch1_1[0] + ch1_1[1] + ch1_1[2] + ch1_1[3]) >> 2;
						*(out_data + dst_ch2_offset + line_1) = ch2_1[0];//(ch2_1[0] + ch2_1[1] + ch2_1[2] + ch2_1[3]) >> 2;
					}
#endif//#elif (defined DST_422)
				}
#endif//#if (defined DST_PLANAR)
			}
		}
	}
}
