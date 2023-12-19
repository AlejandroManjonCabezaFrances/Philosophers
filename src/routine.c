/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:10:53 by amanjon-          #+#    #+#             */
/*   Updated: 2023/12/19 19:44:48 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/**
 * Function that controls the death of the philosopher who did not have time to eat
 * @param	t_philo *philo
 * @return	void
*/
void	ft_death(t_philo *philo)
{
	u_int64_t	time;

	pthread_mutex_lock(&philo->data->aux_mutex);
	if (philo->data->finish_program == 0)
	{
		philo->data->finish_program = 1;
		usleep(philo->data->pause);
		pthread_mutex_lock(&philo->data->print_mutex);
		time = philo->last_meal + philo->data->time_to_die;
		printf("time:%llums | philo:%d | action: %s\n", time - philo->data->start_time, philo->id, DIE);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	pthread_mutex_unlock(&philo->data->aux_mutex);
}

/**
 * This function controls that the philosophers pick up forks, whoever has both can eat.
 * @param	t_philo *philo, u_int64_t time
 * @return	void
*/
void	ft_take_forks_and_eat(t_philo *philo, u_int64_t time)
{
	pthread_mutex_lock(&philo->l_fork);
	if (philo->left_fork == TABLE)
	{
		philo->left_fork = LEFT_HAND;
		ft_print_status(philo, TAKE_LEFT_FORK, time);
	}
	if (philo->data->n_philos > 1)
	{
		pthread_mutex_lock(philo->r_fork);
		if (*philo->right_fork == TABLE)
		{
			*philo->right_fork = RIGHT_HAND;
			ft_print_status(philo, TAKE_RIGHT_FORK, time);
		}
		if (philo->left_fork == LEFT_HAND && *philo->right_fork == RIGHT_HAND)
		{
			philo->status = EATTING;
			philo->last_meal = ft_get_time();
			ft_print_status(philo, EAT, philo->last_meal);
		}
		pthread_mutex_unlock(philo->r_fork);
	}
	pthread_mutex_unlock(&philo->l_fork);
}

/**
 * We control the 'SLEEP' state and the philosophers put down their forks
 * @param	t_philo *philo
 * @return	void
*/
void	ft_drop_forks(t_philo *philo)
{
	philo->status = SLEEPING;
	ft_print_status(philo, SLEEP, (philo->last_meal + philo->data->time_to_eat));
	pthread_mutex_lock(&philo->l_fork);
	philo->left_fork = TABLE;
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	*philo->right_fork = TABLE;
	pthread_mutex_unlock(philo->r_fork);
}

/**
 * We control the 'THINK' state and the number of times each philosopher has to eat
 * @param	t_philo *philo
 * @return	void
*/
void	ft_sleep_and_think(t_philo *philo)
{
	philo->status = THINKING;
	ft_print_status(philo, THINK, philo->last_meal + philo->data->time_to_eat + philo->data->time_to_sleep);
	if (philo->count_meals > 0)
		philo->count_meals--;
}


/**
 * The philosophers manage to pick up forks to eat, sleep, think, and/or die.
 * @param	void *philo_struct
 * @return	void
*/
void	*ft_routine(void *philo_struct)
{
	t_philo 	*philo;
	uint64_t	time;

	philo = (t_philo *)philo_struct;
	philo->last_meal = ft_get_time();
	while (philo->count_meals != 0 && ft_stop_routine(philo->data) == 0)
	{
		time = ft_get_time();
		if (time > philo->last_meal + philo->data->time_to_die)
			ft_death(philo);
		else if (philo->status == THINKING)
			ft_take_forks_and_eat(philo, time);
		else if(philo->status == EATTING && time > philo->last_meal + philo->data->time_to_eat)
			ft_drop_forks(philo);
		else if (philo->status == SLEEPING 
			&& time > philo->last_meal + philo->data->time_to_eat + philo->data->time_to_sleep)
			ft_sleep_and_think(philo);
		ft_synchronization(philo);
	}
	return (0);
}