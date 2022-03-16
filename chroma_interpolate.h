#ifndef __CHROMA_INTERPOLATE_H__
#define __CHROMA_INTERPOLATE_H__

#ifdef __cplusplus
extern "C" {
#endif
    typedef struct _Channel					Channel;
    typedef struct _ChromaLayout			ChromaLayout;
    typedef struct _FormatDescriptor		FormatDescriptor;
    typedef struct _ColorSpaceConverter		ColorSpaceConverter;


    struct _Channel
    {
        int mask1;
        int mask2;
        int byte_offset1;
        int byte_offset2;
        int offset;//channel first pixel offset from frame pointer
        int height;
        int width;
        int stride;
    };

    struct _ChromaLayout
    {
        //the pattern is assumed to repeat throughout the frame

        //For instance I420:
        //[horz_support_start, horz_support_end] = [0, 4]
        //[vert_support_start, vert_support_end] = [0, 4]
        //vert_position = 2
        //horz_position = 1
        //vert_subs_factor = 2
        //horz_subs_factor = 2
        // 0 1 2 3 4 5 6 7 8
        //0┌---┬---┬---┬---┬
        //1| # | # |   |   |...
        //2├-X-┼---┼---┼---┼
        //3| # | # |   |   |...
        //4├---┼---┼---┼---┼
        //...

        int vert_position;
        int horz_position;
        int vert_subs_factor;
        int horz_subs_factor;
        int horz_support_start;
        int horz_support_end;
        int vert_support_start;
        int vert_support_end;
    };

    struct _FormatDescriptor
    {
        //general stuff
        int colorspace;	//YUV or RGB
        int size;		//total framesize (bytes)
        int width;
        int height;
        int stride;
        int organisation; //PLANAR or PACKED
        int active_channels; //0b1110 (RGB/YUV) or 0b1111 (added alpha)
        int pixel_repeat_period; //1 or 2. If 2, "mask2" is used, and the pattern used in pixel#0,2,4... can differ from pixel#1,3,5... of each line
        int active_bpp; //24 or 32 bits per pixel
        int total_bpp; //24 or 32 "pixelstride" (bits per pixel including "dead space")
        int endianness;
        Channel ch0;//Red or Y    : use 0 to signify
        Channel ch1;//Green or U  : use 1 to signify
        Channel ch2;//Blue or V   : use 2 to signify
        Channel ch3;//Alpha (if applicable) : use 3 to signify
        ChromaLayout chromalayout;//info about any chroma subsampling (if YUV)
    };

    struct _ColorSpaceConverter
    {
        int isInit;
        FormatDescriptor dst_format;
        FormatDescriptor src_format;
        int width;
        int height;
        int bDoAdaptiveInterpolation;
        int bAdaptiveIntDemomode;
        int srcIdx;
        int dstIdx;
        int parIdx;
    };

    //enum
    //{
    //  RGB,
    //  YUV601,
    //  YUV709,
    //};
    enum
    {
        sRGB_PC,
        BT601,
        BT709
    };

    enum
    {
        PACKED,
        PLANAR
    };

    //initialize converter
    int init_colorspaceconverter(ColorSpaceConverter* colorconverter, FormatDescriptor src_format, FormatDescriptor dst_format, int height, int width, int bDoAdaptiveInterpolation, int bAdaptiveIntDemomode);
    //reinit colorspaceconverter
    int reinit_colorspaceconverter(ColorSpaceConverter* colorconverter, int bDoAdaptiveInterpolation, int bAdaptiveIntDemomode);
    //do one frame of colorspace conversion
    int colorspaceconvert(ColorSpaceConverter* coreconverter, const unsigned char* src_ptr, unsigned char* dst_ptr, const int in_size, const int out_size);
#if 0
    void luma_adaptive_interp(unsigned char* y_full_ptr, //full-res Y
        unsigned char* u_dec_ptr, //decimated U
        unsigned char* v_dec_ptr, //decimated V
        unsigned char* y_dec_ptr, //decimated Y
        unsigned char* u_full_ptr, //interpolated U to be overwritten
        unsigned char* v_full_ptr, //interpolated V to be overwritten
        unsigned int full_height, //geometry of a full-size frame
        unsigned int full_width, //geometry of a full-size frame
        unsigned int full_stride, //geometry of a full-size frame
        unsigned int demomode //process half frame only?
    );
#endif

    //void select_converter(ColorSpaceConverter *colorconverter, int * srcIdx, int * dstIdx, int * parIdx);
    void select_converter(ColorSpaceConverter* colorconverter, int* srcIdx, int* dstIdx);
    int decode_parameter(ColorSpaceConverter* colorconverter);
    int decode_format(FormatDescriptor format);

    void luma_adaptive_interp_block(int line,//current line in full-resolution array
        int pix,//current pixel in full-resolution array
        const unsigned char* y_ptr, //full-res Y
        int y_stride, //full-res Y
        const unsigned char* u_ptr, //decimated U
        int u_stride, //decimated U
        const unsigned char* v_ptr, //decimated V
        int v_stride, //decimated V
        unsigned char* u_upper0_full_ptr, //interpolated U
        unsigned char* u_upper1_full_ptr, //interpolated U
        unsigned char* u_lower0_full_ptr, //interpolated U
        unsigned char* u_lower1_full_ptr, //interpolated U
        unsigned char* v_upper0_full_ptr, //interpolated V
        unsigned char* v_upper1_full_ptr, //interpolated V
        unsigned char* v_lower0_full_ptr, //interpolated V
        unsigned char* v_lower1_full_ptr, //interpolated V
        unsigned int demomode //process half frame only?
    );

    /*void pixel_BT601_to_BT709(	unsigned char* out_ch_0, unsigned char* out_ch_1, unsigned char* out_ch_2, const unsigned char *in_ch_0, const unsigned char *in_ch_1,const unsigned char *in_ch_2);
    void pixel_BT601_to_sRGB_PC(unsigned char* out_ch_0, unsigned char* out_ch_1, unsigned char* out_ch_2, const unsigned char *in_ch_0, const unsigned char *in_ch_1,const unsigned char *in_ch_2);
    void pixel_BT709_to_BT601(	unsigned char* out_ch_0, unsigned char* out_ch_1, unsigned char* out_ch_2, const unsigned char *in_ch_0, const unsigned char *in_ch_1,const unsigned char *in_ch_2);
    void pixel_BT709_to_sRGB_PC(unsigned char* out_ch_0, unsigned char* out_ch_1, unsigned char* out_ch_2, const unsigned char *in_ch_0, const unsigned char *in_ch_1,const unsigned char *in_ch_2);
    void pixel_sRGB_PC_to_BT709(unsigned char* out_ch_0, unsigned char* out_ch_1, unsigned char* out_ch_2, const unsigned char *in_ch_0, const unsigned char *in_ch_1,const unsigned char *in_ch_2);
    void pixel_sRGB_PC_to_BT601(unsigned char* out_ch_0, unsigned char* out_ch_1, unsigned char* out_ch_2, const unsigned char *in_ch_0, const unsigned char *in_ch_1,const unsigned char *in_ch_2);*/

    void pixel_colspace_to_colspace(unsigned char* out_ch_0, unsigned char* out_ch_1, unsigned char* out_ch_2, const unsigned char* in_ch_0, const unsigned char* in_ch_1, const unsigned char* in_ch_2, signed short* mat, signed short* in_offset, signed short* out_offset, int* exponent, unsigned char* clip);

#ifdef __cplusplus
}
#endif

#endif /* __CHROMA_INTERPOLATE_H__ */
