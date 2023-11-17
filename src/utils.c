/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 08:23:55 by amanjon-          #+#    #+#             */
/*   Updated: 2023/11/17 10:05:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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
 * @param	void
 * @return	unsigned long long
*/
unsigned long long get_time(void) 
{
    struct timeval	tv;
    gettimeofday(&tv, NULL);
    return (unsigned long long)(tv.tv_sec) * 1000 + (unsigned long long)(tv.tv_usec) / 1000;
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
