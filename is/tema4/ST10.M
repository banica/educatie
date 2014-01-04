%
%	Fisierul de date ST10.M
%
% Numarul bolnavilor operati lunar de amigdalita la spitalul 23 August
% in perioada: ian. '82 - dec. '90.
%

	y = [5 6 31 69 90 44 19 23 16 10 8 5];
	y = [y 0 4 28 58 100 71 35 10 13 7 5 0];
	y = [y 1 1 24 87 96 80 26 15 14 6 7 4]; 
	y = [y 0 0 25 59 89 82 32 16 12 9 6 2];
	y = [y 3 3 42 101 110 94 34 26 11 7 8 4]; 
	y = [y 0 2 20 82 76 68 27 20 12 6 5 3];
	y = [y 2 3 40 55 93 76 18 15 10 10 6 5];
	y = [y 1 2 36 61 87 92 22 19 10 5 6 0];
	y = [y 0 1 28 49 67 86 41 20 8 4 7 3];

	Ts = 1 ; 
	unit = 'luna' ;
	ntime  = 1:length(y);
	label = ['Numarul bolnavilor operati de amigdalita ' ... 
	         'la Spitalul 23 August intre 1982 si 1990.'] ; 
    yunit = 'Numar lunar ' ;

%
% Autor:        Dan Stefanoiu
% Data:         30.10.1992 
% Reactualizat: 08.04.2005
%