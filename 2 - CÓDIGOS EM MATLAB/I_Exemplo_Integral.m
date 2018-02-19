%%  Arquivo exemplo para a resolucao numerica de integrais
clc; close all; clear all;

% Etapas da resolucao numerica de uma integral:
      % dividir o intervalo de integracao [a,b] em subintervalos menores
      % calcular a integral ao longo de cada subintervalo
      % somar os resultados para fornecer a integra completa
% O integrando pode ser:
      % funcao analitica
      % conjunto tabulado de pontos

%% Exemplo Proposto
  
  % Integrar a funcao abaixo:
     
        % f = @(x) 0.132 + 1.56e-4.*x + 2.64e-7*(x.^2)


%% RESOLUCAO

     % Definindo Parâmetros
          % Parametros (se presentes) devem ser definidos antes da funcao f

     % Integrando (funcao ou conjunto de pontos)
          f = @(x) 0.132 + 1.56e-4.*x + 2.64e-7*(x.^2);
     
     % Limites de integracao
          a = 0;                    % a: limite inferior
          b = 200;                   % b: limite superior
          N = 30;                    % N: numero de subintervalos             
          h = (b-a)/N;            % h: passo de integracao        
          x = linspace(a, b, N+1);    % vetor x = a:h:b;
     % criando um vetor com valores de f(x)
          y = f(x);

% Calculos

     % Resolucao Analitica: 
     I = 0.132*b + 1.56e-4*(b.^2)/2 + 2.64e-7*(b.^3)/3 - 0.132*a + 1.56e-4*(a.^2)/2 + 2.64e-7*(a.^3)/3;
     
     % Metodo do Retangulo
          Ir = 0;   % valor numerico da integral (inicia em zero)
          vIr(1) = 0;
          for i =1:N
               Ir = Ir + (x(i+1)-x(i))*y(i);
               vIr(i+1) = Ir;       
          end
          % vIr - vetor da integral de f 
          % vIr(i+1) - integral de f indo de 'a' ate x(i+1)
     
     % Metodo Trapezoidal
          It = 0;      
          vIt(1) = 0;  
          for i =1:N
               It = It + (x(i+1)-x(i))*(y(i+1)+y(i))/2;
               VIt(i+1) = It;      
          end

     % Metodo de Simpson 1/3 
         
         % O passo deve ser constante
         % O numero de subintervalos 'N' deve ser par
         
         somp = 0; % somp: soma de todos y(i), para todo i par 
         somi = 0; % somi: soma de todos y(i), para todo i impar
         for i = 2:N
            if(mod(i,2) == 0)
                somp = somp + y(i);
            else
                somi = somi + y(i);
            end
         end
         Is13 = (h/3)*(y(1) + y(N) + 4*somp + 2*somi);

      
     % Metodo de Simpson 3/8 
      
         % O passo deve ser constante
         % O numero de subintervalos 'N' deve ser multiplo de 3

         som38p = 0;
         som38i = 0;
         for i = 2:N-1
            if(mod(i+1,3) == 0)
                 som38p = som38p + y(i) + y(i+1);
            else if(mod(i-1,3) == 0)
                     som38i = som38i + y(i);
                  end
            end
         end
         Is38 = ((3*h)/8)*(y(1)+ y(N)+ 3*som38p+ 2*som38i);

    % Combinacao Simpson 1/3 + 3/8 
         
         % Esta combinacao pode ser feita quando:
              % Numero de subintervalos N é impar e nao multiplo de 3
              % Exemplo: N = 5, 7, 11, 13...
         
         somcp = 0;
         somci = 0; 
         for i=5:N
             if(mod(i,2)~= 0)
                  somcp = somcp + y(i);
             else somci = somci + y(i);
             end
         end
         % Simpson 3/8 - nos 3 primeiros subintervalos, 
         % Simpson 1/3 - nos demais subintervalos
         Isc = ((3*h)/8)*(y(1)+ 3*y(2)+ 3*y(3)+ y(4)) + (h/3)*(y(4) + y(N) + 4*somcp + 2*somci);

%{
% Saida
fprintf('METODO        Valor da integral\n')
fprintf('Analítico:        %f\n', I);
if(mod(N,2)==0)
    fprintf('Retangulo:        %f\n', Ir);
    fprintf('Trapezio:         %f\n', It);
    fprintf('Simpson 1/3:      %f\n',Is13);
        if(mod(N,3)==0)
            fprintf('Simpson 3/8:      %f\n', Is38);
        else fprintf('Simpson 3/8 nao pode ser utilizado\n')
        end
else
    fprintf('Retangulo:        %f\n', Ir);
    fprintf('Trapezio:         %f\n', It);
    fprintf('Simpson 1/3 nao pode ser utilizado\n');
    if(mod(N,3)==0)
         fprintf('Simpson 3/8:       %f\n', Is38);
    else
         fprintf('Simpson 3/8 nao pode ser utilizado\n')
         fprintf('Combinacao 1/3 + 3/8:       %f\n', Isc);
    end
   
end
%}