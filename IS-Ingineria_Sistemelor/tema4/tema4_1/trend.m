function [y_STA,y_T,theta]=trend(y,p)

N = length(y);
M = N;
Ts = 1;
for i = 1:N
    ntime(i) = i;
end

%calcul r_n
for i = 0:p
    sum = 0;
    for ni = 1:N
        sum = sum + power(ntime(ni),i)*y(ntime(ni));
    end
    r_n(i+1,1) = (1/N)*sum;
end

%calcul R_n
for i = 0:p
    for j = 0:p
        sum = 0;
        for ni = 1:N
            sum = sum + power(ntime(ni),i+j);
        end
    R_n(i+1,j+1) = (1/N)*sum;
    end
end

%balansare
for i=0:p
            B_m(1,i+1) = 1/(power(M,i)*power(Ts,i)*sqrt(M*Ts));
end

B_m = diag(B_m);

theta = B_m*inv(B_m*R_n*B_m)*B_m*r_n;


%Y_T, Y_STA
for ni = 1:N
    y_T(ni) = 0;
    for i = 0:p
    y_T(ni) = y_T(ni) + theta(i+1)*power(ntime(ni),i);
    end
    y_STA(ni) = y(ni) - y_T(ni);
end

%media datelor stationarizate
sum = 0;
    for ni = 1:N
        sum = sum + y_STA(ntime(ni));
        y_STA_medie = (1/N)*sum;
    end
for i=1:p+1
    y_STA(i) = y_STA(i) - y_STA_medie;
end
