function [e,lambda2,yAR,theta_AR] = stochastic(v,na)
N=length(v);
for k=1:na+1
  sum=0;
    for n=k+1:N
        sum=sum+v(n)*v(n-k+1);
    end 
  rv(k)=sum/(N-k+1);
end

for i=1:na
    theta_AR(i,1)=0;
    theta_AR_R(i,1)=0;
end

theta_AR(1,1)=-rv(2)/rv(1);
lambda2(1)=rv(1)*(1-theta_AR(1,1)^2);


for p=2:na;
 kp=-rv(p);
    for i=1:p-1
    kp=kp-theta_AR(i,p-1)*rv(p-i+1);
    theta_AR_R(i,p-1)=theta_AR(p-i,p-1);
    end
 kp=kp/lambda2(p-1);
 theta_AR(:,p)=theta_AR(:,p-1)+kp*[theta_AR_R(1:(p-1),p-1);1;theta_AR_R((p+1):na,p-1)];
 lambda2(p)=lambda2(p-1)*(1-kp^2);
end

yAR(1)=0;
for n=2:N
    yAR(n)=0;
    for i=1:na
        if i<n
            yAR(n)=yAR(n)- theta_AR(i,na)*v(n-i);
        end
    end
end
e=v-yAR;