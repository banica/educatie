function [ypred,sigma2,yT,theta,ysta,yS,P0,v,yAR,theta_AR,e,PQ] = ts_predict(y,K,Pmax,Na)

N=length(y)-K;

sigmay=0;
med = mean(y);
for n=1:N
    sigmay=sigmay+(y(n)-med)^2;
end
sigmay=(sigmay/N)^(1/2);


for p=1:Pmax;
    [ysta,yT,theta] = trend(y(1:N),p);
    [v,yS,P,V] = seasonal(ysta);
for na=1:Na
    [e,lambda2,yAR,theta_AR] = stochastic(v,na);  
%theta_AR=theta(na);
    for k=1:K
    %calculez yTextra
    a=1;
    for o=1:p;
    a=[a (N+K)^o];
    end
    yT(N+k)= a*theta;
    %calculez ySextra
    if P~=0
       if mod(N+k,P)==0
        yS(N+k)= yS(P);
       else
        yS(N+k)=yS(mod(N+k,P));
       end 
    end          
end
  
        
for k=1:K
    yAR(N+k)=0;
    vr=N+K-1;
    for i=N+k-1:N+k-na 
        if i>n
        yAR(N+k)=yAR(N+k)-theta_AR(N+k-i,na)*yAR(i);
        vr=i;
        end
    end
    for j=vr+1:N+k-na
        if j>0
        yAR(N+k)=yAR(N+k)-theta_AR(N+k-j,na)*v(j);
    end
    end
end             
sigma2(1)=0;
l=length(theta_AR(:,na));
for o = 1:K
    aux(o)=0;
    falfa(o) = 0;
end
aux(1) = 1;
falfa(1) =1;
for i=2:K
    poli=[zeros(1,i-2) theta_AR(1:min(l,K-i+2),na) zeros(1,K-l-i+2)];   
    aux=aux-falfa(i-1)*poli;
    falfa(i)=aux(i);
end
for k=2:K+1
    sigma2(k)=sigma2(k-1)+lambda2^2*falfa(k-1);
end

ypred=yT+yS+yAR;

suma=0;
for k=1:K
    suma=sigma2(k+1)*abs(ypred(N+k)-y(N+k)) + suma;
end

per(na)=P;
PQ(p,na)=100/(1+suma/(sigmay*sum(sigma2)));

end
end
m = PQ(1,1);
p0 = 1;
na0 = 1;
for o1 = 1:Pmax
    for o2 = 1:Na
        if (m < PQ(o1,o2))
            m = PQ(o1,o2);
            p0 = o1;
            na0 = o2;
        end
    end
end
P0=per(na0);

sigma2(1)=0;
l=length(theta_AR);

for o = 1:K
    rez(o)=0;
    falfa(o) = 0;
end
rez(1) = 1;
falfa(1) =1;
for i=2:K
    poli=[zeros(1,i-2) theta_AR(1:min(l,K-i+2)) zeros(1,K-l-i+2)];   
    aux=aux-falfa(i-1)*poli;
    falfa(i)=aux(i);
end
for k=2:K+1
    sigma2(k)=sigma2(k-1)+lambda2^2*falfa(k-1);
end


[ysta,yT,theta] = trend(y,p0);
[v,yS,P0,V] = seasonal(ysta);
[e,lambda2,yAR,theta_AR] = stochastic(v,na0);
%theta_AR=theta(na);
end



