%Nume program: fft_f.m
%Calculul FFT bazat pe segmentarea semnalului in frecventa
%Autor : Teodorescu Florentina Raluca
%Grupa: 343 AB
%Data ultimei modificari : 28.08.2008

%vectorul de semnal
%X=w*(x[1:M]+x[[M+1:2*M]]),w se calculeaza recursiv

function X=fft_f(x)

M=length(x)/2; % N=2M => M=N/2

if M==1
   X = [ x(1)+x(2)  x(1)-x(2) ]; %testul de iesire din functie se face pt. TFD2
else 
   w=1;
   arg=exp(-pi*j/M);
   for i=1:M
         a=i+M;
         X(i)=x(i)+x(a);
         X(a)=w*(x(i)-x(a));
         w=w*arg;
   end

X=[ fft_f(X([1:M])) fft_f( X([M+1:2*M]))];

end