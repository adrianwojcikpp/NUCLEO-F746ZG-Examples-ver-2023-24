%% Proportional-integral-derivative controller unit test
%%% File info 
%
% *************************************************************************
%
%  @file     unit_test_pid.m
%  @author   Adrian Wojcik
%  @version  2.0
%  @date     17-Dec-2019 14:01:34
%  @brief    Simple PID controller unity test
%
% *************************************************************************
%
close all; clc;
clear variables;
%% Test signal
% sample time & freq
ts = 0.001; % [s]
fs = 1/ts;  % [Hz]

% test time
tmax = 1;   % [s]

% time vector
tvec = (0 : ts : tmax-ts)';

% sample vector
nvec = (0 : length(tvec)-1)';

% test signal - square wave
Tref = 0.1; % [s] signal period
refvec = (3.3/2)*(square(2*pi*tvec/Tref) + 1);

%% Test plant model

% -- GAIN [-] -------------------------------------------------------------
K = 10.0;
    
% -- TIME CONSTANT [s] ----------------------------------------------------
T = 0.5; 
    
% -- S-OPERATOR [1/s] -----------------------------------------------------
s = tf('s');

% -- PLANT TRANSFER FUNCTION ----------------------------------------------
G = K / (1 + T*s);

%% PID controller tunning
% simple pole-placement example

% -- REFERENCE CLOSED LOOP TIME CONSTANT [s] ------------------------------
Tref = 0.01; 

% -- PID CONTROLER GAINS --------------------------------------------------
Ki = 1 / ( K * Tref );
Kp = Ki * T;
Kd = 0;

% -- PID CONTROLLER TRANSFER FUNCTION --------------------------------------
H = Kp + Ki/s + Kd*s;

% -- CLOSED-LOOP SYSTEM ---------------------------------------------------
S_out = feedback(H*G, 1);
S_pid = feedback(H, G);

% -- CLOSED-LOOP SYSTEM RESPONSE COMPUTING --------------------------------
outvec = lsim(S_out,refvec,tvec);
controlvec = lsim(S_pid,refvec,tvec);
errvec = refvec - outvec;

% Control signal: MATLAB lsim built-in function
pid_out_v1 = controlvec; 

%% EXPORT FILTER TO .C/.H FILES
[Kp2, Ki2, Kd2] = generate_pid('PID1', Kp, Ki, Kd, ts);

%% FOR-LOOP REFERENCE PID CONTROLLER RESPONSE COMPUTING

x = single(errvec); % error
xi = single(0);  % error integral
y1 = single(zeros(size(errvec)));
y2 = single(zeros(size(errvec)));
y3 = single(zeros(size(errvec)));

% -- CMSIS ALGORITHM GAINS FORMULAS ---------------------------------------
A0 = Kp2 + Ki2 + Kd2;
A1 = (-Kp2 ) - (2 * Kd2 );
A2 = Kd2;

% CMSIS FORM                                      % n = 1
y2(1) = A0 * x(1);
y3(1) = A0 * x(1);

% EXPLICIT FORM
xi = xi + x(1);
xd = single(0);  % error derivative
y1(1) = Kp2*x(1) + Ki2*xi + Kd2*xd;

% CMSIS FORM                                      % n = 2
y2(2) = A0 * x(2) + A1 * x(1) + y2(1); % code order
y3(2) = y2(1) + A0 * x(2) + A1 * x(1); % doc order

% EXPLICIT FORM
xi = xi + x(2);
xd = x(2) - x(1);   
y1(2) = Kp2*x(2) + Ki2*xi + Kd2*xd;

for n = 3 : length(tvec)                          % n >= 3
    
    % EXPLICIT FORM
    xi = xi + x(n);
    xd = x(n) - x(n-1);   
    y1(n) = Kp2*x(n) + Ki2*xi + Kd2*xd;

    % CMSIS FORM
    y2(n) = A0 * x(n) + A1 * x(n-1) + A2 * x(n-2) + y2(n-1); % code order
    y3(n) = y3(n-1) + A0 * x(n) + A1 * x(n-1) + A2 * x(n-2); % doc order
    
end

% Control signal: for-loop implementation (explicit form)
pid_out_v21 = y1;
% Control signal: for-loop implementation (CMSIS DSP form)
pid_out_v22 = y2;

%% RESULT PLOT
hold on;
    stairs(tvec, outvec, 'DisplayName', 'OUT'); 
    stairs(tvec, refvec, 'DisplayName', 'REF'); 
    stairs(tvec, pid_out_v1,  'DisplayName', 'CONTROL (lsim)');
    stairs(tvec, pid_out_v21, 'DisplayName', 'CONTROL (for loop EXPLICIT)');
    stairs(tvec, pid_out_v22, 'DisplayName', 'CONTROL (for loop CMSIS)');
grid on;
hold off;
xlabel('Time [s]');
legend();

%% SAVE TEST DATA TO .C/.H AND .CSV FILES
generate_vec('X3', errvec);
generate_vec('Y3', zeros(size(pid_out_v22)));
generate_vec('Y3_REF', pid_out_v22);

%% MOVE .C/.H AND .CSV FILES TO Components CATALOG
srcDest = '../Components/Src';
cFiles = dir('*.c');
csvFiles = dir('*.csv');
for i = 1:length(cFiles)
    movefile(cFiles(i).name, fullfile(srcDest, cFiles(i).name));
end
for i = 1:length(csvFiles)
    movefile(csvFiles(i).name, fullfile(srcDest, csvFiles(i).name));
end

incDest = '../Components/Inc';
hFiles = dir('*.h');
for i = 1:length(hFiles)
    movefile(hFiles(i).name, fullfile(incDest, hFiles(i).name));
end