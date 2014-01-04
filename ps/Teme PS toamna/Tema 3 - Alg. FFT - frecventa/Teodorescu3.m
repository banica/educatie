%Nume program: Teodorescu3.m
%Implementarea algorimului FFT bazat pe segmentarea semnalului in frecventa
%Autor : Teodorescu Florentina Raluca
%Grupa: 343 AB
%Data ultimei modificari : 28.08.2008
%Rutine apelate: gen_arma.m, st_arma.m, densitate_spectrala.m, fft_f.m

%%%%%%%%%%% PRIMUL PAS :  Incarcarea seriei de timp

%Utilizatorul alege seria de timp. Introduce numarului ei.
nr_st=-1; %valoarea default, in cazul in care se da Enter fara a introduce vreo valoare
nr_st=input('Dati numarul seriei de timp : ');
while ((nr_st<1) | (nr_st>15) )
    disp('Numarul seriei de timp trebuie sa fie in intervalul 1-15.');
    nr_st=input('Dati numarul seriei de timp : ');
end

%Incarcarea efectiva a seriei de timp
nume_st=['st',int2str(nr_st)];
eval(nume_st);
N=length(y);
Ts=1;

%%%%%%%%%%% AL DOILEA PAS :  Identificarea seriei de timp cu un model ARMA

%generarea numarului de poli (na) si de zerori (nc) in intervalul [10,25]
na=round(rand*10+15);
nc=round(rand*10+15);

%identificarea seriei de timp cu un model ARMA pentru a determina seria simulata 
[model,obiect]=st_arma(y,na,nc);
%generaraea de poli si zerouri pentru filtrarea zgomotului alb
[Z,P,e]=gen_arma(na,nc);

%%%%%%%%%%% AL TREILEA PAS :  Afisarea datelor preliminare

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% FIGURA 1 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%afisarea datelor preliminare
figure(1);

%seria de timp %%%% subfigura mare
subplot(3,2,[1 3 5]);
plot(ntime,y,'r');
axis tight;
grid on;
title(label); %ce reprezinta seria de timp
xlabel(unit); % unitatea de masura a Ts
ylabel(yunit); % unitatea de masura a valorilor lui y
hold on;

%tot seria de timp %%%% subfigura mica
subplot(3,2,2);
plot(ntime,y,'b');
axis tight;
grid on;
title('Seria de timp achizitionata');
ylabel('Date masurate');
hold on;

%simularea seriei de timp
yp=predict(model,obiect,1);

%seria de timp simulata
subplot(3,2,4);
plot(ntime,yp.y,'m');
axis tight;
grid on;
titlu=['Seria de timp simulata cu un model ARMA[',num2str(na),',',num2str(nc),']'];
title(titlu);
ylabel('Date simulate');
hold on;

%estimarea erorii de predictie
eroare=y'-yp.y;
%estimarea dispersiei
lambda2=(eroare'*eroare)/N;

%eroarea de predictie
subplot(3,2,6);
plot(ntime,eroare,'r');
axis tight;
grid on;
titlu=['O estimatie a zgomotului alb (lambda2 = ',num2str(lambda2),')'];
title(titlu);
ylabel('Eroare de predictie');
titlu=['Timp [Ts = ',num2str(Ts),' ',unit,']'];
xlabel(titlu);
hold off;


%verificare daca lungimea seriei este o putere a lui 2
p=2^floor(log2(N)); %cel mai apropiat numar ce este o putere a lui 2 imediat inferior lui N
t=2^ceil(log2(N));%cel mai apropiat numar ce este o putere a lui 2 imediat superior lui N
if (t-N)<(N-p)
    %completarea cu zerouri
    y=[y zeros(1,(t-N))];
    N=t;
else
    %trunchiere
    y=y(1:p);
    N=p;
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% FIGURA 2 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%polii si zerourile modelului de identificare ARMA[na,nc]
figure(2);
zplane(model.C,model.A);
axis([-1 1 -1 1]);
set(2,'DefaultTextVerticalAlignment','top');
string=strcat('Polii(x) si zerourile(o) modelului de identificare ARMA [',num2str(na),',',num2str(nc),']');
title(string); 

%afisare coeficienti polinoamelor modelului ARMA
str='Polinomul C:';
for i=1:nc+1
    str=strvcat(str,num2str(model.C(i)));
end
text(-1.55,1,str,'FontSize',8);
str='Polinomul A:';

for i=1:na+1
    str=strvcat(str,num2str(model.A(i)));
end
text(1.2,1,str,'FontSize',8);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% FIGURA 4 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%polii si zerourile modelului ARMA[na,nc] folosit pentru filtrarea
%zgomotului alb

figure(4);
zplane(Z,P);
A=poly(P);
C=poly(Z);
axis([-1 1 -1 1]);
titlu='Polii(x) si zerourile(o) ale filtrului ARMA [';
titlu=strcat(titlu,num2str(na),',',num2str(nc),']');
title(titlu); 


%afisare coeficienti polinoamelor modelului ARMA
set(4,'DefaultTextVerticalAlignment','top');
str='Polinomul C:';
for i=nc+1:-1:1
    str=strvcat(str,num2str(C(i)));
end
text(-1.55,1,str,'FontSize',8);
str='Polinomul A:';

for i=na+1:-1:1
    str=strvcat(str,num2str(A(i)));
end
text(1.2,1,str,'FontSize',8);


%afisarea zgomotului alb si al zgomotului colorat
%filtrarea zgomotului albcu filtrul ARMA generat=> zgomotul colorat
zg=filter(C,A,e);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% FIGURA 3 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%

figure(3);
subplot(2,1,1);
plot(1:length(e),e,'b');
axis tight;
title('White noise - a realisation');
xlabel('Normalized time');
ylabel('Noise amplitude');
hold on;

subplot(2,1,2);
plot(1:length(zg),zg,'r');
axis tight;
title(strcat('Colored noise (ARMA [',num2str(na),',',num2str(nc),'] )'));
xlabel('Normalized time');
ylabel('Noise amplitude');
hold off;

%reprezentarea grafica a densitatilor spectrale pentru seia de timp si
%zgomotul colorat

modelA=model.A;
modelC=model.C;

[phi_serie,phi_zg,omega]=densitate_spectrala(e,A,C,modelA,modelC,y,lambda2);
                         
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% FIGURA 5 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%

figure(5);
plot(omega/(2*pi),phi_serie,'r');
title('Power spectru density (PSD) of the series');
xlabel('Normalized frequency');
ylabel('PSD amplitude [dB]');
axis tight;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% FIGURA 6 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%

figure(6);
plot(omega/(2*pi),phi_zg,'r');
title('Power spectru density (PSD) of the colored noise');
xlabel('Normalized frequency');
ylabel('PSD amplitude [dB]');
axis tight;

%reprezentarea grafica a spectrelor de putere

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% FIGURA 7 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%pentru seria de timp si zgomotul colorat
Xfft_f=bitrevorder(fft_f(y));
Xfft=fft(y);
Zgfft_f=bitrevorder(fft_f(zg'));
Zgfft=fft(zg);

figure(7);
unitx=linspace(0,1,length(Xfft_f));
subplot(3,1,1);
fft_f_serie=10*log10(abs(Xfft_f));
plot(unitx,fft_f_serie,'b');
axis tight;
grid on;
title('Spectrul seriei de timp evaluat cu algoritmul FFT bazat pe segmentarea semnalului in frecventa');
%xlabel('Frecventa normalizata');
ylabel('Spectru [dB]');
hold on;



subplot(3,1,2);
fft_serie=10*log10(abs(Xfft));
plot(unitx,fft_serie,'r');
axis tight;
grid on;
title('Spectrul seriei de timp evaluat cu functia FFT din MATLAB ');
%xlabel('Frecventa normalizata');
ylabel('Spectru [dB]');
hold on;

subplot(3,1,3);
eroare_spec=fft_f_serie-fft_serie;
plot(unitx,eroare_spec,'r');
axis tight;
grid on;
title('Eroarea spectrala');
xlabel('Frecventa normalizata');
ylabel('Eroare [dB]');
hold off;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% FIGURA 9 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%pentru zgomotul colorat

figure(9);
unitx2=linspace(0,1,length(Zgfft_f));
subplot(3,1,1);
fft_f_zg=10*log10(abs(Zgfft_f));
plot(unitx2,fft_f_zg,'b');
axis tight;
grid on;
title('Spectrul zgomotului colorat evaluat cu algoritmul FFT bazat pe segmentarea semnalului in frecventa');
%xlabel('Frecventa normalizata');
ylabel('Spectru [dB]');
hold on;



subplot(3,1,2);
fft_zg=10*log10(abs(Zgfft));
plot(unitx2,fft_zg,'r');
axis tight;
grid on;
title('Spectrul zgomotului colorat evaluat cu functia FFT din MATLAB ');
%xlabel('Frecventa normalizata');
ylabel('Spectru [dB]');
hold on;

subplot(3,1,3);
eroare_spec_zg=fft_f_zg-fft_zg';
plot(unitx2,eroare_spec_zg,'r');
axis tight;
grid on;
title('Eroarea spectrala');
xlabel('Frecventa normalizata');
ylabel('Eroare [dB]');
hold off;

%reprezentarea grafica a fazelor

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% FIGURA 8 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%pentru seria de timp
figure(8);
subplot(3,1,1);
fft_f_sf=angle(Xfft_f);
plot(unitx,fft_f_sf,'b');
axis tight;
grid on;
title('Faza seriei de timp evaluata cu algoritmul FFT bazat pe segmentarea semnalului in frecventa');
%xlabel('Frecventa normalizata');
ylabel('Spectru [rad]');
hold on;

subplot(3,1,2);
fft_sf=angle(Xfft);
plot(unitx,fft_sf,'r');
axis tight;
grid on;
title('Faza seriei de timp evaluata cu functia FFT din MATLAB ');
%xlabel('Frecventa normalizata');
ylabel('Faza [rad]');
hold on;

subplot(3,1,3);
eroare_spec_faza=fft_f_sf-fft_sf;
plot(unitx,eroare_spec_faza,'r');
axis tight;
grid on;
title('Eroarea de faza');
xlabel('Frecventa normalizata');
ylabel('Faza [rad]');
hold off;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% FIGURA 10 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%pentru zgomotul colorat
figure(10);
subplot(3,1,1);
fft_f_zgf=angle(Zgfft_f);
plot(unitx2,fft_f_zgf,'b');
axis tight;
grid on;
title('Faza zgomotului colorat evaluat cu algoritmul FFT bazat pe segmentarea semnalului in frecventa');
%xlabel('Frecventa normalizata');
ylabel('Faza [rad]');
hold on;

subplot(3,1,2);
fft_zgf=angle(Zgfft);
plot(unitx2,fft_zgf,'r');
axis tight;
grid on;
title('Faza zgomotului colorat evaluat cu functia FFT din MATLAB ');
%xlabel('Frecventa normalizata');
ylabel('Faza [dB]');
hold on;

subplot(3,1,3);
eroare_spec_zg_faza=fft_f_zgf-fft_zgf';
plot(unitx2,eroare_spec_zg_faza,'r');
axis tight;
grid on;
title('Eroarea de faza');
xlabel('Frecventa normalizata');
ylabel('Faza [rad]');
hold off;