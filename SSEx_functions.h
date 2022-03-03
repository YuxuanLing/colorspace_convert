#include <stdint.h>
#include <emmintrin.h>
#pragma warning (disable:177)
#pragma warning (disable:981) //operands are evaluated in unspecified order
#pragma warning (disable:869) //parameter * was never referenced
void FUNCTION_NAME
(const ColorSpaceConverter *colorconverter, const unsigned char *in_data, unsigned char *out_data, const int in_size, const int out_size)
{
//#if ((defined DST_PLANAR)&& (defined DST_3CHANNELS) && (defined DST_420) && (defined DST_YUV601) && (defined SRC_PACKED) && (defined SRC_3CHANNELS) && (defined SRC_PIXELPERIOD2) && (defined SRC_422) && (defined SRC_YUV601) && (defined SRC_16BPP) && ((SRC_CH0_BYTEPOS_0 == 0)) && ((SRC_CH0_BYTEPOS_1 == 0))&& ((SRC_CH1_BYTEPOS_0 == 1))&& ((SRC_CH2_BYTEPOS_1 == 1)))
#if ((defined DST_PLANAR)&& (defined DST_3CHANNELS) && (defined DST_420) && (defined DST_YUV601) && (defined SRC_PACKED) && (defined SRC_3CHANNELS) && (defined SRC_PIXELPERIOD2) && (defined SRC_422) && (defined SRC_YUV601) && (defined SRC_16BPP))
  //YUYV 4:2:2 BT 601 -> I420 BT 601
  //const unsigned char *inp0, *inp1;
  //unsigned char *outp0, *outp1;
  int height, j;
  //  int width;
  unsigned char *inp0, *inp1;

  const int stride_in = colorconverter->src_format.stride;	
  const int stride_out_ch0 = colorconverter->dst_format.ch0.stride;
  const int stride_out_ch1 = colorconverter->dst_format.ch1.stride;
  const int stride_out_ch2 = colorconverter->dst_format.ch2.stride;

  __m128i _zero     = _mm_setzero_si128();
  __m128i _1010mask = _mm_set_epi16(0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00);
  __m128i _0101mask = _mm_set_epi16(0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff, 0x00ff);
  __m128i _0100mask = _mm_set_epi16(0x00ff, 0x0000, 0x00ff, 0x0000, 0x00ff, 0x0000, 0x00ff, 0x0000);
  __m128i _0001mask = _mm_set_epi16(0x0000, 0x00ff, 0x0000, 0x00ff, 0x0000, 0x00ff, 0x0000, 0x00ff);
  __m128i _1000mask = _mm_set_epi16(0xff00, 0x0000, 0xff00, 0x0000, 0xff00, 0x0000, 0xff00, 0x0000);
  __m128i _0010mask = _mm_set_epi16(0x0000, 0xff00, 0x0000, 0xff00, 0x0000, 0xff00, 0x0000, 0xff00);
  __m128i _first64  = _mm_set_epi16(0xffff, 0xffff, 0xffff, 0xffff, 0x0000, 0x0000, 0x0000, 0x0000);


#if(	(SRC_CH0_BYTEPOS_0 == 0)&&(SRC_CH0_BYTEPOS_1 == 0)&&(SRC_CH1_BYTEPOS_0 == 1)&&(SRC_CH2_BYTEPOS_1 == 1))//YUYV
  __m128i _src_ch0_mask = _0101mask;
  __m128i _src_ch1_mask = _0010mask;
  __m128i _src_ch2_mask = _1000mask;
#elif(	(SRC_CH0_BYTEPOS_0 == 0)&&(SRC_CH0_BYTEPOS_1 == 0)&&(SRC_CH1_BYTEPOS_1 == 1)&&(SRC_CH2_BYTEPOS_0 == 1))//YVYU
  __m128i _src_ch0_mask = _0101mask;
  __m128i _src_ch1_mask = _1000mask;
  __m128i _src_ch2_mask = _0010mask;
#elif(	(SRC_CH0_BYTEPOS_0 == 1)&&(SRC_CH0_BYTEPOS_1 == 1)&&(SRC_CH1_BYTEPOS_0 == 0)&&(SRC_CH2_BYTEPOS_1 == 0))//UYVY
  __m128i _src_ch0_mask = _1010mask;
  __m128i _src_ch1_mask = _0001mask;
  __m128i _src_ch2_mask = _0100mask;
#elif(	(SRC_CH0_BYTEPOS_0 == 1)&&(SRC_CH0_BYTEPOS_1 == 1)&&(SRC_CH1_BYTEPOS_1 == 0)&&(SRC_CH2_BYTEPOS_0 == 0))//VYUY
  __m128i _src_ch0_mask = _1010mask;
  __m128i _src_ch1_mask = _0100mask;
  __m128i _src_ch2_mask = _0001mask;
#endif

  //__m128i _test_row_0_0  = _mm_set_epi16(0x7f7f, 0x7f7f, 0x7f7f, 0x7f7f, 0x7f7f, 0x7f7f, 0x7f00, 0xff7f);
  //__m128i _test_row_0_1  = _mm_set_epi16(0x7f7f, 0x7f7f, 0x7f7f, 0x7f7f, 0x7f7f, 0x7f7f, 0x7f7f, 0x7f7f);
  //__m128i _test_row_1_0  = _mm_set_epi16(0x7f7f, 0xff7f, 0x7f7f, 0xff7f, 0x7f7f, 0x7f7f, 0x7f7f, 0x7f7f);
  //__m128i _test_row_1_1  = _mm_set_epi16(0x7f7f, 0xff7f, 0x7f7f, 0xff7f, 0x7f7f, 0x7f7f, 0x7f7f, 0x7f7f);

  unsigned char *out_ch0_0 = out_data + colorconverter->dst_format.ch0.offset;
  unsigned char *out_ch0_1 = out_ch0_0 + colorconverter->dst_format.ch0.stride;
  unsigned char *out_ch1 = out_data + colorconverter->dst_format.ch1.offset;
  unsigned char *out_ch2 = out_data + colorconverter->dst_format.ch2.offset;
  const int count = (colorconverter->width >> 4);
  inp0 = (unsigned char *)in_data; 
  inp1 = (unsigned char *)(in_data + colorconverter->src_format.stride);

  height		=	colorconverter->height;
//  width		=	colorconverter->width;

  for(j = 0; j < height>>1; j ++) {    
    int i;
    for (i = 0; i < count; i++)
    {
      __m128i xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7, xmm8, xmm9, xmm10, xmm11, xmm12, xmm13, xmm14, xmm15,
        xmm16, xmm17, xmm18, xmm19, xmm20, xmm21, xmm22, xmm23, xmm24, xmm25, xmm26, xmm27, xmm28, xmm29, xmm30, xmm31,
        xmm32, xmm33, xmm34, xmm35, xmm36, xmm37, xmm38, xmm39, xmm40, xmm41, xmm42, xmm43, xmm44, xmm45, xmm46, xmm47;

      /* 1. load 2x16 bytes of yuv 4:2:2 packed data */

      //load 2x16 bytes of yuv422 data (16 Ys, 8 Us and 8 Vs) from line#0
      if ((intptr_t)inp0 % 16 == 0)
      {
        xmm0 = _mm_load_si128((__m128i *)(inp0 + i*32));	//|Va3|Ya7|Ua3|Ya6|Va2|Ya5|Ua2|Ya4|Va1|Ya3|Ua1|Ya2|Va0|Ya1|Ua0|Ya0|
        xmm1 = _mm_load_si128((__m128i *)(inp0 + i*32+16));	//|Va7|YaF|Ua7|YaE|Va6|YaD|Ua6|YaC|Va5|YaB|Ua5|YaA|Va4|Ya9|Ua4|Ya8|
      }
      else 
      {
        xmm0 = _mm_loadu_si128((__m128i *)(inp0 + i*32));	//|Va3|Ya7|Ua3|Ya6|Va2|Ya5|Ua2|Ya4|Va1|Ya3|Ua1|Ya2|Va0|Ya1|Ua0|Ya0|
        xmm1 = _mm_loadu_si128((__m128i *)(inp0 + i*32+16));	//|Va7|YaF|Ua7|YaE|Va6|YaD|Ua6|YaC|Va5|YaB|Ua5|YaA|Va4|Ya9|Ua4|Ya8|
      }

      //load 2x16 bytes of yuv422 data (16 Ys, 8 Us and 8 Vs) from line#1
      if ((intptr_t)inp1 % 16 == 0)
      {
        xmm2 = _mm_load_si128((__m128i *)(inp1 + i*32));	//|Vb3|Yb7|Ub3|Yb6|Vb2|Yb5|Ub2|Yb4|Vb1|Yb3|Ub1|Yb2|Vb0|Yb1|Ub0|Yb0|
        xmm3 = _mm_load_si128((__m128i *)(inp1 + i*32+16));	//|Vb7|YbF|Ub7|YbE|Vb6|YbD|Ub6|YbC|Vb5|YbB|Ub5|YbA|Vb4|Yb9|Ub4|Yb8|
      }
      else
      {
        xmm2 = _mm_loadu_si128((__m128i *)(inp1 + i*32));	//|Vb3|Yb7|Ub3|Yb6|Vb2|Yb5|Ub2|Yb4|Vb1|Yb3|Ub1|Yb2|Vb0|Yb1|Ub0|Yb0|
        xmm3 = _mm_loadu_si128((__m128i *)(inp1 + i*32+16));	//|Vb7|YbF|Ub7|YbE|Vb6|YbD|Ub6|YbC|Vb5|YbB|Ub5|YbA|Vb4|Yb9|Ub4|Yb8|
      }

      /* 2. extract into Y, U and V */
      //comments as if format was YUYV!
      xmm4 = _mm_and_si128(xmm0,_src_ch0_mask);	//|   |Ya7|   |Ya6|   |Ya5|   |Ya4|   |Ya3|   |Ya2|   |Ya1|   |Ya0|
      xmm5 = _mm_and_si128(xmm0,_src_ch1_mask);	//|   |   |Ua3|   |   |   |Ua2|   |   |   |Ua1|   |   |   |Ua0|   |
      xmm6 = _mm_and_si128(xmm0,_src_ch2_mask);	//|Va3|   |   |   |Va2|   |   |   |Va1|   |   |   |Va0|   |   |   |

      xmm7 = _mm_and_si128(xmm1,_src_ch0_mask);	//|   |YaF|   |YaE|   |YaD|   |YaC|   |YaB|   |YaA|   |Ya9|   |Ya8|
      xmm8 = _mm_and_si128(xmm1,_src_ch1_mask);	//|   |   |Ua7|   |   |   |Ua6|   |   |   |Ua5|   |   |   |Ua4|   |
      xmm9 = _mm_and_si128(xmm1,_src_ch2_mask);	//|Va7|   |   |   |Va6|   |   |   |Va5|   |   |   |Va4|   |   |   |

      xmm10 = _mm_and_si128(xmm2,_src_ch0_mask);	//|   |Yb7|   |Yb6|   |Yb5|   |Yb4|   |Yb3|   |Yb2|   |Yb1|   |Yb0|
      xmm11 = _mm_and_si128(xmm2,_src_ch1_mask);	//|   |   |Ub3|   |   |   |Ub2|   |   |   |Ub1|   |   |   |Ub0|   |
      xmm12 = _mm_and_si128(xmm2,_src_ch2_mask);	//|Vb3|   |   |   |Vb2|   |   |   |Vb1|   |   |   |Vb0|   |   |   |

      xmm13 = _mm_and_si128(xmm3,_src_ch0_mask);	//|   |YbF|   |YbE|   |YbD|   |YbC|   |YbB|   |YbA|   |Yb9|   |Yb8|
      xmm14 = _mm_and_si128(xmm3,_src_ch1_mask);	//|   |   |Ub7|   |   |   |Ub6|   |   |   |Ub5|   |   |   |Ub4|   |
      xmm15 = _mm_and_si128(xmm3,_src_ch2_mask);	//|Vb7|   |   |   |Vb6|   |   |   |Vb5|   |   |   |Vb4|   |   |   |

#if (SRC_CH0_BYTEPOS_0 == 1)&&(SRC_CH0_BYTEPOS_1 == 1)
      xmm4	= _mm_srli_si128(xmm4, 1);
      xmm7	= _mm_srli_si128(xmm7, 1);
      xmm10	= _mm_srli_si128(xmm10, 1);
      xmm13	= _mm_srli_si128(xmm13, 1);
#endif
      /* 3. Chroma interpolation */
#if(	(SRC_CH0_BYTEPOS_0 == 0)&&(SRC_CH0_BYTEPOS_1 == 0)&&(SRC_CH1_BYTEPOS_0 == 1)&&(SRC_CH2_BYTEPOS_1 == 1))//YUYV
      xmm16 = _mm_slli_si128(xmm5,1);			//|   |Ua3|   |   |   |Ua2|   |   |   |Ua1|   |   |   |Ua0|   |   |
      xmm17 = _mm_slli_si128(xmm11,1);		//|   |Ub3|   |   |   |Ub2|   |   |   |Ub1|   |   |   |Ub0|   |   |
      xmm18 = _mm_slli_si128(xmm8,1);			//|   |Ua7|   |   |   |Ua6|   |   |   |Ua5|   |   |   |Ua4|   |   |
      xmm19 = _mm_slli_si128(xmm14,1);		//|   |Ub7|   |   |   |Ub6|   |   |   |Ub5|   |   |   |Ub4|   |   |
      xmm20 = _mm_srli_si128(xmm6,1);			//|   |Va3|   |   |   |Va2|   |   |   |Va1|   |   |   |Va0|   |   |
      xmm21 = _mm_srli_si128(xmm12,1);		//|   |Vb3|   |   |   |Vb2|   |   |   |Vb1|   |   |   |Vb0|   |   |
      xmm22 = _mm_srli_si128(xmm9,1);			//|   |Va7|   |   |   |Va6|   |   |   |Va5|   |   |   |Va4|   |   |
      xmm23 = _mm_srli_si128(xmm15,1);		//|   |Vb7|   |   |   |Vb6|   |   |   |Vb5|   |   |   |Vb4|   |   |
#elif(	(SRC_CH0_BYTEPOS_0 == 0)&&(SRC_CH0_BYTEPOS_1 == 0)&&(SRC_CH1_BYTEPOS_1 == 1)&&(SRC_CH2_BYTEPOS_0 == 1))//YVYU
      xmm16 = _mm_srli_si128(xmm5,1);			//|   |Ua3|   |   |   |Ua2|   |   |   |Ua1|   |   |   |Ua0|   |   |
      xmm17 = _mm_srli_si128(xmm11,1);		//|   |Ub3|   |   |   |Ub2|   |   |   |Ub1|   |   |   |Ub0|   |   |
      xmm18 = _mm_srli_si128(xmm8,1);			//|   |Ua7|   |   |   |Ua6|   |   |   |Ua5|   |   |   |Ua4|   |   |
      xmm19 = _mm_srli_si128(xmm14,1);		//|   |Ub7|   |   |   |Ub6|   |   |   |Ub5|   |   |   |Ub4|   |   |
      xmm20 = _mm_slli_si128(xmm6,1);			//|   |Va3|   |   |   |Va2|   |   |   |Va1|   |   |   |Va0|   |   |
      xmm21 = _mm_slli_si128(xmm12,1);		//|   |Vb3|   |   |   |Vb2|   |   |   |Vb1|   |   |   |Vb0|   |   |
      xmm22 = _mm_slli_si128(xmm9,1);			//|   |Va7|   |   |   |Va6|   |   |   |Va5|   |   |   |Va4|   |   |
      xmm23 = _mm_slli_si128(xmm15,1);		//|   |Vb7|   |   |   |Vb6|   |   |   |Vb5|   |   |   |Vb4|   |   |
#elif(	(SRC_CH0_BYTEPOS_0 == 1)&&(SRC_CH0_BYTEPOS_1 == 1)&&(SRC_CH1_BYTEPOS_0 == 0)&&(SRC_CH2_BYTEPOS_1 == 0))//UYVY
      xmm16 = _mm_slli_si128(xmm5,2);			//|   |Ua3|   |   |   |Ua2|   |   |   |Ua1|   |   |   |Ua0|   |   |
      xmm17 = _mm_slli_si128(xmm11,2);		//|   |Ub3|   |   |   |Ub2|   |   |   |Ub1|   |   |   |Ub0|   |   |
      xmm18 = _mm_slli_si128(xmm8,2);			//|   |Ua7|   |   |   |Ua6|   |   |   |Ua5|   |   |   |Ua4|   |   |
      xmm19 = _mm_slli_si128(xmm14,2);		//|   |Ub7|   |   |   |Ub6|   |   |   |Ub5|   |   |   |Ub4|   |   |
      xmm20 = _mm_slli_si128(xmm6,0);			//|   |Va3|   |   |   |Va2|   |   |   |Va1|   |   |   |Va0|   |   |
      xmm21 = _mm_slli_si128(xmm12,0);		//|   |Vb3|   |   |   |Vb2|   |   |   |Vb1|   |   |   |Vb0|   |   |
      xmm22 = _mm_slli_si128(xmm9,0);			//|   |Va7|   |   |   |Va6|   |   |   |Va5|   |   |   |Va4|   |   |
      xmm23 = _mm_slli_si128(xmm15,0);		//|   |Vb7|   |   |   |Vb6|   |   |   |Vb5|   |   |   |Vb4|   |   |
#elif(	(SRC_CH0_BYTEPOS_0 == 1)&&(SRC_CH0_BYTEPOS_1 == 1)&&(SRC_CH1_BYTEPOS_1 == 0)&&(SRC_CH2_BYTEPOS_0 == 0))//VYUY
      xmm16 = _mm_slli_si128(xmm5,0);			//|   |Ua3|   |   |   |Ua2|   |   |   |Ua1|   |   |   |Ua0|   |   |
      xmm17 = _mm_slli_si128(xmm11,0);		//|   |Ub3|   |   |   |Ub2|   |   |   |Ub1|   |   |   |Ub0|   |   |
      xmm18 = _mm_slli_si128(xmm8,0);			//|   |Ua7|   |   |   |Ua6|   |   |   |Ua5|   |   |   |Ua4|   |   |
      xmm19 = _mm_slli_si128(xmm14,0);		//|   |Ub7|   |   |   |Ub6|   |   |   |Ub5|   |   |   |Ub4|   |   |
      xmm20 = _mm_slli_si128(xmm6,2);			//|   |Va3|   |   |   |Va2|   |   |   |Va1|   |   |   |Va0|   |   |
      xmm21 = _mm_slli_si128(xmm12,2);		//|   |Vb3|   |   |   |Vb2|   |   |   |Vb1|   |   |   |Vb0|   |   |
      xmm22 = _mm_slli_si128(xmm9,2);			//|   |Va7|   |   |   |Va6|   |   |   |Va5|   |   |   |Va4|   |   |
      xmm23 = _mm_slli_si128(xmm15,2);		//|   |Vb7|   |   |   |Vb6|   |   |   |Vb5|   |   |   |Vb4|   |   |
#endif
      //This is the spot for doing colorspace conversion

      //
      xmm24 = _mm_packus_epi16(xmm16, xmm18);	//|Ua7|   |Ua6|   |Ua5|   |Ua4|   |Ua3|   |Ua2|   |Ua1|   |Ua0|   |
      xmm25 = _mm_packus_epi16(xmm17, xmm19);	//|Ub7|   |Ub6|   |Ub5|   |Ub4|   |Ub3|   |Ub2|   |Ub1|   |Ub0|   |
      xmm26 = _mm_packus_epi16(xmm20, xmm22);	//|Va7|   |Va6|   |Va5|   |Va4|   |Va3|   |Va2|   |Va1|   |Va0|   |
      xmm27 = _mm_packus_epi16(xmm21, xmm23);	//|Vb7|   |Vb6|   |Vb5|   |Vb4|   |Vb3|   |Vb2|   |Vb1|   |Vb0|   |

      xmm28 = _mm_srli_si128(xmm24, 1);		//|   |Ua7|   |Ua6|   |Ua5|   |Ua4|   |Ua3|   |Ua2|   |Ua1|   |Ua0|
      xmm29 = _mm_srli_si128(xmm25, 1);		//|   |Ub7|   |Ub6|   |Ub5|   |Ub4|   |Ub3|   |Ub2|   |Ub1|   |Ub0|
      xmm30 = _mm_srli_si128(xmm26, 1);		//|   |Va7|   |Va6|   |Va5|   |Va4|   |Va3|   |Va2|   |Va1|   |Va0|
      xmm31 = _mm_srli_si128(xmm27, 1);		//|   |Vb7|   |Vb6|   |Vb5|   |Vb4|   |Vb3|   |Vb2|   |Vb1|   |Vb0|

      xmm32 = _mm_or_si128(xmm24, xmm28);		//|Ua7|Ua7|Ua6|Ua6|Ua5|Ua5|Ua4|Ua4|Ua3|Ua3|Ua2|Ua2|Ua1|Ua1|Ua0|Ua0|
      xmm33 = _mm_or_si128(xmm25, xmm29);		//|Ub7|Ub7|Ub6|Ub6|Ub5|Ub5|Ub4|Ub4|Ub3|Ub3|Ub2|Ub2|Ub1|Ub1|Ub0|Ub0|
      xmm34 = _mm_or_si128(xmm26, xmm30);		//|Va7|Va7|Va6|Va6|Va5|Va5|Va4|Va4|Va3|Va3|Va2|Va2|Va1|Va1|Va0|Va0|
      xmm35 = _mm_or_si128(xmm27, xmm31);		//|Vb7|Vb7|Vb6|Vb6|Vb5|Vb5|Vb4|Vb4|Vb3|Vb3|Vb2|Vb2|Vb1|Vb1|Vb0|Vb0|

      /* 4. Chroma decimation */
      xmm36 = _mm_avg_epu8(xmm32, xmm33);		//|U7_avg|U7_avg |U6_avg |U6_avg |U5_avg |U5_avg |U4_avg |U4_avg |U3_avg |U3_avg |U2_avg |U2_avg |U1_avg |U1_avg |U0_avg |U0_avg |
      xmm37 = _mm_srli_si128(xmm36, 1);		//|      |U7_avg |U7_avg |U6_avg |U6_avg |U5_avg |U5_avg |U4_avg |U4_avg |U3_avg |U3_avg |U2_avg |U2_avg |U1_avg |U1_avg |U0_avg |
      xmm38 = _mm_avg_epu8(xmm36, xmm37);		//|xxxxxx|U7_avg |U67_avg|U6_avg |U56_avg|U5_avg |U45_avg|U4_avg |U34_avg|U3_avg |U23_avg|U2_avg |U12_avg|U1_avg |U01_avg|U0_avg |
      xmm39 = _mm_and_si128(xmm38,_0101mask);	//|      |U7_avg |       |U6_avg |       |U5_avg |       |U4_avg |       |U3_avg |       |U2_avg |       |U1_avg |       |U0_avg |
      xmm40 = _mm_packus_epi16(xmm39, _zero);	//|   |   |   |   |   |   |   |   |U7_avg|U6_avg|U5_avg|U4_avg|U3_avg|U2_avg|U1_avg|U0_avg|

      xmm41 = _mm_avg_epu8(xmm34, xmm35);		//|V7_avg|V7_avg |V6_avg |V6_avg |V5_avg |V5_avg |V4_avg |V4_avg |V3_avg |V3_avg |V2_avg |V2_avg |V1_avg |V1_avg |V0_avg |V0_avg|
      xmm42 = _mm_srli_si128(xmm41, 1);		//|      |V7_avg |V7_avg |V6_avg |V6_avg |V5_avg |V5_avg |V4_avg |V4_avg |V3_avg |V3_avg |V2_avg |V2_avg |V1_avg |V1_avg |V0_avg|
      xmm43 = _mm_avg_epu8(xmm41, xmm42);		//|xxxxxx|V7_avg |V67_avg|V6_avg |V56_avg|V5_avg |V45_avg|V4_avg |V34_avg|V3_avg |V23_avg|V2_avg |V12_avg|V1_avg |V01_avg|V0_avg|
      xmm44 = _mm_and_si128(xmm43,_0101mask);	//|      |V7_avg |       |V6_avg |       |V5_avg |       |V4_avg |       |V3_avg |       |V2_avg |       |V1_avg |       |V0_avg|
      xmm45 = _mm_packus_epi16(xmm44, _zero);	//|   |   |   |   |   |   |   |   |V7_avg|V6_avg |V5_avg|V4_avg |V3_avg|V2_avg |V1_avg|V0_avg |

      xmm46	= _mm_packus_epi16(xmm4, xmm7);		//|YaF|YaE|YaD|YaC|YaB|YaA|Ya9|Ya8|Ya7|Ya6|Ya5|Ya4|Ya3|Ya2|Ya1|Ya0|
      xmm47	= _mm_packus_epi16(xmm10, xmm13);	//|YbF|YbE|YbD|YbC|YbB|YbA|Yb9|Yb8|Yb7|Yb6|Yb5|Yb4|Yb3|Yb2|Yb1|Yb0|

      /* 6. store as planar data */
      _mm_stream_si128((__m128i *)&out_ch0_0[i*16], xmm46);//lets not pollute the cache
      _mm_stream_si128((__m128i *)&out_ch0_1[i*16], xmm47);
      _mm_storel_epi64((__m128i *)(&out_ch1[i*8]), xmm40);
      _mm_storel_epi64((__m128i *)(&out_ch2[i*8]), xmm45);
    }
    inp0		+= 2*stride_in;//moving two lines at a time...
    inp1		+= 2*stride_in;
    out_ch0_0	+= 2*stride_out_ch0;//moving two lines at a time...
    out_ch0_1	+= 2*stride_out_ch0;
    out_ch1		+= stride_out_ch1;
    out_ch2		+= stride_out_ch2;
  }
  _mm_sfence();
#else
//  const unsigned char *yp;
  const unsigned char *up, *vp;
  unsigned char *rgbp;
  int height, width;

  const int stride_y = 2 * colorconverter->width;
  const int stride_uv = ((colorconverter->width + 1) >> 1);
  const int stride_rgb = 2 * 4 * colorconverter->width;
  unsigned char *rgbp0 = out_data;
  unsigned char *rgbp1 = out_data + 4 * colorconverter->width;
  //#if (defined(RGB24)||defined(BGR24))
  /*#if (defined DST_3CHANNELS)//DST_24BPP??
  const int stride_rgb = 2 * 3 * width;
  unsigned char *rgbp0 = rgbp;
  unsigned char *rgbp1 = rgbp + 3 * width;
  #else
  const int stride_rgb = 2 * 4 * width;
  unsigned char *rgbp0 = rgbp;
  unsigned char *rgbp1 = rgbp + 4 * width;
  #endif*/
  const unsigned char *yp0 = in_data + colorconverter->src_format.ch0.offset; 
  const unsigned char *yp1 = in_data + colorconverter->src_format.ch0.offset + colorconverter->width;
  const int count = (colorconverter->width >> 4);

  height		=	colorconverter->height;
  //width		=	colorconverter->width;
//  yp			=	in_data + colorconverter->src_format.ch0.offset;
  up			=	in_data + colorconverter->src_format.ch1.offset;
  vp			=	in_data + colorconverter->src_format.ch2.offset;
  //rgbp		=	out_data;

  {
    __m128i _zero     = _mm_setzero_si128();
    __m128i _minus128 = _mm_set_epi16(0xff80, 0xff80, 0xff80, 0xff80, 0xff80, 0xff80, 0xff80, 0xff80);
    __m128i _gvu      = _mm_set_epi16(0xe5e2, 0xf36e, 0xe5e2, 0xf36e, 0xe5e2, 0xf36e, 0xe5e2, 0xf36e);
    __m128i _one      = _mm_set_epi16(0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001);
    __m128i _rb       = _mm_set_epi16(0x3343, 0x40cf, 0x3343, 0x40cf, 0x3343, 0x40cf, 0x3343, 0x40cf);
    __m128i _yscale   = _mm_set_epi16(0x2568, 0x2568, 0x2568, 0x2568, 0x2568, 0x2568, 0x2568, 0x2568); 
    __m128i _M1       = _mm_set_epi16(0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00);
    __m128i _M2       = _mm_set_epi16(0x0000, 0x00ff, 0x0000, 0x00ff, 0x0000, 0x00ff, 0x0000, 0x00ff);
    __m128i _M3       = _mm_set_epi16(0x00ff, 0x0000, 0x00ff, 0x0000, 0x00ff, 0x0000, 0x00ff, 0x0000);
    __m128i _T1       = _mm_set_epi16(0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x00ff, 0xffff);
    __m128i _T2       = _mm_set_epi16(0x0000, 0x0000, 0x0000, 0x0000, 0x00ff, 0xffff, 0x0000, 0x0000);
    __m128i _T3       = _mm_set_epi16(0x0000, 0x0000, 0x00ff, 0xffff, 0x0000, 0x0000, 0x0000, 0x0000);
    __m128i _T4       = _mm_set_epi16(0x00ff, 0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000);
    __m128i _a        = _mm_set_epi16(0xff00, 0x0000, 0xff00, 0x0000, 0xff00, 0x0000, 0xff00, 0x0000);


    int j;

    height = ((height + 1) >> 1);
    for(j = 0; j < height; j ++) {    
      int i;
      for (i = 0; i < count; i++)
      {
        __m128i xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7, xmm8, xmm9, xmm10, xmm11, xmm12, xmm13, xmm14, xmm15;
        xmm0  = _mm_unpacklo_epi8(_mm_unpacklo_epi8(_mm_cvtsi32_si128(*(int*)&up[i*8+0]), _mm_cvtsi32_si128(*(int*)&vp[i*8+0])), _zero);                  
        xmm8  = _mm_unpacklo_epi8(_mm_unpacklo_epi8(_mm_cvtsi32_si128(*(int*)&up[i*8+4]), _mm_cvtsi32_si128(*(int*)&vp[i*8+4])), _zero); 
        xmm6  = _mm_unpacklo_epi8(_mm_loadl_epi64((__m128i *)(&yp0[i*16+0])), _zero);                  
        xmm7  = _mm_unpacklo_epi8(_mm_loadl_epi64((__m128i *)(&yp1[i*16+0])), _zero);                                    
        xmm14 = _mm_unpacklo_epi8(_mm_loadl_epi64((__m128i *)(&yp0[i*16+8])), _zero);               
        xmm15 = _mm_unpacklo_epi8(_mm_loadl_epi64((__m128i *)(&yp1[i*16+8])), _zero);               
        xmm0 = _mm_slli_epi16(_mm_add_epi16(xmm0, _minus128), 3); 
        xmm8 = _mm_slli_epi16(_mm_add_epi16(xmm8, _minus128), 3); 
        xmm6 = _mm_add_epi16(_mm_slli_epi16(xmm6, 3), _minus128);                  
        xmm7 = _mm_add_epi16(_mm_slli_epi16(xmm7, 3), _minus128);                                              
        xmm14 = _mm_add_epi16(_mm_slli_epi16(xmm14, 3), _minus128);               
        xmm15 = _mm_add_epi16(_mm_slli_epi16(xmm15, 3), _minus128);                                        
        xmm13 = xmm8;                                         
        xmm5 = xmm0;                                         
        xmm0 = _mm_mulhi_epi16(xmm0, _gvu);                  
        xmm8 = _mm_mulhi_epi16(xmm8, _gvu);                      
        xmm0 = _mm_madd_epi16(xmm0, _one);                      
        xmm8 = _mm_madd_epi16(xmm8, _one);                   
        xmm5 = _mm_mulhi_epi16(xmm5, _rb);                   
        xmm13 = _mm_mulhi_epi16(xmm13, _rb);                   
        xmm12 = xmm13;                                         
        xmm4 = xmm5;                                            
        xmm5 = _mm_unpackhi_epi16(xmm5,xmm0);                   
        xmm4 = _mm_unpacklo_epi16(xmm4,xmm0);                   
        xmm6 = _mm_mulhi_epi16(xmm6,_yscale);                       
        xmm3 = _mm_shuffle_epi32(xmm4,238);    	                   
        xmm4 = _mm_shuffle_epi32(xmm4,68);	                       
        xmm0 = _mm_adds_epi16(_mm_shuffle_epi32(_mm_shufflelo_epi16(xmm6,80) ,80), xmm4);                         
        xmm1 = _mm_adds_epi16(_mm_shuffle_epi32(_mm_shufflelo_epi16(xmm6,250),80), xmm3);	                       
        xmm0 = _mm_packus_epi16(xmm0, xmm1);	
        xmm0 = _mm_or_si128(xmm0, _a);
#if (((DST_CH0_BYTEPOS_0 == 0) && (DST_CH1_BYTEPOS_0 == 1) && (DST_CH2_BYTEPOS_0 == 2)) || ((DST_CH0_BYTEPOS_0 == 1) && (DST_CH1_BYTEPOS_0 == 2) && (DST_CH2_BYTEPOS_0 == 3)))
        //#if (defined(RGBA32)||defined(ARGB32))
        xmm0 = _mm_or_si128(_mm_and_si128(xmm0,_M1),_mm_or_si128(_mm_slli_si128(_mm_and_si128(xmm0,_M2),2),_mm_srli_si128(_mm_and_si128(xmm0,_M3),2)));
#endif
        //#endif
#if (((DST_CH0_BYTEPOS_0 == 1) && (DST_CH1_BYTEPOS_0 == 2) && (DST_CH2_BYTEPOS_0 == 3)) || ((DST_CH0_BYTEPOS_0 == 3) && (DST_CH1_BYTEPOS_0 == 2) && (DST_CH2_BYTEPOS_0 == 1)))
        //#if (defined(ARGB32)||defined(ABGR32))
        xmm0 = _mm_or_si128(_mm_slli_si128(xmm0,1),_M2);
#endif
        //#endif
        _mm_store_si128((__m128i *)&rgbp0[i*64], xmm0);   
        xmm13 = _mm_unpackhi_epi16(xmm13,xmm8);                
        xmm12 = _mm_unpacklo_epi16(xmm12,xmm8);                
        xmm14 = _mm_mulhi_epi16(xmm14,_yscale);                                    
        xmm11 = _mm_shuffle_epi32(xmm12,238);    	              
        xmm12 = _mm_shuffle_epi32(xmm12,68);	                  
        xmm8 = _mm_adds_epi16(_mm_shuffle_epi32(_mm_shufflelo_epi16(xmm14,80) ,80), xmm12);                   
        xmm9 = _mm_adds_epi16(_mm_shuffle_epi32(_mm_shufflelo_epi16(xmm14,250),80), xmm11);	                 
        xmm8 = _mm_packus_epi16(xmm8, xmm9);	
        xmm8 = _mm_or_si128(xmm8, _a);
#if (((DST_CH0_BYTEPOS_0 == 0) && (DST_CH1_BYTEPOS_0 == 1) && (DST_CH2_BYTEPOS_0 == 2)) || ((DST_CH0_BYTEPOS_0 == 1) && (DST_CH1_BYTEPOS_0 == 2) && (DST_CH2_BYTEPOS_0 == 3)))
        //#if (defined(RGBA32)||defined(ARGB32))
        xmm8 = _mm_or_si128(_mm_and_si128(xmm8,_M1),_mm_or_si128(_mm_slli_si128(_mm_and_si128(xmm8,_M2),2),_mm_srli_si128(_mm_and_si128(xmm8,_M3),2)));
        //#endif
#endif
#if (((DST_CH0_BYTEPOS_0 == 1) && (DST_CH1_BYTEPOS_0 == 2) && (DST_CH2_BYTEPOS_0 == 3)) || ((DST_CH0_BYTEPOS_0 == 3) && (DST_CH1_BYTEPOS_0 == 2) && (DST_CH2_BYTEPOS_0 == 1)))
        //#if (defined(ARGB32)||defined(ABGR32))
        xmm8 = _mm_or_si128(_mm_slli_si128(xmm8,1),_M2);
#endif
        //#endif
        _mm_store_si128((__m128i *)&rgbp0[i*64+32], xmm8);   
        xmm7 = _mm_mulhi_epi16(xmm7,_yscale);                      
        xmm0 = _mm_adds_epi16(_mm_shuffle_epi32(_mm_shufflelo_epi16(xmm7,80),80), xmm4);                         
        xmm1 = _mm_adds_epi16(_mm_shuffle_epi32(_mm_shufflelo_epi16(xmm7,250),80), xmm3);	
        xmm15 = _mm_mulhi_epi16(xmm15,_yscale);
        xmm8 = _mm_adds_epi16(_mm_shuffle_epi32(_mm_shufflelo_epi16(xmm15,80),80), xmm12);                   
        xmm9 = _mm_adds_epi16(_mm_shuffle_epi32(_mm_shufflelo_epi16(xmm15,250),80), xmm11);	
        xmm0 = _mm_packus_epi16(xmm0, xmm1);
        xmm1 = _mm_packus_epi16(xmm8, xmm9);
        xmm0 = _mm_or_si128(xmm0, _a);
        xmm1 = _mm_or_si128(xmm1, _a);
#if (((DST_CH0_BYTEPOS_0 == 0) && (DST_CH1_BYTEPOS_0 == 1) && (DST_CH2_BYTEPOS_0 == 2)) || ((DST_CH0_BYTEPOS_0 == 1) && (DST_CH1_BYTEPOS_0 == 2) && (DST_CH2_BYTEPOS_0 == 3)))
        //#if (defined(RGBA32)||defined(ARGB32))
        xmm0 = _mm_or_si128(_mm_and_si128(xmm0,_M1),_mm_or_si128(_mm_slli_si128(_mm_and_si128(xmm0,_M2),2),_mm_srli_si128(_mm_and_si128(xmm0,_M3),2)));
        xmm1 = _mm_or_si128(_mm_and_si128(xmm1,_M1),_mm_or_si128(_mm_slli_si128(_mm_and_si128(xmm1,_M2),2),_mm_srli_si128(_mm_and_si128(xmm1,_M3),2)));
        //#endif
#endif
#if (((DST_CH0_BYTEPOS_0 == 1) && (DST_CH1_BYTEPOS_0 == 2) && (DST_CH2_BYTEPOS_0 == 3)) || ((DST_CH0_BYTEPOS_0 == 3) && (DST_CH1_BYTEPOS_0 == 2) && (DST_CH2_BYTEPOS_0 == 1)))
        //#if (defined(ARGB32)||defined(ABGR32))
        xmm0 = _mm_or_si128(_mm_slli_si128(xmm0,1),_M2);
        xmm1 = _mm_or_si128(_mm_slli_si128(xmm1,1),_M2);
        //#endif
#endif
        _mm_store_si128((__m128i *)&rgbp1[i*64],   xmm0);       
        _mm_store_si128((__m128i *)&rgbp1[i*64+32],xmm1); 
        xmm0 = _mm_shufflehi_epi16(xmm6,80);                       
        xmm1 = _mm_shufflehi_epi16(xmm6,250);	                     
        xmm2 = _mm_shufflehi_epi16(xmm7,80);	                     
        xmm3 = _mm_shufflehi_epi16(xmm7,250);                      
        xmm4 = _mm_shuffle_epi32(xmm5,238);	                       
        xmm5 = _mm_shuffle_epi32(xmm5,68);	                       
        xmm0 = _mm_adds_epi16(_mm_shuffle_epi32(xmm0,250), xmm5);	                       
        xmm1 = _mm_adds_epi16(_mm_shuffle_epi32(xmm1,250), xmm4);	                       
        xmm2 = _mm_adds_epi16(_mm_shuffle_epi32(xmm2,250), xmm5);                         
        xmm3 = _mm_adds_epi16(_mm_shuffle_epi32(xmm3,250), xmm4);	  
        xmm0 = _mm_packus_epi16(xmm0, xmm1);
        xmm1 = _mm_packus_epi16(xmm2, xmm3);
        xmm0 = _mm_or_si128(xmm0, _a);
        xmm1 = _mm_or_si128(xmm1, _a);
#if (((DST_CH0_BYTEPOS_0 == 0) && (DST_CH1_BYTEPOS_0 == 1) && (DST_CH2_BYTEPOS_0 == 2)) || ((DST_CH0_BYTEPOS_0 == 1) && (DST_CH1_BYTEPOS_0 == 2) && (DST_CH2_BYTEPOS_0 == 3)))
        //#if (defined(RGBA32)||defined(ARGB32))
        xmm0 = _mm_or_si128(_mm_and_si128(xmm0,_M1),_mm_or_si128(_mm_slli_si128(_mm_and_si128(xmm0,_M2),2),_mm_srli_si128(_mm_and_si128(xmm0,_M3),2)));
        xmm1 = _mm_or_si128(_mm_and_si128(xmm1,_M1),_mm_or_si128(_mm_slli_si128(_mm_and_si128(xmm1,_M2),2),_mm_srli_si128(_mm_and_si128(xmm1,_M3),2)));
        //#endif
#endif
#if (((DST_CH0_BYTEPOS_0 == 1) && (DST_CH1_BYTEPOS_0 == 2) && (DST_CH2_BYTEPOS_0 == 3)) || ((DST_CH0_BYTEPOS_0 == 3) && (DST_CH1_BYTEPOS_0 == 2) && (DST_CH2_BYTEPOS_0 == 1)))
        //#if (defined(ARGB32)||defined(ABGR32))
        xmm0 = _mm_or_si128(_mm_slli_si128(xmm0,1),_M2);
        xmm1 = _mm_or_si128(_mm_slli_si128(xmm1,1),_M2);
        //#endif
#endif
        _mm_store_si128((__m128i *)&rgbp0[i*64+16], xmm0);         
        _mm_store_si128((__m128i *)&rgbp1[i*64+16], xmm1);    
        xmm8  = _mm_shufflehi_epi16(xmm14,80);                 
        xmm9  = _mm_shufflehi_epi16(xmm14,250);	               
        xmm10 = _mm_shufflehi_epi16(xmm15,80);	                
        xmm11 = _mm_shufflehi_epi16(xmm15,250);                 
        xmm12 = _mm_shuffle_epi32(xmm13,238);	                  
        xmm13 = _mm_shuffle_epi32(xmm13,68);	                  
        xmm8  = _mm_adds_epi16(_mm_shuffle_epi32(xmm8,250), xmm13);	                 
        xmm9  = _mm_adds_epi16(_mm_shuffle_epi32(xmm9,250), xmm12);	                 
        xmm10 = _mm_adds_epi16(_mm_shuffle_epi32(xmm10,250), xmm13);                    
        xmm11 = _mm_adds_epi16(_mm_shuffle_epi32(xmm11,250), xmm12);	  
        xmm0 = _mm_packus_epi16(xmm8, xmm9);
        xmm1 = _mm_packus_epi16(xmm10, xmm11);
        xmm0 = _mm_or_si128(xmm0, _a);
        xmm1 = _mm_or_si128(xmm1, _a);
#if (((DST_CH0_BYTEPOS_0 == 0) && (DST_CH1_BYTEPOS_0 == 1) && (DST_CH2_BYTEPOS_0 == 2)) || ((DST_CH0_BYTEPOS_0 == 1) && (DST_CH1_BYTEPOS_0 == 2) && (DST_CH2_BYTEPOS_0 == 3)))
        xmm0 = _mm_or_si128(_mm_and_si128(xmm0,_M1),_mm_or_si128(_mm_slli_si128(_mm_and_si128(xmm0,_M2),2),_mm_srli_si128(_mm_and_si128(xmm0,_M3),2)));
        xmm1 = _mm_or_si128(_mm_and_si128(xmm1,_M1),_mm_or_si128(_mm_slli_si128(_mm_and_si128(xmm1,_M2),2),_mm_srli_si128(_mm_and_si128(xmm1,_M3),2)));
        //#endif
#endif
#if (((DST_CH0_BYTEPOS_0 == 1) && (DST_CH1_BYTEPOS_0 == 2) && (DST_CH2_BYTEPOS_0 == 3)) || ((DST_CH0_BYTEPOS_0 == 3) && (DST_CH1_BYTEPOS_0 == 2) && (DST_CH2_BYTEPOS_0 == 1)))
        //#if (defined(ARGB32)||defined(ABGR32))
        xmm0 = _mm_or_si128(_mm_slli_si128(xmm0,1),_M2);
        xmm1 = _mm_or_si128(_mm_slli_si128(xmm1,1),_M2);
        //#endif
#endif
        _mm_store_si128((__m128i *)&rgbp0[i*64+48], xmm0);   
        _mm_store_si128((__m128i *)&rgbp1[i*64+48], xmm1);   
      }
      yp0+=stride_y;
      yp1+=stride_y;
      up+=stride_uv;
      vp+=stride_uv;
      rgbp0+=stride_rgb;
      rgbp1+=stride_rgb;
    }
  }
#endif
}
