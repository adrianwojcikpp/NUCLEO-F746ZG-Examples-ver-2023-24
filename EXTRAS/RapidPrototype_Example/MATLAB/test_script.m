% Define the serial port and parameters
serialPortName = 'COM8';  % Modify this to your specific serial port
baudRate = 115200;

try
    % Create a serialport object
    s = serialport(serialPortName, baudRate);

    while true
        % Generate the message in the specified format
        for value = 45:45:360
            message = sprintf('d%03d', value);
            % Send the message over the serial port
            write(s, message, "char");
            disp(['Sent: ' message]);
            for p = [0, 180]
                message = sprintf('p%03d', p);
                % Send the message over the serial port
                write(s, message, "char");
                disp(['Sent: ' message]);
                pause(2);  % Wait for 2 seconds
            end
        end
    end
catch exception
    close(s);
    error('Error occurred: %s', exception.message);
end

% Close the serial port
close(s);
