%Nume program: goertzel.m
%Implementarea eficienta a algorimului Goertzel (de calcul TFD)
%Autor : Teodorescu Florentina Raluca
%Grupa: 343 AB
%Data ultimei modificari : 28.08.2008

function [X]=goertzel(x);

N=length(x);

for k=0:N-1    %k=0:N-1 si n=0:N-1 dar, deoarece Matlab nu permite folosirea indecsilor <=0 luam n=1:N
    vk1=x(1); % n=0 =>v[0]=x[0] =>v[1]=x[1] conform comentariului de mai sus
    vk2=2*cos(2*k*pi/N)*vk1+x(2); %n=1 se obs ca v[-1]=0 si rezulta expresia
    for n=3:N
        aux=2*cos(2*k*pi/N)*vk2-vk1+x(n);%evaluare expresie si reactualizare variabile
        vk1=vk2; %corespunde termenului de la pas n-2
        vk2=aux;%corespunde termenului de la pas n-1
    end
    vk1=2*cos(2*k*pi/N)*vk2-vk1;
    X(k+1)=vk1-complex(cos(2*k*pi/N),-sin(2*k*pi/N))*vk2;
end