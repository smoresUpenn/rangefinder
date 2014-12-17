%% initialization

clc
clear all
%close all
%s = serial('/dev/tty.usbserial-A601EW9I');
s = serial('/dev/ttyUSB0');
s.BaudRate=19200;
%s.InputBufferSize = 512;

%% Read Data
ROW = 40;
LINE = 640;

figure();
fopen(s);
while 1
    if fread(s,1) == 115
        img = zeros(ROW,LINE);
        for m = 1:ROW
            for n = 1:LINE
                img(m,n) = fread(s,1);
            end
        end
        if fread(s,1) == 101
            disp('OK');
            break
        end
    end
end

while 1
    if fread(s,1) == 115
        max_line = zeros(ROW,1);
        for m = 1:ROW*2
            max_line(m) = fread(s,1);
        end
        if fread(s,1) == 101
            disp('OK');
            break
        end
    end
end
max_line = 256*max_line(1:2:ROW*2)+max_line(2:2:ROW*2);
fclose(s);
%%
% RGB = demosaic(uint8(img), 'gbrg');
RGB = demosaic(uint8(img), 'gbrg');
imshow(RGB)
hold all
% ROW = 30;
row = 1:ROW;
line = zeros(1, ROW);
for i = 1:ROW
    line(i) = max_line(ROW-i+1);
end
line = line + 1;
plot(line(1:2:end),row(end:-2:1));
axis([0 640 0 ROW])
% pause
%
%%

red_ch = img(2:2:end, :);
red_ch(:,2:2:end) = 0;

[red_ch_value, red_ch_ind] = max(red_ch, [], 2);
red_ch_ind = [(2:2:size(img, 1))' red_ch_ind];
plot(red_ch_ind(:,2), red_ch_ind(:,1));

%[U1,U2] = max(img,[],2);
%U2 = [(1:size(img,1))' U2];
%plot(U2(:,2),U2(1:1:end,1));
