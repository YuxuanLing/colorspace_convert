#define NEXT_HEADERFILE1 "colorspace_template3.h"
//stuff for templated pipeline
//Traversing every legal input format,
#define NO_ADAPTIVE_INTERPOLATION

#define SRC_PACKED
	#define SRC_3CHANNELS
		#define SRC_PIXELPERIOD1
			#define SRC_RGB
				#define SRC_32BPP
					#define SRC_FUNCTION_INDEX 0
						#define SRC_NAME packed_rgbx32
						#define SRC_CH0_BYTEPOS_0 0
						#define SRC_CH0_BYTEPOS_1 0
						#define SRC_CH1_BYTEPOS_0 1
						#define SRC_CH1_BYTEPOS_1 1
						#define SRC_CH2_BYTEPOS_0 2
						#define SRC_CH2_BYTEPOS_1 2
						//#define SRC_CH3_BYTEPOS_0 3
						//#define SRC_CH3_BYTEPOS_1 3
						
						#include NEXT_HEADERFILE1

						#undef SRC_CH0_BYTEPOS_0
						#undef SRC_CH0_BYTEPOS_1
						#undef SRC_CH1_BYTEPOS_0
						#undef SRC_CH1_BYTEPOS_1
						#undef SRC_CH2_BYTEPOS_0
						#undef SRC_CH2_BYTEPOS_1
						//#undef SRC_CH3_BYTEPOS_0
						//#undef SRC_CH3_BYTEPOS_1
						#undef SRC_NAME
					#undef SRC_FUNCTION_INDEX
					#define SRC_FUNCTION_INDEX 1
						#define SRC_NAME packed_xrgb32

						#define SRC_CH0_BYTEPOS_0 1
						#define SRC_CH0_BYTEPOS_1 1
						#define SRC_CH1_BYTEPOS_0 2
						#define SRC_CH1_BYTEPOS_1 2
						#define SRC_CH2_BYTEPOS_0 3
						#define SRC_CH2_BYTEPOS_1 3
						//#define SRC_CH3_BYTEPOS_0 0
						//#define SRC_CH3_BYTEPOS_1 0

						#include NEXT_HEADERFILE1

						#undef SRC_CH0_BYTEPOS_0
						#undef SRC_CH0_BYTEPOS_1
						#undef SRC_CH1_BYTEPOS_0
						#undef SRC_CH1_BYTEPOS_1
						#undef SRC_CH2_BYTEPOS_0
						#undef SRC_CH2_BYTEPOS_1
						//#undef SRC_CH3_BYTEPOS_0
						//#undef SRC_CH3_BYTEPOS_1
						#undef SRC_NAME
					#undef SRC_FUNCTION_INDEX
					#define SRC_FUNCTION_INDEX 2
						#define SRC_NAME packed_bgrx32

						#define SRC_CH0_BYTEPOS_0 2
						#define SRC_CH0_BYTEPOS_1 2
						#define SRC_CH1_BYTEPOS_0 1
						#define SRC_CH1_BYTEPOS_1 1
						#define SRC_CH2_BYTEPOS_0 0
						#define SRC_CH2_BYTEPOS_1 0
						//#define SRC_CH3_BYTEPOS_0 3
						//#define SRC_CH3_BYTEPOS_1 3
						#include NEXT_HEADERFILE1

						#undef SRC_CH0_BYTEPOS_0
						#undef SRC_CH0_BYTEPOS_1
						#undef SRC_CH1_BYTEPOS_0
						#undef SRC_CH1_BYTEPOS_1
						#undef SRC_CH2_BYTEPOS_0
						#undef SRC_CH2_BYTEPOS_1
						//#undef SRC_CH3_BYTEPOS_0
						//#undef SRC_CH3_BYTEPOS_1
						#undef SRC_NAME
					#undef SRC_FUNCTION_INDEX
					#define SRC_FUNCTION_INDEX 3
						#define SRC_NAME packed_xbgr32

						#define SRC_CH0_BYTEPOS_0 3
						#define SRC_CH0_BYTEPOS_1 3
						#define SRC_CH1_BYTEPOS_0 2
						#define SRC_CH1_BYTEPOS_1 2
						#define SRC_CH2_BYTEPOS_0 1
						#define SRC_CH2_BYTEPOS_1 1
						//#define SRC_CH3_BYTEPOS_0 0
						//#define SRC_CH3_BYTEPOS_1 0
						#include NEXT_HEADERFILE1

						#undef SRC_CH0_BYTEPOS_0
						#undef SRC_CH0_BYTEPOS_1
						#undef SRC_CH1_BYTEPOS_0
						#undef SRC_CH1_BYTEPOS_1
						#undef SRC_CH2_BYTEPOS_0
						#undef SRC_CH2_BYTEPOS_1
						//#undef SRC_CH3_BYTEPOS_0
						//#undef SRC_CH3_BYTEPOS_1
						#undef SRC_NAME
					#undef SRC_FUNCTION_INDEX
				#undef SRC_32BPP
				#define SRC_24BPP
					#define SRC_FUNCTION_INDEX 4
						#define SRC_NAME packed_rgb24

						#define SRC_CH0_BYTEPOS_0 0
						#define SRC_CH0_BYTEPOS_1 0
						#define SRC_CH1_BYTEPOS_0 1
						#define SRC_CH1_BYTEPOS_1 1
						#define SRC_CH2_BYTEPOS_0 2
						#define SRC_CH2_BYTEPOS_1 2
						#include NEXT_HEADERFILE1

						#undef SRC_CH0_BYTEPOS_0
						#undef SRC_CH0_BYTEPOS_1
						#undef SRC_CH1_BYTEPOS_0
						#undef SRC_CH1_BYTEPOS_1
						#undef SRC_CH2_BYTEPOS_0
						#undef SRC_CH2_BYTEPOS_1
						//#undef SRC_CH3_BYTEPOS_0
						//#undef SRC_CH3_BYTEPOS_1

						#undef SRC_NAME
					#undef SRC_FUNCTION_INDEX
					#define SRC_FUNCTION_INDEX 5
						#define SRC_NAME packed_bgr24

						#define SRC_CH0_BYTEPOS_0 2
						#define SRC_CH0_BYTEPOS_1 2
						#define SRC_CH1_BYTEPOS_0 1
						#define SRC_CH1_BYTEPOS_1 1
						#define SRC_CH2_BYTEPOS_0 0
						#define SRC_CH2_BYTEPOS_1 0

						#include NEXT_HEADERFILE1

						#undef SRC_CH0_BYTEPOS_0
						#undef SRC_CH0_BYTEPOS_1
						#undef SRC_CH1_BYTEPOS_0
						#undef SRC_CH1_BYTEPOS_1
						#undef SRC_CH2_BYTEPOS_0
						#undef SRC_CH2_BYTEPOS_1
						//#undef SRC_CH3_BYTEPOS_0
						//#undef SRC_CH3_BYTEPOS_1

						#undef SRC_NAME
					#undef SRC_FUNCTION_INDEX
				#undef SRC_24BPP
			#undef SRC_RGB
		#undef SRC_PIXELPERIOD1
		#define SRC_PIXELPERIOD2
			#define SRC_422
				#define SRC_16BPP
					#define SRC_YUV601
						#define SRC_FUNCTION_INDEX 6
							#define SRC_NAME packed_yuyv_601
							#define SRC_CH0_BYTEPOS_0 0
							#define SRC_CH0_BYTEPOS_1 0
							#define SRC_CH1_BYTEPOS_0 1
							//#define SRC_CH1_BYTEPOS_1
							//#define SRC_CH2_BYTEPOS_0
							#define SRC_CH2_BYTEPOS_1 1

							#include NEXT_HEADERFILE1

							#undef SRC_CH0_BYTEPOS_0
							#undef SRC_CH0_BYTEPOS_1
							#undef SRC_CH1_BYTEPOS_0
							//#undef SRC_CH1_BYTEPOS_1
							//#undef SRC_CH2_BYTEPOS_0
							#undef SRC_CH2_BYTEPOS_1
							#undef SRC_NAME
						#undef SRC_FUNCTION_INDEX
						#define SRC_FUNCTION_INDEX 7
							#define SRC_NAME packed_yvyu_601
							#define SRC_CH0_BYTEPOS_0 0
							#define SRC_CH0_BYTEPOS_1 0
							//#define SRC_CH1_BYTEPOS_0
							#define SRC_CH1_BYTEPOS_1 1
							#define SRC_CH2_BYTEPOS_0 1
							//#define SRC_CH2_BYTEPOS_1

							#include NEXT_HEADERFILE1

							#undef SRC_CH0_BYTEPOS_0
							#undef SRC_CH0_BYTEPOS_1
							//#undef SRC_CH1_BYTEPOS_0
							#undef SRC_CH1_BYTEPOS_1
							#undef SRC_CH2_BYTEPOS_0
							//#undef SRC_CH2_BYTEPOS_1
							#undef SRC_NAME
						#undef SRC_FUNCTION_INDEX
						#define SRC_FUNCTION_INDEX 8
							#define SRC_NAME packed_uyvy_601
							#define SRC_CH0_BYTEPOS_0 1
							#define SRC_CH0_BYTEPOS_1 1
							#define SRC_CH1_BYTEPOS_0 0
							//#define SRC_CH1_BYTEPOS_1
							//#define SRC_CH2_BYTEPOS_0
							#define SRC_CH2_BYTEPOS_1 0

							#include NEXT_HEADERFILE1

							#undef SRC_CH0_BYTEPOS_0
							#undef SRC_CH0_BYTEPOS_1
							#undef SRC_CH1_BYTEPOS_0
							//#undef SRC_CH1_BYTEPOS_1
							//#undef SRC_CH2_BYTEPOS_0
							#undef SRC_CH2_BYTEPOS_1
							#undef SRC_NAME
						#undef SRC_FUNCTION_INDEX
						#define SRC_FUNCTION_INDEX 9
							#define SRC_NAME packed_vyuy_601
							#define SRC_CH0_BYTEPOS_0 1
							#define SRC_CH0_BYTEPOS_1 1
							//#define SRC_CH1_BYTEPOS_0
							#define SRC_CH1_BYTEPOS_1 0
							#define SRC_CH2_BYTEPOS_0 0
							//#define SRC_CH2_BYTEPOS_1

							#include NEXT_HEADERFILE1

							#undef SRC_CH0_BYTEPOS_0
							#undef SRC_CH0_BYTEPOS_1
							//#undef SRC_CH1_BYTEPOS_0
							#undef SRC_CH1_BYTEPOS_1
							#undef SRC_CH2_BYTEPOS_0
							//#undef SRC_CH2_BYTEPOS_1
							#undef SRC_NAME
						#undef SRC_FUNCTION_INDEX
					#undef SRC_YUV601
					#define SRC_YUV709
						#define SRC_FUNCTION_INDEX 10
							#define SRC_NAME packed_yuyv_709
							#define SRC_CH0_BYTEPOS_0 0
							#define SRC_CH0_BYTEPOS_1 0
							#define SRC_CH1_BYTEPOS_0 1
							//#define SRC_CH1_BYTEPOS_1
							//#define SRC_CH2_BYTEPOS_0
							#define SRC_CH2_BYTEPOS_1 1

							#include NEXT_HEADERFILE1

							#undef SRC_CH0_BYTEPOS_0
							#undef SRC_CH0_BYTEPOS_1
							#undef SRC_CH1_BYTEPOS_0
							//#undef SRC_CH1_BYTEPOS_1
							//#undef SRC_CH2_BYTEPOS_0
							#undef SRC_CH2_BYTEPOS_1
							#undef SRC_NAME
						#undef SRC_FUNCTION_INDEX
						#define SRC_FUNCTION_INDEX 11
							#define SRC_NAME packed_yvyu_709
							#define SRC_CH0_BYTEPOS_0 0
							#define SRC_CH0_BYTEPOS_1 0
							//#define SRC_CH1_BYTEPOS_0
							#define SRC_CH1_BYTEPOS_1 1
							#define SRC_CH2_BYTEPOS_0 1
							//#define SRC_CH2_BYTEPOS_1

							#include NEXT_HEADERFILE1

							#undef SRC_CH0_BYTEPOS_0
							#undef SRC_CH0_BYTEPOS_1
							//#undef SRC_CH1_BYTEPOS_0
							#undef SRC_CH1_BYTEPOS_1
							#undef SRC_CH2_BYTEPOS_0
							//#undef SRC_CH2_BYTEPOS_1
							#undef SRC_NAME
						#undef SRC_FUNCTION_INDEX
						#define SRC_FUNCTION_INDEX 12
							#define SRC_NAME packed_uyvy_709
							#define SRC_CH0_BYTEPOS_0 1
							#define SRC_CH0_BYTEPOS_1 1
							#define SRC_CH1_BYTEPOS_0 0
							//#define SRC_CH1_BYTEPOS_1
							//#define SRC_CH2_BYTEPOS_0
							#define SRC_CH2_BYTEPOS_1 0

							#include NEXT_HEADERFILE1

							#undef SRC_CH0_BYTEPOS_0
							#undef SRC_CH0_BYTEPOS_1
							#undef SRC_CH1_BYTEPOS_0
							//#undef SRC_CH1_BYTEPOS_1
							//#undef SRC_CH2_BYTEPOS_0
							#undef SRC_CH2_BYTEPOS_1
							#undef SRC_NAME
						#undef SRC_FUNCTION_INDEX
						#define SRC_FUNCTION_INDEX 13
							#define SRC_NAME packed_vyuy_709
							#define SRC_CH0_BYTEPOS_0 1
							#define SRC_CH0_BYTEPOS_1 1
							//#define SRC_CH1_BYTEPOS_0
							#define SRC_CH1_BYTEPOS_1 0
							#define SRC_CH2_BYTEPOS_0 0
							//#define SRC_CH2_BYTEPOS_1

							#include NEXT_HEADERFILE1

							#undef SRC_CH0_BYTEPOS_0
							#undef SRC_CH0_BYTEPOS_1
							//#undef SRC_CH1_BYTEPOS_0
							#undef SRC_CH1_BYTEPOS_1
							#undef SRC_CH2_BYTEPOS_0
							//#undef SRC_CH2_BYTEPOS_1
							#undef SRC_NAME
						#undef SRC_FUNCTION_INDEX
					#undef SRC_YUV709
				#undef SRC_16BPP
			#undef SRC_422
		#undef SRC_PIXELPERIOD2
	#undef SRC_3CHANNELS

	#define SRC_4CHANNELS
		#define SRC_RGB
			#define SRC_PIXELPERIOD1
				#define SRC_32BPP
					#define SRC_FUNCTION_INDEX 14
						#define SRC_NAME packed_rgba32
						#define SRC_CH0_BYTEPOS_0 0
						#define SRC_CH0_BYTEPOS_1 0
						#define SRC_CH1_BYTEPOS_0 1
						#define SRC_CH1_BYTEPOS_1 1
						#define SRC_CH2_BYTEPOS_0 2
						#define SRC_CH2_BYTEPOS_1 2
						#define SRC_CH3_BYTEPOS_0 3
						#define SRC_CH3_BYTEPOS_1 3
						
						#include NEXT_HEADERFILE1

						#undef SRC_CH0_BYTEPOS_0
						#undef SRC_CH0_BYTEPOS_1
						#undef SRC_CH1_BYTEPOS_0
						#undef SRC_CH1_BYTEPOS_1
						#undef SRC_CH2_BYTEPOS_0
						#undef SRC_CH2_BYTEPOS_1
						#undef SRC_CH3_BYTEPOS_0
						#undef SRC_CH3_BYTEPOS_1
						#undef SRC_NAME
					#undef SRC_FUNCTION_INDEX
					#define SRC_FUNCTION_INDEX 15
						#define SRC_NAME packed_argb32

						#define SRC_CH0_BYTEPOS_0 1
						#define SRC_CH0_BYTEPOS_1 1
						#define SRC_CH1_BYTEPOS_0 2
						#define SRC_CH1_BYTEPOS_1 2
						#define SRC_CH2_BYTEPOS_0 3
						#define SRC_CH2_BYTEPOS_1 3
						#define SRC_CH3_BYTEPOS_0 0
						#define SRC_CH3_BYTEPOS_1 0

						#include NEXT_HEADERFILE1

						#undef SRC_CH0_BYTEPOS_0
						#undef SRC_CH0_BYTEPOS_1
						#undef SRC_CH1_BYTEPOS_0
						#undef SRC_CH1_BYTEPOS_1
						#undef SRC_CH2_BYTEPOS_0
						#undef SRC_CH2_BYTEPOS_1
						#undef SRC_CH3_BYTEPOS_0
						#undef SRC_CH3_BYTEPOS_1
						#undef SRC_NAME
					#undef SRC_FUNCTION_INDEX
					#define SRC_FUNCTION_INDEX 16
						#define SRC_NAME packed_bgra32

						#define SRC_CH0_BYTEPOS_0 2
						#define SRC_CH0_BYTEPOS_1 2
						#define SRC_CH1_BYTEPOS_0 1
						#define SRC_CH1_BYTEPOS_1 1
						#define SRC_CH2_BYTEPOS_0 0
						#define SRC_CH2_BYTEPOS_1 0
						#define SRC_CH3_BYTEPOS_0 3
						#define SRC_CH3_BYTEPOS_1 3
						#include NEXT_HEADERFILE1

						#undef SRC_CH0_BYTEPOS_0
						#undef SRC_CH0_BYTEPOS_1
						#undef SRC_CH1_BYTEPOS_0
						#undef SRC_CH1_BYTEPOS_1
						#undef SRC_CH2_BYTEPOS_0
						#undef SRC_CH2_BYTEPOS_1
						#undef SRC_CH3_BYTEPOS_0
						#undef SRC_CH3_BYTEPOS_1
						#undef SRC_NAME
					#undef SRC_FUNCTION_INDEX
					#define SRC_FUNCTION_INDEX 17
						#define SRC_NAME packed_abgr32

						#define SRC_CH0_BYTEPOS_0 3
						#define SRC_CH0_BYTEPOS_1 3
						#define SRC_CH1_BYTEPOS_0 2
						#define SRC_CH1_BYTEPOS_1 2
						#define SRC_CH2_BYTEPOS_0 1
						#define SRC_CH2_BYTEPOS_1 1
						#define SRC_CH3_BYTEPOS_0 0
						#define SRC_CH3_BYTEPOS_1 0
						#include NEXT_HEADERFILE1

						#undef SRC_CH0_BYTEPOS_0
						#undef SRC_CH0_BYTEPOS_1
						#undef SRC_CH1_BYTEPOS_0
						#undef SRC_CH1_BYTEPOS_1
						#undef SRC_CH2_BYTEPOS_0
						#undef SRC_CH2_BYTEPOS_1
						#undef SRC_CH3_BYTEPOS_0
						#undef SRC_CH3_BYTEPOS_1
						#undef SRC_NAME
					#undef SRC_FUNCTION_INDEX
				#undef SRC_32BPP
			#undef SRC_PIXELPERIOD1
		#undef SRC_RGB
		#define SRC_PIXELPERIOD1
			#undef SRC_32BPP
				#define SRC_YUV601
					#define SRC_FUNCTION_INDEX 18
					#define SRC_NAME packed_4444_ayuv601
					#define SRC_CH0_BYTEPOS_0 1
					#define SRC_CH1_BYTEPOS_0 2
					#define SRC_CH2_BYTEPOS_0 3
					#define SRC_CH3_BYTEPOS_0 0
					#include NEXT_HEADERFILE1
					#undef SRC_CH0_BYTEPOS_0
					#undef SRC_CH1_BYTEPOS_0
					#undef SRC_CH2_BYTEPOS_0
					#undef SRC_CH3_BYTEPOS_0
					#undef SRC_NAME			
					#undef SRC_FUNCTION_INDEX
				#undef SRC_YUV601
			#undef SRC_32BPP
		#undef SRC_PIXELPERIOD1
	#undef SRC_4CHANNELS
#undef SRC_PACKED

#define SRC_PLANAR
	#define SRC_3CHANNELS
		#define SRC_444
			#define SRC_YUV601
				#define SRC_FUNCTION_INDEX 19
				#define SRC_NAME  planar_444_yuv601
				#include NEXT_HEADERFILE1
				#undef SRC_NAME
				#undef SRC_FUNCTION_INDEX
			#undef SRC_YUV601
			#define SRC_YUV709
				#define SRC_FUNCTION_INDEX 20
				#define SRC_NAME  planar_444_yuv709
				#include NEXT_HEADERFILE1
				#undef SRC_NAME
				#undef SRC_FUNCTION_INDEX
			#undef SRC_YUV709
		#undef SRC_444
		#define SRC_422
			#define SRC_YUV601
				#define SRC_FUNCTION_INDEX 21
				#define SRC_NAME  planar_422_yuv601
				#include NEXT_HEADERFILE1
				#undef SRC_NAME
				#undef SRC_FUNCTION_INDEX
			#undef SRC_YUV601
			#define SRC_YUV709
				#define SRC_FUNCTION_INDEX 22
				#define SRC_NAME  planar_422_yuv709
				#include NEXT_HEADERFILE1
				#undef SRC_NAME
				#undef SRC_FUNCTION_INDEX
			#undef SRC_YUV709
		#undef SRC_422
		#define SRC_420
			#define SRC_YUV601
				#define SRC_FUNCTION_INDEX 23
				#define SRC_NAME  planar_420_yuv601
				#include NEXT_HEADERFILE1
				#undef SRC_NAME
				#undef SRC_FUNCTION_INDEX
			#undef SRC_YUV601
			#define SRC_YUV709
				#define SRC_FUNCTION_INDEX 24
				#define SRC_NAME  planar_420_yuv709
				#include NEXT_HEADERFILE1
				#undef SRC_NAME
				#undef SRC_FUNCTION_INDEX
			#undef SRC_YUV709
		#undef SRC_420
	#undef SRC_3CHANNELS

	#define SRC_4CHANNELS
		#define SRC_444
			#define SRC_YUV601
				#define SRC_FUNCTION_INDEX 25
				#define SRC_NAME  planar_4444_yuv601
				#include NEXT_HEADERFILE1
				#undef SRC_NAME
				#undef SRC_FUNCTION_INDEX
			#undef SRC_YUV601
			#define SRC_YUV709
				#define SRC_FUNCTION_INDEX 26
				#define SRC_NAME  planar_4444_yuv709
				#include NEXT_HEADERFILE1
				#undef SRC_NAME
				#undef SRC_FUNCTION_INDEX
			#undef SRC_YUV709
		#undef SRC_444
		#define SRC_422
			#define SRC_YUV601
				#define SRC_FUNCTION_INDEX 27
				#define SRC_NAME  planar_4224_yuv601
				#include NEXT_HEADERFILE1
				#undef SRC_NAME
				#undef SRC_FUNCTION_INDEX
			#undef SRC_YUV601
			#define SRC_YUV709
				#define SRC_FUNCTION_INDEX 28
				#define SRC_NAME  planar_4224_yuv709
				#include NEXT_HEADERFILE1
				#undef SRC_NAME
				#undef SRC_FUNCTION_INDEX
			#undef SRC_YUV709
		#undef SRC_422
		#define SRC_420
			#define SRC_YUV601
				#define SRC_FUNCTION_INDEX 29
				#define SRC_NAME  planar_4204_yuv601
				#include NEXT_HEADERFILE1
				#undef SRC_NAME
				#undef SRC_FUNCTION_INDEX
			#undef SRC_YUV601
			#define SRC_YUV709
				#define SRC_FUNCTION_INDEX 30
				#define SRC_NAME  planar_4204_yuv709
				#include NEXT_HEADERFILE1
				#undef SRC_NAME
				#undef SRC_FUNCTION_INDEX
			#undef SRC_YUV709
		#undef SRC_420
	#undef SRC_4CHANNELS
#undef SRC_PLANAR

#undef NO_ADAPTIVE_INTERPOLATION
#define DO_ADAPTIVE_INTERPOLATION
//special (asymmetric!!) "format" added to allocate the luma-adaptive interpolation functions
//note that this is defined for source 4:2:0 planar
#define SRC_PLANAR
	#define SRC_3CHANNELS
		#define SRC_420
			#define SRC_YUV601
				#define SRC_FUNCTION_INDEX 31
				#define SRC_NAME planar_420_yuv601_lumaadaptive
				#include NEXT_HEADERFILE1
				#undef SRC_NAME
				#undef SRC_FUNCTION_INDEX
			#undef SRC_YUV601
		#undef SRC_420
	#undef SRC_3CHANNELS
#undef SRC_PLANAR
#undef DO_ADAPTIVE_INTERPOLATION
