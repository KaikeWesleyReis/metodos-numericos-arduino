%% Funcao para resolucao de um  sistema de 2 EDOs
% Utiliza diferentes metodos na forma de Rk

function[y,z] = sedo2(EDO1, EDO2, xrange, passo, y0, z0, metodo)

f1 = EDO1;
f2 = EDO2;
x = xrange;
h = passo;
% condicoes iniciais
y(1) = y0;
z(1) = z0;

switch metodo
    case 'explicito'     % Euler Simples
        a2= 0; a3= 0; a4= 0; b21= 0; b31= 0; b32= 0; b41= 0; b42= 0; b43= 0; c1= 1; c2 = 0; c3= 0; c4= 0; 
    
    case 'modificado'    % Euler Modificado 
        a2=1; a3=0; a4=0; b21=1; b31=0; b32=0; b41=0; b42=0; b43=0; c1=1/2; c2=1/2; c3=0; c4=0;
    
    case 'pontocentral'  % Ponto Central
         a2=1/2; a3=0; a4=0; b21=1/2; b31=0; b32=0; b41=0; b42=0; b43=0; c1=0; c2=1; c3=0; c4=0;
    
    case 'Heun'          % Runge-Kutta de ordem 2 (Heun)
        a2=2/3; a3=0; a4=0; b21=2/3; b31=0; b32=0; b41=0; b42=0; b43=0; c1=1/4; c2=3/4; c3=0; c4=0; 
    
    case 'Rk3'           % Runge-Kutta de ordem 3
        a2=1/2; a3=1; a4=0; b21=1/2; b31=-1; b32=2; b41=0; b42=0; b43=0; c1=1/6; c2=4/6; c3= 1/6; c4=0;
    
    case 'Rk4'           % Runge-Kutta de ordem 4
        a2=1/2; a3=1/2; a4=1; b21=1/2; b31=0; b32=1/2; b41=0; b42=0; b43=1; c1=1/6; c4=1/6; c3=2/6; c2=2/6;
        
end    
           
        
for i=1:length(x)-1
    ky1 = f1(x(i),y(i),z(i));
    kz1 = f2(x(i),y(i),z(i));
    ky2 = f1(x(i)+ a2*h, y(i)+ b21*ky1*h, z(i)+ b21*kz1*h);
    kz2 = f2(x(i)+ a2*h, y(i)+ b21*ky1*h, z(i)+ b21*kz1*h);
    ky3 = f1(x(i)+ a3*h, y(i)+ b31*ky1*h+ b32*ky2*h, z(i)+ b31*kz1*h+ b32*kz2*h);
    kz3 = f2(x(i)+ a3*h, y(i)+ b31*ky1*h+ b32*ky2*h, z(i)+ b31*kz1*h+ b32*kz2*h);
    ky4 = f1(x(i)+ a4*h, y(i)+ b41*ky1*h+ b42*ky2*h+ b43*ky3*h, z(i)+ b41*kz1*h+ b42*kz2*h+ b43*kz3*h);
    kz4 = f2(x(i)+ a4*h, y(i)+ b41*ky1*h+ b42*ky2*h+ b43*ky3*h, z(i)+ b41*kz1*h+ b42*kz2*h+ b43*kz3*h);
    y(i+1) = y(i) + (c1*ky1 + c2*ky2 + c3*ky3 + c4*ky4)*h;
    z(i+1) = z(i) + (c1*kz1 + c2*kz2 + c3*kz3 + c4*kz4)*h;
end
end