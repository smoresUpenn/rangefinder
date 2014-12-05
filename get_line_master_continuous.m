%% initialization

clc
clear all
close all

% Create a serial object.  Change the string to the port name on your
% computer.
s = serial('/dev/tty.usbserial-A601EW9I');
s.BaudRate=19200;

%% Read Data
ROW = 480;   % previous value is 1000
LINE = 65;

%open the serial port.  If this line throws an error, you may need to chmod
%your serial port.
fopen(s);

max_line = zeros(ROW,1);
figure(1);
h = plot(max_line(1:ROW),1:ROW);
hold all
grid on
axis([0 640 0 ROW/2]);
temp(1,1:100) = 0;
counts = 0;
while 1
    if fread(s,1) == 115
        max_line = zeros(ROW*2,1);
        %for m = 1:ROW*2
        m=1;
        while(max_line~=101)
            max_line(m) = fread(s,1);
            m=m+1;
        end
        %end
        %if max_line(m-1) == 101
            counts
            %break
            max_line = 256*max_line(1:2:ROW*2)+max_line(2:2:ROW*2);
            label = bitshift(bitand(max_line, 32768), -15);
            max_line = bitand(max_line, 32767);
            counts = counts+1;
            temp(counts,:) = max_line(200:299);
%             plot(max_line(1:500),1:500);
            set(h,'XData',max_line(1:ROW),'YData',1:ROW);
            drawnow;
        %end
    end

end
fclose(s);






