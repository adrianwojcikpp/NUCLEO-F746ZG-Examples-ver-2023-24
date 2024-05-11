% Open serial port
s = serialport('COM8', 115200);
configureTerminator(s, "LF");

% Create figure and axes
figure;
ax = gca;
xlabel('Sensor');
ylabel('Temperature [deg C]');
title('Temperature Readings');
hold on; 

% Initialize bar plot
barHandle = bar([0, 1, 2], [NaN, NaN, NaN]);
ax.XTick = [0, 1, 2];
ax.XLim = [-1, 3];
ax.YLim = [20, 40]; % Adjust as needed

try
    while true
        % Read data from serial port
        data = readline(s);
        
        % Decode JSON data
        jsonData = jsondecode(data);
        
        % Extract sensor and temperature values
        sensor = jsonData.sensor;
        temperature = jsonData.temperature;
        
        % Update bar plot
        barHandle.YData(sensor+1) = temperature; % MATLAB indexing starts from 1
        drawnow;
    end
catch ME
    disp(ME);
    % Close serial port
    delete(s);
    clear s;
end
