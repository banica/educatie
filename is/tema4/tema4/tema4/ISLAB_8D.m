% tema 4
%Bercan Radu 346 AA
function ISLAB_8D()

nr_fisier = 0;
while nr_fisier<1 | nr_fisier>15
nr_fisier = input('Dati setul de date de intrare (1-15): ');
end

Pmax = -1;
while Pmax<0
Pmax = input('Dati gradul polinomului Pmax (>0):');
end

Na = 0;
while Na<1 | Na>100
Na = input('Dati ordinul modelului Na (1-100):');
end

K = 0;
while K<1 | K>100
K = input('Dati marimea orizontului de predictie K (1-100):');
end


fis= sprintf('st%i', nr_fisier);eval(fis);

N=length(y);
[ypred,sigma2,yT,theta,ysta,yS,P0,v,yAR,theta_AR,e,PQ] = ts_predict(y,K,Pmax,Na);


%Grafice - 

figure(1)
plot (ntime(1:N-K),y(1:N-K),'r');
hold on
plot (ntime(1:N-K),yT(1:N-K),'g');
hold on
legend('Seria de timp', 'Tendinta');
xlabel(unit);
ylabel(yunit);
title(sprintf('%s in care p=%i',label,P0));


figure(2)
plot(ntime, ysta, 'g')
hold on;
plot(ntime,yS,'r')
hold on;
xlabel(unit);
ylabel(yunit);
title(label);
if(yS==0)
legend('Seria stationarizata','Nu are componenta sezoniera!')
else
legend('Seria stationarizata','Componenta sezoniera')
end

lambda2e=sigma2(2);
lambda2y=sum(y.^2)/length(y);
SNR=lambda2y/lambda2e;


figure(3)
plot (ntime(1:N-K),yAR(1:N-K),'b');
hold on
plot (ntime(1:N-K),v(1:N-K),'r');
hold on
legend('Zgomotul colorat', 'Componenta aleatoare');
xlabel(unit);
ylabel(yunit);
title(sprintf('SNR=%i',SNR));

figure(4)
disp=sum(v.^2)/length(v);
disp=sqrt(disp);
plot (ntime(1:N-K),e(1:N-K),'g');
hold on
plot (ntime(1:N-K),disp,'k');
titlu=sprintf('Dispersia=%f',disp);
xlabel(unit);
ylabel(yunit);
title(titlu);


figure(5)
p=length(theta)-1;
na=length(theta_AR);
surf(PQ);
title(sprintf('Maxim=%f',PQ(p,na)));


figure(6)
sigmak=sigma2.^(1/2);
plot (ntime(N-K:N),y(N-K:N),'g');
hold on
plot (ntime(N-K:N),ypred(N-K:N),'b');
hold on
plot (ntime(N-K:N),ypred(N-K:N)+3*sigmak,'r');
hold on
plot (ntime(N-K:N),ypred(N-K:N)-3*sigmak,'r');
legend('Date masurate', 'Date predictie','Tub incredere');