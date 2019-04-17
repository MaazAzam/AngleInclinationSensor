delete(instrfind); 

s = serial('COM3', 'BaudRate', 38400, 'Terminator','CR'); 

fopen(s); 
ylim([0,100]);

x=1:0.5:50000;
y=zeros(1,50000);
i = 1;

while(true)
    a = fscanf(s);
    angle = str2double(a);
    y(i)=angle;
    plot(x(1:i),y(1:i));
    title("Accelerometer Real-Time Angle Output");
    xlabel("Time (s)");
    ylabel("Angle (degrees)");
    pause(0.001);
    i = i + 1;
end

fclose(s);