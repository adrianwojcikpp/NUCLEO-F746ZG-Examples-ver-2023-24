%% Infinite impulse response filter unit test
%%% File info 
%
% *************************************************************************
%
%  @file     unit_test_iir.m
%  @author   Adrian Wojcik
%  @version  2.0
%  @date     17-Dec-2019 10:33:27
%  @brief    Simple IIR filter unity test
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
tvec = 0 : ts : tmax-ts;

% sample vector
nvec = 0 : length(tvec)-1;

% test signal - square wave
Tx = 0.1; % [s] signal period
xvec = (3.3/2)*(square(2*pi*tvec/Tx) + 1);

% test signal amplitude spectrum
% frequency vector
frange = (-1/2 : 1/length(nvec) : 1/2-1/length(nvec)); % [-]
fxvec = frange*fs;                               % [Hz]
% amplitude response
Axvec = abs(fftshift(fft(xvec,length(nvec)))); % [-]
Axvec = Axvec / length(nvec);

%% FILTER EXAMPLE 
% Version 1: custom transfer function model -------------------------------

    % -- S-OPERATOR -------------------------------------------------------
    s = tf('s');

    % -- MODEL PARAMS -----------------------------------------------------
    f = 10.0;   % [Hz]
    w = 2*pi*f; % [rad/s]
    e = 0.7;    % [-]

    % -- CONTINUOUS TRANSFER FUNCTION -------------------------------------
    G = 1 / ((1 + 2*e*s/w + s^2 / w^2));

    % -- DISCRETIZATION ---------------------------------------------------
    H = c2d(G,ts, 'zoh');

    % -- DISCRETE FILTER --------------------------------------------------
    b = H.num{1};
    a = H.den{1};

% Version 2: low-pass Chebyshev type I filter -----------------------------

    % -- FILTER PARAMS ----------------------------------------------------
    N = 3;          % [-]
    R = 1;          % [-]
    Wp = 17.5 / fs; % [-]

    % -- DISCRETE FILTER --------------------------------------------------
    [b,a] = cheby1(N,R,Wp,'low');

% -- FILTER RESPONSE COMPUTING --------------------------------------------
% filtered signal time series: MATLAB filter built-in function
xfvec_v1 = filter(b,a,xvec); 
% filtered signal time series: MATLAB lsim built-in function
%xfvec_v1 = lsim(H,xvec,tvec)'; 

% Filter frequency response
% no. of samples
n = 10^4; % [-]
% frequency vector
frange = (-1/2 : 1/n : 1/2-1/n); % [-]
fhvec = frange*fs;               % [Hz]
% amplitude response
Ahvec_v1 = abs(freqz(b,a, 2*pi*frange)); % [-] frequency response
Ahvec_v1 = 20*log10(Ahvec_v1); % [dB]

% filtered signal amplitude spectrum
% amplitude response
Axfvec = abs(fftshift(fft(xfvec_v1, length(nvec)))); % [-]
Axfvec = Axfvec / length(nvec);

%% EXPORT FILTER TO .C/.H FILES
biquad_coeffs = generate_biquad_df1('IIR1', b, a);

if length(biquad_coeffs) == 1
    %% FOR-LOOP REFERENCE FILTER RESPONSE COMPUTING
    
    % EXPLICIT FORM
    b0 = biquad_coeffs{1}(1);
    b1 = biquad_coeffs{1}(2);
    b2 = biquad_coeffs{1}(3);
    a1 = biquad_coeffs{1}(4);
    a2 = biquad_coeffs{1}(5);
    
    x = xvec;
    y = single(zeros(size(xfvec_v1)));
    
    y(1) = b0 * x(1);                                        % n = 1
    y(2) = b0 * x(2) + b1 * x(1) + a1 * y(1);                % n = 2
    for n = 3 : length(tvec)    
        y(n) = b0 * x(n) + b1 * x(n-1) + b2 * x(n-2) + ...   % n >= 3
                         + a1 * y(n-1) + a2 * y(n-2);
    end
    
    % filtered signal time series: for-loop implementation (CMSIS DSP form)
    xfvec_v2 = y;
    
    % filtered signal amplitude spectrum
    % amplitude response
    Axfvec = abs(fftshift(fft(xfvec_v2,length(nvec)))); % [-]
    Axfvec = Axfvec / length(nvec);
end

%% Plot results
fminmax = [-10 fs/2];
tminmax = [0 tmax];
Aminmax = [-0.1 3.5];
AdBminmax = [-120 5];

subplot(2,2,1)
  plot(nvec/fs, xvec, 'b'); grid on;
  xlabel("Time [s]");
  ylabel("Amplitude [-]");
  axis([tminmax Aminmax]);
  title('Orginal test signal time series');
  hold off;
subplot(2,2,2)
  yyaxis left
    plot(fxvec, Axvec, '-');
    xlabel("Frequency [Hz]");
    ylabel("Amplitude spectrum [-]");
    set(gca,'YLim', [0 0.51*3.3], 'XLim', fminmax);
    hold on;
    grid on;
  yyaxis right
    plot(fhvec, Ahvec_v1, '-');
    ylabel("Amplitude response [dB]"); 
    %plot([f1 f1], AdBminmax, 'k--');
    %plot([f2 f2], AdBminmax, 'k--'); 
    set(gca,'YLim', AdBminmax, 'XLim', fminmax);
    title('Original test signal ampltitude spectrum');
    hold off;
subplot(2,2,3)
  plot(nvec/fs, xfvec_v1, 'b'); grid on; hold on;
  xlabel("Time [s]");
  ylabel("Amplitude [-]");
  axis([tminmax Aminmax]);
  title('Filtered test signal time series');
  hold off;
subplot(2,2,4)
  yyaxis left
    plot(fxvec, Axfvec, '-');
    xlabel("Frequency [Hz]");
    ylabel("Amplitude spectrum [-]");
    set(gca, 'YLim', [0 0.51*3.3], 'XLim', fminmax);
    hold on; grid on
  yyaxis right
    plot(fhvec, Ahvec_v1, '-');  
    ylabel("Amplitude response [dB]"); 
    %plot([f1 f1], AdBminmax, 'k--');
    %plot([f2 f2], AdBminmax, 'k--'); 
    set(gca, 'YLim', AdBminmax, 'XLim', fminmax);
    title('Filtered test signal ampltitude spectrum');
    hold off;

%% SAVE TEST DATA TO .C/.H AND .CSV FILES
generate_vec('X2', xvec);
generate_vec('Y2', zeros(size(xfvec_v1)));
generate_vec('Y2_REF', xfvec_v1);

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