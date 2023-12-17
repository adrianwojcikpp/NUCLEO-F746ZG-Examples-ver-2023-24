function coeffs_cell = generate_biquad_df1(name, tf_num, tf_den)
% GENERATE_BIQUAD_DF1 Generates source file (.c), header file (.h) and text data 
% file (.csv) for ARM CMSIS DSP infinite impulse response filter instance.
%
%   COEFFS_CELL = GENERATE_BIQUAD_DF1(NAME, TF_NUM, TF_DEN) generated source, 
%   header and data files for IIR filter instance named NAME from input coefficients
%   vectors TF_NUM and TF_DEN and returns cell array with coefficients as 
%   biquad direct form #1 vectors for each stage
%
%   Example:
%        generate_biquad_df1('myFilter', [0, 0.001, 0.001], [1, -1.9, 0.9])
%
%   generates files: myFilter_biquad_df1.c, myFilter_biquad_df1.h, myFilter_state_init.csv 
%   and myFilter_coeffs.csv with instance of single-presicion floating point 
%   IIR filter named 'myFilter'
%
    [sos, g] = tf2sos(tf_num, tf_den);
    coeffs_cell = cell(size(g));
    
    % to single-precision floating-point number
    sos = single(sos);
    g = single(g);
    num_stages = size(sos,1);
    
    for sec = 1 : num_stages
        if sec == 1
          b0 = sos(sec, 1)*g;
          b1 = sos(sec, 2)*g;
          b2 = sos(sec, 3)*g;
        else
          b0 = sos(sec, 1);
          b1 = sos(sec, 2);
          b2 = sos(sec, 3);
        end
        a1 = -sos(sec, 5);
        a2 = -sos(sec, 6);
        % To CMSIS DSP biquad df1 form
        coeffs_cell{sec} = [b0 b1 b2 a1 a2];
    end

    coeffs = cell2mat(coeffs_cell);
    coeffs = coeffs';
    coeffs = coeffs(:)';

    vec2csvfile([name '_coeffs.csv'], coeffs);
    vec2csvfile([name '_state_init.csv'], zeros(1,4*num_stages));

    source_file = {
        ['/* MATLAB GENERATED SOURCE FILE: ' name '_biquad_df1.c */']
        ['#include "' name '_biquad_df1.h"']
         '// Filter state' 
        ['uint32_t ' name '_STATE_UINT[4*' upper(name) '_NUM_STAGES] = {']
        ['  #include "' name '_state_init.csv"' ]
         '};'                                                                
        ['float32_t *' name '_STATE = (float32_t*)' name '_STATE_UINT;' ]
         '// Filter coefficients'
        ['uint32_t ' name '_COEFFS_UINT[5*' upper(name) '_NUM_STAGES] = {']
	    ['  #include "' name '_coeffs.csv"']
         '};'                                                                  
        ['float32_t *' name '_COEFFS = (float32_t*)' name '_COEFFS_UINT;']
         '// Filter instance'                                                  
        ['arm_biquad_casd_df1_inst_f32 ' name ';' ]
    };

    fileID = fopen([name '_biquad_df1.c'],'w');
    for i = 1 : length(source_file)
        fprintf(fileID,'%s\n', source_file{i});
    end
    fclose(fileID);

    header_file = {
        ['/* MATLAB GENERATED  HEADER FILE: ' name '_biquad_df1.h */']
        ['#ifndef INC_' upper(name) '_H_']
        ['#define INC_' upper(name) '_H_']
         ''
         '#include "arm_math.h"'        
         ''
        ['#define ' upper(name) '_NUM_STAGES  ' num2str(num_stages)]
        ['#define ' upper(name) '_BLOCK_SIZE  ' num2str(1)];
         '// Filter state'                                                    
        ['extern float32_t *' name '_STATE;']
         '// Filter coefficients'                                              
        ['extern float32_t *' name '_COEFFS;']
         '// Filter instance'       
        ['extern arm_biquad_casd_df1_inst_f32 ' name ';']
        ['#endif // INC_' upper(name) '_H_']
    };

    fileID = fopen([name '_biquad_df1.h'],'w');
    for i = 1 : length(header_file)
        fprintf(fileID,'%s\n', header_file{i});
    end
    fclose(fileID);

end
