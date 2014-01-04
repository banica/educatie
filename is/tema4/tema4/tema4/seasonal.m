function [v,yS,P,V]=seasonal(ysta)
N = length(ysta);
Ts = 1;
M = N;
yS = [];


%parte intreaga-floor
for P=2:floor(M/2)
    L=floor(M/P);
    Ysta=[];
    for k=0:L-1
        for p=1:P
            Ysta(k+1,p)=ysta(k*P+p);    
        end
    end
%calculez yS si vector de adecvanta corespunzator
    yS = mean(Ysta);
    V(P)=0;
    aux = length(yS);
    for i=1:N
      V(P)=V(P)+(ysta(i)-yS(mod(i,aux)))^2;
    end    
end

%calculez P
aux_1 = V(1);
aux_2 = V(2);
V(1)=max(V)+1;
V(2)=max(V)+1;
[ceva,P0] = min(V);
V(1) = aux_1;
V(2) = aux_2;
P=P0;
Ysta=[];

%recalculez Ysta pt P-ul de mai sus
for k=0:L-1
        for p=1:P
            Ysta(k+1,p)=ysta(k*P+p);
        end
end

%calculez yS pentru P adecvat
yS = mean(Ysta);

%calculez energia si verific existenta componentei sezoniere
energie=sum(ysta.^2);
if V(P0)>=(1/4)*energie 
    display('Seria nu are componenta sezoniera!!!')
    P=0;
    yS=0;
    v=ysta;
    return;
end

aux = length(yS);
for i=1:N
    yS(i) = yS(mod(i,aux));
end
%calculez zgomotul colorat
for i=1:N
    v(i)=ysta(i)-yS(i);
end

end
