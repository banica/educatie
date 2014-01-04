numeFis = input('Introdu numele fisierului:\n','s');
numeFis = [numeFis];
idx = fopen (numeFis,'rt');
if (idx < 0)
    error('Eroare la deschiderea fisiereului.');
end
eval(fscanf(idx, '%c'));

K = input('Introdu lungimea ordinului de predictie:\n');

Pmax = input('Introdu gradul maxim al polinomului de tendinta:\n');

Na = input('Introdu gradul maxim al modelului AR:\n');

N = length(y);

%lambda_y2 = disp(y);

[ypred, sigma2, yT, theta, ysta, yS, P0, v, yAR, theta_AR, e, PQ] = ts_predict(y, K, Pmax, Na);

subplot(3, 1, 1);
plot(y);
hold on
plot(yT(1 : N - K), 'r');
hold off

xlabel(['[Ts] = ', unit])
title(label)

% xlabel('Ts')
% ylabel('ysta(t)')
% legend('ysta(t)');


subplot(3, 1, 2);


subplot(3, 1, 3);


subplot(3, 2, 1);


subplot(3, 2, 2);


subplot(3, 2, 3);























% N = length(ysta) - k;
% strP0 = num2str(P0);

%evaluez dispersia pentru zgomotul colorat
% lambda = 0;
% for i = 1 : N
    % lambda = lambda + v(ntime(i))^2;
% end
% lambda = sqrt(lambda / N);
% strLambda = num2str(lambda);

%trasez graficul criteriului de adecvanta
% subplot(3, 1, 1);
% stem(V);
% xlabel('P')
% ylabel('V')
% title('Criteriul de adecvanta')
% strmin = num2str(V(P0));
% legend(['Criteriu de adecvanta'], ['min = ', strmin], ['P_0 = ', strP0])

%trasez graficele pentru ysta si pentru yS
% subplot(3, 1, 2);
% plot(ntime(1:N), ysta(1:N));

% xi = 1;
% for i = 1 : N
	% graf_yS(ntime(i)) = yS(xi);
	% if xi == P0
		% xi = 1;
	% else
		% xi = xi + 1;
	% end
% end
% hold on
% plot(ntime(1:N), graf_yS(1:N), 'r');
% hold off
% xlabel(['[Ts] = ', unit])
% legend(['ysta(t)'], ['y_S(t)'], ['P_0 = ', strP0]);

%trasez graficul zgomotului colorat
% subplot(3, 1, 3);
% plot(ntime(1:N), v(1:N));
% xlabel(['[Ts] = ', unit])
% ylabel('v(t)');
% legend(['v(t)'], ['dispersia = ', strLambda]);