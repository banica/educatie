function alpha=calcul_alpha(thetaAR, na)
alpha = zeros(1, 5);
alpha(1) = 1;

if na >= 1 
    alpha(2) = thetaAR(1);
    if na >= 2
        alpha(3) = thetaAR(1) ^2 - thetaAR(2);
        if na >= 3
            alpha(4) = thetaAR(1) * thetaAR(2) - thetaAR(3) - thetaAR(1) * alpha(3);
            if na >= 4

                alpha(5) = thetaAR(1)^4 + thetaAR(2)^2 - 3 * (thetaAR(1)^2) * thetaAR(2) + 2 * thetaAR(1) * thetaAR(3) - thetaAR(4); 
            end
        end
    end
end
