function [e,lambda2,yAR,theta_AR] = stochastic(v,na)

N=length(v);
for k=1:na+1
    rv(k)=(1/(N-k+1))*sumaC_1(N,k,v);
end


theta=-rv(2)/rv(1);

lambda2=rv(1)*(1-theta^2);

for p=2:na;
    
kp=-rv(p);
for i=1:p-1
kp=kp-theta(i)*rv(p-i+1);
thetaR(i)=theta(p-i);
end
kp=kp/lambda2;

theta=[theta 0]+kp*[thetaR 1];
lambda2=lambda2*(1-kp^2);
end

yAR(1)=0;
for n=2:N
yAR(n)=0;
j=n-1;
while(j>n-na & j>0)
yAR(n)=yAR(n)-theta(n-j)*v(j);
j=j-1;
end
end
e=v-yAR;
theta_AR=theta;
