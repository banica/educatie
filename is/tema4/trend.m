function [ysta,yT,theta] = trend(y, p, K)

N = length(y) - K;

for i=1:p+1
    
    if i==1
        R=1;
        
        r(i)=0;
        for t=1:N
            r(i)=r(i)+y(t);
        end
        r(i)=r(i)/N;
        
        bm=1/sqrt(N);
    end
    
    if i~=1
		v=zeros(1,i-1);
		for j=0:i-2
			for t=1:N
				v(j+1)=v(j+1)+t^(i+j-1);
			end
			v(j+1)=v(j+1)/N;
		end
		R=[R;v];
		v(i)=0;
		for t=1:N
			v(i)=v(i)+t^(i+i-2);
		end
		v(i)=v(i)/N;
		R=[R v'];
    end
    
	if i~=p+1
	    sum=0;
	    for t=1:N
	        sum=sum+(t^i)*y(t);
	    end
	    sum=sum/N;
	    r=[r; sum];
        
        bm = [bm, bm(i)/(N^i)];
    end
end

Bm=diag(bm);

theta=Bm*(inv(Bm*R*Bm))*Bm*r;

for t=1:N
    yT(t)=0;
    for i=1:p+1
        yT(t)=yT(t)+theta(i)*t^(i-1);
    end
    ysta(t)=y(t)-yT(t); 
end

avg=0;
for t=1:N
    avg=avg+ysta(t);
end
avg=avg/N;

for t=1:N
    ysta(t)=ysta(t)-avg;
end

theta(1) = theta(1) + avg;
