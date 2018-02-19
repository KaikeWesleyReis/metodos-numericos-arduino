%% Transferencia de calor em uma barra de ferro
% pretende-se encontrar a temperatura ao longo de uma barra de ferro longa 
%e de largura desprezível, sendo que a barra tem as temperaturas fixas em sua extremidade  
L = 10;     % Comprimento [cm]
k = 0.163 ;   % Condutividade termica do ferro [cal/(s*cm*C)]
C = 0.110; % Calor especifico do ferro [cal/(g*C)]
rho =  7.87;  % massa especifica ferro [g/cm3]
K = (k/C/rho);

Tt0 = 25; % C temperatura da barra para t=0;
% Condicao de contorno
xi = 0; Ti = 100;
xf = L; Tf = 100;

% Discretizacao em x
dx = 2; % cm
x = xi:dx:xf; 
Nx = length(x);

% Discretizacao no tempo
dt = 0.5; tf = 5;
t = 0:dt:tf;
Nt = length(t);

% Temperatura inical para toda a barra no instante t = 0
T(1:Nt,1) = Ti; T(1,2:Nx-1) = Tt0; T(1:Nt,Nx) = Tf;

%% solucao

for j = 1:Nt-1 % passo em t
    for i = 2:Nx-1 % passo em x
        T(j+1,i) = T(j,i) + K*dt*(T(j,i+1) - 2*T(j,i) + T(j,i-1))/dx^2; % Metodo de Euller explicito para a resolucao da EDP parabolica
    end
end

%% Resultados
surf(x,t,T)
xlabel('Comprimento (cm)')
ylabel('Tempo (s)')
zlabel('Temperatua (C)')


