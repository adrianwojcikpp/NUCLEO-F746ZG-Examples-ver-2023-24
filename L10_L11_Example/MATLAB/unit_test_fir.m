%% Finite impulse response filter unit test
%%% File info 
%
% ************************************************************************
%
%  @file     unit_test_fir.m
%  @author   Adrian Wojcik
%  @version  2.0
%  @date     12-Dec-2020 19:59:05
%  @brief    Simple FIR digital low-pass filter design and test
%
% ************************************************************************
%
close all; clc;
clear variables;
%% TEST SIGNAL
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

% Filter desired parameters
% cut-off frequency
f1 = 10;  % [Hz]
% frequency at the end transition band
f2 = 50; % [Hz]
% transition band length
df = f2 - f1;
% stopband attenuation of A [dB] at f2 [Hz]
A = 50; % [dB]
               
% Filter order estimation
% with 'fred harris rule of thumb'
N = round( (fs/df)*A / 22 );

% Filter object with fir1 funcion
% normalised frequency
w = f1 / (fs/2); % [-]
% low pass filter
b = fir1(N, w, 'low');

% Filter frequency response
% no. of samples
n = 10^4; % [-]
% frequency vector
frange = (-1/2 : 1/n : 1/2-1/n); % [-]
fhvec = frange*fs;               % [Hz]
% amplitude response
Ahvec_v1 = abs(freqz(b, 1, 2*pi*frange)); % [-] frequency response
Ahvec_v1 = 20*log10(Ahvec_v1); % [dB]
Ahvec_v2 = abs(fftshift(fft(b,n)));       % [-] impulse response fft 
Ahvec_v2 = 20*log10(Ahvec_v2); % [dB]

% Test signal filtration
xfvec = filter(b,1,xvec);

% filtered signal amplitude spectrum
% amplitude response
Axfvec = abs(fftshift(fft(xfvec,length(nvec)))); % [-]
Axfvec = Axfvec / length(nvec);

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
    plot([f1 f1], AdBminmax, 'k--');
    plot([f2 f2], AdBminmax, 'k--'); 
    set(gca,'YLim', AdBminmax, 'XLim', fminmax);
    title('Original test signal ampltitude spectrum');
    hold off;
subplot(2,2,3)
  plot(nvec/fs, xfvec, 'b'); grid on; hold on;
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
    plot(fhvec, Ahvec_v2, '-');  
    ylabel("Amplitude response [dB]"); 
    plot([f1 f1], AdBminmax, 'k--');
    plot([f2 f2], AdBminmax, 'k--'); 
    set(gca, 'YLim', AdBminmax, 'XLim', fminmax);
    title('Filtered test signal ampltitude spectrum');
    hold off;
  
%% EXPORT FILTER TO .C/.H FILES
generate_fir('FIR1', b, 1);

%% SAVE TEST DATA TO .C/.H AND .CSV FILES
generate_vec('X1', xvec);
generate_vec('Y1', zeros(size(xfvec)));
generate_vec('Y1_REF', xfvec);

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