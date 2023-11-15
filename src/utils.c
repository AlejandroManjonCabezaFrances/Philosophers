/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 08:23:55 by amanjon-          #+#    #+#             */
/*   Updated: 2023/11/13 16:53:50 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_print_error(char *str)
{
	printf("%s\n" ,str);
	exit(EXIT_FAILURE);
}

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
