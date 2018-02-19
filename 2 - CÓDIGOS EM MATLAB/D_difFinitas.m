%% Funcao para a resolucao numericas de derivadas por diferencas finitas

function [ dydx ] = difFinitas(x, y)

N = length(y);  % tamanho do vetor y (numero de pontos)
dydx = zeros(1,N);

% Progressiva 3pts
dydx(1) = (-3*y(1) + 4*y(2) - y(3))/(x(3) - x(1));  
% Central
for i = 2:(N-1)
    dydx(i) = (y(i+1) - y(i-1))/(x(i+1)-x(i-1));
end
% Regressiva 3pts
dydx(N) = (3*y(N) - 4*y(N-1) + y(N-2))/(x(N)-x(N-2));

end

