% 1. Read the CSV fil
%data = readtable('./output/output.csv'); 
%t = table2array(data(:, 1)); % Time column
%x = table2array(data(:, 2)); % Signal column

% 2. Calculate sampling rate
%fs = 1 / mean(diff(t)); 

% 3. Compute and plot the spectrogram
%figure;
%spectrogram(x, 500, 480, [], fs, 'yaxis'); 
%title('Spectrogram from CSV');
%xlabel('Time (s)');
%ylabel('Frequency (Hz)');
%colorbar;

filename = './output/output.csv';

matrix = readmatrix(filename);
disp(matrix);

fh = figure;
ah = axes(fh);
surf(ah, matrix);