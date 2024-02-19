time = data(:, 1); % time
theta = data(:, 2); % theta
omega = data(:, 3); % omega
alpha = data(:, 4); % alpha
sensor_actuator = data(:, 5); % sensor_actuator
actuator = data(:, 6); % actuator
h = data(:, 7); % h
pEnergy = data(:, 8); % potential energy
kEnergy = data(:, 9); % kinetic energy
totEnergy = data(:, 10); % total energy

figure
hold on
plot(time, rad2deg(theta), 'DisplayName','theta','LineWidth',2);
plot(time, rad2deg(omega), 'DisplayName','omega','LineWidth',2);
plot(time, actuator, 'DisplayName','Act Force','LineWidth',2);
hold off
legend