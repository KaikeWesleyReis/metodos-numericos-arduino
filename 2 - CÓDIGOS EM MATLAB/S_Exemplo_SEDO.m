%% Arquivo exemplo para a resolucao de um sistema de até 4 EDOs 
clc; clear all; close all;

% EDOs descrevem diversos processos modelados por taxa de variacao
% Quando esses processos envolvem varias variaveis dependentes que afetam
% umas as outras, eh necessario resolver um sistema de EDOs (SEDO)

% Este codigo eh usado para resolver um SEDO:
      % de primeira ordem
      % com 2 a 4 EDOs
      % problema de valor inicial (PVI)
      
% Neste codigo, será usada a seguinte representacao:
      % f1, f2, f3, f4 - funcoes que representam as equacoes diferenciais
      % y,z,w,r - vetores das variaveis dependentes
      % x - variavel independente
      % y0,w0,z0,r0 - condicoes iniciais

% Na resolucao, utiliza-se as subrotinas sedo2.m, sedo3.m e sedo4.m

% Os seguintes metodos na forma de Runge-Kutta poderao ser escolhidos:
      % 'explicito' - Euler Simples
      % 'modificado' - Euler Modificado
      % 'pontocentral' - Ponto Central
      % 'Heun' - Runge-Kutta de segunda ordem (Heun)
      % 'Rk3' - Runge-Kutta de terceira ordem 
      % 'Rk4' - Runge-Kutta de quarta ordem 

      
%% Exemplo Proposto
  
 % Resolver o SEDO abaixo:
      
     % dydx = (- 10*z + 10*r - 5*y + 5*w + 15)/250; 
     % dzdx = y;
     % dwdx = (10*z - 18*r + 5*y - 5*w  - 14.2)/10;
     % drdx = w;

 % Considerar: 
     % Condicoes iniciais: y0 = z0 = w0 = r0 = 0 
     % x0= 0 e xf= 10;


%% RESOLUCAO
     
     % Definir o numero de EDOs do sistema
        Ne = 4;

     % Definindo parametros
        % Parametros (caso presentes) devem ser definidos antes das funcoes
        
       
     % Representando as EDOs como uma funcao:
         % f(x,y,z) - sistema de duas EDOs
         % f(x,y,z,w) - sistema de tres EDOs
         % f(x,y,z,w,r) - sistema de quatro EDOs
         
         f1 = @(x,y,z,w,r) (- 10*z + 10*r - 5*y + 5*w + 15)/250;
	     f2 = @(x,y,z,w,r) y;
         f3 = @(x,y,z,w,r) (10*z - 18*r + 5*y - 5*w - 14.2)/10;
         f4 = @(x,y,z,w,r) w;
         
     % Passo e dominio
         x0 = 0;        % x0: valor inicial da variavel independente
         xf = 10;      % xf: valor final da variavel independente
         h = 0.1;       % h:  passo (definido pelo usuario)
         x = x0:h:xf;   % dominio (vetor com os valores discretizados de x)
         N = length(x); % numero de elementos do vetor x (tamanho de x)

     % Condicoes iniciais
         y0 = 0;
         z0 = 0;
         w0 = 0;
         r0 = 0; 

%% RESOLUCAO

switch Ne
  
    case 2
        % Cálculo
        [y,z] = S_sedo2(f1,f2,x,h,y0,z0,'Rk4');

        % Gráfico
        plot(x,y,'*',x,z,'+');
        title('SOLUÇÃO DO SISTEMA');
        xlabel('x')
        legend('y(x)','z(x)');

        % Resultados
        fprintf( 'x               y                 z\n');
        for i=1:length(x)
           fprintf('%f     %f       %f\n', x(i), y(i), z(i) );
        end
        fprintf( 'x               y                 z\n');
    

    case 3 
     
        % Cálculo
        [y,z,w] = S_sedo3(f1,f2,f3,x,h,y0,z0,w0,'Rk4');
    
        % Gráfico
        plot(x,y,'*',x,z,'+', x,w,'.');
        title('SOLUÇÃO DO SISTEMA');
        xlabel('x')
        legend('y(x)','z(x)','w(x)');

        % Resultados
        fprintf( 'x               y                 z               w\n');
        for i=1:length(x)
            fprintf('%f     %f       %f       %f\n', x(i), y(i), z(i), w(i) ); 
        end
        fprintf( 'x               y                 z               w\n');

    
    case 4
     
        % Cálculo
        [y,z,w,r] = S_sedo4(f1,f2,f3,f4,x,h,y0,z0,w0,r0,'Rk4');
    
        % Gráfico
        plot(x,y,'*',x,z,'+', x,w,'.',x,r,'+');
        title('SOLUÇÃO DO SISTEMA');
        xlabel('x')
        legend('y(x)','z(x)','w(x)','r(x)');

        % Resultados
        fprintf( 'x               y                z              w           r\n');
        for i=1:length(x)
             fprintf('%f     %f       %f       %f      %f\n', x(i), y(i), z(i), w(i), r(i) ); 
        end
        fprintf( 'x               y                z              w           r\n');    
    
 
end
