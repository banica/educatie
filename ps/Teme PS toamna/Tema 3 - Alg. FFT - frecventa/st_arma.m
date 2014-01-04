%Nume program: st_arma.m
%Identificarea seriei de timp cu un model ARMA
%Autor : Teodorescu Florentina Raluca
%Grupa: 343 AB
%Data ultimei modificari : 28.08.2008

function [model,obiect]=st_arma(y,na,nc);

%crearea unui obiect de tip DATA folosit la identificare
obiect=iddata(y',[]);

%generare model ARMA 
model=armax(obiect,[na nc]);