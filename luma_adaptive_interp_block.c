#include <math.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void
luma_adaptive_interp_block(int line,//current line in full-resolution array
                           int pix,//current pixel in full-resolution array
                           const unsigned char *y_ptr, //full-res Y
                           int y_stride, //full-res Y
                           const unsigned char *u_ptr, //decimated U
                           int u_stride, //decimated U
                           const unsigned char *v_ptr, //decimated V
                           int v_stride, //decimated V
                           unsigned char *u_upper0_full_ptr, //interpolated U
                           unsigned char *u_upper1_full_ptr, //interpolated U
                           unsigned char *u_lower0_full_ptr, //interpolated U
                           unsigned char *u_lower1_full_ptr, //interpolated U
                           unsigned char *v_upper0_full_ptr, //interpolated V
                           unsigned char *v_upper1_full_ptr, //interpolated V
                           unsigned char *v_lower0_full_ptr, //interpolated V
                           unsigned char *v_lower1_full_ptr, //interpolated V
                           unsigned int demomode //process half frame only?
                           )
{
  unsigned int vect_cnt;//, number_corrected_u, number_corrected_v;
  //unsigned char *y_full_in1, *y_full_in2, *u_full_in1, *u_full_in2, *v_full_in1, *v_full_in2, *u_full_out1, *u_full_out2, *v_full_out1, *v_full_out2;
  //unsigned char *y_dec_in1, *y_dec_in2, *y_dec_in3, *u_dec_in1, *u_dec_in2, *u_dec_in3, *v_dec_in1, *v_dec_in2, *v_dec_in3;	
  unsigned char y_local[4], u_prototype[4], v_prototype[4], y_d_cen, u_d_cen, v_d_cen;
  //unsigned int dec_in_height, dec_in_stride, full_in_height, full_in_width, full_in_stride; 
  int dec_in_width;
  int y_d_local[8], u_d_local[8], v_d_local[8];
  float u_scaling[8], v_scaling[8], u_scaling_scalar, v_scaling_scalar, u_error, v_error, quality;
  //float mean_quality_u, mean_quality_v, percent_corrected_u, percent_corrected_v;
  unsigned char y_mask[8], u_mask[8], v_mask[8];
  unsigned char mask_tr;
  unsigned char num_u, num_v;
  int quality_scale;
  int early_skip_tr, y_min, y_max;

  dec_in_width = u_stride;

  mask_tr = 3;
  quality_scale = 32*8;
  y_local[0]		= *(y_ptr + ((line + 0)*y_stride) + pix + 0);
  y_local[1]		= *(y_ptr + ((line + 0)*y_stride) + pix + 1);
  y_local[2]		= *(y_ptr + ((line + 1)*y_stride) + pix + 0);
  y_local[3]		= *(y_ptr + ((line + 1)*y_stride) + pix + 1);

  early_skip_tr = 25;
  y_min = y_local[0];
  y_max = y_local[0];
  for (vect_cnt = 1; vect_cnt<4; vect_cnt++)
  {
    if ((y_local[vect_cnt])>y_max)
      y_max = y_local[vect_cnt];
    else if ((y_local[vect_cnt])<y_min)
      y_min = y_local[vect_cnt];
  }
  if ((y_max - y_min) > early_skip_tr) {
    //generate a decimated 3x3 window (excluding center) into a 8-element vector
    y_d_local[0]=(*(y_ptr + ((line - 2)*y_stride) + pix - 2)
      + *(y_ptr + ((line - 2)*y_stride) + pix - 1)
      + *(y_ptr + ((line - 1)*y_stride) + pix - 2)
      + *(y_ptr + ((line - 1)*y_stride) + pix - 1)) >> 2;
    y_d_local[1]=(*(y_ptr + ((line - 2)*y_stride) + pix + 0)
      + *(y_ptr + ((line - 2)*y_stride) + pix + 1)
      + *(y_ptr + ((line - 1)*y_stride) + pix + 0)
      + *(y_ptr + ((line - 1)*y_stride) + pix + 1)) >> 2;
    y_d_local[2]=(*(y_ptr + ((line - 2)*y_stride) + pix + 2)
      + *(y_ptr + ((line - 2)*y_stride) + pix + 3)
      + *(y_ptr + ((line - 1)*y_stride) + pix + 2)
      + *(y_ptr + ((line - 1)*y_stride) + pix + 3)) >> 2;
    y_d_local[3]= (*(y_ptr + ((line +0)*y_stride) + pix - 2)
      + *(y_ptr + ((line + 0)*y_stride) + pix - 1)
      + *(y_ptr + ((line + 1)*y_stride) + pix - 2)
      + *(y_ptr + ((line + 1)*y_stride) + pix - 1)) >> 2;
    y_d_cen = (unsigned char)((*(y_ptr + ((line +0)*y_stride) + pix + 0)
      + *(y_ptr + ((line + 0)*y_stride) + pix + 1)
      + *(y_ptr + ((line + 1)*y_stride) + pix + 0)
      + *(y_ptr + ((line + 1)*y_stride) + pix + 1)) >> 2);//store away center element separately
    y_d_local[4]= (*(y_ptr + ((line +0)*y_stride) + pix + 2)
      + *(y_ptr + ((line + 0)*y_stride) + pix + 3)
      + *(y_ptr + ((line + 1)*y_stride) + pix + 2)
      + *(y_ptr + ((line + 1)*y_stride) + pix + 3)) >> 2;;
    y_d_local[5]= (*(y_ptr + ((line +2)*y_stride) + pix - 2)
      + *(y_ptr + ((line + 2)*y_stride) + pix - 1)
      + *(y_ptr + ((line + 3)*y_stride) + pix - 2)
      + *(y_ptr + ((line + 3)*y_stride) + pix - 1)) >> 2;;
    y_d_local[6]= (*(y_ptr + ((line +2)*y_stride) + pix + 0)
      + *(y_ptr + ((line + 2)*y_stride) + pix + 1)
      + *(y_ptr + ((line + 3)*y_stride) + pix + 0)
      + *(y_ptr + ((line + 3)*y_stride) + pix + 1)) >> 2;;
    y_d_local[7]= (*(y_ptr + ((line +2)*y_stride) + pix + 2)
      + *(y_ptr + ((line + 2)*y_stride) + pix + 3)
      + *(y_ptr + ((line + 3)*y_stride) + pix + 2)
      + *(y_ptr + ((line + 3)*y_stride) + pix + 3)) >> 2;;

    u_d_local[0]	= *(u_ptr + (((line >> 1) - 1) * u_stride) + ((pix >> 1) - 1));
    u_d_local[1]	= *(u_ptr + (((line >> 1) - 1) * u_stride) + ((pix >> 1) - 0));
    u_d_local[2]	= *(u_ptr + (((line >> 1) - 1) * u_stride) + ((pix >> 1) + 1));
    u_d_local[3]	= *(u_ptr + (((line >> 1) - 0) * u_stride) + ((pix >> 1) - 1));
    u_d_cen			= *(u_ptr + (((line >> 1) - 0) * u_stride) + ((pix >> 1) - 0));//store away center element separately
    u_d_local[4]	= *(u_ptr + (((line >> 1) - 0) * u_stride) + ((pix >> 1) + 1));
    u_d_local[5]	= *(u_ptr + (((line >> 1) + 1) * u_stride) + ((pix >> 1) - 1));
    u_d_local[6]	= *(u_ptr + (((line >> 1) + 1) * u_stride) + ((pix >> 1) - 0));
    u_d_local[7]	= *(u_ptr + (((line >> 1) + 1) * u_stride) + ((pix >> 1) + 1));

    v_d_local[0]	= *(v_ptr + (((line >> 1) - 1) * v_stride) + ((pix >> 1) - 1));
    v_d_local[1]	= *(v_ptr + (((line >> 1) - 1) * v_stride) + ((pix >> 1) - 0));
    v_d_local[2]	= *(v_ptr + (((line >> 1) - 1) * v_stride) + ((pix >> 1) + 1));
    v_d_local[3]	= *(v_ptr + (((line >> 1) - 0) * v_stride) + ((pix >> 1) - 1));
    v_d_cen			= *(v_ptr + (((line >> 1) - 0) * v_stride) + ((pix >> 1) - 0));//store away center element separately
    v_d_local[4]	= *(v_ptr + (((line >> 1) - 0) * v_stride) + ((pix >> 1) + 1));
    v_d_local[5]	= *(v_ptr + (((line >> 1) + 1) * v_stride) + ((pix >> 1) - 1));
    v_d_local[6]	= *(v_ptr + (((line >> 1) + 1) * v_stride) + ((pix >> 1) - 0));
    v_d_local[7]	= *(v_ptr + (((line >> 1) + 1) * v_stride) + ((pix >> 1) + 1));

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
      y_mask[vect_cnt]			=	(unsigned char)(abs(y_d_local[vect_cnt]) >= mask_tr);
      //U pre-process
      u_d_local[vect_cnt]		=	u_d_local[vect_cnt] - u_d_cen;
      if ((y_d_local[vect_cnt] != 0) && (u_d_local[vect_cnt] != 0)) {
        u_scaling[vect_cnt]	=	(float) u_d_local[vect_cnt] / (float) y_d_local[vect_cnt];
      }
      else 
        u_scaling[vect_cnt]	=	0;
      u_mask[vect_cnt] = (unsigned char)(abs(u_d_local[vect_cnt]) >= mask_tr);
      u_mask[vect_cnt] = (unsigned char)(u_mask[vect_cnt] && y_mask[vect_cnt]);
      num_u += u_mask[vect_cnt];
      //V pre-process
      v_d_local[vect_cnt]		=	v_d_local[vect_cnt] - v_d_cen;
      if ((y_d_local[vect_cnt] != 0) && (v_d_local[vect_cnt] != 0)) {
        v_scaling[vect_cnt]	=	(float) v_d_local[vect_cnt] / (float) y_d_local[vect_cnt];
      }
      else 
        v_scaling[vect_cnt]	=	0;
      v_mask[vect_cnt] = (unsigned char)(abs(v_d_local[vect_cnt]) >= mask_tr);
      v_mask[vect_cnt] = (unsigned char)(v_mask[vect_cnt] && y_mask[vect_cnt]);
      num_v += v_mask[vect_cnt];
    }
    //Do conditional sharpening of U
    if(num_u > 0 && (pix < dec_in_width || !demomode))
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
        u_prototype[vect_cnt] = (unsigned char)(((y_local[vect_cnt] - y_d_cen)* u_scaling_scalar) + u_d_cen);
      }
      //estimate prediction error
      for (vect_cnt = 0; vect_cnt<8; vect_cnt++)
      {
        u_error += fabsf((float)y_d_local[vect_cnt] * u_scaling_scalar - (float)u_d_local[vect_cnt]);
      }
      quality = quality_scale - u_error;
      quality = quality * (quality>0) / quality_scale;

      *u_upper0_full_ptr = (unsigned char) ((quality * (float)u_prototype[0]) + ((1 - quality) * (float)(*u_upper0_full_ptr)));
      *u_upper1_full_ptr = (unsigned char) ((quality * (float)u_prototype[1]) + ((1 - quality) * (float)(*u_upper1_full_ptr)));				 
      *u_lower0_full_ptr = (unsigned char) ((quality * (float)u_prototype[2]) + ((1 - quality) * (float)(*u_lower0_full_ptr)));
      *u_lower1_full_ptr = (unsigned char) ((quality * (float)u_prototype[3]) + ((1 - quality) * (float)(*u_lower1_full_ptr)));
      //mean_quality_u += quality;
      //number_corrected_u +=1;
    }
    //Do conditional sharpening of V
    if(num_v > 0 && (pix < dec_in_width || !demomode))
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
        v_prototype[vect_cnt] = (unsigned char)(((y_local[vect_cnt] - y_d_cen)* v_scaling_scalar) + v_d_cen);
      }
      //estimate prediction error
      for (vect_cnt = 0; vect_cnt<8; vect_cnt++)
      {
        v_error += fabsf((float)y_d_local[vect_cnt] * v_scaling_scalar - (float)v_d_local[vect_cnt]);
      }
      quality = quality_scale - v_error;
      quality = quality * (quality>0) / quality_scale;
      //form a blended output
      *v_upper0_full_ptr = (unsigned char) ((quality * (float)v_prototype[0]) + ((1 - quality) * (float)(*v_upper0_full_ptr)));
      *v_upper1_full_ptr = (unsigned char) ((quality * (float)v_prototype[1]) + ((1 - quality) * (float)(*v_upper1_full_ptr)));				 
      *v_lower0_full_ptr = (unsigned char) ((quality * (float)v_prototype[2]) + ((1 - quality) * (float)(*v_lower0_full_ptr)));
      *v_lower1_full_ptr = (unsigned char) ((quality * (float)v_prototype[3]) + ((1 - quality) * (float)(*v_lower1_full_ptr)));
      //mean_quality_v += quality;
      //number_corrected_v +=1;
    }
  }
}
