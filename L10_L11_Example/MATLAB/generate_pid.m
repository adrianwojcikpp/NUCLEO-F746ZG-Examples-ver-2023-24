function [Kp2, Ki2, Kd2] = generate_pid(name, Kp, Ki, Kd, Ts)
% GENERATE_PID Generates source file (.c), header file (.h) and text data 
% file (.csv) for ARM CMSIS DSP proportional-integral-derivative controller
%
%   [KP2, KI2, KD2] = GENERATE_PID(NAME, KP, KI, KD, TS) generated source, 
%   header and data file for PID controller instance named NAME from
%   proportional, integral end derivative gains in parallel form and
%   sample time expressed in seconds; returns PID gains scaled by sample time
%
%   Example:
%        generate_pid('myController', 10, 0.5, 0.1, 0.001)
%
%   generates files: myController_pid.c, myController_pid.h and myController_gains.csv 
%   with instance of single-presicion floating point PID controller named 'myController'
%
    Kp2 = single(Kp);
    Ki2 = single(Ki * Ts); 
    Kd2 = single(Kd / Ts);

    vec2csvfile([name '_gains.csv'], [Kp2 Ki2 Kd2]);

    source_file = {
        ['/* MATLAB GENERATED SOURCE FILE: ' name '_pid.c */']
        ['#include "' name '_pid.h"']
         '// Controller gains'
        ['uint32_t ' upper(name) '_GAINS_UINT[3] = ']
         '{'
        ['  #include "' name '_gains.csv"']
         '};' 
         '// Controller instance'
        ['arm_pid_instance_f32 ' name ';']
    };

    fileID = fopen([name '_pid.c'],'w');
    for i = 1 : length(source_file)
        fprintf(fileID,'%s\n', source_file{i});
    end
    fclose(fileID);

    header_file = {
        ['/* MATLAB GENERATED  HEADER FILE: ' name '_pid.h */']
        ['#ifndef INC_' upper(name) '_H_']
        ['#define INC_' upper(name) '_H_']
         ''
         '#include "arm_math.h"'        
         ''
         '// Controller gains'
        ['extern uint32_t ' upper(name) '_GAINS_UINT[3];']
        ['#define ' name '_KP  (((float32_t*)' name '_GAINS_UINT)[0])']
        ['#define ' name '_KI  (((float32_t*)' name '_GAINS_UINT)[1])']
        ['#define ' name '_KD  (((float32_t*)' name '_GAINS_UINT)[2])']
         '// Controller instance'
        ['extern arm_pid_instance_f32 ' name ';']
        ['#endif // INC_' upper(name) '_H_']
    };

    fileID = fopen([name '_pid.h'],'w');
    for i = 1 : length(header_file)
        fprintf(fileID,'%s\n', header_file{i});
    end
    fclose(fileID);

end
