%% Funcao para a resolucao numericas de derivadas segundas

function [ d2ydx2 ] = difFinitas2(x, y)

N = length(y);   % tamanho do vetor y (numero de pontos)
d2ydx2 = zeros(1,N);
% Primeiro Ponto
d2ydx2(1) = (y(3)- 2*y(2)+ y(1))/((x(2)-x(1))^2);
% Pontos 2 ao N-1
for i = 2:N-1
    d2ydx2(i) = (y(i+1)- 2*y(i)+ y(i-1))/((x(i+1)-x(i))^2);
end
% Ultimo ponto
d2ydx2(N) = (y(N)- 2*y(N-1) +y(N-2))/((x(N)-x(N-1))^2);

end

