function generate_fir(name, fir_coeffs, blocksize)
% GENERATE_FIR Generates source file (.c), header file (.h) and text data 
% file (.csv) for ARM CMSIS DSP finite impulse response filter instance.
%
%   GENERATE_FIR(NAME, FIR_COEFFS, BLOCKSIZE) generated source, header and 
%   data file for FIR filter instance named NAME from input coefficients
%   vector FIR_COEFFS and with single input entry size of BLOCKSIZE
%
%   Example:
%        generate_fir('myFilter', [1/3 1/3 1/3], 1)
%
%   generates files: myFilter_fir.c, myFilter_fir.h, myFilter_state_init.csv 
%   and myFilter_coeffs.csv with instance of single-presicion floating point 
%   FIR filter named 'myFilter'
%
    vec2csvfile([name '_coeffs.csv'], fir_coeffs);
    vec2csvfile([name '_state_init.csv'], zeros(size(fir_coeffs)));
   
    source_file = {
        ['/* MATLAB GENERATED SOURCE FILE: ' name '_fir.c */']
        ['#include "' name '_fir.h"'];
         '// Filter state'
        ['uint32_t ' name '_STATE_UINT[' upper(name) '_NUM_TAPS+' upper(name) '_BLOCK_SIZE-1] = {'];  % numTaps+blockSize-1
        ['  #include "' name '_state_init.csv"'];
         '};'
        ['float32_t *' name '_STATE = (float32_t*)' name '_STATE_UINT;'];
         '// Filter coefficients'  
        ['uint32_t ' name '_COEFFS_UINT[' upper(name) '_NUM_TAPS] = {']
        ['  #include "' name '_coeffs.csv"']
         '};'
        ['float32_t *' name '_COEFFS = (float32_t*)' name '_COEFFS_UINT;']
         '// Filter instance' 
        ['arm_fir_instance_f32 ' name ';']
    };
    
    fileID = fopen([name '_fir.c'],'w');
    for i = 1 : length(source_file)
        fprintf(fileID,'%s\n', source_file{i});
    end
    fclose(fileID);
    
    header_file = {
        ['/* MATLAB GENERATED  HEADER FILE: ' name '_fir.h */']
        ['#ifndef INC_' upper(name) '_H_'];
        ['#define INC_' upper(name) '_H_'];
         ''
         '#include "arm_math.h"'
         ''
        ['#define ' upper(name) '_NUM_TAPS  ' num2str(length(fir_coeffs))];
        ['#define ' upper(name) '_BLOCK_SIZE  ' num2str(blocksize)];
         '// Filter state';
        ['extern float32_t *' name '_STATE;'];
        ['// Filter coefficients'];
        ['extern float32_t *' name '_COEFFS;'];
         '// Filter instance';       
        ['extern arm_fir_instance_f32 ' name ';'];
         ''
        ['#endif // INC_' upper(name) '_H_'];
         ''
    };
    
    fileID = fopen([name '_fir.h'],'w');
    for i = 1 : length(header_file)
        fprintf(fileID,'%s\n', header_file{i});
    end
    fclose(fileID);
    
end
