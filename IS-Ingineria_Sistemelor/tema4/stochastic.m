function [e, lambda2, yAR, thetaAR] = stochastic(v, na)

N = length(v);

if na < 1
	na = 1;
end	

%calculeez rv
for i = 0 : na
    sum = 0;
    for j = i + 1 : N
        sum = sum + v(j) * v(j - i);
    end
    rv(i + 1) = (1 / (N - i)) * sum;
end

a(1, 1) = -(rv(2) / rv(1));

lambda2 = rv(1) * (1 - a(1, 1)^2);

thetaAR(1) = a(1, 1);

%calculez thaetaAR recursiv
for p = 2 : na
    thetap = [];
    
    sum = 0;
    for i = 0 : p - 1
        if i == 0
            sum = sum + rv(p - i + 1);
        else
            sum = sum + a(p-1, i) * rv(p - i + 1);
        end
    end
    
    kp = -(1 / lambda2) * sum;
    
    a(p, p) = kp;
    
    for i = 1 : p - 1
        a(p, i) = a(p-1, i) + a(p, p) * a(p-1, p-i);
        thetap = [thetap; a(p-1, p-i)];
    end
    
    thetaAR = [thetaAR; 0] + kp * [thetap; 1];
    
    lambda2 = lambda2 * (1 - kp^2);
end


yAR(1) = 0;

%calculez yAR recursiv
for n = 2 : N
    sum = 0;
    if n <= na
        for i = 1 : n - 1
            sum = sum - a(na, i) * v(n - i);
        end
    else
        for i = 1 : na
            sum = sum - a(na, i) * v(n - i);
        end
    end
    yAR = [yAR, sum];
    e(n) = v(n) - yAR(n);
end
