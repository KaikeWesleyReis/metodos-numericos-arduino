%% Arquivo exemplo para a resolucao numerica derivadas
clc; close all; clear all;

% A diferenciacao da a medida da taxa na qual uma medida varia
% A diferenciacao numerica é util quando:
     % A diferenciacao analitica da funcao é dificil ou impossivel
     % Afuncao eh dada como um conjunto de pontos discretos
% Método das diferencas finitas 3 pts
% Serao utilizadas as subrotinas:
     % difFinitas.m
     % difFinitas2.m

%% Exemplo Proposto
 
  % Observar o comportamento das derivadas (primeira e segunda)
  % da funcao f = x.^3 - 12*x
     
     % Intervalo: [0,20]
     % Comparar resultado analitico com o resultado por diferencas finitas
     % 

%% RESOLUCAO
 
   f = @(x)  x.^3 - 4*x.^2;

   % Passo e dominio
        x0 = 0;         % x0: valor inicial da variavel independente
        xf = 20;        % xf: valor final da variavel independente
        h = 2;          % h:  passo (definido pelo usuario)
        x = x0:h:xf;    % dominio (vetor com os valores discretizados de x)
        N = length(x);  % numero de elementos do vetor x (tamanho de x)  
   
        y = f(x);       % vetor com os valores de f(x)

   % Calculos
       % Derivada Analitica
           % primeira derivada
           Y = 3*x.^2 - 8*x ;
           % segunda derivada
           Y2 = 6*x - 8;
       % Diferencas Finitas 
           % primeira derivada
           ydf = D_difFinitas(x, y);
           % segunda derivada
           ydf2 = D_difFinitas2(x, y);

    

%% Graficos

plot(x, Y,'',x,ydf,'*',x,Y2,'',x,ydf2,'+')
title('Comportamento da derivada de f(x)')
xlabel('x');
legend('Resultado Analítico - primeira', 'Dif Finitas - primeira derivada','Analitico - segunda', 'Dif Finitas - segunda derivada');





