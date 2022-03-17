#include <emmintrin.h>
#pragma warning (disable:177)
#if defined(RGBA32)
void  yuv420_to_rgba32
#elif defined(BGRA32)
void  yuv420_to_bgra32
#elif defined(ARGB32)
void  yuv420_to_argb32
#elif defined(ABGR32)
void  yuv420_to_abgr32
#endif
(const unsigned char *yp, 
 const unsigned char *up, 
 const unsigned char *vp, 
 unsigned char *rgbp,
 int height,
 const int width) 
{
  const int count = (width >> 4);
  __m128i _zero     = _mm_setzero_si128();
  __m128i _minus128 = _mm_set_epi16(0xff80, 0xff80, 0xff80, 0xff80, 0xff80, 0xff80, 0xff80, 0xff80);
  __m128i _gvu      = _mm_set_epi16(0xe5e2, 0xf36e, 0xe5e2, 0xf36e, 0xe5e2, 0xf36e, 0xe5e2, 0xf36e);
  __m128i _one      = _mm_set_epi16(0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001);
  __m128i _rb       = _mm_set_epi16(0x3343, 0x40cf, 0x3343, 0x40cf, 0x3343, 0x40cf, 0x3343, 0x40cf);
  __m128i _yscale   = _mm_set_epi16(0x2568, 0x2568, 0x2568, 0x2568, 0x2568, 0x2568, 0x2568, 0x2568); 
  __m128i _M1       = _mm_set_epi16(0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00);
  __m128i _M2       = _mm_set_epi16(0x0000, 0x00ff, 0x0000, 0x00ff, 0x0000, 0x00ff, 0x0000, 0x00ff);
  __m128i _M3       = _mm_set_epi16(0x00ff, 0x0000, 0x00ff, 0x0000, 0x00ff, 0x0000, 0x00ff, 0x0000);

  const int stride_y = 2 * width;
  const int stride_uv =  ((width + 1) >> 1);
  const int stride_rgb = 2 * 4 * width;
  unsigned char *rgbp0 = rgbp;
  unsigned char *rgbp1 = rgbp + 4 * width;
  const unsigned char *yp0 = yp; 
  const unsigned char *yp1 = yp + width;

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
#if (defined(RGBA32)||defined(ARGB32))
      xmm0 = _mm_or_si128(_mm_and_si128(xmm0,_M1),_mm_or_si128(_mm_slli_si128(_mm_and_si128(xmm0,_M2),2),_mm_srli_si128(_mm_and_si128(xmm0,_M3),2)));
#endif
#if (defined(ARGB32)||defined(ABGR32))
      xmm0 = _mm_or_si128(_mm_slli_si128(xmm0,1),_M2);
#endif
      _mm_store_si128((__m128i *)&rgbp0[i*64], xmm0);   
      xmm13 = _mm_unpackhi_epi16(xmm13,xmm8);                
      xmm12 = _mm_unpacklo_epi16(xmm12,xmm8);                
      xmm14 = _mm_mulhi_epi16(xmm14,_yscale);                                    
      xmm11 = _mm_shuffle_epi32(xmm12,238);    	              
      xmm12 = _mm_shuffle_epi32(xmm12,68);	                  
      xmm8 = _mm_adds_epi16(_mm_shuffle_epi32(_mm_shufflelo_epi16(xmm14,80) ,80), xmm12);                   
      xmm9 = _mm_adds_epi16(_mm_shuffle_epi32(_mm_shufflelo_epi16(xmm14,250),80), xmm11);	                 
      xmm8 = _mm_packus_epi16(xmm8, xmm9);	   
#if (defined(RGBA32)||defined(ARGB32))
      xmm8 = _mm_or_si128(_mm_and_si128(xmm8,_M1),_mm_or_si128(_mm_slli_si128(_mm_and_si128(xmm8,_M2),2),_mm_srli_si128(_mm_and_si128(xmm8,_M3),2)));
#endif
#if (defined(ARGB32)||defined(ABGR32))
      xmm8 = _mm_or_si128(_mm_slli_si128(xmm8,1),_M2);
#endif
      _mm_store_si128((__m128i *)&rgbp0[i*64+32], xmm8);   
      xmm7 = _mm_mulhi_epi16(xmm7,_yscale);                      
      xmm0 = _mm_adds_epi16(_mm_shuffle_epi32(_mm_shufflelo_epi16(xmm7,80),80), xmm4);                         
      xmm1 = _mm_adds_epi16(_mm_shuffle_epi32(_mm_shufflelo_epi16(xmm7,250),80), xmm3);	
      xmm15 = _mm_mulhi_epi16(xmm15,_yscale);
      xmm8 = _mm_adds_epi16(_mm_shuffle_epi32(_mm_shufflelo_epi16(xmm15,80),80), xmm12);                   
      xmm9 = _mm_adds_epi16(_mm_shuffle_epi32(_mm_shufflelo_epi16(xmm15,250),80), xmm11);	
      xmm0 = _mm_packus_epi16(xmm0, xmm1);
      xmm1 = _mm_packus_epi16(xmm8, xmm9);
#if (defined(RGBA32)||defined(ARGB32))
      xmm0 = _mm_or_si128(_mm_and_si128(xmm0,_M1),_mm_or_si128(_mm_slli_si128(_mm_and_si128(xmm0,_M2),2),_mm_srli_si128(_mm_and_si128(xmm0,_M3),2)));
      xmm1 = _mm_or_si128(_mm_and_si128(xmm1,_M1),_mm_or_si128(_mm_slli_si128(_mm_and_si128(xmm1,_M2),2),_mm_srli_si128(_mm_and_si128(xmm1,_M3),2)));
#endif
#if (defined(ARGB32)||defined(ABGR32))
      xmm0 = _mm_or_si128(_mm_slli_si128(xmm0,1),_M2);
      xmm1 = _mm_or_si128(_mm_slli_si128(xmm1,1),_M2);
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
#if (defined(RGBA32)||defined(ARGB32))
      xmm0 = _mm_or_si128(_mm_and_si128(xmm0,_M1),_mm_or_si128(_mm_slli_si128(_mm_and_si128(xmm0,_M2),2),_mm_srli_si128(_mm_and_si128(xmm0,_M3),2)));
      xmm1 = _mm_or_si128(_mm_and_si128(xmm1,_M1),_mm_or_si128(_mm_slli_si128(_mm_and_si128(xmm1,_M2),2),_mm_srli_si128(_mm_and_si128(xmm1,_M3),2)));
#endif
#if (defined(ARGB32)||defined(ABGR32))
      xmm0 = _mm_or_si128(_mm_slli_si128(xmm0,1),_M2);
      xmm1 = _mm_or_si128(_mm_slli_si128(xmm1,1),_M2);
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
#if (defined(RGBA32)||defined(ARGB32))
      xmm0 = _mm_or_si128(_mm_and_si128(xmm0,_M1),_mm_or_si128(_mm_slli_si128(_mm_and_si128(xmm0,_M2),2),_mm_srli_si128(_mm_and_si128(xmm0,_M3),2)));
      xmm1 = _mm_or_si128(_mm_and_si128(xmm1,_M1),_mm_or_si128(_mm_slli_si128(_mm_and_si128(xmm1,_M2),2),_mm_srli_si128(_mm_and_si128(xmm1,_M3),2)));
#endif
#if (defined(ARGB32)||defined(ABGR32))
      xmm0 = _mm_or_si128(_mm_slli_si128(xmm0,1),_M2);
      xmm1 = _mm_or_si128(_mm_slli_si128(xmm1,1),_M2);
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
