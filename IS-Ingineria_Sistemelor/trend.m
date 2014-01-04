%calcul  R
function [ysta, yT, theta] = trend(y, p)
[tz, N] = size(y);
R = 1;
for i = 1:p
	for j = 1:i
		suma = 0;
		for k = 1:N
			suma = suma + k^j;
		end
		A(j) = suma / N;
	end
	suma = 0;
	for k = 1:N
		suma = suma + k^(i + 1);
    end
     B = A';   
	 B(j + 1) = suma / N;
     for t = 1:i + 1
         R(t, i + 1) = B(t);   
     end
     for t = 1:i + 1
         R(i + 1, t) = B(t);
     end   
end

%calcul  r


for i = 1:p
    for j = 1:i
        suma = 0;
        for k = 1:N
            suma = suma + k^(i + j-1);
        end
        A(j) = suma/N;
    end
    suma = 0;
    for k = 1:N
        suma = suma + k^(i + j);
    end
    B = A';   
    B(j + 1) = suma/N;
    for t = 1:i + 1
        r(t, i + 1) = B(t);   
    end
    for t = 1:i + 1
        r(i + 1, t) = B(t);
    end   
end

%calcul  theta (balansarea)
b = 1 / sqrt(N);

for i = 1 : p
    b = [b,  b(i) * (N^i)];
end

[B] = diag(b);

theta = B * inv(B * R * B) * B * r;

%yT = theta
yT = theta;

%ystationar
for i = 1:N
    ysta(i) = y(i);
end
for i = 1:p + 1
       ysta(i) = y(i)-yT(i);
end


suma = 0;
for i = 1:N
        suma = suma + ysta(i);
end
ys = suma / N;

for i = 1:p + 1
    ysta(i) = ysta(i)-ys;
end
yT(1) = yT(1) + ys;

