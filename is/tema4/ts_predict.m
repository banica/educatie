function [ypred, sigma2, yT, theta, ysta, yS, P0, v, yAR, theta_AR, e, PQ] = ts_predict(y, K, Pmax, Na)

N = length(y) - K;

med_y = min(y);


%calcul sigma_y%
sum=0;
for i=1:N
        sum=sum+y(i);
end
sum=sum/N;
sigma_y=0;
for i=1:N
    sigma_y=(y(i)-sum)^2;
end
sigma_y=sqrt(sigma_y/N);
%calcul sigma_y%


yAR_extra=zeros(N+K+Na);
ypred=zeros(N+K+Na);

for p = 0 : Pmax
    
    ysta = 0;
    yT = 0;
    theta = 0;
    v = 0;
    yS = 0;
    P0 = 0;
    V = 0;
    
	[ysta, yT, theta] = trend(y, p, K);
	[v, yS, P0, V] = seasonal(ysta);
    
    if P0 == 0
        yS = y;
        v = zeros(1, N);
        xi = 1;
        for i = 1 : N
	        v(i) = ysta(i) - yS(xi);
	        if xi == P0
		        xi = 1;
	        else
		    xi = xi + 1;
	        end
        end
    end
	
	yT_extra = yT;
	yS_extra = yS;
	for i=1:N
        yAR_extra(i) = v(i);
    end
	
	for na = 1 : Na
        yS_extra = 0;
        yT_extra = 0;
        sigma2 = 0;
    
        
		[e, lambda2, yAR, thetaAR] = stochastic(v, na);

		for t = N + 1 : N + K
			yT_extra(t) = 0;
			for i = 1 : p + 1
				yT_extra(t) = yT_extra(t) + theta(i) * t^(i-1);
			end
		end
		
		xi = 1;
		for i = 1 : N + K
			yS_extra(i) = yS(xi);
			if xi == P0
				xi = 1;
			else
				xi = xi + 1;
			end
		end
		
		for k = 1 : na
			sum=0;
            for lol=1:na
                sum=sum+thetaAR(lol)*yAR_extra(N+k-lol+1);
            end
            sum=-sum;
            vv=0;
            
            sum=sum-vv;
            yAR_extra(N + k) = sum;
		end
		
		for k = na+1:K
            sum=0;
            for lol=1:na
                sum=sum+thetaAR(na-lol+1)*yAR_extra(N+k-lol);
            end
            sum=-sum;
            yAR_extra(N + k) = sum;
            
        end
		alpha=calcul_alpha(thetaAR,na);
		
        sigma2(1) = 0;
        
		for k = 1 : K
			sigma2(k + 1) = sqrt(sigma2(k)^2 + lambda2^2 * alpha(k)^2);
        end

    for i=1:N
        ypred(i) = yT_extra(i) + yS_extra(i) + yAR_extra(i);
    end
				
		if na == 1 && p == 0
            sum=0;
            for k=1:K
                sum=sum+sigma2(k)*ypred(N+k)-yAR_extra(N+k);
            end
            numarator=(1 + sum);
			sum=0;
            for i=1:K
                sum=sum+sigma2(i);
            end
            numitor=sigma_y*sum;
            PQ = 100 /numarator/numitor ;
			na0 = na;
			p0 = p;
        else
            sum=0;
            for k=1:K
                sum=sum+sigma2(k)*ypred(N+k)-yAR_extra(N+k);
            end
            numarator=(1 + sum);
			sum=0;
            for i=1:K
                sum=sum+sigma2(i);
            end
            numitor=sigma_y*sum;
            
            aux = 100 /numarator/numitor;
			if aux > PQ
				PQ = aux;
				na0 = na;
				p0 = p;
			end
		end
	end
end

[ysta, yT, theta] = trend(y, p0, K);
[v, yS, P0, V] = seasonal(ysta, K);

if P0 == 0
	yS = y;
	v = zeros(1, N);
	xi = 1;
	for i = 1 : N
		v(i) = ysta(i) - yS(xi);
		if xi == P0
			xi = 1;
		else
		xi = xi + 1;
		end
	end
end
    
[e, lambda2, yAR, thetaAR] = stochastic(v, na0, K);



for t = N + 1 : N + K
	yT_extra(t) = 0;
	for i = 1 : Pmax + 1
		yT_extra(t) = yT_extra(t) + theta(i) * t^(i-1);
	end
end

xi = 1;
for i = 1 : N + K
	yS_extra(i) = yS(xi);
	if xi == P0
		xi = 1;
	else
		xi = xi + 1;
	end
end

for k = 1 : na
	yAR_extra(N + k) = - (sum(thetaAR(1 : k - 1) .* yAR_extra(N + k - 1 : -1 : N + 1)) + sum(thetaAR(k : na) .* v(N : -1 : N + k - na)));
end

for k = na + 1 : K
	yAR_extra(N + k) = - (sum(thetaAR(1 : na) .* yAR_extra(N + k - 1 : -1 : N - na)));
end

alpha=calcul_alpha(thetaAR,na);

sigma2(1) = 0;
for k = 1 : K
	sigma2(k + 1) = sigma2(k) + lambda2 * alpha(k)^2;
end

ypred = yT_extra + yS_extra + yAR_extra;





		