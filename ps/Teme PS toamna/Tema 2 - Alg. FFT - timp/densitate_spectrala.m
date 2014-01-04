%Nume program: densitate_spectrala.m
%Calculul densitailor spectrale pentru seria de timp si zgomotul colorat
%Autor : Teodorescu Florentina Raluca
%Grupa: 343 AB
%Data ultimei modificari : 28.08.2008

function [phi_serie,phi_zg,omega]=densitate_spectrala(e,A,C,modelA,modelC,y,lambda2);

%   densitatea spectrala se calculeaza astfel: phi(y)=|H(e^jw)|^2 * phi(u) ,
%   unde:
%   phi este densitatea spectrala pura a semnalului  
%   phi(u) este densitatea spectrala a zgomotului alb egala cu dispersia (=1)

omega=0:pi/300:pi;

for i=1:301
    phi_serie(i)=(power(abs((polyval(modelC,exp(-j*omega(i))))/(polyval(modelA,exp(-j*omega(i))))),2))*lambda2;
    phi_zg(i)=power(abs((polyval(C,exp(j*omega(i))))/(polyval(A,exp(j*omega(i))))),2);
end

%transformare in decibeli
phi_serie=10*log10(phi_serie);
phi_zg=10*log10(phi_zg);
    