
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:06:23 by amanjon-          #+#    #+#             */
/*   Updated: 2023/11/14 18:55:55 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"


/**
 * Se inicializa struct_data, algunas de estas variables con memoria dinámica.
 * Se inicializa start_time de la cena
 * left fork assignment is correctly connected to the first fork in the table.
 * @param	char **argv, t_data *data
 * @return	void
*/
void	ft_malloc_init_struct_data(char **argv, t_data *data)
{
	data->n_philos = ft_atoi_philo(argv[1]);
	data->philos = NULL;
	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philos)
		ft_print_error("error malloc");
	data->thread = NULL;
	data->thread = malloc(sizeof(pthread_t) * data->n_philos);
	if (!data->thread)
		ft_print_error("error malloc");
		data->forks = NULL;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->forks)
		ft_print_error("error malloc");
	data->lock = NULL;
	data->lock = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->lock)
		ft_print_error("error malloc");
	data->print_mutex = NULL;
	data->print_mutex = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->print_mutex)
		ft_print_error("error malloc");
	data->start_time = ft_get_time();

	printf("data->start_time = %llu\n", data->start_time);
}

/**
 * int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
 * This function initialize the mutexes and ensures that the last philosopher `s
 * left fork assignment is correctly connected to the first fork in the table.
 * @param	void
 * @return	void
*/
void	ft_init_mutex(t_data *data, int i)
{
	if (pthread_mutex_init(&(data->lock[i]), NULL) != 0)
		ft_print_error("error init mutex");
	// data->lock = &(data->lock[i]);
	if (pthread_mutex_init(&(data->print_mutex[i]), NULL) != 0)
		ft_print_error("error init mutex");
	// data->print_mutex = &(data->print_mutex[i]);
	if (pthread_mutex_init(&(data->forks[i]), NULL) != 0)
		ft_print_error("error init mutex");
	data->philos[i].right_fork = &data->forks[i];	//
	if (i == (data->n_philos - 1))
		data->philos[i].left_fork = &data->forks[0];	//
	else
		data->philos[i].left_fork = &data->forks[i + 1];	//
}

void	ft_init_philo(int argc, char **argv, t_data *data, int i)
{
	data->time_to_die = ft_atoi_philo(argv[2]);
	data->time_to_eat = ft_atoi_philo(argv[3]);
	data->time_to_sleep = ft_atoi_philo(argv[4]);
	if (argc == 6)
		data->n_times_to_eat = ft_atoi_philo(argv[5]);
	data->philos[i].id = i + 1;
	data->finish_program = 0;
	data->philos[i].last_meal = 0;
	data->philos[i].data = data;
}

void	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	ft_print_status(philo, TAKE_RIGHT_FORK);
	pthread_mutex_lock(philo->left_fork);
	ft_print_status(philo, TAKE_LEFT_FORK);
}

void	ft_drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	ft_print_status(philo, SLEEP);
	ft_usleep(philo->data->time_to_sleep);
}

void	ft_philo_eat(t_philo *philo)
{
	pthread_mutex_unlock(philo->data->print_mutex);	// 1 -> entrada función
	ft_take_forks(philo);
	pthread_mutex_lock(philo->data->print_mutex);
	philo->last_meal = 0;
	philo->last_meal = ft_get_time() - philo->data->start_time;
	// ft_print_status(philo, EAT);  						//SEGV ***************
	pthread_mutex_unlock(philo->data->print_mutex);
	// ft_usleep(philo->data->time_to_eat);					//SEGV ***************
	// ft_drop_forks(philo);									//SEGV ***************
	ft_print_status(philo, THINK);
	pthread_mutex_lock(philo->data->print_mutex);	// 2 -> salida función
}

void	*ft_routine(void *philo_struct)
{
	t_philo *philo;

	philo = philo_struct;
	// if (philo->id % 2 == 0)
	// 	ft_usleep(200);

	pthread_mutex_lock(philo->data->print_mutex);		// 1 -> entrada función
	ft_philo_eat(philo);
	pthread_mutex_unlock(philo->data->print_mutex);	// 2 -> salida función
	
	return (NULL);
}

/**
 * int pthread_create(pthread_t *thread, const pthread_attr_t *attr,void *(*start_routine) (void *), void *arg);
 * This function 
 * @param	void
 * @return	void
*/
void	ft_init_elems_and_create_threads(int argc, char **argv, t_data *data)
{
	int i;

	i = 0;
	// printf("data->thread = %lu\n", (unsigned long)data->thread);
	while (i < data->n_philos)
	{
		ft_init_mutex(data, i);
		printf("fin ft_init mutex\n\n\n");
		ft_init_philo(argc, argv, data, i);
		printf("fin ft_init philo\n\n\n");
		pthread_create(&(data->thread[i]), NULL, ft_routine, &(data->philos[i]));
		printf("fin ft_crear hilos\n\n\n");
		i++;
	}
	// i = 0;
	// while (i < data->n_philos)
	// {
	// 	pthread_create(&(data->thread[i]), NULL, ft_routine, &(data->philos[i]));
	// 	i++;
	// }
}

int main(int argc, char **argv)
{
	// t_philo	philos;
	t_data	data;

	if (argc < 5 || argc > 6)
		ft_print_error("Numbers of arguments invaled");
	ft_malloc_init_struct_data(argv, &data);
	if (data.n_philos >= 1 && data.n_philos <= 200)
	{
		pthread_mutex_lock(data.print_mutex);
		ft_init_elems_and_create_threads(argc, argv, &data);
		pthread_mutex_unlock(data.print_mutex);
	}
	printf("llega aqui******______________\n");
	pthread_join(*data.thread, NULL);	// Evita un SEGV, pero se queda pillado aqui mismo
	return (0);	
}
