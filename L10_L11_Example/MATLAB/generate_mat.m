function generate_mat(name, x)
% GENERATE_MAT Generates source file (.c), header file (.h) and text data 
% file (.csv) for ARM CMSIS DSP matrix instance.
%
%   GENERATE_MAT(NAME, X) generated source, header and data file for matrix
%   instance named NAME from input matrix X
%
%   Example:
%        generate_mat('myMatrix', [1 2; 3 4])
%
%   generates files: myMatrix_mat.c, myMatrix_mat.h and myMatrix.csv with
%   instance of single-presicion floating point matrix named 'myMatrix'
%

HEADER_STR = {
   ['/* MATLAB GENERATED HEADER FILE: ' name '_mat.h */']
   ['#ifndef INC_' upper(name) '_MAT_H_']
   ['#define INC_' upper(name) '_MAT_H_']
    ''
    '#include "arm_math.h"'
    ''
   ['#define ' upper(name) '_ROWS ' num2str(size(x,1))]
   ['#define ' upper(name) '_COLS ' num2str(size(x,2))]
   ['extern float32_t* ' upper(name) '_DATA;']
   ['extern arm_matrix_instance_f32 ' name ';']
    ''
   ['#endif /* INC_' upper(name) '_MAT_H_ */']
};

fileID = fopen([name '_mat.h'],'w');
for i = 1 : length(HEADER_STR)
    fprintf(fileID,'%s\n', HEADER_STR{i});
end
fclose(fileID);

SOURCE_STR = {
   ['/* MATLAB GENERATED SOURCE FILE: ' name '_mat.c */']
   ['#include "' name '_mat.h"']
   ['uint32_t ' upper(name) '_DATA_UINT[' upper(name) '_ROWS*' upper(name) '_COLS] = ']
    '{'
   ['  #include "' name '.csv"']
    '};'
   ['float32_t* ' upper(name) '_DATA = (float32_t*)' upper(name) '_DATA_UINT;']   
   ['arm_matrix_instance_f32 ' name ';']
};

fileID = fopen([name '_mat.c'],'w');
for i = 1 : length(SOURCE_STR)
    fprintf(fileID,'%s\n', SOURCE_STR{i});
end
fclose(fileID);

x = x';
x = x(:);

vec2csvfile([name '.csv'], x);
