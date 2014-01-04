function [elem] = matr(i,j,matrice,linii,coloane)
    if((i <= 0) | (j <= 0) | (i > linii) | (j > coloane))
        elem = 0;
    else
        elem = matrice(i,j);
        elem = uint32(elem);
    end
end

