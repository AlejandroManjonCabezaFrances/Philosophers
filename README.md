# Philosophers
[![filosofos.png](https://i.postimg.cc/TwWKnDPc/filosofos.png)](https://postimg.cc/XG4NbXdZ)
Cinco filósofos se sientan alrededor de una mesa y pasan su vida cenando y pensando. Cada filósofo tiene un plato de fideos y un tenedor a la izquierda de su plato. Para comer los fideos son necesarios dos tenedores y cada filósofo sólo puede tomar los que están a su izquierda y derecha. Si cualquier filósofo toma un tenedor y el otro está ocupado, se quedará esperando, con el tenedor en la mano, hasta que pueda tomar el otro tenedor, para luego empezar a comer.

Si dos filósofos adyacentes intentan tomar el mismo tenedor a una vez, se produce una condición de carrera: ambos compiten por tomar el mismo tenedor, y uno de ellos se queda sin comer.

Si todos los filósofos toman el tenedor que está a su derecha al mismo tiempo, entonces todos se quedarán esperando eternamente, porque alguien debe liberar el tenedor que les falta. Nadie lo hará porque todos se encuentran en la misma situación (esperando que alguno deje sus tenedores). Entonces los filósofos se morirán de hambre. Este bloqueo mutuo se denomina interbloqueo o deadlock.

• Cada filósofo debe ser un hilo.
• Hay un tenedor entre cada filósofo. por lo tanto, si hay varios filósofos, cada filósofo
debe tener un tenedor a su izquierda y otro a su derecha. si solo hay un filósofo,
solo habrá un tenedor en la mesa.
• Para prevenir que los filósofos dupliquen los tenedores, deberás proteger los estados
de los tenedores con un mutex por cada uno de ellos.

• Tu programa debe aceptar los siguientes argumentos:
number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]
◦ number_of_philosophers: es el número de filósofos, pero también el número
de tenedores.
◦ time_to_die (en milisegundos): si un filósofo no empieza a comer en time_to_die
milisegundos desde el comienzo de su ultima comida o desde el principio de la
simulación, este morirá.
◦ time_to_eat (en milisegundos): es el tiempo que tiene un filósofo para comer.
Durante ese tiempo, tendrá los tenedores ocupados.
◦ time_to_sleep (en milisegundos): es el tiempo que tiene un filósofo para
dormir.
◦ number_of_times_each_philosopher_must_eat (argumento opcional): si todos los filósofos comen al menos number_of_times_each_philosopher_must_eat
veces, la simulación se detendrá. Si no se especifica, la simulación se detendrá
con la muerte de un filósofo.


Example of arguments expected result:

./philo 4 310 200 100 → Philosopher die.
./philo 1 200 200 200 → Philosopher 1 takes a fork and dies after 200 ms.
./philo 2 800 200 200 → No philosopher dies.
./philo 5 800 200 200 → No philosopher dies.
./philo 5 800 200 200 7 → The program stops when each philosopher has eaten 7 times.
./philo 4 410 200 200 → No philosopher dies.
./philo 4 310 200 200 → A philosopher dies.
./philo 4 500 200 1.2 → Invalid argument.
./philo 4 0 200 200 → Invalid argument.
./philo 4 -500 200 200 → Invalid argument.
./philo 4 500 200 2147483647 → A philosopher dies after 500 ms
./philo 4 2147483647 200 200 → No philosopher dies.
./philo 4 214748364732 200 200 → Invalid argument.
./philo 4 200 210 200 → A philosopher dies, it should display the death before 210 ms.
./philo 5 800 200 150 → No philosopher dies.
./philo 3 610 200 80 → No philosopher dies.
./philo 100 400 100 100 → No philosopher dies.
./philo 198 400 100 100 → No philosopher dies.
