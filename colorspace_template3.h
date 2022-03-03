#define NEXT_HEADERFILE2 "colorspace_template4.h"
//stuff for templated pipeline
//Traversing every legal output format
#define DST_PACKED
	#define DST_3CHANNELS
		#define DST_PIXELPERIOD1
			#define DST_RGB
				#define DST_32BPP
					#define DST_FUNCTION_INDEX 0
						#define DST_NAME packed_rgbx32
						#define DST_CH0_BYTEPOS_0 0
						#define DST_CH0_BYTEPOS_1 0
						#define DST_CH1_BYTEPOS_0 1
						#define DST_CH1_BYTEPOS_1 1
						#define DST_CH2_BYTEPOS_0 2
						#define DST_CH2_BYTEPOS_1 2
						//#define DST_CH3_BYTEPOS_0 3
						//#define DST_CH3_BYTEPOS_1 3
						
						#include NEXT_HEADERFILE2

						#undef DST_CH0_BYTEPOS_0
						#undef DST_CH0_BYTEPOS_1
						#undef DST_CH1_BYTEPOS_0
						#undef DST_CH1_BYTEPOS_1
						#undef DST_CH2_BYTEPOS_0
						#undef DST_CH2_BYTEPOS_1
						//#undef DST_CH3_BYTEPOS_0
						//#undef DST_CH3_BYTEPOS_1
						#undef DST_NAME
					#undef DST_FUNCTION_INDEX
					#define DST_FUNCTION_INDEX 1
						#define DST_NAME packed_xrgb32

						#define DST_CH0_BYTEPOS_0 1
						#define DST_CH0_BYTEPOS_1 1
						#define DST_CH1_BYTEPOS_0 2
						#define DST_CH1_BYTEPOS_1 2
						#define DST_CH2_BYTEPOS_0 3
						#define DST_CH2_BYTEPOS_1 3
						//#define DST_CH3_BYTEPOS_0 0
						//#define DST_CH3_BYTEPOS_1 0

						#include NEXT_HEADERFILE2

						#undef DST_CH0_BYTEPOS_0
						#undef DST_CH0_BYTEPOS_1
						#undef DST_CH1_BYTEPOS_0
						#undef DST_CH1_BYTEPOS_1
						#undef DST_CH2_BYTEPOS_0
						#undef DST_CH2_BYTEPOS_1
						//#undef DST_CH3_BYTEPOS_0
						//#undef DST_CH3_BYTEPOS_1
						#undef DST_NAME
					#undef DST_FUNCTION_INDEX
					#define DST_FUNCTION_INDEX 2
						#define DST_NAME packed_bgrx32

						#define DST_CH0_BYTEPOS_0 2
						#define DST_CH0_BYTEPOS_1 2
						#define DST_CH1_BYTEPOS_0 1
						#define DST_CH1_BYTEPOS_1 1
						#define DST_CH2_BYTEPOS_0 0
						#define DST_CH2_BYTEPOS_1 0
						//#define DST_CH3_BYTEPOS_0 3
						//#define DST_CH3_BYTEPOS_1 3
						#include NEXT_HEADERFILE2

						#undef DST_CH0_BYTEPOS_0
						#undef DST_CH0_BYTEPOS_1
						#undef DST_CH1_BYTEPOS_0
						#undef DST_CH1_BYTEPOS_1
						#undef DST_CH2_BYTEPOS_0
						#undef DST_CH2_BYTEPOS_1
						//#undef DST_CH3_BYTEPOS_0
						//#undef DST_CH3_BYTEPOS_1
						#undef DST_NAME
					#undef DST_FUNCTION_INDEX
					#define DST_FUNCTION_INDEX 3
						#define DST_NAME packed_xbgr32

						#define DST_CH0_BYTEPOS_0 3
						#define DST_CH0_BYTEPOS_1 3
						#define DST_CH1_BYTEPOS_0 2
						#define DST_CH1_BYTEPOS_1 2
						#define DST_CH2_BYTEPOS_0 1
						#define DST_CH2_BYTEPOS_1 1
						//#define DST_CH3_BYTEPOS_0 0
						//#define DST_CH3_BYTEPOS_1 0
						#include NEXT_HEADERFILE2

						#undef DST_CH0_BYTEPOS_0
						#undef DST_CH0_BYTEPOS_1
						#undef DST_CH1_BYTEPOS_0
						#undef DST_CH1_BYTEPOS_1
						#undef DST_CH2_BYTEPOS_0
						#undef DST_CH2_BYTEPOS_1
						//#undef DST_CH3_BYTEPOS_0
						//#undef DST_CH3_BYTEPOS_1
						#undef DST_NAME
					#undef DST_FUNCTION_INDEX
				#undef DST_32BPP
				#define DST_24BPP
					#define DST_FUNCTION_INDEX 4
						#define DST_NAME packed_rgb24

						#define DST_CH0_BYTEPOS_0 0
						#define DST_CH0_BYTEPOS_1 0
						#define DST_CH1_BYTEPOS_0 1
						#define DST_CH1_BYTEPOS_1 1
						#define DST_CH2_BYTEPOS_0 2
						#define DST_CH2_BYTEPOS_1 2
						#include NEXT_HEADERFILE2

						#undef DST_CH0_BYTEPOS_0
						#undef DST_CH0_BYTEPOS_1
						#undef DST_CH1_BYTEPOS_0
						#undef DST_CH1_BYTEPOS_1
						#undef DST_CH2_BYTEPOS_0
						#undef DST_CH2_BYTEPOS_1
						//#undef DST_CH3_BYTEPOS_0
						//#undef DST_CH3_BYTEPOS_1

						#undef DST_NAME
					#undef DST_FUNCTION_INDEX
					#define DST_FUNCTION_INDEX 5
						#define DST_NAME packed_bgr24

						#define DST_CH0_BYTEPOS_0 2
						#define DST_CH0_BYTEPOS_1 2
						#define DST_CH1_BYTEPOS_0 1
						#define DST_CH1_BYTEPOS_1 1
						#define DST_CH2_BYTEPOS_0 0
						#define DST_CH2_BYTEPOS_1 0

						#include NEXT_HEADERFILE2

						#undef DST_CH0_BYTEPOS_0
						#undef DST_CH0_BYTEPOS_1
						#undef DST_CH1_BYTEPOS_0
						#undef DST_CH1_BYTEPOS_1
						#undef DST_CH2_BYTEPOS_0
						#undef DST_CH2_BYTEPOS_1
						//#undef DST_CH3_BYTEPOS_0
						//#undef DST_CH3_BYTEPOS_1

						#undef DST_NAME
					#undef DST_FUNCTION_INDEX
				#undef DST_24BPP
			#undef DST_RGB
		#undef DST_PIXELPERIOD1
		#define DST_PIXELPERIOD2
			#define DST_422
				#define DST_16BPP
					#define DST_YUV601
						#define DST_FUNCTION_INDEX 6
							#define DST_NAME packed_yuyv_601
							#define DST_CH0_BYTEPOS_0 0
							#define DST_CH0_BYTEPOS_1 0
							#define DST_CH1_BYTEPOS_0 1
							//#define DST_CH1_BYTEPOS_1
							//#define DST_CH2_BYTEPOS_0
							#define DST_CH2_BYTEPOS_1 1

							#include NEXT_HEADERFILE2

							#undef DST_CH0_BYTEPOS_0
							#undef DST_CH0_BYTEPOS_1
							#undef DST_CH1_BYTEPOS_0
							//#undef DST_CH1_BYTEPOS_1
							//#undef DST_CH2_BYTEPOS_0
							#undef DST_CH2_BYTEPOS_1
							#undef DST_NAME
						#undef DST_FUNCTION_INDEX
						#define DST_FUNCTION_INDEX 7
							#define DST_NAME packed_yvyu_601
							#define DST_CH0_BYTEPOS_0 0
							#define DST_CH0_BYTEPOS_1 0
							//#define DST_CH1_BYTEPOS_0
							#define DST_CH1_BYTEPOS_1 1
							#define DST_CH2_BYTEPOS_0 1
							//#define DST_CH2_BYTEPOS_1

							#include NEXT_HEADERFILE2

							#undef DST_CH0_BYTEPOS_0
							#undef DST_CH0_BYTEPOS_1
							//#undef DST_CH1_BYTEPOS_0
							#undef DST_CH1_BYTEPOS_1
							#undef DST_CH2_BYTEPOS_0
							//#undef DST_CH2_BYTEPOS_1
							#undef DST_NAME
						#undef DST_FUNCTION_INDEX
						#define DST_FUNCTION_INDEX 8
							#define DST_NAME packed_uyvy_601
							#define DST_CH0_BYTEPOS_0 1
							#define DST_CH0_BYTEPOS_1 1
							#define DST_CH1_BYTEPOS_0 0
							//#define DST_CH1_BYTEPOS_1
							//#define DST_CH2_BYTEPOS_0
							#define DST_CH2_BYTEPOS_1 0

							#include NEXT_HEADERFILE2

							#undef DST_CH0_BYTEPOS_0
							#undef DST_CH0_BYTEPOS_1
							#undef DST_CH1_BYTEPOS_0
							//#undef DST_CH1_BYTEPOS_1
							//#undef DST_CH2_BYTEPOS_0
							#undef DST_CH2_BYTEPOS_1
							#undef DST_NAME
						#undef DST_FUNCTION_INDEX
						#define DST_FUNCTION_INDEX 9
							#define DST_NAME packed_vyuy_601
							#define DST_CH0_BYTEPOS_0 1
							#define DST_CH0_BYTEPOS_1 1
							//#define DST_CH1_BYTEPOS_0
							#define DST_CH1_BYTEPOS_1 0
							#define DST_CH2_BYTEPOS_0 0
							//#define DST_CH2_BYTEPOS_1

							#include NEXT_HEADERFILE2

							#undef DST_CH0_BYTEPOS_0
							#undef DST_CH0_BYTEPOS_1
							//#undef DST_CH1_BYTEPOS_0
							#undef DST_CH1_BYTEPOS_1
							#undef DST_CH2_BYTEPOS_0
							//#undef DST_CH2_BYTEPOS_1
							#undef DST_NAME
						#undef DST_FUNCTION_INDEX
					#undef DST_YUV601
					#define DST_YUV709
						#define DST_FUNCTION_INDEX 10
							#define DST_NAME packed_yuyv_709
							#define DST_CH0_BYTEPOS_0 0
							#define DST_CH0_BYTEPOS_1 0
							#define DST_CH1_BYTEPOS_0 1
							//#define DST_CH1_BYTEPOS_1
							//#define DST_CH2_BYTEPOS_0
							#define DST_CH2_BYTEPOS_1 1

							#include NEXT_HEADERFILE2

							#undef DST_CH0_BYTEPOS_0
							#undef DST_CH0_BYTEPOS_1
							#undef DST_CH1_BYTEPOS_0
							//#undef DST_CH1_BYTEPOS_1
							//#undef DST_CH2_BYTEPOS_0
							#undef DST_CH2_BYTEPOS_1
							#undef DST_NAME
						#undef DST_FUNCTION_INDEX
						#define DST_FUNCTION_INDEX 11
							#define DST_NAME packed_yvyu_709
							#define DST_CH0_BYTEPOS_0 0
							#define DST_CH0_BYTEPOS_1 0
							//#define DST_CH1_BYTEPOS_0
							#define DST_CH1_BYTEPOS_1 1
							#define DST_CH2_BYTEPOS_0 1
							//#define DST_CH2_BYTEPOS_1

							#include NEXT_HEADERFILE2

							#undef DST_CH0_BYTEPOS_0
							#undef DST_CH0_BYTEPOS_1
							//#undef DST_CH1_BYTEPOS_0
							#undef DST_CH1_BYTEPOS_1
							#undef DST_CH2_BYTEPOS_0
							//#undef DST_CH2_BYTEPOS_1
							#undef DST_NAME
						#undef DST_FUNCTION_INDEX
						#define DST_FUNCTION_INDEX 12
							#define DST_NAME packed_uyvy_709
							#define DST_CH0_BYTEPOS_0 1
							#define DST_CH0_BYTEPOS_1 1
							#define DST_CH1_BYTEPOS_0 0
							//#define DST_CH1_BYTEPOS_1
							//#define DST_CH2_BYTEPOS_0
							#define DST_CH2_BYTEPOS_1 0

							#include NEXT_HEADERFILE2

							#undef DST_CH0_BYTEPOS_0
							#undef DST_CH0_BYTEPOS_1
							#undef DST_CH1_BYTEPOS_0
							//#undef DST_CH1_BYTEPOS_1
							//#undef DST_CH2_BYTEPOS_0
							#undef DST_CH2_BYTEPOS_1
							#undef DST_NAME
						#undef DST_FUNCTION_INDEX
						#define DST_FUNCTION_INDEX 13
							#define DST_NAME packed_vyuy_709
							#define DST_CH0_BYTEPOS_0 1
							#define DST_CH0_BYTEPOS_1 1
							//#define DST_CH1_BYTEPOS_0
							#define DST_CH1_BYTEPOS_1 0
							#define DST_CH2_BYTEPOS_0 0
							//#define DST_CH2_BYTEPOS_1

							#include NEXT_HEADERFILE2

							#undef DST_CH0_BYTEPOS_0
							#undef DST_CH0_BYTEPOS_1
							//#undef DST_CH1_BYTEPOS_0
							#undef DST_CH1_BYTEPOS_1
							#undef DST_CH2_BYTEPOS_0
							//#undef DST_CH2_BYTEPOS_1
							#undef DST_NAME
						#undef DST_FUNCTION_INDEX
					#undef DST_YUV709
				#undef DST_16BPP
			#undef DST_422
		#undef DST_PIXELPERIOD2
	#undef DST_3CHANNELS

	#define DST_4CHANNELS
		#define DST_RGB
			#define DST_PIXELPERIOD1
				#define DST_32BPP
					#define DST_FUNCTION_INDEX 14
						#define DST_NAME packed_rgba32
						#define DST_CH0_BYTEPOS_0 0
						#define DST_CH0_BYTEPOS_1 0
						#define DST_CH1_BYTEPOS_0 1
						#define DST_CH1_BYTEPOS_1 1
						#define DST_CH2_BYTEPOS_0 2
						#define DST_CH2_BYTEPOS_1 2
						#define DST_CH3_BYTEPOS_0 3
						#define DST_CH3_BYTEPOS_1 3
						
						#include NEXT_HEADERFILE2

						#undef DST_CH0_BYTEPOS_0
						#undef DST_CH0_BYTEPOS_1
						#undef DST_CH1_BYTEPOS_0
						#undef DST_CH1_BYTEPOS_1
						#undef DST_CH2_BYTEPOS_0
						#undef DST_CH2_BYTEPOS_1
						#undef DST_CH3_BYTEPOS_0
						#undef DST_CH3_BYTEPOS_1
						#undef DST_NAME
					#undef DST_FUNCTION_INDEX
					#define DST_FUNCTION_INDEX 15
						#define DST_NAME packed_argb32

						#define DST_CH0_BYTEPOS_0 1
						#define DST_CH0_BYTEPOS_1 1
						#define DST_CH1_BYTEPOS_0 2
						#define DST_CH1_BYTEPOS_1 2
						#define DST_CH2_BYTEPOS_0 3
						#define DST_CH2_BYTEPOS_1 3
						#define DST_CH3_BYTEPOS_0 0
						#define DST_CH3_BYTEPOS_1 0

						#include NEXT_HEADERFILE2

						#undef DST_CH0_BYTEPOS_0
						#undef DST_CH0_BYTEPOS_1
						#undef DST_CH1_BYTEPOS_0
						#undef DST_CH1_BYTEPOS_1
						#undef DST_CH2_BYTEPOS_0
						#undef DST_CH2_BYTEPOS_1
						#undef DST_CH3_BYTEPOS_0
						#undef DST_CH3_BYTEPOS_1
						#undef DST_NAME
					#undef DST_FUNCTION_INDEX
					#define DST_FUNCTION_INDEX 16
						#define DST_NAME packed_bgra32

						#define DST_CH0_BYTEPOS_0 2
						#define DST_CH0_BYTEPOS_1 2
						#define DST_CH1_BYTEPOS_0 1
						#define DST_CH1_BYTEPOS_1 1
						#define DST_CH2_BYTEPOS_0 0
						#define DST_CH2_BYTEPOS_1 0
						#define DST_CH3_BYTEPOS_0 3
						#define DST_CH3_BYTEPOS_1 3
						#include NEXT_HEADERFILE2

						#undef DST_CH0_BYTEPOS_0
						#undef DST_CH0_BYTEPOS_1
						#undef DST_CH1_BYTEPOS_0
						#undef DST_CH1_BYTEPOS_1
						#undef DST_CH2_BYTEPOS_0
						#undef DST_CH2_BYTEPOS_1
						#undef DST_CH3_BYTEPOS_0
						#undef DST_CH3_BYTEPOS_1
						#undef DST_NAME
					#undef DST_FUNCTION_INDEX
					#define DST_FUNCTION_INDEX 17
						#define DST_NAME packed_abgr32

						#define DST_CH0_BYTEPOS_0 3
						#define DST_CH0_BYTEPOS_1 3
						#define DST_CH1_BYTEPOS_0 2
						#define DST_CH1_BYTEPOS_1 2
						#define DST_CH2_BYTEPOS_0 1
						#define DST_CH2_BYTEPOS_1 1
						#define DST_CH3_BYTEPOS_0 0
						#define DST_CH3_BYTEPOS_1 0
						#include NEXT_HEADERFILE2

						#undef DST_CH0_BYTEPOS_0
						#undef DST_CH0_BYTEPOS_1
						#undef DST_CH1_BYTEPOS_0
						#undef DST_CH1_BYTEPOS_1
						#undef DST_CH2_BYTEPOS_0
						#undef DST_CH2_BYTEPOS_1
						#undef DST_CH3_BYTEPOS_0
						#undef DST_CH3_BYTEPOS_1
						#undef DST_NAME
					#undef DST_FUNCTION_INDEX
				#undef DST_32BPP
			#undef DST_PIXELPERIOD1
		#undef DST_RGB
		#define DST_PIXELPERIOD1
			#undef DST_32BPP
				#define DST_YUV601
					#define DST_FUNCTION_INDEX 18
					#define DST_NAME packed_4444_ayuv601
					#define DST_CH0_BYTEPOS_0 1
					#define DST_CH1_BYTEPOS_0 2
					#define DST_CH2_BYTEPOS_0 3
					#define DST_CH3_BYTEPOS_0 0
					#include NEXT_HEADERFILE2
					#undef DST_CH0_BYTEPOS_0
					#undef DST_CH1_BYTEPOS_0
					#undef DST_CH2_BYTEPOS_0
					#undef DST_CH3_BYTEPOS_0
					#undef DST_NAME			
					#undef DST_FUNCTION_INDEX
				#undef DST_YUV601
			#undef DST_32BPP
		#undef DST_PIXELPERIOD1
	#undef DST_4CHANNELS
#undef DST_PACKED

#define DST_PLANAR
	#define DST_3CHANNELS
		#define DST_444
			#define DST_YUV601
				#define DST_FUNCTION_INDEX 19
				#define DST_NAME  planar_444_yuv601
				#include NEXT_HEADERFILE2
				#undef DST_NAME
				#undef DST_FUNCTION_INDEX
			#undef DST_YUV601
			#define DST_YUV709
				#define DST_FUNCTION_INDEX 20
				#define DST_NAME  planar_444_yuv709
				#include NEXT_HEADERFILE2
				#undef DST_NAME
				#undef DST_FUNCTION_INDEX
			#undef DST_YUV709
		#undef DST_444
		#define DST_422
			#define DST_YUV601
				#define DST_FUNCTION_INDEX 21
				#define DST_NAME  planar_422_yuv601
				#include NEXT_HEADERFILE2
				#undef DST_NAME
				#undef DST_FUNCTION_INDEX
			#undef DST_YUV601
			#define DST_YUV709
				#define DST_FUNCTION_INDEX 22
				#define DST_NAME  planar_422_yuv709
				#include NEXT_HEADERFILE2
				#undef DST_NAME
				#undef DST_FUNCTION_INDEX
			#undef DST_YUV709
		#undef DST_422
		#define DST_420
			#define DST_YUV601
				#define DST_FUNCTION_INDEX 23
				#define DST_NAME  planar_420_yuv601
				#include NEXT_HEADERFILE2
				#undef DST_NAME
				#undef DST_FUNCTION_INDEX
			#undef DST_YUV601
			#define DST_YUV709
				#define DST_FUNCTION_INDEX 24
				#define DST_NAME  planar_420_yuv709
				#include NEXT_HEADERFILE2
				#undef DST_NAME
				#undef DST_FUNCTION_INDEX
			#undef DST_YUV709
		#undef DST_420
	#undef DST_3CHANNELS

	#define DST_4CHANNELS
		#define DST_444
			#define DST_YUV601
				#define DST_FUNCTION_INDEX 25
				#define DST_NAME  planar_4444_yuv601
				#include NEXT_HEADERFILE2
				#undef DST_NAME
				#undef DST_FUNCTION_INDEX
			#undef DST_YUV601
			#define DST_YUV709
				#define DST_FUNCTION_INDEX 26
				#define DST_NAME  planar_4444_yuv709
				#include NEXT_HEADERFILE2
				#undef DST_NAME
				#undef DST_FUNCTION_INDEX
			#undef DST_YUV709
		#undef DST_444
		#define DST_422
			#define DST_YUV601
				#define DST_FUNCTION_INDEX 27
				#define DST_NAME  planar_4224_yuv601
				#include NEXT_HEADERFILE2
				#undef DST_NAME
				#undef DST_FUNCTION_INDEX
			#undef DST_YUV601
			#define DST_YUV709
				#define DST_FUNCTION_INDEX 28
				#define DST_NAME  planar_4224_yuv709
				#include NEXT_HEADERFILE2
				#undef DST_NAME
				#undef DST_FUNCTION_INDEX
			#undef DST_YUV709
		#undef DST_422
		#define DST_420
			#define DST_YUV601
				#define DST_FUNCTION_INDEX 29
				#define DST_NAME  planar_4204_yuv601
				#include NEXT_HEADERFILE2
				#undef DST_NAME
				#undef DST_FUNCTION_INDEX
			#undef DST_YUV601
			#define DST_YUV709
				#define DST_FUNCTION_INDEX 30
				#define DST_NAME  planar_4204_yuv709
				#include NEXT_HEADERFILE2
				#undef DST_NAME
				#undef DST_FUNCTION_INDEX
			#undef DST_YUV709
		#undef DST_420
	#undef DST_4CHANNELS
#undef DST_PLANAR
