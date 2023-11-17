
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

void	ft_malloc_struct_data(char **argv, t_data *data)
{
	data->n_philos = ft_atoi_philo(argv[1]);
	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philos)
		ft_print_error("error malloc");
	data->thread = malloc(sizeof(pthread_t) * data->n_philos);
	if (!data->thread)
		ft_print_error("error malloc");
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->forks)
		ft_print_error("error malloc");
	data->lock = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->lock)
		ft_print_error("error malloc");
	data->print_mutex = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->print_mutex)
		ft_print_error("error malloc");
}

/**
 * int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
 * This function 
 * @param	void
 * @return	void
*/
void	ft_init_mutex(t_data *data, int i)
{
	if (pthread_mutex_init(&(data->lock[i]), NULL) != 0)
		ft_print_error("error init mutex");
	if (pthread_mutex_init(&(data->forks[i]), NULL) != 0)
		ft_print_error("error init mutex");
	if (pthread_mutex_init(&(data->print_mutex[i]), NULL) != 0)
		ft_print_error("error init mutex");
}

void	ft_init_philo(int argc, char **argv, t_data *data, int i)
{
		data->philos[i].time_to_die = ft_atoi_philo(argv[2]);
		data->philos[i].time_to_eat = ft_atoi_philo(argv[3]);
		data->philos[i].time_to_sleep = ft_atoi_philo(argv[4]);
		if (argc == 6)
			data->philos[i].n_times_to_eat = ft_atoi_philo(argv[5]);
}

void	ft_routine(void *philo_struct)
{
	t_philo *philo;

	philo = philo_struct;
	

	
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
	while (i < data->n_philos)
	{
		ft_init_mutex(data, i);
		ft_init_philo(argc, argv, data, i);
		pthread_create(&(data->thread[i]), NULL, ft_routine, &(data->philos[i]));
		i++;
	}
}

int main(int argc, char **argv)
{
	// t_philo	philos;
	t_data	data;
	if (argc < 5 || argc > 6)
		ft_print_error("Numbers of arguments invaled");
	ft_malloc_struct_data(argv, &data);
		if (data.n_philos >= 1 && data.n_philos <= 200)
	{
		ft_init_elems_and_create_threads(argc, argv, &data);
	}
	return (0);	
}