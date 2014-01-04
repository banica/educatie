function [b,a] = but_f_tol(wb, ws, Delta_b, Delta_s)
% Proiectare filtru Butterworth pentru problema F_TOL
% wb, wb      - frecventele normalizate definind benzile
%               de trecere, respectiv oprire
% Delta_b     - toleranta in baza de trecere
% Delta_s     - toleranta in baza de oprire

Mb = 1 - Delta_b;

% transforma specificatiile in continuu
Omega_b = tan(wb*pi/2);
Omega_s = tan(ws*pi/2);

% determina parametrii filtrului Butterworth analogic
Mb2 = Mb * Mb;
Ds2 = Delta_s * Delta_s;
n = ceil( log(Mb2 * (1-Ds2) / Ds2 / (1-Mb2)) / 2 / log(Omega_s/Omega_b) );
Omega_t = Omega_b / ((1-Mb2)/Mb2)^(1/2/n);

% polii filtrului Butterworth analogic
poli_a = Omega_t * exp( -sqrt(-1) * pi / 2 / n * ( (1:2:2*n) + n ) );

% functia de transfer a filtrului Butterworth digital
zero_d = - ones(n,1);
poli_d = (1 + poli_a) ./ (1 - poli_a);
amplif = real(prod(-poli_a) / prod(1 - poli_a));

b = amplif * real(poly(zero_d));
a = real(poly(poli_d));
