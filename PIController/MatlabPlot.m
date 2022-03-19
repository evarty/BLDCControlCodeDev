%% 
%plotting SVPWM voltage outputs
Data = fopen('Output.txt');
%Data = fopen('OutputImp.txt');
s = textscan(Data, '%f %d %d %d','headerlines',1);
fclose(Data);

plot(s{1},s{2})
hold on
plot(s{1},s{3})
hold on
plot(s{1},s{4})
legend({'U','V','W'})

%% 
%%plotting PWM output

figure
Data2 = fopen('OutputPWM1.txt');
s = textscan(Data2, '%d %d %d','headerlines',1);
fclose(Data2);

plot(s{2},s{1,3}+4)
hold on

Data2 = fopen('OutputPWM2.txt');
s = textscan(Data2, '%d %d %d','headerlines',1);
fclose(Data2);

plot(s{2},s{1,3}+2)
hold on

Data2 = fopen('OutputPWM3.txt');
s = textscan(Data2, '%d %d %d','headerlines',1);
fclose(Data2);

plot(s{2},s{1,3})
legend({'U','V','W'})

ylim([-.1, 5.1])

