clear
clc
I0 = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0; 0 9 9 9 9 9 9 9 9 9 9 9 9 9 0; 0 9 1 9 9 0 1 9 9 9 9 1 4 9 0; 0 9 9 9 9 9 9 9 9 9 9 0 9 9 0; 0 9 9 9 9 9 9 9 9 9 9 9 9 9 0; 0 9 2 9 9 0 0 0 0 0 9 9 9 9 0; 0 9 1 9 9 0 0 8 0 0 9 9 0 9 0; 0 9 0 9 9 0 0 9 0 0 9 9 9 9 0; 0 9 9 9 9 0 0 0 0 0 9 9 9 9 0; 0 9 9 9 9 0 0 0 0 0 9 9 9 9 0; 0 9 2 9 9 9 0 0 0 9 9 9 0 9 0; 0 9 1 9 9 9 0 8 0 9 9 1 0 9 0; 0 9 9 9 9 9 0 0 0 9 9 9 9 9 0; 0 9 9 9 9 9 0 0 0 9 9 9 9 9 0; 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]
[m,n]=size(I0);

%eliminare zgomot din I0 utilizand filtrul bazat pe valoare medie
%neponderata FM1. Rezultatul e I1.
for i=1:m
    for j=1:n
      I1(i,j) = matr(i,j,I0,m,n)+matr(i-1,j-1,I0,m,n)+matr(i-1,j,I0,m,n)+matr(i-1,j+1,I0,m,n)+matr(i,j+1,I0,m,n)+matr(i+1,j+1,I0,m,n)+matr(i+1,j,I0,m,n)+matr(i+1,j-1,I0,m,n)+matr(i,j-1,I0,m,n);  
      I1(i,j) = I1(i,j)/9;     
    end
end
display('1. Eliminarea zgomotului folosind FM1.');
I1

%eliminare zgomot din I0 utilizand filtrul bazat pe valoare medie
%ponderata FM2. Rezultatul e I2.
for i=1:m
    for j=1:n
      I2(i,j) = 2*matr(i,j,I0,m,n)+matr(i-1,j-1,I0,m,n)+matr(i-1,j,I0,m,n)+matr(i-1,j+1,I0,m,n)+matr(i,j+1,I0,m,n)+matr(i+1,j+1,I0,m,n)+matr(i+1,j,I0,m,n)+matr(i+1,j-1,I0,m,n)+matr(i,j-1,I0,m,n);  
      I2(i,j) = I2(i,j)/10;     
    end
end
display('2. Eliminarea zgomotului folosind FM2.');
I2

%eliminare zgomot din I0 utilizand filtrul bazat pe valoare medie
%ponderata FM3. Rezultatul e I3.
for i=1:m
    for j=1:n
      I3(i,j) = 4*matr(i,j,I0,m,n)+matr(i-1,j-1,I0,m,n)+2*matr(i-1,j,I0,m,n)+matr(i-1,j+1,I0,m,n)+2*matr(i,j+1,I0,m,n)+matr(i+1,j+1,I0,m,n)+2*matr(i+1,j,I0,m,n)+matr(i+1,j-1,I0,m,n)+2*matr(i,j-1,I0,m,n);  
      I3(i,j) = I3(i,j)/16;     
    end
end
display('3. Eliminarea zgomotului folosind FM3.');
I3

%eliminare zgomot din I0 utilizand vecinatatile de 5 puncte
%succesiv de 2 ori. Rezultatul e I4_ si I4.
for i=1:m
    for j=1:n
          vector_sortare = [matr(i,j,I0,m,n) matr(i-1,j,I0,m,n) matr(i,j+1,I0,m,n) matr(i+1,j,I0,m,n) matr(i,j-1,I0,m,n)];
          vector_sortare = sort(vector_sortare);
          I4_(i,j) = vector_sortare(3);
    end
end
for i=1:m
    for j=1:n
          vector_sortare = [matr(i,j,I4_,m,n) matr(i-1,j,I4_,m,n) matr(i,j+1,I4_,m,n) matr(i+1,j,I4_,m,n) matr(i,j-1,I4_,m,n)];
          vector_sortare = sort(vector_sortare);
          I4(i,j) = vector_sortare(3);
    end
end
display('4. Eliminarea zgomotului folosind vecinatatile de 5 puncte.');
I4_
I4

%binarizarea lui I0 cu un prag P convenabil ales astfel incat imaginea
%obtinuta I5 sa se apropie cat mai mult de imaginea ideala
P = 1;
for i=1:m
    for j=1:n
        if(I0(i,j) >= P)            
            I5(i,j) = 1;            
        else
            I5(i,j) = 0;
        end
    end
end
display('5. Binarizarea lui I0 cu pragul P = 1.');
I5

%eliminarea zgomotului din I5 folosind filtru de netezire logica 
%(filtru binar)
for i=1:m
    for j=1:n
        if(matr(i,j,I5,m,n) == 1 & matr(i-1,j,I5,m,n) == 0 & matr(i-1,j+1,I5,m,n) ==0 & matr(i,j+1,I5,m,n) == 0 & matr(i+1,j+1,I5,m,n) == 0 & matr(i+1,j,I5,m,n) == 0 & matr(i+1,j-1,I5,m,n) == 0 & matr(i,j-1,I5,m,n) == 0 & matr(i-1,j-1,I5,m,n) == 0)
            I6(i,j) = 0;
        else
            I6(i,j) = I5(i,j);
        end
    end
end
for i=1:m
    for j=1:n
        if(matr(i,j,I5,m,n) == 0 & matr(i-1,j,I5,m,n) == 1 & matr(i-1,j+1,I5,m,n) == 1 & matr(i,j+1,I5,m,n) == 1 & matr(i+1,j+1,I5,m,n) == 1 & matr(i+1,j,I5,m,n) == 1 & matr(i+1,j-1,I5,m,n) == 1 & matr(i,j-1,I5,m,n) == 1 & matr(i-1,j-1,I5,m,n) == 1)
            I6(i,j) = 1;
        else
            I6(i,j) = I5(i,j);
        end
    end
end
display('6. I5 folosind filtru de netezire logica este');
I6

%histograma lui I1 si binarizarea lui I1 cu un prag P convenabil ales 
%astfel incat imaginea obtinuta I7 sa se apropie cat mai mult de 
%imaginea ideala
for k=1:1:9
    vector(k) = 0;
    for i=1:m
        for j=1:n
            if(I1(i,j) == k)                
                vector(k) = vector(k)+1;
            end                
        end
    end
end
figure(1);
stem(vector)
xlabel('Nuantele de gri');
ylabel('Numarul de aparitii');
title('Histograma lui I1');

P = 4;
for i=1:m
    for j=1:n
        if(I1(i,j) >= P)            
            I7(i,j) = 1;            
        else
            I7(i,j) = 0;
        end
    end
end
display('7. Binarizarea lui I1 cu pragul P = 4.');
I7

%histograma lui I2 si binarizarea lui I2 cu un prag P convenabil ales 
%astfel incat imaginea obtinuta I8 sa se apropie cat mai mult de 
%imaginea ideala
for k=1:1:9
    vector(k) = 0;
    for i=1:m
        for j=1:n
            if(I2(i,j) == k)                
                vector(k) = vector(k)+1;
            end                
        end
    end
end
figure(2);
stem(vector)
xlabel('Nuantele de gri');
ylabel('Numarul de aparitii');
title('Histograma lui I2');

P = 4;
for i=1:m
    for j=1:n
        if(I2(i,j) >= P)            
            I8(i,j) = 1;            
        else
            I8(i,j) = 0;
        end
    end
end
display('8. Binarizarea lui I2 cu pragul P = 4.');
I8

%histograma lui I3 si binarizarea lui I3 cu un prag P convenabil ales 
%astfel incat imaginea obtinuta I9 sa se apropie cat mai mult de 
%imaginea ideala
for k=1:1:9
    vector(k) = 0;
    for i=1:m
        for j=1:n
            if(I3(i,j) == k)                
                vector(k) = vector(k)+1;
            end                
        end
    end
end
figure(3);
stem(vector)
xlabel('Nuantele de gri');
ylabel('Numarul de aparitii');
title('Histograma lui I3');

P = 4;
for i=1:m
    for j=1:n
        if(I3(i,j) >= P)            
            I9(i,j) = 1;            
        else
            I9(i,j) = 0;
        end
    end
end
display('9. Binarizarea lui I3 cu pragul P = 4.');
I9

%histograma lui I4 si binarizarea lui I4 cu un prag P convenabil ales 
%astfel incat imaginea obtinuta I10 sa se apropie cat mai mult de 
%imaginea ideala
for k=1:1:9
    vector(k) = 0;
    for i=1:m
        for j=1:n
            if(I4(i,j) == k)                
                vector(k) = vector(k)+1;
            end                
        end
    end
end
figure(4);
stem(vector)
xlabel('Nuantele de gri');
ylabel('Numarul de aparitii');
title('Histograma lui I4');

P = 9;
for i=1:m
    for j=1:n
        if(I4(i,j) >= P)            
            I10(i,j) = 1;            
        else
            I10(i,j) = 0;
        end
    end
end
display('10. Binarizarea lui I4 cu pragul P = 9.');
I10

%sa se aleaga cea mai buna imagine intre I6,I7,I8,I9,I10
Img_ideala = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0; 0 1 1 1 1 1 1 1 1 1 1 1 1 1 0; 0 1 1 1 1 1 1 1 1 1 1 1 1 1 0; 0 1 1 1 1 1 1 1 1 1 1 1 1 1 0; 0 1 1 1 1 1 1 1 1 1 1 1 1 1 0; 0 1 1 1 1 0 0 0 0 0 1 1 1 1 0; 0 1 1 1 1 0 0 0 0 0 1 1 1 1 0; 0 1 1 1 1 0 0 0 0 0 1 1 1 1 0; 0 1 1 1 1 0 0 0 0 0 1 1 1 1 0; 0 1 1 1 1 0 0 0 0 0 1 1 1 1 0; 0 1 1 1 1 1 0 0 0 1 1 1 1 1 0; 0 1 1 1 1 1 0 0 0 1 1 1 1 1 0; 0 1 1 1 1 1 0 0 0 1 1 1 1 1 0; 0 1 1 1 1 1 0 0 0 1 1 1 1 1 0; 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
for k=1:5
    diferente(k) = 0;
end
for i=1:m
    for j=1:n
        if(I6(i,j) ~= Img_ideala(i,j))
            diferente(1) = diferente(1) + 1;
        end
    end
end
for i=1:m
    for j=1:n
        if(I7(i,j) ~= Img_ideala(i,j))
            diferente(2) = diferente(2) + 1;
        end
    end
end

for i=1:m
    for j=1:n
        if(I8(i,j) ~= Img_ideala(i,j))
            diferente(3) = diferente(3) + 1;
        end  
    end
end

for i=1:m
    for j=1:n
        if(I9(i,j) ~= Img_ideala(i,j))
            diferente(4) = diferente(4) + 1;
        end
    end
end

for i=1:m
    for j=1:n
        if(I10(i,j) ~= Img_ideala(i,j))
            diferente(5) = diferente(5) + 1;
        end
    end
end
vector = sort(diferente);
min = vector(1);

for k=1:5
    if(diferente(k) == min)
        if k == 1
            display('11. Cea mai apropiata de imaginea ideala este imaginea I6');
            I6
        end
        if k == 2
            display('11. Cea mai apropiata de imaginea ideala este imaginea I7');
            I11 = I7;
            I11
        end
        if k == 3
            display('11. Cea mai apropiata de imaginea ideala este imaginea I8');
            I11 = I8;
            I11
        end
        if k == 4
            display('11. Cea mai apropiata de imaginea ideala este imaginea I9');
            I11 = I9;
            I11
        end
        if k == 5
            display('11. Cea mai apropiata de imaginea ideala este imaginea I10');
            I11 = I10;
            I11
        end
    end
end

%utilizand filtrul Roberts 2x2 se determina conturul din I4 punand in
%evidenta matricile intermediare
for i=1:m
    for j=1:n
        R1(i,j) = matr(i+1,j,I4,m,n) - matr(i,j+1,I4,m,n);
    end
end
display('12.a) Matricea R1 este de forma urmatoare');
R1

for i=1:m
    for j=1:n
        R2(i,j) = matr(i+1,j+1,I4,m,n) - matr(i,j,I4,m,n);
    end
end
display('12.b) Matricea R2 este de forma urmatoare');
R2

for i=1:m
    for j=1:n
        A(i,j) = round(sqrt(double((R1(i,j)^2) + (R2(i,j)^2))));
    end
end
display('12.c) Matricea A este sub forma urmatoare');
A

P = 4;
for i=1:m
    for j=1:n
        if(A(i,j) >= P)
            I12(i,j) = 1;
        else
            I12(i,j) = 0;
        end
    end
end
display('12.d) Matricea I12 este sub forma urmatoare');
I12

%determinam conturu folosind filtru binar cu vecinatati de 5 
%puncte din I11
for i=1:m
    for j=1:n
        if(matr(i,j,I11,m,n) == 1 & matr(i-1,j,I11,m,n) == 1 & matr(i,j+1,I11,m,n) == 1 & matr(i+1,j,I11,m,n) == 1 & matr(i,j-1,I11,m,n) == 1)
            I13(i,j) = 0;
        else
            I13(i,j) = I11(i,j);
        end
    end
end
display('13. Conturul lui I11 cu filtru binar cu 5 vecinatati este');
I13

%determinam aria lui I11 direct
suma_unu = 0;
for i=1:m
    for j=1:n
        if(I11(i,j) == 1)
            suma_unu = suma_unu + 1;
        else
            suma_unu = suma_unu + 0;
        end
    end
end
display('14. Aria lui I11 calculata direct este');
Aria = suma_unu;
Aria

%determinam perimetrul din I13 direct
suma_unu = 0;
for i=1:m
    for j=1:n
        if(I13(i,j) == 1)
            suma_unu = suma_unu + 1;
        else
            suma_unu = suma_unu + 0;
        end
    end
end
display('15. Perimetrul lui I13 calculat direct este');
Perimetru = suma_unu;
Perimetru

%calculam aria si perimetrul lui I11 utilizand forme patratice binare
n1 = 0;
n2 = 0;
n3 = 0;
n4 = 0;

for i=1:m-1
    for j=1:n-1
        if((I11(i,j) == 1 & I11(i,j+1) == 0 & I11(i+1,j+1) == 0 & I11(i+1,j) == 0) | (I11(i,j) == 0 & I11(i,j+1) == 1 & I11(i+1,j+1) == 0 & I11(i+1,j) == 0) | (I11(i,j) == 0 & I11(i,j+1) == 0 & I11(i+1,j+1) == 0 & I11(i+1,j) == 1) | (I11(i,j) == 0 & I11(i,j+1) == 0 & I11(i+1,j+1) == 1 & I11(i+1,j) == 0))
            n1 = n1+1;
        end
    end
end
for i=1:m-1
    for j=1:n-1
        if((I11(i,j) == 1 & I11(i,j+1) == 1 & I11(i+1,j+1) == 0 & I11(i+1,j) == 0) | (I11(i,j) == 1 & I11(i,j+1) == 0 & I11(i+1,j+1) == 0 & I11(i+1,j) == 1) | (I11(i,j) == 0 & I11(i,j+1) == 1 & I11(i+1,j+1) == 1 & I11(i+1,j) == 0) | (I11(i,j) == 0 & I11(i,j+1) == 0 & I11(i+1,j+1) == 1 & I11(i+1,j) == 1))
            n2 = n2+1;
        end
    end
end
for i=1:m-1
    for j=1:n-1
        if((I11(i,j) == 1 & I11(i,j+1) == 1 & I11(i+1,j+1) == 0 & I11(i+1,j) == 1) | (I11(i,j) == 1 & I11(i,j+1) == 1 & I11(i+1,j+1) == 1 & I11(i+1,j) == 0) | (I11(i,j) == 0 & I11(i,j+1) == 1 & I11(i+1,j+1) == 1 & I11(i+1,j) == 1) | (I11(i,j) == 1 & I11(i,j+1) == 0 & I11(i+1,j+1) == 1 & I11(i+1,j) == 1))
            n3 = n3+1;
        end
    end
end
for i=1:m-1
    for j=1:n-1
        if(I11(i,j) == 1 & I11(i,j+1) == 1 & I11(i+1,j+1) == 1 & I11(i+1,j) == 1)
            n4 = n4+1;
        end
    end
end
Aria = (n1/4)+((2*n2)/4)+((3*n3)/4)+((4*n4)/4);
display('16.a) Aria lui I11 calculata cu forme binare patratice este');
n1
n2
n3
n4
Aria

Perimetru = round(n2 + n3*sqrt(2));

display('16.b) Perimetrul lui I11 calculat cu forme binare patratice este');
Perimetru

%determinarea centrului de greutate a imaginii I11
nrlinii = 0;
I = 0;
for i=1:m-1
    for j=1:n
        if(I11(i+1,j) == 1)
            nrlinii = nrlinii + 1;
        end        
    end    
    nrlinii = i * nrlinii;
    I = I + nrlinii;
    nrlinii = 0;
end
nrcoloane = 0;
J = 0;
for j=1:n-1
    for i=1:m
        if(I11(j+1,i) == 1)
            nrcoloane = nrcoloane + 1;
        end        
    end
    nrcoloane = j * nrcoloane;
    J = J + nrcoloane;
    nrcoloane = 0;
end
IG = round(I/Aria);
JG = round(J/Aria);

display('17. Centrul de greutate alui I11 e de coordonate');
IG
JG

%determinarea razei minime/maxime/medii pe baza a ce s-a obtinut mai sus
%pentru I11
raza_med = 0;
raza = 0;
while ((IG + raza) <= m | (IG - raza) >= 1 | (JG + raza) <= n | (JG - raza) >= 1)    
       if(I13(IG+raza,JG) ~= 1)
            raza = raza + 1;
       else
            raza_min(1) = raza;
            break;
       end 
end
raza = 0;
while ((IG + raza) <= m | (IG - raza) >= 1 | (JG + raza) <= n | (JG - raza) >= 1)    
       if(I13(IG-raza,JG) ~= 1)
            raza = raza + 1;
       else
            raza_min(2) = raza;
            break;
       end 
end
raza = 0;
while ((IG + raza) <= m | (IG - raza) >= 1 | (JG + raza) <= n | (JG - raza) >= 1)    
       if(I13(IG,JG+raza) ~= 1)
            raza = raza + 1;
       else
            raza_min(3) = raza;
            break;
       end 
end
raza = 0;
while ((IG + raza) <= m | (IG - raza) >= 1 | (JG + raza) <= n | (JG - raza) >= 1)    
       if(I13(IG,JG-raza) ~= 1)
            raza = raza + 1;
       else
            raza_min(4) = raza;
            break;
       end 
end
raza_min = sort(raza_min);
display('18.a) Raza minima a imaginii I11 folosind I13 este');
raza_minima = raza_min(2);
raza_minima

raza = 0;
while ((IG + raza) <= m | (IG - raza) >= 1 | (JG + raza) <= n | (JG - raza) >= 1)
       if(I13(IG+raza,JG+raza) ~= 1)
            raza = raza + 1;
       else
            raza_max(1) = round(raza*sqrt(2));
            break;
       end 
end
raza = 0;
while ((IG + raza) <= m | (IG - raza) >= 1 | (JG + raza) <= n | (JG - raza) >= 1)
       if(I13(IG-raza,JG-raza) ~= 1)
            raza = raza + 1;
       else
            raza_max(2) = round(raza*sqrt(2));
            break;
       end 
end
raza = 0;
while ((IG + raza) <= m | (IG - raza) >= 1 | (JG + raza) <= n | (JG - raza) >= 1)
       if(I13(IG-raza,JG+raza) ~= 1)
            raza = raza + 1;
       else
            raza_max(3) = round(raza*sqrt(2));
            break;
       end 
end
raza = 0;
while ((IG + raza) <= m | (IG - raza) >= 1 | (JG + raza) <= n | (JG - raza) >= 1)
       if(I13(IG+raza,JG-raza) ~= 1)
            raza = raza + 1;
       else
            raza_max(4) = round(raza*sqrt(2));
            break;
       end
end
raza_max = sort(raza_max);
display('18.b) Raza maxima a imaginii I11 folosind I13 este');
raza_maxima = raza_max(4);
raza_maxima

raza = 0;
for i=1:m
    for j=1:n
        if I13(i,j) == 1
            raza = raza + 1;
            raza_med = raza_med + ((IG-i)^2+(JG-j)^2)^(1/2);
        end
    end
end
raza_med = raza_med / raza;
raza_med = round(raza_med);
display('18.c) Raza medie a imaginii I11 folosind I13 este');
raza_medie = raza_med;
raza_medie
            