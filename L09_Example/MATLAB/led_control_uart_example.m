%{
 **************************************************************************
 * @file    led_control_uart_example.m
 * @author  AW             Adrian.Wojcik@put.poznan.pl
 * @version 1.0
 * @date    12-Dec-2021
 * @brief   Simple MATLAB serial port client example for LED current control
 **************************************************************************
%}

%% Serial port set up
if ~exist('huart', 'var')
    huart = serialport('COM8',115200,'Timeout', 10);
    configureTerminator(huart,"CR");
end

%% Reference control signal
duty_ref = 0 : 1 : 100;
N = length(duty_ref);

%% Characteristic plot
hFig = figure();
    hPlot = plot(nan(N,1),nan(N,1), 'k');
    xlabel('Duty [%]');
    ylabel('LED current [mA]');
    hold on; grid on;
 
%% Perform experiment
k = 1;               % [-]

for i = 1: length(duty_ref)
    
    str = sprintf("R%03d.0%%", duty_ref(i));
    huart.writeline(str);
    
    pause(0.1)
    
    str = sprintf("ADC0000", duty_ref(i));
    huart.writeline(str);
    rawData = huart.readline();
     
    if ~isempty(rawData)
        data = jsondecode(rawData);
        if isfield(data,'I1')
            updateplot(hPlot, data.I1, duty_ref(i), i, N);
        end
    end
    pause(0.1)
end

%% Close serial port and remove handler
huart = [];
clearvars('huart');

%% Plot update function: save only last N samples
function updateplot(hplot, y, x, k, N)
    if k > N

        hplot.YData(end) = y; 
        hplot.XData = circshift(hplot.XData, -1); 
        hplot.XData(end) = x; 
    else
        hplot.YData(k) = y; 
        hplot.XData(k) = x; 
    end
end