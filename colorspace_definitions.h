/*Constants necessary for the colorspace conversion. First MATLAB script for generating values,
then printout from MATLAB*/


/*
% function [out_ch0, out_ch1, out_ch2] = transform_colorspace(in_ch0, in_ch1, in_ch2, in_colspace, out_colspace, precision)
% %Will only do 1 pixel sized images...
% %
% %[out_ch0, out_ch1, out_ch2] = transform_colorspace(in_ch0, in_ch1, in_ch2, in_colspace, out_colspace, precision)
% %   in_colspace and out_colspace are strings describing the input and output
% %       colorspaces:
% %       'sRGB_PC'       - sRGB with levels from 0-255
% %       'sRGB_Studio'   - sRGB with levels from 16-235
% %       'BT601'         - YCbCr according to ITU-Rec.601
% %       'BT709'         - YCbCr according to ITU-Rec.709
% %
% %   out_ch0, out_ch1, out_ch2
% %       doubles with outputvalues for either R'G'B' or Y'CbCr
% %
% %   in_ch0, in_ch1, in_ch2
% %       doubles with inputvalues for either R'G'B' or Y'CbCr
% %
% %   precision
% %       string for calculating with integer precision as well, 'int32' or
% %       'int16'
% % e.g. 
% %[out_ch0, out_ch1, out_ch2] = transform_colorspace(0, 128,255, 'sRGB_PC', 'BT601', 'int16')
% %
% %   TANDBERG 28.05.2008
% %   Knut Inge Hvidsten
% %   knut.inge.hvidsten@tandberg.com
% %
% [in_offset, in_excursion, out_offset, conv_matrix, clip] = calculate_color_coefficients2(in_colspace, out_colspace);
% out = out_offset + (conv_matrix*([in_ch0, in_ch1, in_ch2]-in_offset(:)')');
% out = round(out);
% out(out < clip(:,1)) = clip(out < clip(:,1));
% out(out > clip(:,2)) = clip(out > clip(:,2));
% out_ch0 = out(1);
% out_ch1 = out(2); 
% out_ch2 = out(3);
% 
% %doing integer transform:
% [in_offset_int, out_offset_int, conv_matrix_int, clip_int, exponent] = get_integer_tranform_from_floatingpoint_transform(in_offset, in_excursion, out_offset, conv_matrix, clip, precision);
% [ch0_out, ch1_out, ch2_out] = do_integer_tranform(in_ch0, in_ch1, in_ch2, in_offset_int, out_offset_int, conv_matrix_int, clip_int, exponent, precision);
% 
% %calculating the error
% disp(['error doing ', precision, '-based conversion instead of double-precision (then rounded to uint8)'])
% disp([double([out_ch0, out_ch1, out_ch2]) - double([ch0_out, ch1_out, ch2_out])]);

function generate_coefficients()
format long
print_precision = 7;

precision       = 'int16';
scalar_prefix_f = 'const float';
vect_prefix_f   = 'const float';
array_prefix_f  = 'const float';
scalar_prefix_i = 'const signed short';
vect_prefix_i   = 'const signed short';
array_prefix_i  = 'const signed short';

colorspaces = {'sRGB_PC','BT601','BT709'};

%generate C-style enum
disp('enum')
disp('{')
for i=1:(length(colorspaces) -1)
 disp([colorspaces{i},',']);
end
disp([colorspaces{end}]);
disp('};')

complete_conv_matrix_float	= zeros(3, 3, length(colorspaces), length(colorspaces));
complete_clip_float          = zeros(3,2, length(colorspaces), length(colorspaces));
complete_in_offset_float     = zeros(3, length(colorspaces), length(colorspaces));
complete_out_offset_float    = zeros(3, length(colorspaces), length(colorspaces));

complete_conv_matrix_int16	= zeros(3, 3, length(colorspaces), length(colorspaces));
complete_clip_int16          = zeros(3, 2,length(colorspaces), length(colorspaces));
complete_exponent_int16      = zeros(length(colorspaces), length(colorspaces));
complete_in_excursion_int16  = zeros(3, length(colorspaces), length(colorspaces));
complete_in_offset_int16     = zeros(3, length(colorspaces), length(colorspaces));
complete_out_offset_int16    = zeros(3, length(colorspaces), length(colorspaces));

%generate multidimensional arrays describing conversion;
for src_index = 1:length(colorspaces)
    for dst_index = 1:length(colorspaces)
        %calculate for float stuff
        [in_offset, in_excursion, out_offset, conv_matrix, clip]    =   calculate_color_coefficients2(colorspaces{src_index}, colorspaces{dst_index});
        complete_conv_matrix_float(:,:,src_index,dst_index)                =   conv_matrix;
        complete_clip_float(:,:,src_index,dst_index)                       =   clip;
        complete_in_offset_float(:,src_index,dst_index)                  =   in_offset;
        complete_out_offset_float(:,src_index,dst_index)                 =   out_offset;
        %calculate for int16 stuff
        [in_offset_int16, out_offset_int16, conv_matrix_int16, clip_int16, exponent_int16] = get_integer_tranform_from_floatingpoint_transform(in_offset, in_excursion, out_offset, conv_matrix, clip, precision);
        complete_conv_matrix_int16(:,:,src_index,dst_index)                =   conv_matrix_int16;
        complete_clip_int16(:,:,src_index,dst_index)                       =   clip_int16;
        complete_in_offset_int16(:,src_index,dst_index)                  =   in_offset_int16;
        complete_out_offset_int16(:,src_index,dst_index)                 =   out_offset_int16;    
        complete_exponent_int16(src_index,dst_index)                       =   exponent_int16; 
    end
end

%display in C-friendly format
generate_C_multidim_array(array_prefix_f,'float_in_offset', complete_in_offset_float, print_precision);
generate_C_multidim_array(array_prefix_f,'float_out_offset', complete_out_offset_float, print_precision);
generate_C_multidim_array(array_prefix_f,'float_conv_matrix', complete_conv_matrix_float, print_precision);

generate_C_multidim_array(array_prefix_i, 'int16_in_offset', complete_in_offset_int16, print_precision);
generate_C_multidim_array(array_prefix_i, 'int16_out_offset', complete_out_offset_int16, print_precision);
generate_C_multidim_array(array_prefix_i, 'int16_conv_matrix', complete_conv_matrix_int16, print_precision);
generate_C_multidim_array(array_prefix_i, 'int16_clip', complete_clip_int16, print_precision);   
generate_C_multidim_array(array_prefix_i, 'int16_exponent', complete_exponent_int16, print_precision);       

function [in_offset_int, out_offset_int, conv_matrix_int, clip_int, exponent] = get_integer_tranform_from_floatingpoint_transform(in_offset, in_excursion, out_offset, conv_matrix, clip, precision)
%!in_excursion = [16, 235; 16, 240; 16, 240];
%find the legal (within in_excursion) input values that cause the largest
%values - use those for scaling
in_min_max_offset = in_excursion - in_offset*ones(1,2);
in_min_offset = in_min_max_offset(:,1)*ones(1,3);
in_max_offset = in_min_max_offset(:,2)*ones(1,3);
in_offset_worstcase = in_min_offset.*(conv_matrix < 0) + in_max_offset.*(conv_matrix >= 0);
worst_case = conv_matrix .* in_offset_worstcase;
worst_case(:,4) =  out_offset;
worst_case(:,5) =  sum(worst_case(:,1:4)');
%we need to make sure that no clipping occurs for any intermediate
%calculation
worst_case_vect = max(worst_case');
overflow_vect = (double(intmax(precision))./worst_case_vect);
%We could actually use a different scaling for the different components,
%but...
exponent = min(floor(log2(overflow_vect)));

%conv_matrix.*(in_min_max_offset(:,2)*ones(1,3))
%exponent_max = log2(double(intmax(precision))./sum([out_offset, conv_matrix*(clip(:,2)-in_offset)]'));
%exponent = floor(min(exponent_max));
in_offset_int       = in_offset;
out_offset_int      = out_offset * 2^exponent +  2^(exponent-1);%adding offset and quantisation offset into one
conv_matrix_int     = round(conv_matrix * 2^exponent);
clip_int            = clip * 2^exponent;

function [ch0_out, ch1_out, ch2_out] = do_integer_tranform(ch0_in, ch1_in, ch2_in, in_offset_int, out_offset_int, conv_matrix_int, clip_int, exponent, precision)

if strcmp(precision, 'int32')
    in_offset_int   = int32(in_offset_int);
    out_offset_int  = int32(out_offset_int);
    conv_matrix_int = int32(conv_matrix_int);
    clip_int        = int32(clip_int);
    ch0_out = (conv_matrix_int(1,1)*(ch0_in - in_offset_int(1))... 
            + conv_matrix_int(1,2)*(ch1_in - in_offset_int(2))... 
            + conv_matrix_int(1,3)*(ch2_in - in_offset_int(3))...
            + out_offset_int(1));
    ch0_out =  uint8(bitshift(uint32(ch0_out),-exponent));
    ch1_out = (conv_matrix_int(2,1)*(ch0_in - in_offset_int(1))... 
            + conv_matrix_int(2,2)*(ch1_in - in_offset_int(2))... 
            + conv_matrix_int(2,3)*(ch2_in - in_offset_int(3))...
            + out_offset_int(2));
    ch1_out =  uint8(bitshift(uint32(ch1_out),-exponent));
    ch2_out = (conv_matrix_int(3,1)*(ch0_in - in_offset_int(1))... 
            + conv_matrix_int(3,2)*(ch1_in - in_offset_int(2))... 
            + conv_matrix_int(3,3)*(ch2_in - in_offset_int(3))...
            + out_offset_int(3));
    ch2_out =  uint8(bitshift(uint32(ch2_out),-exponent));   
elseif strcmp(precision, 'int16')    
    in_offset_int   = int16(in_offset_int);
    out_offset_int  = int16(out_offset_int);
    conv_matrix_int = int16(conv_matrix_int);
    clip_int        = int16(clip_int);    
    ch0_out = (conv_matrix_int(1,1)*(ch0_in - in_offset_int(1))... 
            + conv_matrix_int(1,2)*(ch1_in - in_offset_int(2))... 
            + conv_matrix_int(1,3)*(ch2_in - in_offset_int(3))...
            + out_offset_int(1));
    ch0_out =  uint8(bitshift(uint16(ch0_out),-exponent));
    ch1_out = (conv_matrix_int(2,1)*(ch0_in - in_offset_int(1))... 
            + conv_matrix_int(2,2)*(ch1_in - in_offset_int(2))... 
            + conv_matrix_int(2,3)*(ch2_in - in_offset_int(3))...
            + out_offset_int(2));
    ch1_out =  uint8(bitshift(uint16(ch1_out),-exponent));
    ch2_out = (conv_matrix_int(3,1)*(ch0_in - in_offset_int(1))... 
            + conv_matrix_int(3,2)*(ch1_in - in_offset_int(2))... 
            + conv_matrix_int(3,3)*(ch2_in - in_offset_int(3))...
            + out_offset_int(3));
    ch2_out =  uint8(bitshift(uint16(ch2_out),-exponent));
end

                       
function [in_offset, in_excursion, out_offset, conv_matrix, clip] = calculate_color_coefficients2(in_colspace, out_colspace)
%http://www.poynton.com/PDFs/ColorFAQ.pdf
sRGB_normalised_seed = struct(...
    'excursion',    [0, 1],...
    'clip',         [0, 1],...
    'offset',        0.5);

sRGB_PC_seed = struct(...
    'excursion',    [0, 255],...
    'clip',         [0, 255],...
    'offset',       0);

sRGB_Studio_seed = struct(...
    'excursion',    [16, 235],...
    'clip',         [16, 235],...
    'offset',       0);

ITU_BT601_seed = struct(...
    'Wr',               0.299,...
    'Wb',               0.114,...
    'Y_excursion',      [16, 235],...
    'Y_clip',           [1, 254],...
    'Y_offset',         16,...
    'CbCr_excursion',   [16, 240],...
    'CbCr_clip',        [1, 254],...
    'CbCr_offset',      128);

ITU_BT709_seed = struct(...
    'Wr',               0.2126,...
    'Wb',               0.0722,...
    'Y_excursion',      [16, 235],...
    'Y_clip',           [1, 254],...
    'Y_offset',         16,...    
    'CbCr_excursion',   [16, 240],...
    'CbCr_clip',        [1, 254],...
    'CbCr_offset',      128);

if      strcmp(in_colspace, 'sRGB_PC')      in_seed = sRGB_PC_seed;         in_offset = sRGB_PC_seed.offset*ones(3,1);
elseif  strcmp(in_colspace, 'sRGB_Studio')  in_seed = sRGB_Studio_seed;     in_offset = sRGB_Studio_seed.offset*ones(3,1);
elseif  strcmp(in_colspace, 'BT601')        in_seed = ITU_BT601_seed;       in_offset = [ITU_BT601_seed.Y_offset; ITU_BT601_seed.CbCr_offset*ones(2,1)];
elseif  strcmp(in_colspace, 'BT709')        in_seed = ITU_BT709_seed;       in_offset = [ITU_BT709_seed.Y_offset; ITU_BT709_seed.CbCr_offset*ones(2,1)];
end

if      strcmp(out_colspace, 'sRGB_PC')      out_seed = sRGB_PC_seed;       out_offset = sRGB_PC_seed.offset*ones(3,1);
elseif  strcmp(out_colspace, 'sRGB_Studio')  out_seed = sRGB_Studio_seed;   out_offset = sRGB_Studio_seed.offset*ones(3,1);
elseif  strcmp(out_colspace, 'BT601')        out_seed = ITU_BT601_seed;     out_offset = [ITU_BT601_seed.Y_offset; ITU_BT601_seed.CbCr_offset*ones(2,1)];
elseif  strcmp(out_colspace, 'BT709')        out_seed = ITU_BT709_seed;     out_offset = [ITU_BT709_seed.Y_offset; ITU_BT709_seed.CbCr_offset*ones(2,1)];
end

if      ((strcmp(in_colspace, 'sRGB_PC')  || strcmp(in_colspace, 'sRGB_Studio')) && (strcmp(out_colspace, 'BT601')   || strcmp(out_colspace, 'BT709')))
    conv_matrix = sRGB_to_YCbCr(out_seed, in_seed);
elseif  ((strcmp(in_colspace, 'BT601')    || strcmp(in_colspace, 'BT709'))       && (strcmp(out_colspace, 'sRGB_PC') || strcmp(out_colspace, 'sRGB_Studio')))
    conv_matrix = inv(sRGB_to_YCbCr(in_seed, out_seed));
elseif  ((strcmp(in_colspace, 'BT601')   ||  strcmp(in_colspace, 'BT709'))       && (strcmp(out_colspace, 'BT601')   || strcmp(out_colspace, 'BT709')))
    conv_matrix = sRGB_to_YCbCr(out_seed, sRGB_normalised_seed)*inv(sRGB_to_YCbCr(in_seed, sRGB_normalised_seed));
elseif  ((strcmp(in_colspace, 'sRGB_PC') ||  strcmp(in_colspace, 'sRGB_Studio')) && (strcmp(out_colspace, 'sRGB_PC') || strcmp(out_colspace, 'sRGB_Studio')))
    conv_matrix = inv(sRGB_to_YCbCr(ITU_BT601_seed, out_seed))*sRGB_to_YCbCr(ITU_BT601_seed, in_seed);
end

if (strcmp(out_colspace, 'sRGB_PC') || strcmp(out_colspace, 'sRGB_Studio'))
    clip = ones(3,1)*(out_seed.clip);
else
    clip = [out_seed.Y_clip; out_seed.CbCr_clip; out_seed.CbCr_clip];
end

if (strcmp(in_colspace, 'sRGB_PC') || strcmp(in_colspace, 'sRGB_Studio'))
    in_excursion = ones(3,1)*in_seed.excursion;
else
    in_excursion = [in_seed.Y_excursion; in_seed.CbCr_excursion; in_seed.CbCr_excursion];
end

function sRGB_to_YPbPr_mat = sRGB_to_YPbPr(ITU_seed)
sRGB_to_YPbPr_mat = ...
	[ITU_seed.Wr,                       (1-ITU_seed.Wr-ITU_seed.Wb),                ITU_seed.Wb;...
	-0.5*ITU_seed.Wr/(1-ITU_seed.Wb),   -0.5*(1 + ITU_seed.Wr/(ITU_seed.Wb-1)),     0.5	;...
	0.5,                                -0.5*(1  - (ITU_seed.Wb/(1-ITU_seed.Wr))),  -0.5*ITU_seed.Wb/(1-ITU_seed.Wr)];

function sRGB_to_YCbCr_mat = sRGB_to_YCbCr(ITU_seed, sRGB_seed)
    sRGB_to_YPbPr_mat = sRGB_to_YPbPr(ITU_seed);
    sRGB_swing = diff(sRGB_seed.excursion);
    Y_swing = diff(ITU_seed.Y_excursion);
    CbCr_swing = diff(ITU_seed.CbCr_excursion);   
    sRGB_to_YCbCr_mat = sRGB_to_YPbPr_mat.*([Y_swing; CbCr_swing; CbCr_swing]*ones(1,3))/sRGB_swing;

function generate_C_scalar(prefix, postfix, name, scalar, print_precision)
    disp([prefix, ' ', name, postfix, ' = ', num2str(scalar, print_precision), ';']);
    
function generate_C_vector(prefix, postfix, name, vect, print_precision)
    disp([prefix, ' ', name, postfix, ' = {']);
    for i=1:length(vect)
        disp([num2str(vect(i), print_precision), ','])
    end
    disp('};');

function generate_C_array(prefix, postfix, name, array, print_precision)
    disp([prefix, ' ', name, postfix, ' = {']);
    for i=1:size(array,1)
        disp('{');
        for j=1:size(array,2)
            disp([num2str(array(i,j), print_precision), ','])
        end
        disp('},');
    end
    disp('};');
    
% function generate_C_multidim_array(prefix, postfix, name, array, print_precision)
%     disp([prefix, ' ', name, postfix, ' = {']);
%     for i=1:size(array,1)
%         disp('{');
%         for j=1:size(array,2)
%             disp('{');
%             for k=1:size(array,3)
%                 for l=1:size(array,4)
%                     disp([num2str(array(i,j,k,l), print_precision), ','])
%                 end
%                 disp('},');
%             end
%             disp('},');
%         end
%         disp('},');
%     end
%     disp('};');    
    
function generate_C_multidim_array(prefix, name, array, print_precision)
    dimensions = ndims(array);
    if (dimensions == 2 && (((size(array,1) == 1)) || (size(array,2) == 1)))
        dimensions = 1;
    end
    postfix = [];
    for i=1:dimensions
        postfix = [postfix, '[', num2str(size(array,i)), ']'];
    end
    disp([prefix, ' ', name, postfix, '= {']);
    for i=1:size(array,1)
        if (dimensions > 1)
            disp('{');
            for j=1:size(array,2)
                if (dimensions > 2)
                    disp('{');
                    for k=1:size(array,3)
                        if (dimensions > 3)
                            disp('{');
                            for l=1:size(array,4)
                                disp([num2str(array(i,j,k,l), print_precision), ','])
                            end
                            disp('},');
                        else
                            disp([num2str(array(i,j,k), print_precision), ','])
                        end
                    end
                    disp('},');
                else
                    disp([num2str(array(i,j), print_precision), ','])
                end
            end
            disp('},');
        else
            disp([num2str(array(i), print_precision), ','])
        end
    end
    disp('};');
*/

const unsigned char BT601_lo[3]			=	{16,	16,		16};
const unsigned char BT601_hi[3]			=	{235,	240,	240};

const unsigned char BT709_lo[3]			=	{16,	16,		16};
const unsigned char BT709_hi[3]			=	{235,	240,	240};

const unsigned char sRGB_PC_lo[3]		=	{0,		0,	0};
const unsigned char sRGB_PC_hi[3]		=	{255,	255,	255};

const unsigned char sRGB_Studio_lo[3]	=	{16,	16,		16};
const unsigned char sRGB_Studio_hi[3]	=	{235,	235,	235};

/* -= Constants copied from script above: =- */

const float float_in_offset[3][3][3]= {
{
{
0,
0,
0,
},
{
16,
16,
16,
},
{
16,
16,
16,
},
},
{
{
0,
0,
0,
},
{
128,
128,
128,
},
{
128,
128,
128,
},
},
{
{
0,
0,
0,
},
{
128,
128,
128,
},
{
128,
128,
128,
},
},
};
const float float_out_offset[3][3][3]= {
{
{
0,
16,
16,
},
{
0,
16,
16,
},
{
0,
16,
16,
},
},
{
{
0,
128,
128,
},
{
0,
128,
128,
},
{
0,
128,
128,
},
},
{
{
0,
128,
128,
},
{
0,
128,
128,
},
{
0,
128,
128,
},
},
};
const float float_conv_matrix[3][3][3][3]= 
{
{

{
{	1,			0.2567882,	0.1825859,	},
{	1.164384,	1,			1,			},
{	1.164384,	1,			1,			},},

{
{
1.110223e-016,
0.5041294,
0.6142306,
},
{
-5.598944e-017,
-2.775558e-017,
-0.1155497,
},
{
-0,
0.09931166,
0,
},
},
{
{
-1.387779e-017,
0.09790588,
0.06200706,
},
{
1.596027,
-1.110223e-016,
-0.2079376,
},
{
1.792741,
0.1916995,
-3.428638e-018,
},
},
},
{
{
{
-5.551115e-017,
-0.1482229,
-0.1006437,
},
{
1.164384,
1.110223e-016,
1.110223e-016,
},
{
1.164384,
1.110223e-016,
1.110223e-016,
},
},
{
{
1,
-0.2909928,
-0.338572,
},
{
-0.3917623,
1,
1.01864,
},
{
-0.2132486,
0.9898538,
1,
},
},
{
{
0,
0.4392157,
0.4392157,
},
{
-0.8129676,
-2.775558e-017,
0.114618,
},
{
-0.5329093,
-0.1106525,
3.469447e-018,
},
},
},
{
{
{
-6.225957e-017,
0.4392157,
0.4392157,
},
{
1.164384,
0,
-2.081668e-017,
},
{
1.164384,
1.110223e-016,
9.020562e-017,
},
},
{
{
-1.51855e-016,
-0.3677883,
-0.3989422,
},
{
2.017232,
2.775558e-017,
0.07504945,
},
{
2.112402,
-0.07245296,
0,
},
},
{
{
1,
-0.07142737,
-0.04027352,
},
{
1.110223e-016,
1,
1.025327,
},
{
0,
0.9833978,
1,
},
},
},
};
const signed short int16_in_offset[3][3][3]= {
{
{
0,
0,
0,
},
{
16,
16,
16,
},
{
16,
16,
16,
},
},
{
{
0,
0,
0,
},
{
128,
128,
128,
},
{
128,
128,
128,
},
},
{
{
0,
0,
0,
},
{
128,
128,
128,
},
{
128,
128,
128,
},
},
};
const signed short int16_out_offset[3][3][3]= {
{
{
64,
2112,
2112,
},
{
16,
2112,
2112,
},
{
16,
1056,
2112,
},
},
{
{
64,
16448,
16448,
},
{
16,
16448,
16448,
},
{
16,
8224,
16448,
},
},
{
{
64,
16448,
16448,
},
{
16,
16448,
16448,
},
{
16,
8224,
16448,
},
},
};
const signed short int16_conv_matrix[3][3][3][3]= {
{
{
{
128,
33,
23,
},
{
37,
128,
128,
},
{
37,
64,
128,
},
},
{
{
0,
65,
79,
},
{
-0,
-0,
-15,
},
{
0,
6,
0,
},
},
{
{
-0,
13,
8,
},
{
51,
-0,
-27,
},
{
57,
12,
-0,
},
},
},
{
{
{
-0,
-19,
-13,
},
{
37,
0,
0,
},
{
37,
0,
0,
},
},
{
{
128,
-37,
-43,
},
{
-13,
128,
130,
},
{
-7,
63,
128,
},
},
{
{
0,
56,
56,
},
{
-26,
-0,
15,
},
{
-17,
-7,
0,
},
},
},
{
{
{
-0,
56,
56,
},
{
37,
0,
-0,
},
{
37,
0,
0,
},
},
{
{
-0,
-47,
-51,
},
{
65,
0,
10,
},
{
68,
-5,
0,
},
},
{
{
128,
-9,
-5,
},
{
0,
128,
131,
},
{
0,
63,
128,
},
},
},
};
const signed short int16_clip[3][2][3][3]= {
{
{
{
0,
128,
128,
},
{
0,
128,
128,
},
{
0,
64,
128,
},
},
{
{
32640,
32512,
32512,
},
{
8160,
32512,
32512,
},
{
8160,
16256,
32512,
},
},
},
{
{
{
0,
128,
128,
},
{
0,
128,
128,
},
{
0,
64,
128,
},
},
{
{
32640,
32512,
32512,
},
{
8160,
32512,
32512,
},
{
8160,
16256,
32512,
},
},
},
{
{
{
0,
128,
128,
},
{
0,
128,
128,
},
{
0,
64,
128,
},
},
{
{
32640,
32512,
32512,
},
{
8160,
32512,
32512,
},
{
8160,
16256,
32512,
},
},
},
};
const signed short int16_exponent[3][3]= {
{
7,
7,
7,
},
{
5,
7,
7,
},
{
5,
6,
7,
},
};
