function generate_vec(name, x)

HEADER_STR = {
   ['/* MATLAB GENERATED HEADER FILE: ' name '_vec.h */']
   ['#ifndef INC_' upper(name) '_VEC_H_']
   ['#define INC_' upper(name) '_VEC_H_']
    ''
    '#include "arm_math.h"'
    ''
   ['#define ' upper(name) '_LEN ' num2str(length(x))]
   ['extern float32_t* ' name ';']
    ''
   ['#endif /* INC_' upper(name) '_VEC_H_ */']
};

fileID = fopen([name '_vec.h'],'w');
for i = 1 : length(HEADER_STR)
    fprintf(fileID,'%s\n', HEADER_STR{i});
end
fclose(fileID);

SOURCE_STR = {
   ['/* MATLAB GENERATED SOURCE FILE: ' name '_vec.c */']
   ['#include "' name '_vec.h"']
   ['uint32_t ' upper(name) '_DATA_UINT[' upper(name) '_LEN] = ']
    '{'
   ['  #include "' name '.csv"']
    '};'
   ['float32_t* ' name ' = (float32_t*)' upper(name) '_DATA_UINT;']   
};

fileID = fopen([name '_vec.c'],'w');
for i = 1 : length(SOURCE_STR)
    fprintf(fileID,'%s\n', SOURCE_STR{i});
end
fclose(fileID);

x = x';
x = x(:);

vec2csvfile([name '.csv'], x);
