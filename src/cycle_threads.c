/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:01:58 by amanjon-          #+#    #+#             */
/*   Updated: 2023/12/19 16:04:45 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/**
 * int pthread_create(pthread_t *thread, const pthread_attr_t *attr,void *(*start_routine) (void *), void *arg);
 * This function 
 * @param	void
 * @return	void
*/
int	ft_init_threads(t_philo *philo)
{
	int i;

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
 * int pthread_mutex_destroy(pthread_mutex_t *mutex);
 * @param	t_philo *philo, t_data *data
 * @return	void
*/
void	ft_join_threads(t_data *data ,t_philo *philo)
{
	int i;

	i = -1;
	while (++i < data->n_philos)
		pthread_join(philo[i].thread, NULL);
	i = -1;
	while (++i < data->n_philos)
		pthread_mutex_destroy(&philo[i].l_fork);
}

void	ft_destroy_threads(t_data *data ,t_philo *philo)
{
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->aux_mutex);
	free (philo);
}