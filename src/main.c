
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

void	ft_malloc_init_struct_data(char **argv, t_data *data)
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
	data->start_time = ft_get_time();
	//printf("data->start_time = %lu\n", data->start_time);
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
	printf("ft_init_mutex\n");
	if (pthread_mutex_init(&(data->lock[i]), NULL) != 0)
		ft_print_error("error init mutex");
	if (pthread_mutex_init(&(data->print_mutex[i]), NULL) != 0)
		ft_print_error("error init mutex");
	if (pthread_mutex_init(&(data->forks[i]), NULL) != 0)
		ft_print_error("error init mutex");
	data->philos[i].right_fork = &data->forks[i];
	if (i == (data->n_philos - 1))
		data->philos[i].left_fork = &data->forks[0];
	else
		data->philos[i].left_fork = &data->forks[i + 1];

}

void	ft_init_philo(int argc, char **argv, t_data *data, int i)
{
	printf("ft_init_philo\n");
	data->philos[i].time_to_die = ft_atoi_philo(argv[2]);
	data->philos[i].time_to_eat = ft_atoi_philo(argv[3]);
	data->philos[i].time_to_sleep = ft_atoi_philo(argv[4]);
	if (argc == 6)
		data->philos[i].n_times_to_eat = ft_atoi_philo(argv[5]);
	data->philos->id = i + 1;
	data->philos->finish_program = 0;
	data->philos->data = data;
}

void	ft_take_forks(t_philo *philo)
{
	printf("ft_take_forks\n");
	pthread_mutex_lock(philo->right_fork);
	printf("ft_take_forks_2\n");
	ft_print_status(philo, TAKE_RIGHT_FORK);
	pthread_mutex_lock(philo->left_fork);
	ft_print_status(philo, TAKE_LEFT_FORK);

	//DROP FORKS
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	ft_philo_eat(t_philo *philo)
{
	printf("ft_philo_eat\n");
	//pthread_mutex_unlock(philo->data->print_mutex);
	ft_take_forks(philo);
}

void	*ft_routine(void *philo_struct)
{
	t_philo *philo;

	philo = philo_struct;
	printf("ft_routine\n");
	//if (philo->id % 2 == 0)
		//ft_usleep(200);
	printf("ft_routine_2\n");
	//pthread_mutex_lock(philo->data->print_mutex);
	ft_philo_eat(philo);
	
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
	while (i < data->n_philos)
	{
		printf("ft_init_elements\n");
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
	ft_malloc_init_struct_data(argv, &data);
	if (data.n_philos >= 1 && data.n_philos <= 200)
		ft_init_elems_and_create_threads(argc, argv, &data);
	return (0);	
}