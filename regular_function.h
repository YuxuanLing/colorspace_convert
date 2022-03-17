void FUNCTION_NAME
(const ColorSpaceConverter* colorconverter, const unsigned char* in_data, unsigned char* out_data, const int in_size, const int out_size)
{
	int ret;
	unsigned char ch0_0[4], ch1_0[4], ch2_0[4], ch3_0[4];
	unsigned char ch0_1[4], ch1_1[4], ch2_1[4], ch3_1[4];
	int line, pix;
	int localpix, out_channel, in_channel;
	signed short calc, exponent;
	unsigned char clip_lo[3], clip_hi[3];
	signed short in_offset[3], out_offset[3];
	signed short conv_matrix[3][3];
	unsigned char* out_channels[3];

	const unsigned char alpha_dummy = 0xff;
	const int dst_ch0_byteoffset1 = colorconverter->dst_format.ch0.byte_offset1;
	const int dst_ch1_byteoffset1 = colorconverter->dst_format.ch1.byte_offset1;
	const int dst_ch2_byteoffset1 = colorconverter->dst_format.ch2.byte_offset1;
	const int dst_ch3_byteoffset1 = colorconverter->dst_format.ch3.byte_offset1;
	const int dst_ch0_byteoffset2 = colorconverter->dst_format.ch0.byte_offset2;
	const int dst_ch1_byteoffset2 = colorconverter->dst_format.ch1.byte_offset2;
	const int dst_ch2_byteoffset2 = colorconverter->dst_format.ch2.byte_offset2;
	const int dst_ch3_byteoffset2 = colorconverter->dst_format.ch3.byte_offset2;
	const int dst_ch0_offset = colorconverter->dst_format.ch0.offset;
	const int dst_ch1_offset = colorconverter->dst_format.ch1.offset;
	const int dst_ch2_offset = colorconverter->dst_format.ch2.offset;
	const int dst_ch0_stride = colorconverter->dst_format.ch0.stride;
	const int dst_ch1_stride = colorconverter->dst_format.ch1.stride;
	//const int dst_ch2_stride		=	colorconverter->dst_format.ch2.stride;
	const int dst_stride = colorconverter->dst_format.stride;

	const int src_ch0_byteoffset1 = colorconverter->src_format.ch0.byte_offset1;
	const int src_ch1_byteoffset1 = colorconverter->src_format.ch1.byte_offset1;
	const int src_ch2_byteoffset1 = colorconverter->src_format.ch2.byte_offset1;
	const int src_ch3_byteoffset1 = colorconverter->src_format.ch3.byte_offset1;
	const int src_ch0_byteoffset2 = colorconverter->src_format.ch0.byte_offset2;
	const int src_ch1_byteoffset2 = colorconverter->src_format.ch1.byte_offset2;
	const int src_ch2_byteoffset2 = colorconverter->src_format.ch2.byte_offset2;
	const int src_ch3_byteoffset2 = colorconverter->src_format.ch3.byte_offset2;
	const int src_ch0_offset = colorconverter->src_format.ch0.offset;
	const int src_ch1_offset = colorconverter->src_format.ch1.offset;
	const int src_ch2_offset = colorconverter->src_format.ch2.offset;
	const int src_ch0_stride = colorconverter->src_format.ch0.stride;
	const int src_ch1_stride = colorconverter->src_format.ch1.stride;
	//const int src_ch2_stride		=	colorconverter->src_format.ch2.stride;
	const int src_stride = colorconverter->src_format.stride;

	const int src_total_byte_pr_pixel = colorconverter->src_format.total_bpp / 8;
	const int dst_total_byte_pr_pixel = colorconverter->dst_format.total_bpp / 8;
	const int height = colorconverter->height;
	const int width = colorconverter->width;

	out_channels[0] = &ch0_1[0];
	out_channels[1] = &ch1_1[0];
	out_channels[2] = &ch2_1[0];

	assert(colorconverter->isInit);
	ret = 0;

	exponent = int16_exponent[colorconverter->src_format.colorspace][colorconverter->dst_format.colorspace];
	for (in_channel = 0; in_channel < 3; in_channel++)
	{
		in_offset[in_channel] = int16_in_offset[in_channel][colorconverter->src_format.colorspace][colorconverter->dst_format.colorspace];
	}
	for (out_channel = 0; out_channel < 3; out_channel++)
	{
		out_offset[out_channel] = int16_out_offset[out_channel][colorconverter->src_format.colorspace][colorconverter->dst_format.colorspace];
		for (in_channel = 0; in_channel < 3; in_channel++)
		{
			conv_matrix[out_channel][in_channel] = int16_conv_matrix[out_channel][in_channel][colorconverter->src_format.colorspace][colorconverter->dst_format.colorspace];
		}
		if (colorconverter->dst_format.colorspace == sRGB_PC) {
			clip_lo[out_channel] = sRGB_PC_lo[out_channel];
			clip_hi[out_channel] = sRGB_PC_hi[out_channel];
		}
		else if (colorconverter->dst_format.colorspace == BT601) {
			clip_lo[out_channel] = BT601_lo[out_channel];
			clip_hi[out_channel] = BT601_hi[out_channel];
		}
		else if (colorconverter->dst_format.colorspace == BT709) {
			clip_lo[out_channel] = BT709_lo[out_channel];
			clip_hi[out_channel] = BT709_hi[out_channel];
		}
	}
	{
#ifdef __INTEL_COMPILER
		__assume_aligned(in_data, 8);
		__assume_aligned(out_data, 64);
#pragma ivdep;
#pragma vector nontemporal
#endif
		for (line = 0; line < height; line += 2)
		{
#pragma ivdep
			for (pix = 0; pix < width; pix += 2)
			{
				if (colorconverter->src_format.organisation == PACKED)
				{
					if (colorconverter->src_format.pixel_repeat_period == 1)
					{
						ch0_0[0] = *(in_data + src_ch0_byteoffset1 + (line * src_stride) + (pix * src_total_byte_pr_pixel));
						ch0_0[1] = *(in_data + src_ch0_byteoffset1 + (line * src_stride) + ((pix + 1) * src_total_byte_pr_pixel));
						ch0_0[2] = *(in_data + src_ch0_byteoffset1 + ((line + 1) * src_stride) + (pix * src_total_byte_pr_pixel));
						ch0_0[3] = *(in_data + src_ch0_byteoffset1 + ((line + 1) * src_stride) + ((pix + 1) * src_total_byte_pr_pixel));
						ch1_0[0] = *(in_data + src_ch1_byteoffset1 + (line * src_stride) + (pix * src_total_byte_pr_pixel));
						ch1_0[1] = *(in_data + src_ch1_byteoffset1 + (line * src_stride) + ((pix + 1) * src_total_byte_pr_pixel));
						ch1_0[2] = *(in_data + src_ch1_byteoffset1 + ((line + 1) * src_stride) + (pix * src_total_byte_pr_pixel));
						ch1_0[3] = *(in_data + src_ch1_byteoffset1 + ((line + 1) * src_stride) + ((pix + 1) * src_total_byte_pr_pixel));
						ch2_0[0] = *(in_data + src_ch2_byteoffset1 + (line * src_stride) + (pix * src_total_byte_pr_pixel));
						ch2_0[1] = *(in_data + src_ch2_byteoffset1 + (line * src_stride) + ((pix + 1) * src_total_byte_pr_pixel));
						ch2_0[2] = *(in_data + src_ch2_byteoffset1 + ((line + 1) * src_stride) + (pix * src_total_byte_pr_pixel));
						ch2_0[3] = *(in_data + src_ch2_byteoffset1 + ((line + 1) * src_stride) + ((pix + 1) * src_total_byte_pr_pixel));
						if (colorconverter->src_format.active_channels == 4)
						{
							ch3_0[0] = *(in_data + src_ch3_byteoffset1 + (line * src_stride) + (pix * src_total_byte_pr_pixel));
							ch3_0[1] = *(in_data + src_ch3_byteoffset1 + (line * src_stride) + ((pix + 1) * src_total_byte_pr_pixel));
							ch3_0[2] = *(in_data + src_ch3_byteoffset1 + ((line + 1) * src_stride) + (pix * src_total_byte_pr_pixel));
							ch3_0[3] = *(in_data + src_ch3_byteoffset1 + ((line + 1) * src_stride) + ((pix + 1) * src_total_byte_pr_pixel));
						}
					}
					else //(colorconverter->src_format.pixel_repeat_period == 2)
					{
						ch0_0[0] = *(in_data + src_ch0_byteoffset1 + (line * src_stride) + (pix * src_total_byte_pr_pixel));
						ch0_0[1] = *(in_data + src_ch0_byteoffset2 + (line * src_stride) + ((pix + 1) * src_total_byte_pr_pixel));
						ch0_0[2] = *(in_data + src_ch0_byteoffset1 + ((line + 1) * src_stride) + (pix * src_total_byte_pr_pixel));
						ch0_0[3] = *(in_data + src_ch0_byteoffset2 + ((line + 1) * src_stride) + ((pix + 1) * src_total_byte_pr_pixel));
						if (colorconverter->src_format.ch1.mask1 == 0
							&& colorconverter->src_format.ch1.mask2 != 0
							&& colorconverter->src_format.ch2.mask1 != 0
							&& colorconverter->src_format.ch2.mask2 == 0)
						{
							ch1_0[0] = ch1_0[1] = *(in_data + src_ch1_byteoffset2 + (line * src_stride) + ((pix + 1) * src_total_byte_pr_pixel));//4:2:2->4:4:4 of upper pixel pair
							ch1_0[2] = ch1_0[3] = *(in_data + src_ch1_byteoffset2 + ((line + 1) * src_stride) + ((pix + 1) * src_total_byte_pr_pixel));//4:2:2->4:4:4 of lower pixel pair
							ch2_0[0] = ch2_0[1] = *(in_data + src_ch2_byteoffset1 + (line * src_stride) + (pix * src_total_byte_pr_pixel));
							ch2_0[2] = ch2_0[3] = *(in_data + src_ch2_byteoffset1 + ((line + 1) * src_stride) + (pix * src_total_byte_pr_pixel));
						}
						else if (colorconverter->src_format.ch1.mask1 != 0
							&& colorconverter->src_format.ch1.mask2 == 0
							&& colorconverter->src_format.ch2.mask1 == 0
							&& colorconverter->src_format.ch2.mask2 != 0)
						{
							ch1_0[0] = ch1_0[1] = *(in_data + src_ch1_byteoffset1 + (line * src_stride) + (pix * src_total_byte_pr_pixel));//4:4:4->4:2:2 of upper pixel pair
							ch1_0[2] = ch1_0[3] = *(in_data + src_ch1_byteoffset1 + ((line + 1) * src_stride) + (pix * src_total_byte_pr_pixel));//4:4:4->4:2:2 of lower pixel pair
							ch2_0[0] = ch2_0[1] = *(in_data + src_ch2_byteoffset2 + (line * src_stride) + ((pix + 1) * src_total_byte_pr_pixel));
							ch2_0[2] = ch2_0[3] = *(in_data + src_ch2_byteoffset2 + ((line + 1) * src_stride) + ((pix + 1) * src_total_byte_pr_pixel));
						}
						if (colorconverter->src_format.active_channels == 4)
						{
							ch3_0[0] = *(in_data + src_ch3_byteoffset2 + (line * src_stride) + (pix * src_total_byte_pr_pixel));
							ch3_0[1] = *(in_data + src_ch3_byteoffset2 + (line * src_stride) + ((pix + 1) * src_total_byte_pr_pixel));
							ch3_0[2] = *(in_data + src_ch3_byteoffset2 + ((line + 1) * src_stride) + (pix * src_total_byte_pr_pixel));
							ch3_0[3] = *(in_data + src_ch3_byteoffset2 + ((line + 1) * src_stride) + ((pix + 1) * src_total_byte_pr_pixel));
						}
					}
				}
				else//planar format
				{
					int line_0_1 = (line * src_ch0_stride + pix);
					int line_0_2 = ((line + 1) * src_ch0_stride + pix);

					ch0_0[0] = *(in_data + src_ch0_offset + line_0_1);
					ch0_0[1] = *(in_data + src_ch0_offset + line_0_1 + 1);
					ch0_0[2] = *(in_data + src_ch0_offset + line_0_2);
					ch0_0[3] = *(in_data + src_ch0_offset + line_0_2 + 1);

					if (colorconverter->src_format.active_channels == 4)
					{
						int src_ch3_offset = colorconverter->src_format.ch3.offset;
						ch3_0[0] = *(in_data + src_ch3_offset + line_0_1);
						ch3_0[1] = *(in_data + src_ch3_offset + line_0_1 + 1);
						ch3_0[2] = *(in_data + src_ch3_offset + line_0_2);
						ch3_0[3] = *(in_data + src_ch3_offset + line_0_2 + 1);
					}
					if (colorconverter->src_format.chromalayout.horz_subs_factor == 1
						&& colorconverter->src_format.chromalayout.vert_subs_factor == 1)///4:4:4
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
					else if (colorconverter->src_format.chromalayout.horz_subs_factor == 2
						&& colorconverter->src_format.chromalayout.vert_subs_factor == 1)//4:2:2
					{
						int line_1_0 = (line * src_ch1_stride) + (pix >> 1);
						int line_1_1 = (line * src_ch1_stride) + (pix >> 1);
						ch1_0[0] = ch1_0[1] = *(in_data + src_ch1_offset + line_1_0);
						ch1_0[2] = ch1_0[3] = *(in_data + src_ch1_offset + line_1_1);

						ch2_0[0] = ch2_0[1] = *(in_data + src_ch2_offset + line_1_0);
						ch2_0[2] = ch2_0[3] = *(in_data + src_ch2_offset + line_1_1);
					}
					else if (colorconverter->src_format.chromalayout.horz_subs_factor == 2
						&& colorconverter->src_format.chromalayout.vert_subs_factor == 2)//4:2:0
					{
						int line_1 = ((line >> 1) * src_ch1_stride) + (pix >> 1);
						ch1_0[0] = ch1_0[1] = ch1_0[2] = ch1_0[3] = *(in_data + src_ch1_offset + line_1);
						ch2_0[0] = ch2_0[1] = ch2_0[2] = ch2_0[3] = *(in_data + src_ch2_offset + line_1);

						if (colorconverter->bDoAdaptiveInterpolation)
						{
							if (line > 1 && line < (height - 1) && pix > 1 && pix < (width - 1))//can only process if we have a valid 6x6/3x3 area
							{
								luma_adaptive_interp_block(
									line,//current line in full-resolution array
									pix,//current pixel in full-resolution array
									(in_data + src_ch0_offset), //full-res Y
									colorconverter->src_format.ch0.stride, //full-res Y
									(in_data + src_ch1_offset), //decimated U
									colorconverter->src_format.ch1.stride, //decimated U
									(in_data + src_ch2_offset), //decimated V
									colorconverter->src_format.ch2.stride, //decimated V
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
					}
				}
				//we should now have 2x2 full-resolution pixels in 3(4) channels located in buffer 0
				if (colorconverter->src_format.colorspace != colorconverter->dst_format.colorspace)
				{
					for (localpix = 0; localpix < 4; localpix++)
					{
						const int in_channels[3] =
						{
							((int)ch0_0[localpix] - in_offset[0]),
							((int)ch1_0[localpix] - in_offset[1]),
							((int)ch2_0[localpix] - in_offset[2])
						};
						for (out_channel = 0; out_channel < 3; out_channel++)
						{
							calc = 0;
							for (in_channel = 0; in_channel < 3; in_channel++)
							{
								calc += conv_matrix[out_channel][in_channel] * in_channels[in_channel];
							}
							calc += out_offset[out_channel];
							calc = calc >> exponent;
							*(out_channels[out_channel] + localpix) = (unsigned char)(calc < clip_lo[out_channel] ? clip_lo[out_channel] : (calc > clip_hi[out_channel] ? clip_hi[out_channel] : calc));
						}
					}
				}
				//copy from buffer 0 to buffer 1 if no colorspace conversion
				else
				{
					//todo: copy one 4-byte chunk instead?
					//allign buffers?
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
				//alpha channel not used in colorspace conversion anyways
				//so copy it if it is used in both input and output
				//set it to a safe value if only used in output
				if (colorconverter->src_format.active_channels == 4
					&& colorconverter->dst_format.active_channels == 4)
				{
					ch3_1[0] = ch3_0[0];
					ch3_1[1] = ch3_0[1];
					ch3_1[2] = ch3_0[2];
					ch3_1[3] = ch3_0[3];
				}
				else if (colorconverter->src_format.active_channels == 3
					&& colorconverter->dst_format.active_channels == 4)
				{
					ch3_1[0] = alpha_dummy;
					ch3_1[1] = alpha_dummy;
					ch3_1[2] = alpha_dummy;
					ch3_1[3] = alpha_dummy;
				}
				//We should now have 2x2 pixels in the desired destination colorspace and desired number of channels
				//will do decimation and packing.
				if (colorconverter->dst_format.organisation == PACKED)
				{
					int line1 = line * dst_stride;
					int line2 = ((line + 1) * dst_stride);
					int pix1 = pix * dst_total_byte_pr_pixel;
					int pix2 = (pix + 1) * dst_total_byte_pr_pixel;
					if (colorconverter->dst_format.pixel_repeat_period == 1)
					{
						*(out_data + dst_ch2_byteoffset1 + line1 + pix1) = ch2_1[0];
						*(out_data + dst_ch1_byteoffset1 + line1 + pix1) = ch1_1[0];
						*(out_data + dst_ch0_byteoffset1 + line1 + pix1) = ch0_1[0];

						*(out_data + dst_ch2_byteoffset1 + line1 + pix2) = ch2_1[1];
						*(out_data + dst_ch1_byteoffset1 + line1 + pix2) = ch1_1[1];
						*(out_data + dst_ch0_byteoffset1 + line1 + pix2) = ch0_1[1];

						*(out_data + dst_ch2_byteoffset1 + line2 + pix1) = ch2_1[2];
						*(out_data + dst_ch1_byteoffset1 + line2 + pix1) = ch1_1[2];
						*(out_data + dst_ch0_byteoffset1 + line2 + pix1) = ch0_1[2];

						*(out_data + dst_ch2_byteoffset1 + line2 + pix2) = ch2_1[3];
						*(out_data + dst_ch1_byteoffset1 + line2 + pix2) = ch1_1[3];
						*(out_data + dst_ch0_byteoffset1 + line2 + pix2) = ch0_1[3];
						if (colorconverter->dst_format.active_channels == 4)
						{
							*(out_data + dst_ch3_byteoffset1 + line1 + pix1) = ch3_1[0];
							*(out_data + dst_ch3_byteoffset1 + line1 + pix2) = ch3_1[1];
							*(out_data + dst_ch3_byteoffset1 + line2 + pix1) = ch3_1[2];
							*(out_data + dst_ch3_byteoffset1 + line2 + pix2) = ch3_1[3];
						}
					}
					else //(colorconverter->dst_format.pixel_repeat_period == 2)
					{
						*(out_data + dst_ch0_byteoffset1 + line1 + pix1) = ch0_1[0];
						*(out_data + dst_ch0_byteoffset2 + line1 + pix2) = ch0_1[1];
						*(out_data + dst_ch0_byteoffset1 + line2 + pix1) = ch0_1[2];
						*(out_data + dst_ch0_byteoffset2 + line2 + pix2) = ch0_1[3];
						if (colorconverter->dst_format.ch1.mask1 == 0
							&& colorconverter->dst_format.ch1.mask2 != 0
							&& colorconverter->dst_format.ch2.mask1 != 0
							&& colorconverter->dst_format.ch2.mask2 == 0)
						{
							*(out_data + dst_ch1_byteoffset2 + line1 + pix2) = (ch1_1[0] + ch1_1[1]) >> 1;
							*(out_data + dst_ch1_byteoffset2 + line2 + pix2) = (ch1_1[2] + ch1_1[3]) >> 1;
							*(out_data + dst_ch2_byteoffset1 + line1 + pix1) = (ch2_1[0] + ch2_1[1]) >> 1;
							*(out_data + dst_ch2_byteoffset1 + line2 + pix1) = (ch2_1[2] + ch2_1[3]) >> 1;
						}
						if (colorconverter->dst_format.ch1.mask1 != 0
							&& colorconverter->dst_format.ch1.mask2 == 0
							&& colorconverter->dst_format.ch2.mask1 == 0
							&& colorconverter->dst_format.ch2.mask2 != 0)
						{
							*(out_data + dst_ch1_byteoffset1 + line1 + pix1) = (ch1_1[0] + ch1_1[1]) >> 1;
							*(out_data + dst_ch1_byteoffset1 + line2 + pix1) = (ch1_1[2] + ch1_1[3]) >> 1;
							*(out_data + dst_ch2_byteoffset2 + line1 + pix2) = (ch2_1[0] + ch2_1[1]) >> 1;
							*(out_data + dst_ch2_byteoffset2 + line2 + pix2) = (ch2_1[2] + ch2_1[3]) >> 1;
						}
						if (colorconverter->dst_format.active_channels == 4)
						{
							*(out_data + dst_ch3_byteoffset2 + line1 + pix1) = ch3_1[0];
							*(out_data + dst_ch3_byteoffset2 + line1 + pix2) = ch3_1[1];
							*(out_data + dst_ch3_byteoffset2 + line2 + pix1) = ch3_1[2];
							*(out_data + dst_ch3_byteoffset2 + line2 + pix2) = ch3_1[3];
						}
					}
				}
				else//planar format
				{
					int line_0_1 = (line * dst_ch0_stride + pix);
					int line_0_2 = ((line + 1) * dst_ch0_stride + pix);
					*(out_data + dst_ch0_offset + line_0_1) = ch0_1[0];
					*(out_data + dst_ch0_offset + line_0_1 + 1) = ch0_1[1];
					*(out_data + dst_ch0_offset + line_0_2) = ch0_1[2];
					*(out_data + dst_ch0_offset + line_0_2 + 1) = ch0_1[3];
					if (colorconverter->dst_format.active_channels == 4)
					{
						int dst_ch3_offset = colorconverter->dst_format.ch3.offset;
						*(out_data + dst_ch3_offset + line_0_1) = ch3_1[0];
						*(out_data + dst_ch3_offset + line_0_1 + 1) = ch3_1[1];
						*(out_data + dst_ch3_offset + line_0_2) = ch3_1[2];
						*(out_data + dst_ch3_offset + line_0_2 + 1) = ch3_1[3];
					}
					if (colorconverter->dst_format.chromalayout.horz_subs_factor == 1
						&& colorconverter->dst_format.chromalayout.vert_subs_factor == 1)///4:4:4
					{
						int line_1 = ((line)*dst_ch1_stride) + (pix >> 1);
						int line_2 = ((line + 1) * dst_ch1_stride) + (pix >> 1);
						*(out_data + dst_ch1_offset + line_1 + pix) = ch1_1[0];
						*(out_data + dst_ch1_offset + line_1 + pix + 1) = ch1_1[1];
						*(out_data + dst_ch1_offset + line_2 + pix) = ch1_1[2];
						*(out_data + dst_ch1_offset + line_2 + pix + 1) = ch1_1[3];

						*(out_data + dst_ch2_offset + line_1 + pix) = ch2_1[0];
						*(out_data + dst_ch2_offset + line_1 + pix + 1) = ch2_1[1];
						*(out_data + dst_ch2_offset + line_2 + pix) = ch2_1[2];
						*(out_data + dst_ch2_offset + line_2 + pix + 1) = ch2_1[3];
					}
					else if (colorconverter->dst_format.chromalayout.horz_subs_factor == 2
						&& colorconverter->dst_format.chromalayout.vert_subs_factor == 1)//4:2:2
					{
						int line_1 = ((line)*dst_ch1_stride) + (pix >> 1);
						int line_2 = ((line + 1) * dst_ch1_stride) + (pix >> 1);
						*(out_data + dst_ch1_offset + line_1) = (ch1_1[0] + ch1_1[1]) >> 1;
						*(out_data + dst_ch1_offset + line_2) = (ch1_1[2] + ch1_1[3]) >> 1;
						*(out_data + dst_ch2_offset + line_1) = (ch2_1[0] + ch2_1[1]) >> 1;
						*(out_data + dst_ch2_offset + line_2) = (ch2_1[2] + ch2_1[3]) >> 1;
					}
					else if (colorconverter->dst_format.chromalayout.horz_subs_factor == 2
						&& colorconverter->dst_format.chromalayout.vert_subs_factor == 2)//4:2:0
					{
						int line_1 = ((line >> 1) * dst_ch1_stride) + (pix >> 1);
						*(out_data + dst_ch1_offset + line_1) = (ch1_1[0] + ch1_1[1] + ch1_1[2] + ch1_1[3]) >> 2;
						*(out_data + dst_ch2_offset + line_1) = (ch2_1[0] + ch2_1[1] + ch2_1[2] + ch2_1[3]) >> 2;
					}
				}
			}
		}
	}
}
