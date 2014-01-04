%Nume program: fft_t.m
%Calculul FFT bazat pe segmentarea semnalului in timp
%Autor : Teodorescu Florentina Raluca
%Grupa: 343 AB
%Data ultimei modificari : 28.08.2008

function [X]=fft_t(x);

v=bitrevorder(x);%rearanjarea semnalului de intrare
N=length(x);
L=log2(N);
for l=0:L-1
    c=bitshift(1,l+1); %calculez 2^l+1
    d=bitshift(1,l);%calculez 2^l+1
   for m=1:d
        arg=(m-1)*pi/d;
        w=exp(-j*arg);
        for k=0:N/c-1 %k=0:(2^L/2^(l+1))-1
            ckm=bitshift(k,l+1)+m;%calculez 2^l+1*k
            ckmd=ckm+d;
            x=v(ckm);
            y=w*v(ckmd);%o singura inmultire complexa
            v(ckm)=x+y;
            v(ckmd)=x-y;
        end
    end
 end
X=v;%transformata Fourier Discreta
             