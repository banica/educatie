function [v, yS, P0, V] = seasonal(ysta)

%introduc in N numarul de elemente din y minus k (care e o variabila
%introdusa de la tastatura)

N = length(ysta);

for P = 2 : floor(N/2)
	L = floor(N/P);
    
    %calculez vectorul yS pentru fiecare valoare a lui P ca sa vad care P
    %este minim cu criteriul de adecvanta
	for p = 1 : P
		sum = 0;
		for k = 0 : L-1
			sum = sum + ysta(k*P + p);
		end
		ySP(p) = sum / L;
	end
	
    %calculez V(P) si prelungesc prin perioada yS folosindu-ma de variabila
    %xi care se autoincrementeaza in for si cand devine = P atunci revine
    %la valoarea 1
	sum = 0;
	xi = 1;
	for i = 1 : N
		sum = sum + (ysta(i) - ySP(xi))^2;
        if xi == P
			xi = 1;
		else
			xi = xi + 1;
		end
	end
	V(P) = sum;
	
    %calculez P0
	if P == 2
		min = V(P);
		P0 = P;
	else
		if min > V(P)
			min = V(P);
			P0 = P;
		end
	end
end

%calculez epsilon(ysta) ca sa testez daca seria are componenta sezoniera
eps = 0;
for i = 1 : N
	eps = eps + ysta(i)^2;
end

%testez daca V(P0) e mai mic decat 1/4 * epsilon(ysta)
%daca nu e, atunci ies din program afisand eroare
if V(P0) >= (1/4) * eps
	P0 = 0;
	yS = 0;	
    v = zeros(1, N);
    return;
end

%calculez yS pentru P0
L = floor(N/P0);
for p = 1 : P0
	sum = 0;
	for k = 0 : L-1
		sum = sum + ysta(k*P0 + p);
	end
	yS(p) = sum / L;
end

%evaluarea zgomotului colorat; folosesc si aici prelungirea prin perioada a
%lui yS
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


	