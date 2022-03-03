#include "chroma_interpolate.h"
#include "colorspace_definitions.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define INTEGER_TRANSFORM//undef falls back to text-book floating point operations (for debugging)
#define USE_MACRO_TEMPLATES//undef falls back to straight function-oriented pipeline (for debugging)
#include "colorspace_template1.h"

void select_converter(ColorSpaceConverter *colorconverter, int * srcIdx, int * dstIdx)
{
	int index;
	index = decode_format(colorconverter->src_format);
	//this is really dirty...
	if ((index == 23) && colorconverter->bDoAdaptiveInterpolation) {
		index = 31;
	}
	*srcIdx	= index;
	*dstIdx	=	decode_format(colorconverter->dst_format);
}

int decode_format(FormatDescriptor format)
{
	int index;
	index = -1;
	if (format.organisation == PACKED) {
		if (format.active_channels == 3) {
			if (format.pixel_repeat_period == 1) {
				if (format.colorspace == sRGB_PC) {				
					if		(format.ch0.byte_offset1 == 0 && format.ch1.byte_offset1 == 1 && format.ch2.byte_offset1 == 2) {
						index = 0;//rgbx32
					}
					else if	(format.ch0.byte_offset1 == 1 && format.ch1.byte_offset1 == 2 && format.ch2.byte_offset1 == 3) {
						index = 1;//xrgb32
					}
					else if	(format.ch0.byte_offset1 == 2 && format.ch1.byte_offset1 == 1 && format.ch2.byte_offset1 == 0) {
						index = 2;//bgrx32
					}
					else if	(format.ch0.byte_offset1 == 3 && format.ch1.byte_offset1 == 2 && format.ch2.byte_offset1 == 1) {
						index = 3;//xbgr32
					}
					else if	(format.ch0.byte_offset1 == 0 && format.ch1.byte_offset1 == 1 && format.ch2.byte_offset1 == 2) {
						index = 4;//rgb24
					}
					else if	(format.ch0.byte_offset1 == 2 && format.ch1.byte_offset1 == 1 && format.ch2.byte_offset1 == 0) {
						index = 5;//bgr24
					}
				}
			}
			else if (format.pixel_repeat_period == 2) {
				if		(format.chromalayout.vert_subs_factor == 1 && format.chromalayout.horz_subs_factor == 2) {
					if (format.colorspace == BT601) {
						if (format.ch0.byte_offset1 == 0 && format.ch1.byte_offset1 == 1 && format.ch0.byte_offset2 == 0 && format.ch2.byte_offset2 == 1) {
							index = 6;//yuyv_601
						}
						else if (format.ch0.byte_offset1 == 0 && format.ch1.byte_offset2 == 1 && format.ch0.byte_offset2 == 0 && format.ch2.byte_offset1 == 1) {
							index = 7;//yvyu_601
						}
						else if (format.ch0.byte_offset1 == 1 && format.ch1.byte_offset1 == 0 && format.ch0.byte_offset2 == 1 && format.ch2.byte_offset2 == 0) {
							index = 8;//uyvy_601
						}
						else if (format.ch0.byte_offset1 == 1 && format.ch1.byte_offset2 == 0 && format.ch0.byte_offset2 == 1 && format.ch2.byte_offset1 == 0) {
							index = 9;//vyuy_601
						}
					}
					else if (format.colorspace == BT709) {
						if (format.ch0.byte_offset1 == 0 && format.ch1.byte_offset1 == 1 && format.ch0.byte_offset2 == 0 && format.ch2.byte_offset2 == 1) {
							index = 10;//yuyv_709
						}
						else if (format.ch0.byte_offset1 == 0 && format.ch1.byte_offset2 == 1 && format.ch0.byte_offset2 == 0 && format.ch2.byte_offset1 == 1) {
							index = 11;//yvyu_709
						}
						else if (format.ch0.byte_offset1 == 1 && format.ch1.byte_offset1 == 0 && format.ch0.byte_offset2 == 1 && format.ch2.byte_offset2 == 0) {
							index = 12;//uyvy_709
						}
						else if (format.ch0.byte_offset1 == 1 && format.ch1.byte_offset2 == 0 && format.ch0.byte_offset2 == 1 && format.ch2.byte_offset1 == 0) {
							index = 13;//vyuy_709
						}
					}
				}
			}
		}
		else if (format.active_channels == 4) {
			if (format.pixel_repeat_period == 1) {
				if (format.colorspace == sRGB_PC) {
					if		(format.ch0.byte_offset1 == 0 && format.ch1.byte_offset1 == 1 && format.ch2.byte_offset1 == 2 && format.ch3.byte_offset1 == 3) {
						index = 14;//rgba32
					}
					else if	(format.ch0.byte_offset1 == 1 && format.ch1.byte_offset1 == 2 && format.ch2.byte_offset1 == 3 && format.ch3.byte_offset1 == 0) {
						index = 15;//argb32
					}
					else if	(format.ch0.byte_offset1 == 2 && format.ch1.byte_offset1 == 1 && format.ch2.byte_offset1 == 0 && format.ch3.byte_offset1 == 3) {
						index = 16;//bgra32
					}
					else if	(format.ch0.byte_offset1 == 3 && format.ch1.byte_offset1 == 2 && format.ch2.byte_offset1 == 1 && format.ch3.byte_offset1 == 0) {
						index = 17;//abgr32
					}
				}
				else if (format.colorspace == BT601 && format.chromalayout.horz_subs_factor == 1 && format.chromalayout.vert_subs_factor == 1) {
						index = 18;//AYUV 4:4:4:4
				}
			}
		}
	}
	else if (format.organisation == PLANAR) {
		if (format.active_channels == 3) {
			if (	format.chromalayout.horz_subs_factor ==	1//444
				&&	format.chromalayout.vert_subs_factor ==	1) {
					if (format.colorspace == BT601) {
						index = 19;
					}
					else if (format.colorspace == BT709) {
						index = 20;
					}
			}
			else if (	format.chromalayout.horz_subs_factor ==	2//422
				&&	format.chromalayout.vert_subs_factor ==	1) {
					if (format.colorspace == BT601) {
						index = 21;
					}
					else if (format.colorspace == BT709) {
						index = 22;
					}
			}
			else if (	format.chromalayout.horz_subs_factor ==	2//420
				&&	format.chromalayout.vert_subs_factor ==	2) {
					if (format.colorspace == BT601) {
						index = 23;
					}
					else if (format.colorspace == BT709) {
						index = 24;
					}
			}
		}
		else if (format.active_channels == 4) {
			if (	format.chromalayout.horz_subs_factor ==	1//444
				&&	format.chromalayout.vert_subs_factor ==	1) {
					if (format.colorspace == BT601) {
						index = 25;
					}
					else if (format.colorspace == BT709) {
						index = 26;
					}
			}
			else if (	format.chromalayout.horz_subs_factor ==	2//422
				&&	format.chromalayout.vert_subs_factor ==	1) {
					if (format.colorspace == BT601) {
						index = 27;
					}
					else if (format.colorspace == BT709) {
						index = 28;
					}
			}
			else if (	format.chromalayout.horz_subs_factor ==	2//420
				&&	format.chromalayout.vert_subs_factor ==	2) {
					if (format.colorspace == BT601) {
						index = 29;
					}
					else if (format.colorspace == BT709) {
						index = 30;
					}
			}
		}
	}
	return index;
}

int channelmask_to_byte_offset(int mask, int total_byte_per_pixel, int *byte_offset)
{
	int ret;
	const int byte0 = 0xFF000000;
	const int byte1 = 0x00FF0000;
	const int byte2 = 0x0000FF00;
	const int byte3 = 0x000000FF;
	ret = 0;
	if		(mask == byte3)	*byte_offset = total_byte_per_pixel - 1;
	else if (mask == byte2)	*byte_offset = total_byte_per_pixel - 2;
	else if (mask == byte1)	*byte_offset = total_byte_per_pixel - 3;
	else if (mask == byte0)	*byte_offset = total_byte_per_pixel - 4;
	else ret = 1;
	return ret;
}

int format_byte_offset(FormatDescriptor *format)
{
	int total_byte_per_pixel;
	int ret = 0;

	//figuring out the packing
	total_byte_per_pixel = format->total_bpp/8;

	ret += channelmask_to_byte_offset(format->ch0.mask1, total_byte_per_pixel, &format->ch0.byte_offset1);
	if (format->ch1.mask1 != 0)
		ret += channelmask_to_byte_offset(format->ch1.mask1, total_byte_per_pixel, &format->ch1.byte_offset1);
	if (format->ch2.mask1 != 0)
		ret += channelmask_to_byte_offset(format->ch2.mask1, total_byte_per_pixel, &format->ch2.byte_offset1);
	if (format->active_channels == 4)
	{
		ret += channelmask_to_byte_offset(format->ch3.mask1, total_byte_per_pixel, &format->ch3.byte_offset1);
	}

	if (format->pixel_repeat_period == 2)
	{
		ret += channelmask_to_byte_offset(format->ch0.mask2, total_byte_per_pixel, &format->ch0.byte_offset2);
		if (format->ch1.mask2 != 0)
			ret += channelmask_to_byte_offset(format->ch1.mask2, total_byte_per_pixel, &format->ch1.byte_offset2);
		if (format->ch2.mask2 != 0)
			ret += channelmask_to_byte_offset(format->ch2.mask2, total_byte_per_pixel, &format->ch2.byte_offset2);
		if (format->active_channels == 4)
		{
			ret += channelmask_to_byte_offset(format->ch3.mask2, total_byte_per_pixel, &format->ch3.byte_offset2);
		}
	}
	return ret;
}

int init_colorspaceconverter(ColorSpaceConverter *colorconverter, FormatDescriptor src_format, FormatDescriptor dst_format, int height, int width, int bDoAdaptiveInterpolation, int bAdaptiveIntDemomode)
{
	int ret = 0;
	int srcIdx, dstIdx;//, parIdx;

	colorconverter->isInit = 0;

	colorconverter->src_format					=	src_format;
	colorconverter->dst_format					=	dst_format;
	colorconverter->width						=	width;
	colorconverter->height						=	height;
	colorconverter->bDoAdaptiveInterpolation	=	bDoAdaptiveInterpolation;
	colorconverter->bAdaptiveIntDemomode		=	bAdaptiveIntDemomode;

	if (colorconverter->dst_format.organisation == PACKED)	{
		ret += format_byte_offset(&colorconverter->dst_format);
	}
	if (colorconverter->src_format.organisation == PACKED)	{
		ret += format_byte_offset(&colorconverter->src_format);
	}

	init_function_table();

	select_converter(colorconverter, &srcIdx, &dstIdx);
	colorconverter->srcIdx = srcIdx;
	colorconverter->dstIdx = dstIdx;
	if ((srcIdx < 0) || (dstIdx < 0)) {
		ret = -1;
	}
	//if ((colorconverter->height % 16 != 0) || (colorconverter->width % 16 != 0)) {
	if ((colorconverter->height % 2 != 0) || (colorconverter->width % 16 != 0)) {
		ret = -1;
	}
	if (ret==0)
	{
		colorconverter->isInit = 1;
	}
#if (defined USE_MACRO_TEMPLATES)
#else
	//in the fall-back-case (no X-MACROS), we still use a 3-d function pointer array, but the only function is located at [0][0][0]
	if (colorconverter->isInit == 1)
	{
		colorconverter->srcIdx = 0;
		colorconverter->dstIdx = 0;
	}
#endif
	return ret;
}

int reinit_colorspaceconverter(ColorSpaceConverter *colorconverter, int bDoAdaptiveInterpolation, int bAdaptiveIntDemomode)
{
        int srcIdx, dstIdx;//, parIdx;
	int ret = 0;
        colorconverter->isInit = 0;	
	colorconverter->bDoAdaptiveInterpolation	=	bDoAdaptiveInterpolation;
	colorconverter->bAdaptiveIntDemomode		=	bAdaptiveIntDemomode;
	select_converter(colorconverter, &srcIdx, &dstIdx);
	colorconverter->srcIdx = srcIdx;
	colorconverter->dstIdx = dstIdx;
	if ((srcIdx < 0) || (dstIdx < 0)) {
		ret = -1;
	}
	if (ret==0)
	{
		colorconverter->isInit = 1;
	}
	return ret;
}

int colorspaceconvert(ColorSpaceConverter *colorconverter, const unsigned char *in_data, unsigned char *out_data, const int in_size, const int out_size)
{
	int ret;
	ret = 0;
	colorconverter->src_format.size		=	in_size;
	colorconverter->dst_format.size		=	out_size;
	colorconvert_funcArray[colorconverter->srcIdx][colorconverter->dstIdx](colorconverter,  in_data, out_data,  in_size,  out_size);
	return ret;
}

#if 0
//interpolate chroma using luma values, and blend with classic chroma interpolation
void luma_adaptive_interp(unsigned char *y_full_ptr, //full-res Y
						  unsigned char *u_dec_ptr, //decimated U
						  unsigned char *v_dec_ptr, //decimated V
						  unsigned char *y_dec_ptr, //decimated Y
						  unsigned char *u_full_ptr, //interpolated U to be overwritten
						  unsigned char *v_full_ptr, //interpolated V to be overwritten
						  unsigned int full_height, //geometry of a full-size frame
						  unsigned int full_width, //geometry of a full-size frame						  
						  unsigned int full_stride, //geometry of a full-size frame
						  unsigned int demomode //process half frame only?
						  )

{
	unsigned int line, pix,vect_cnt, number_corrected_u, number_corrected_v;
	unsigned char *y_full_in1, *y_full_in2, *u_full_in1, *u_full_in2, *v_full_in1, *v_full_in2, *u_full_out1, *u_full_out2, *v_full_out1, *v_full_out2;
	unsigned char *y_dec_in1, *y_dec_in2, *y_dec_in3, *u_dec_in1, *u_dec_in2, *u_dec_in3, *v_dec_in1, *v_dec_in2, *v_dec_in3;	
	unsigned char y_local[4], u_prototype[4], v_prototype[4], y_d_cen, u_d_cen, v_d_cen;
	unsigned int dec_in_height, dec_in_width, dec_in_stride, full_in_height, full_in_width, full_in_stride; 
	int y_d_local[8], u_d_local[8], v_d_local[8];
	float u_scaling[8], v_scaling[8], u_scaling_scalar, v_scaling_scalar, u_error, v_error, quality;
	float mean_quality_u, mean_quality_v, percent_corrected_u, percent_corrected_v;
	unsigned char y_mask[8], u_mask[8], v_mask[8];
	unsigned char mask_tr;
	unsigned char num_u, num_v;
	int quality_scale;

	mask_tr = 3;
	quality_scale = 32*8;

	y_full_in1 = y_full_ptr + (2 * full_stride) + 2;//inY.planeptr + (2 * inY.stride) + 2;
	u_full_in1 = u_full_ptr + (2 * full_stride) + 2;//fullU.planeptr + (2 * fullU.stride) + 2;//start at 3rd row, 3rd col...
	v_full_in1 = v_full_ptr + (2 * full_stride) + 2;//fullV.planeptr + (2 * fullV.stride) + 2;//start at 3rd row, 3rd col...
	u_full_out1 = u_full_in1;//start at 3rd row, 3rd col...
	v_full_out1 = v_full_in1;
	y_dec_in1 = y_dec_ptr;//decLuma.planeptr;
	u_dec_in1 = u_dec_ptr;//inU.planeptr;
	v_dec_in1 = v_dec_ptr;//inV.planeptr;
	dec_in_height = full_height >> 1;//decLuma.height;
	dec_in_stride = full_stride >> 1;//decLuma.stride;
	dec_in_width = full_width >> 1;//decLuma.width;
	full_in_height = full_height;//fullU.height;
	full_in_stride = full_stride;//fullU.stride;
	full_in_width = full_width;//fullU.width;

	mean_quality_u = 0;
	mean_quality_v = 0;
	number_corrected_u = 0;
	number_corrected_v = 0;

	for (line = 1; line < dec_in_height-1; line++)
	{
		u_full_out2 = u_full_out1 + full_in_stride;
		v_full_out2 = v_full_out1 + full_in_stride;
		y_dec_in2 = y_dec_in1 + dec_in_stride;
		y_dec_in3 = y_dec_in2 + dec_in_stride;
		u_dec_in2 = u_dec_in1 + dec_in_stride;
		u_dec_in3 = u_dec_in2 + dec_in_stride;
		v_dec_in2 = v_dec_in1 + dec_in_stride;
		v_dec_in3 = v_dec_in2 + dec_in_stride;

		y_full_in2  = y_full_in1  + full_in_stride;
		u_full_in2  = u_full_in1  + full_in_stride;
		v_full_in2  = v_full_in1  + full_in_stride;

		for (pix = 1; pix < dec_in_width-1; pix++)
		{
			//copy a 2x2 window into a 4-element vector
			y_local[0]		= y_full_in1[2*pix-2];
			y_local[1]		= y_full_in1[2*pix-1];
			y_local[2]		= y_full_in2[2*pix-2];
			y_local[3]		= y_full_in2[2*pix-1];

			//copy a 3x3 window (excluding center) into a 8-element vector
			y_d_local[0]	= y_dec_in1[pix-1];
			y_d_local[1]	= y_dec_in1[pix];
			y_d_local[2]	= y_dec_in1[pix+1];
			y_d_local[3]	= y_dec_in2[pix-1];
			y_d_cen		= y_dec_in2[pix];//store away center element separately
			y_d_local[4]	= y_dec_in2[pix+1];
			y_d_local[5]	= y_dec_in3[pix-1];
			y_d_local[6]	= y_dec_in3[pix];
			y_d_local[7]	= y_dec_in3[pix+1];

			u_d_local[0]	= u_dec_in1[pix-1];
			u_d_local[1]	= u_dec_in1[pix];
			u_d_local[2]	= u_dec_in1[pix+1];
			u_d_local[3]	= u_dec_in2[pix-1];
			u_d_cen		= u_dec_in2[pix];//store away center element separately
			u_d_local[4]	= u_dec_in2[pix+1];
			u_d_local[5]	= u_dec_in3[pix-1];
			u_d_local[6]	= u_dec_in3[pix];
			u_d_local[7]	= u_dec_in3[pix+1];

			v_d_local[0]	= v_dec_in1[pix-1];
			v_d_local[1]	= v_dec_in1[pix];
			v_d_local[2]	= v_dec_in1[pix+1];
			v_d_local[3]	= v_dec_in2[pix-1];
			v_d_cen		= v_dec_in2[pix];//store away center element separately
			v_d_local[4]	= v_dec_in2[pix+1];
			v_d_local[5]	= v_dec_in3[pix-1];
			v_d_local[6]	= v_dec_in3[pix];
			v_d_local[7]	= v_dec_in3[pix+1];

			num_u = 0;
			num_v = 0;
			u_error = 0;
			v_error = 0;
			u_scaling_scalar = 0;
			v_scaling_scalar = 0;
			//Do initial processing
			for (vect_cnt = 0; vect_cnt<8; vect_cnt++)
			{
				////Y pre-process
				y_d_local[vect_cnt]		=	y_d_local[vect_cnt] - y_d_cen;
				y_mask[vect_cnt]			=	(abs(y_d_local[vect_cnt]) >= mask_tr);
				//U pre-process
				u_d_local[vect_cnt]		=	u_d_local[vect_cnt] - u_d_cen;
				if ((y_d_local[vect_cnt] != 0) && (u_d_local[vect_cnt] != 0)) {
					u_scaling[vect_cnt]	=	(float) u_d_local[vect_cnt] / (float) y_d_local[vect_cnt];
				}
				else 
					u_scaling[vect_cnt]	=	0;
				u_mask[vect_cnt]			=	(abs(u_d_local[vect_cnt]) >= mask_tr);
				u_mask[vect_cnt]			=	(u_mask[vect_cnt] && y_mask[vect_cnt]);
				num_u						+=	u_mask[vect_cnt];
				//V pre-process
				v_d_local[vect_cnt]		=	v_d_local[vect_cnt] - v_d_cen;
				if ((y_d_local[vect_cnt] != 0) && (v_d_local[vect_cnt] != 0)) {
					v_scaling[vect_cnt]	=	(float) v_d_local[vect_cnt] / (float) y_d_local[vect_cnt];
				}
				else 
					v_scaling[vect_cnt]	=	0;
				v_mask[vect_cnt]			=	(abs(v_d_local[vect_cnt]) >= mask_tr);
				v_mask[vect_cnt]			=	(v_mask[vect_cnt] && y_mask[vect_cnt]);
				num_v						+=	v_mask[vect_cnt];
			}
			//Do conditional sharpening of U
			if(num_u > 0 && (pix < dec_in_width/2 || !demomode))
			{
				//accumulate valid scaling values
				for (vect_cnt = 0; vect_cnt<8; vect_cnt++)
				{
					u_scaling_scalar += u_mask[vect_cnt] ? u_scaling[vect_cnt] : 0;
				}
				u_scaling_scalar = u_scaling_scalar / num_u;
				//generate prototype high-resolution 2x2 chroma
				for (vect_cnt = 0; vect_cnt<4; vect_cnt++)
				{
					u_prototype[vect_cnt] = ((y_local[vect_cnt] - y_d_cen)* u_scaling_scalar) + u_d_cen;
				}
				//estimate prediction error
				for (vect_cnt = 0; vect_cnt<8; vect_cnt++)
				{
					u_error += fabs((float)y_d_local[vect_cnt] * u_scaling_scalar - (float)u_d_local[vect_cnt]);
				}
				quality = quality_scale - u_error;
				quality = quality * (quality>0) / quality_scale;

				//*u_full_out1 = (guint8) ((quality * (float)u_prototype[0]) + ((1 - quality) * (float)(*u_full_out1++)));	
				//*u_full_out1 = (guint8) ((quality * (float)u_prototype[1]) + ((1 - quality) * (float)(*u_full_out1++)));				 
				//*u_full_out2 = (guint8) ((quality * (float)u_prototype[2]) + ((1 - quality) * (float)(*u_full_out2++)));
				//*u_full_out2 = (guint8) ((quality * (float)u_prototype[3]) + ((1 - quality) * (float)(*u_full_out2++)));
				*u_full_out1 = (unsigned char) ((quality * (float)u_prototype[0]) + ((1 - quality) * (float)(*u_full_out1++)));	
				*u_full_out1 = (unsigned char) ((quality * (float)u_prototype[1]) + ((1 - quality) * (float)(*u_full_out1++)));				 
				*u_full_out2 = (unsigned char) ((quality * (float)u_prototype[2]) + ((1 - quality) * (float)(*u_full_out2++)));
				*u_full_out2 = (unsigned char) ((quality * (float)u_prototype[3]) + ((1 - quality) * (float)(*u_full_out2++)));

				mean_quality_u += quality;
				number_corrected_u +=1;
			}
			else
			{
				*u_full_out1++;
				*u_full_out1++;
				*u_full_out2++;
				*u_full_out2++;
			}
			//Do conditional sharpening of V
			if(num_v > 0 && (pix < dec_in_width/2 || !demomode))
				//#ifdef demomode //process only left half image...
				//			 if(num_v > 0 && pix < dec_in_width/2)
				//#else
				//			 if(num_v > 0) 
				//#endif			 
			{
				//accumulate valid scaling values
				for (vect_cnt = 0; vect_cnt<8; vect_cnt++)
				{
					v_scaling_scalar += v_mask[vect_cnt] ? v_scaling[vect_cnt] : 0;
				}
				v_scaling_scalar = v_scaling_scalar / num_v;
				//generate prototype high-resolution 2x2 chroma
				for (vect_cnt = 0; vect_cnt<4; vect_cnt++)
				{
					v_prototype[vect_cnt] = ((y_local[vect_cnt] - y_d_cen)* v_scaling_scalar) + v_d_cen;
				}
				//estimate prediction error
				for (vect_cnt = 0; vect_cnt<8; vect_cnt++)
				{
					v_error += fabs((float)y_d_local[vect_cnt] * v_scaling_scalar - (float)v_d_local[vect_cnt]);
				}
				quality = quality_scale - v_error;
				quality = quality * (quality>0) / quality_scale;
				//form a blended output
				//*v_full_out1 = (guint8) ((quality * (float)v_prototype[0]) + ((1 - quality) * (float)(*v_full_out1++)));	
				//*v_full_out1 = (guint8) ((quality * (float)v_prototype[1]) + ((1 - quality) * (float)(*v_full_out1++)));
				//*v_full_out2 = (guint8) ((quality * (float)v_prototype[2]) + ((1 - quality) * (float)(*v_full_out2++)));
				//*v_full_out2 = (guint8) ((quality * (float)v_prototype[3]) + ((1 - quality) * (float)(*v_full_out2++)));
				*v_full_out1 = (unsigned char) ((quality * (float)v_prototype[0]) + ((1 - quality) * (float)(*v_full_out1++)));	
				*v_full_out1 = (unsigned char) ((quality * (float)v_prototype[1]) + ((1 - quality) * (float)(*v_full_out1++)));
				*v_full_out2 = (unsigned char) ((quality * (float)v_prototype[2]) + ((1 - quality) * (float)(*v_full_out2++)));
				*v_full_out2 = (unsigned char) ((quality * (float)v_prototype[3]) + ((1 - quality) * (float)(*v_full_out2++)));

				mean_quality_v += quality;
				number_corrected_v +=1;
			}
			else
			{
				*v_full_out1++;
				*v_full_out1++;
				*v_full_out2++;
				*v_full_out2++;
			}
		}
		u_full_out1 += 2*full_in_stride - full_in_width + 4;
		v_full_out1 += 2*full_in_stride - full_in_width + 4;
		y_full_in1 += 2*full_in_stride;
		u_full_in1 += 2*full_in_stride;
		v_full_in1 += 2*full_in_stride;
		y_dec_in1 += dec_in_stride;
		u_dec_in1 += dec_in_stride;
		v_dec_in1 += dec_in_stride;
	}
	mean_quality_v = mean_quality_v/number_corrected_v;
	percent_corrected_v = 100*number_corrected_v/(dec_in_height*dec_in_width);
	mean_quality_u = mean_quality_u/number_corrected_u;
	percent_corrected_u = 100*number_corrected_u/(dec_in_height*dec_in_width);
}
#endif
