/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:01:58 by amanjon-          #+#    #+#             */
/*   Updated: 2023/12/21 10:12:15 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/**
 * int pthread_create(pthread_t *thread, NULL, void *(*routine) (*), void *arg);
 * We create threads in two loops independently, the even and the odd ones,
 * in this way we ensure that not all the philosophers
 * pick up the forks at the same time.
 * @param	t_philo *philo
 * @return	int
*/
int	ft_init_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->n_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, &ft_routine, &philo[i]) != 0)
		{
			printf("error creating even thread\n");
			return (1);
		}
		i = i + 2;
	}
	usleep(50);
	i = 1;
	while (i < philo->data->n_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, &ft_routine, &philo[i]) != 0)
		{
			printf("error creating odd thread\n");
			return (1);
		}
		i = i + 2;
	}
	return (0);
}

/**
 * We wait for the threads to reach this point
 * and destroy all the mutexes of the left fork in a loop
 * @param	t_data *data ,t_philo *philo
 * @return	void
*/
void	ft_join_threads(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
		pthread_join(philo[i].thread, NULL);
	i = -1;
	while (++i < data->n_philos)
		pthread_mutex_destroy(&philo[i].l_fork);
}

/**
 * int pthread_mutex_destroy(pthread_mutex_t *mutex);
 * Destroy mutex og the data struct
 * @param	t_data *data ,t_philo *philo
 * @return	void
*/
void	ft_destroy_threads(t_data *data, t_philo *philo)
{
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->aux_mutex);
	free (philo);
}
