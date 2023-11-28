
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
	printf("****************3\n");
	// data->lock = &(data->lock[i]);
	if (pthread_mutex_init(&(data->print_mutex[i]), NULL) != 0)
		ft_print_error("error init mutex");
	printf("****************4\n");
	// data->print_mutex = &(data->print_mutex[i]);
	if (pthread_mutex_init(&(data->forks[i]), NULL) != 0)
		ft_print_error("error init mutex");
	printf("****************5\n");
	data->philos[i].right_fork = &data->forks[i];	//
	if (i == (data->n_philos - 1))
		data->philos[i].left_fork = &data->forks[0];	//
	else
		data->philos[i].left_fork = &data->forks[i + 1];	//
	printf("****************6\n");
}

void	ft_init_philo(int argc, char **argv, t_data *data, int i)
{
	data->time_to_die = ft_atoi_philo(argv[2]);
	data->time_to_eat = ft_atoi_philo(argv[3]);
	data->time_to_sleep = ft_atoi_philo(argv[4]);
	printf("****************8\n");
	if (argc == 6)
		data->n_times_to_eat = ft_atoi_philo(argv[5]);
	printf("****************9\n");
	data->philos[i].id = i + 1;
	data->finish_program = 0;
	data->philos[i].last_meal = 0;
	data->philos[i].data = data;
	printf("****************10\n");
}

void	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	printf("****************15\n");
	ft_print_status(philo, TAKE_RIGHT_FORK);
	printf("****************18\n");
	pthread_mutex_lock(philo->left_fork);
	ft_print_status(philo, TAKE_LEFT_FORK);
	printf("****************19\n");
}

void	ft_drop_forks(t_philo *philo)
{
	printf("****************23\n");
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	ft_print_status(philo, SLEEP);
	printf("****************24\n");
	ft_usleep(philo->data->time_to_sleep);
}

void	ft_philo_eat(t_philo *philo)
{
	printf("****************14\n");
	pthread_mutex_unlock(philo->data->print_mutex);				// 1 -> entrada función
	ft_take_forks(philo);
	pthread_mutex_lock(philo->data->print_mutex);
	philo->last_meal = 0;
	printf("****************20\n");
	// philo->last_meal = ft_get_time() - philo->data->start_time;
	ft_print_status(philo, EAT); 
	printf("****************22\n"); 								// Evita SEGV 112
	pthread_mutex_unlock(philo->data->print_mutex);
	// ft_usleep(philo->data->time_to_eat);							// Evita SEGV 112
	ft_drop_forks(philo);
	printf("****************25\n");									// Evita SEGV 112
	ft_print_status(philo, THINK);
	pthread_mutex_lock(philo->data->print_mutex);					// 2 -> salida función
	printf("****************26\n");
}

void	*ft_routine(void *philo_struct)
{
	t_philo *philo;

	philo = philo_struct;
	printf("****************12\n");
	// if (philo->id % 2 == 0)									// bucle infinito
	// 	ft_usleep(200);

	pthread_mutex_lock(philo->data->print_mutex);				// 1 -> entrada función
	printf("****************13\n");
	ft_philo_eat(philo);
	printf("****************27\n");
	pthread_mutex_unlock(philo->data->print_mutex);				// 2 -> salida función
	
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
		printf("****************2\n");
		ft_init_mutex(data, i);
		printf("****************7\n");
		ft_init_philo(argc, argv, data, i);
		printf("****************11\n");
		pthread_create(&(data->thread[i]), NULL, ft_routine, &(data->philos[i]));
		i++;
		printf("****************28\n");
	}
	printf("****************29\n");
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
	int i;

	if (argc < 5 || argc > 6)
		ft_print_error("Numbers of arguments invaled");
	ft_malloc_init_struct_data(argv, &data);
	if (data.n_philos >= 1 && data.n_philos <= 200)
	{
		printf("****************1\n");
		pthread_mutex_lock(data.print_mutex);
		ft_init_elems_and_create_threads(argc, argv, &data);
		pthread_mutex_unlock(data.print_mutex);
	}
	printf("****************30\n");
	// pthread_join(*data.thread, NULL);		// Evita un SEGV, pero se queda pillado aqui mismo
	i = 0;
	while (i < data.n_philos)					// Evita SEGV 112
	{
		pthread_join(data.thread[i], NULL);
		i++;
	}
	printf("****************31\n");
	return (0);	
}
