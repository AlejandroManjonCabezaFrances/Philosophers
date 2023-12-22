/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 08:23:55 by amanjon-          #+#    #+#             */
/*   Updated: 2023/12/21 08:53:49 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/**
 * Prints the status of each thread. Time, philo identifier and action
 * @param	t_philo *philo, char *action, uint64_t time
 * @return	void
*/
void	ft_print_status(t_philo *philo, char *action, uint64_t time)
{
	pthread_mutex_lock(&philo->data->aux_mutex);
	if (philo->data->finish_program == 0)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("time:%llums | philo:%d | action: %s\n",
			time - philo->data->start_time, philo->id, action);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	pthread_mutex_unlock(&philo->data->aux_mutex);
}

/**
 * This function returns the current time in milliseconds
 * (tv.tv_sec) * 1000 -> seconds to milliseconds
 * (tv.tv_usec) / 1000 -> microseconds to milliseconds
 * @param	void
 * @return	uint64_t
*/
uint64_t	ft_get_time(void)
{
	struct timeval	tv;
	uint64_t		result;

	gettimeofday(&tv, NULL);
	result = (tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / (uint64_t)1000);
	return (result);
}

/**
 * Prints an error passed by arguments and exits the program
 * @param	char *str
 * @return	int
*/
int	ft_print_error(char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

/**
 * Transform a char into an int if the number is positive and between 1 and 9
 * and does not exceed INT_MAX
 * @param	const char *str
 * @return	int
*/
int	ft_atoi_philo(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		ft_print_error("Invalid arguments: just numbers positives");
	if (str[i] < '1' || str[i] > '9')
		ft_print_error("Invalid arguments: just numbers from 1 to 9");
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	if ((str[i] < '1' || str[i] > '9') && str[i])
		ft_print_error("Invalid arguments: just numbers from 1 to 9");
	if (result > INT_MAX)
		ft_print_error("Invalid arguments: overflow INT");
	return ((int)result);
}

/**
 * 
 * @param	t_philo *philo
 * @return	void
*/
void	ft_synchronization(t_philo *philo)
{
	if (philo->status_changed)
	{
		usleep(philo->data->pause);
		philo->status_changed = FALSE;
	}
	else
		usleep(philo->data->min_pause);
}
