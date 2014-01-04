% Genereaza semnale "muzicale".
% Frecventa de esantionare este 40KHz
% (astfel incat sa se pastreze frecventele < 20 kHz, adica
% cele din zona audibila).

% Program pentru Laborator 3, Prelucrarea semnalelor

test = 5;			% 0 - suma de sinusoide filtrata
						% 1 - vioara
						% 2 - viola
                  % 3 - clarinet
                  % 4 - trombon
                  % 5 - tuba

Fes = 40000;		% frewcventa de esantionare
L = 80000;			% numar esantioane - 2 secunde

Nf = 1000;			% numarul de puncte cu care se deseneaza spectrele

% alege amplitudinile sinusoidelor
% (1 pentru suma de sinusoide ce va fi filtrata,
%  valori predefinite pentru instrumentele muzicale)
switch test
  case 0,				% suma de sinusoide - baza + armonice
	 Fbaza = 440;		% frecventa in Hz a sunetului la
	 Narm = 8;			% numar de armonice
	 xampl = ones(1, Narm);	% amplitudinile armonicelor

  case 1,				% vioara
	 Fbaza = 440;		% la
	 Narm = 18;
    xampl = [100 45 21 26 48 53 53 62 53 26 24 16 16 35 12 34 23 11] / 100;

  case 2,				% viola
	 Fbaza = 440;		% la
    Narm = 10;
    xampl = [100 45 40 20 40 30 10 15 8 8] / 100;

  case 3,				% clarinet
	 Fbaza = 180;		% fa diez
	 Narm = 10;
	 xampl = [100 0 50 10 60 30 50 30 10 2] / 100;
    
  case 4,				% trombon
	 Fbaza = 230;		% si bemol
	 Narm = 6;
    xampl = [100 100 50 60 10 3] / 100;
    
  case 5,				% tuba
	 Fbaza = 230;		% si bemol
	 Narm = 5;
	 xampl = [100 70 8 3 2] / 100;
    
end
    
f_baza = Fbaza/Fes*2;			% frecventa discreta a fundamentalei
omega_baza = 2*pi*f_baza;		% pulsatia fundamentalei

% construieste suma de sinusoide
x = zeros(1,L);					% semnalul
for i = 1 : Narm
  x = x + xampl(i) * sin(i*omega_baza*(0:L-1));
end

% spectrul sumei de sinusoide
[X,f] = freqz(x,1,Nf);
figure(1)
plot(f/pi,abs(X));

% filtru reprezentand instrumentul
if test == 0
  b = 1;						% alege un filtru IIR (instrumentul !!!)
  a = [1 -0.95];
  figure(3)
  freqz(b,a);				% caracteristica de frecventa
else
  b = 1; a = 1;			% pentru instrumentele predefinite, nu filtram
end

y = filter(b,a,x);		% iesirea filtrului
[Y,f] = freqz(y,1,Nf);% spectrul semnalului de iesire
figure(2)
plot(f/pi,abs(Y));

% salveaza semnal audio
y = y / max(abs(y));

auwrite(y,40000,16,'linear',['muz' int2str(test) '.au'])