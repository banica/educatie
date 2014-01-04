%Nume program: gen_arma.m
%Generarea zgomotului filtrat folosind un model ARMA[na,nc]
%Autor : Teodorescu Florentina Raluca
%Grupa: 343 AB
%Data ultimei modificari : 28.08.2008

function [Z,P,e]=gen_arma(na,nc);


%Generez aleator polii si zerourile astfel incat modelul sa fie stabil si
%coeficientii reali, conform proprietatilor: "Orice polinom cu coeficienti 
%reali are un numar par de radacini complexe" si "Orice polinom cu coeficienti
%reali de grad impar are cel putin o radacina reala".


nr=ceil(rand*10)+3;%generare numar de poli reali suficient de mic

if (mod(na,2)==0) %polinomul A va avea nr par de poli reali (nr<<na)
                   %na-nr poli complex conjugati pentru ca coef sai sa fie reali
    if (mod(nr,2)~=0) 
        nr=nr-1;%il fortez sa fie numar par
    end
    for p=1:nr
        P(p)=rand*(-1)^(1+floor(2*rand)); %radacini reale
    end
    i=nr;
end

if (mod(na,2)==1)%polinomul A va avea na-nr poli complex conjugati si cel putin o radacina reala
    if (mod(nr,2)==0) 
        nr=nr+1; %nr trebuie sa fie un numar impar
    end
    for k=1:nr
        P(k)=rand*(-1)^(1+floor(2*rand)); %radacina reala
    end
    i=nr;
    
end  

while (i<=na)
    x=rand*(-1)^(1+floor(2*rand));
    y=sqrt(1-x^2)-0.1;
    P(i)=complex(x,y);
    P(i+1)=complex(x,-y);
    i=i+2;
 end

P=P';%vector coloana

%generare zerouri conform algoritmului de mai sus



nrz=ceil(rand*10)+3;%generare numar de zerouri reale suficient de mic (nrz<<nc)

if (mod(nc,2)==0) %polinomul C va avea nc-nrz zerouri complex conjugate pentru ca coef sai sa fie reali
    if (mod(nrz,2)~=0)
        nrz=nrz+1; %il fortez sa fie numar par
    end
    for z=1:nrz
        Z(z)=rand*(-1)^(1+floor(2*rand)); %radacina reala
    end
    j=nrz;
end
if (mod(nc,2)==1)%polinomul C va avea nc-1 zerouri complex conjugate si cel putin o radacina reala
    if (mod(nrz,2)==0)
        nrz=nrz-1; %il fortez sa fie numar impar
    end
    for z=1:nrz
        Z(z)=rand*(-1)^(1+floor(2*rand)); %radacina reala
    end
    j=nrz;
end  

while (j<=nc)
    a=rand*(-1)^(1+floor(2*rand));
    b=rand*(-1)^(1+floor(2*rand));
    Z(j)=complex(a,b);
    Z(j+1)=complex(a,-b);
    j=j+2;
end

Z=Z'; %vector coloana

%generarea zgomotului alb
e=randn(1024,1);
