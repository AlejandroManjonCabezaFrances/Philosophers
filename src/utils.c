/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 08:23:55 by amanjon-          #+#    #+#             */
/*   Updated: 2023/11/23 12:53:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_print_status(t_philo *philo, char *action)
{
	uint64_t	time;

	printf("ft_print_status_1\n");
	pthread_mutex_lock(philo->data->print_mutex);
	time = (ft_get_time() - philo->data->start_time);
	/* printf("time = %lu\n", time); */
	printf("ft_print_status_2\n");
	if (philo->finish_program == 0)
		printf("time:%lums | philo:%d | action:%s\n", time, philo->id, action);
	pthread_mutex_unlock(philo->data->print_mutex);
}

/**
 * Prints an error passed by arguments and exits the program
 * @param	char *str
 * @return	int
*/
int	ft_print_error(char *str)
{
	printf("%s\n" ,str);
	exit(EXIT_FAILURE);
}

/**
 * Time expressed in milliseconds since January 1, 1970, known as the "epoch"
 * (tv.tv_sec) * 1000 -> seconds*1000 y (tv.tv_usec) / 1000 -> microseconds/1000 to go to ms
 * @param	void
 * @return	unsigned long long
*/
uint64_t	ft_get_time(void)
{
	struct timeval	tv;
	uint64_t		result;

	/* printf("ft_get_time\n"); */
	gettimeofday(&tv, NULL);
	/* printf("ft_get_time_1\n"); */
	result = (tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / (uint64_t)1000);
	/* printf("result = %lu\n", result); */
	return (result);
}

int	ft_usleep(unsigned int our_time)
{
	uint64_t	time;
	
	time = ft_get_time() + our_time;
	while (ft_get_time() < time)
		usleep(100);
	return (0);
}

/**
 * Transform a char into an int if the number is positive and between 1 and 9
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
		ft_print_error("Invalid arguments: numbers negatives");
	if (str[i] < '1' || str[i] > '9')
		ft_print_error("Invalid arguments: just numbers from 1 to 9");
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	if (result > INT_MAX)
		ft_print_error("Invalid arguments: overflow INT");
	return ((int)result);
}
