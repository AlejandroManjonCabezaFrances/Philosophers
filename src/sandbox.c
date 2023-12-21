/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 06:50:27 by amanjon-          #+#    #+#             */
/*   Updated: 2023/12/21 08:39:36 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/* ##############################  1  ############################## */
/* #######################  INICIALIZAR 1 HILO  ####################### */
// ejecutar : con make re

// O_APPEND = Al abrirse archivo añade nueva línea.
// Comprobar file descriptor diferente de -1 para escribir.
// void	*ft_thread_routine(void *arg)
// {
// 	int i;
// 	int n_lines;
// 	int fd;

// 	i = 0;
// 	n_lines = *((int *)arg);
// 	while (i < n_lines)
// 	{
// 		fd = open(PATH_FD, O_WRONLY | O_APPEND);
// 		write(fd, "nueva linea\n", 12);
// 		close(fd);
// 		i++;
// 	}
// 	return (NULL);
// }

// pthread_create(identificador, atributos "por defecto", rutina del hilo,
// argumento de entrada "numero de lineas pasado por argumentos") --> 
// value = argv[1] --> n_lines

// // pthread_join(identificador, NULL "valor de retorno"); -->
// esta función evita que el programa acabe
// // sin que acabe el hilo de ejecutarse
// int main(int argc, char **argv)
// {
// 	(void) argc;
// 	(void) argv;

// 	pthread_t	thread1;
// 	int 		value;

// 	value = atoi(argv[1]);
// 	if (pthread_create(&thread1, NULL, ft_thread_routine, &value) != 0)
// 	{
// 		printf("pthread not created!!\n");
// 		return (-1);
// 	}

// 	pthread_join(thread1, NULL);

// 	return (0);
// }

/* ##############################  2  ############################## */
/* ############################  MUTEX  ############################ */
// ejecutar :  gcc sandbox.c -lpthread -o philosophers

// static int count = 10;
// pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;

// void	*ft_thread1_routine(void *unused)
// {
// 	int i;

// 	i = 0;
// 	while (i < 10000)
// 	{
// 		pthread_mutex_lock(&my_mutex);
// 		count++;
// 		pthread_mutex_unlock(&my_mutex);
// 		i++;
// 	}
// 	printf("count funcion 1 = %d\n", count);
// 	return (NULL);
// }

// void	*ft_thread2_routine(void *unused)
// {
// 	int i;

// 	i = 0;
// 	while (i < 10000)
// 	{
// 		pthread_mutex_lock(&my_mutex);
// 		count--;
// 		pthread_mutex_unlock(&my_mutex);
// 		i++;
// 	}
// 	printf("count funcion 2 = %d\n", count);
// 	return (NULL);
// }

// void	ft_error_exit(char *error)
// {
// 	perror(error);
// 	exit(1);
// }

// int main(int argc, char **argv)
// {
// 	pthread_mutex_t my_mutex;
// 	pthread_t		thread1;
// 	pthread_t		thread2;

// 	if (pthread_create(&thread1, NULL, ft_thread1_routine, NULL) != 0)
// 	{
// 		ft_error_exit("thread1 cannnot be created!!\n");
// 	}
// 	if (pthread_create(&thread2, NULL, ft_thread2_routine, NULL) != 0)
// 	{
// 		ft_error_exit("thread1 cannnot be created!!\n");
// 	}

// 	pthread_join(thread1, NULL);
// 	pthread_join(thread2, NULL);

// 	printf("count value %d\n", count); // en el viceo solo muestra este printf,
// los demás son por check

// 	return (0);
// }

/* ##############################  3  ############################## */
/* ######################## GET TIME IN MS ######################## */
//  hora expresada en milisegundos transcurridos desde el 1 de enero de 1970,
//  conocido como el "epoch" en sistemas Unix.

// uint64_t	ft_get_time(void)
// {
// 	struct timeval	tv;

// 	gettimeofday(&tv, NULL);
// 	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
// }

// unsigned long long ft_get_time(void)
// {
//     struct timeval	tv;

//  	gettimeofday(&tv, NULL);
// 	return (unsigned long long)(tv.tv_sec) * 1000
//		+ (unsigned long long)(tv.tv_usec) / 1000;
// }

// int main(int argc, char **argv)
// {
//     unsigned long long current_time = ft_get_time();
//     printf("Current time in milliseconds: %llu\n", current_time);
//     return (0);
// }

// int main(int argc, char **argv) 
// {
//     unsigned long long current_time;// Reemplaza con el valor obtenido
// 	time_t epoch_time;
// 	struct tm *local_time;

// 	current_time = 1700136498936;
//     epoch_time = current_time / 1000;  // Convierte milisegundos a segundos
//     local_time = localtime(&epoch_time);

//     printf("Fecha y hora local: %s", asctime(local_time));

//     return (0);
// }

/* ############################  4  ############################ */
/* ######################## EXAMPLE MUTEX ######################## */

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, TAKE_FORK);
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, TAKE_FORK);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	print_action(philo, SLEEPING);
	philo_usleep(philo->data->time_to_sleep);
}

// We need to lock and unlock the print mutex 
// to avoid data races when printing
void	philo_eat(t_philo *philo)
{
	while (philo->data->finish_program == 0)
	{
		pthread_mutex_unlock(philo->print);
		take_forks(philo);
		pthread_mutex_lock(philo->lock);
		philo->last_meal = set_time() - philo->data->start_time;
		if (philo->data->number_of_meals != -1)
			philo->meal_counter++;
		print_action(philo, EATING);
		pthread_mutex_unlock(philo->lock);
		philo_usleep(philo->data->time_to_eat);
		drop_forks(philo);
		print_action(philo, THINKING);
		pthread_mutex_lock(philo->print);
	}
}

// Routine for the philos
// They lock and unlock the print mutex to avoid printing at the same time
void	*routine(void *philo_no_casted)
{
	t_philo	*philo;

	philo = philo_no_casted;
	if (philo->id % 2 == 0)
		philo_usleep(200);
	pthread_mutex_lock(data->print_mutex);
	philo_eat(philo);
	pthread_mutex_unlock(data->print_mutex);
	return (NULL);
}
