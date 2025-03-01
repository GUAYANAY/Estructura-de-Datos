% Cargar los datos desde el archivo .txt
datos = readtable('C:\Users/Admin/Desktop/Prueba_3er_parcial/datos_demostracion.txt');

% Extraer columnas
n = datos.n;
eLogN = datos.e_log_n_;
nVal = datos.n;

% Crear una figura con dos subgráficos
figure;

% Primera gráfica - Escala lineal
subplot(1,2,1);
plot(n, eLogN, 'bo-', 'LineWidth', 2, 'MarkerSize', 5); % Graficar e*log(n) en azul con marcadores
hold on;
plot(n, nVal, 'r--', 'LineWidth', 2); % Graficar n en rojo con línea discontinua
grid on;
xlabel('n');
ylabel('Valor');
title('Comparación de e·log(n) vs n');
legend('e·log(n)', 'n', 'Location', 'northwest');

% Segunda gráfica - Escala logarítmica en Y
subplot(1,2,2);
semilogy(n, eLogN, 'bo-', 'LineWidth', 2, 'MarkerSize', 5); % Graficar e*log(n) con escala logarítmica
hold on;
semilogy(n, nVal, 'r--', 'LineWidth', 2); % Graficar n con escala logarítmica
grid on;
xlabel('n');
ylabel('Valor (escala logarítmica)');
title('Comparación en escala logarítmica');
legend('e·log(n)', 'n', 'Location', 'northwest');

% Mostrar la tabla de datos en la consola
disp(datos);
