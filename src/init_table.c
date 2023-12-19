/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:01:44 by amanjon-          #+#    #+#             */
/*   Updated: 2023/12/19 16:37:59 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/**
 * int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
 * This function initialize the mutexes and ensures that the last philosopher `s
 * left fork assignment is correctly connected to the first fork in the table.
 * @param	void
 * @return	void
*/
int	ft_init_mutex(t_data *data, t_philo *philo/* , int i */)
{
	int i;

	i = 0;
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		printf("error init mutex: print_mutex");
		return (1);
	}
	if (pthread_mutex_init(&data->aux_mutex, NULL) != 0)
	{
		printf("error init mutex: kill_mutex");
		return (1);
	}
	while (i < data->n_philos)
	{
		if (pthread_mutex_init(&philo[i].l_fork, NULL) != 0)
		{
			printf("error init mutex: l_fork");
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_init_philos(int argc, t_data *data, t_philo *philo)
{
	int i;

	i = 0;
	while (i < data->n_philos)
	{
		philo[i].id = i + 1;
		philo[i].last_meal = 0;
		philo[i].data = data;
		philo[i].left_fork = 0;
		philo[i].r_fork = NULL;
		philo[i].right_fork = NULL;
		philo[i].status = THINKING;
		philo[i].status_changed = FALSE;
		if (argc == 6)
			philo[i].count_meals = data->n_times_to_eat;
		else
			philo[i].count_meals = -1;
		i++;
	}
}

/**
 * The pointers of the right fork and the right fork mutex are initialized
 * in a loop for each thread, the right fork = memory address of the left
 * fork of the next thread
 * @param	t_data *data
 * @return	void
*/
void	ft_init_forks_right(int n_philos, t_philo *philo/* , int i */)
{
	int pos_philo;
	int i;

	i = 0;
	while (i < n_philos)
	{
		if (i == n_philos - 1)
			pos_philo = 0;
		else
			pos_philo = i + 1;
		philo[i].right_fork = &philo[pos_philo].left_fork;
		philo[i].r_fork = &philo[pos_philo].l_fork;
		i++;
	}
}

void	ft_init_table(int argc, t_philo *philo, t_data *data)
{
	ft_init_mutex(data, philo);
	ft_init_philos(argc, data, philo);
	ft_init_forks_right(data->n_philos, philo);
	ft_init_threads(philo);
	ft_join_threads(data, philo);
	ft_destroy_threads(data, philo);
}
