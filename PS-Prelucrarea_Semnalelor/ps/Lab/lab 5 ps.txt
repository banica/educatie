function h = opt2c_tj( M, wb, ws, n0 )
% Proiectare filtru FIR trece-jos in sens CMMP cu prototip complex
% M        - ordinul filtrului
% wb, ws   - frecventele (normalizate) definind benzile de trecere, respectiv oprire
% n0       - intarzierea de grup a filtrului dorit

T = (0:M)';				% suportul filtrului
P = wb*sinc(T*wb) - ws*sinc(T*ws) + eye(size(T));
P = toeplitz(P);
q = wb*sinc((T-n0)*wb);
h = P \ q;
