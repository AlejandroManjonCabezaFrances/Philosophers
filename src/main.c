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

void	ft_malloc_struct_data(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	data->thread = malloc(sizeof(pthread_t) * data->n_philos);
}

void	ft_parse(t_data *data, int argc, char **argv)
{
	data->n_philos = ft_atoi_philo(argv[1]);
	data->philos->time_to_die = ft_atoi_philo(argv[2]);
	data->philos->time_to_eat = ft_atoi_philo(argv[3]);
	data->philos->time_to_sleep = ft_atoi_philo(argv[4]);
	if (argc == 6)
		data->philos->n_times_to_eat = ft_atoi_philo(argv[5]);
}

// #### data->n_philos (inicializarlo con alguna instancia o con malloc, SEGV) ####
int main(int argc, char **argv)
{
	// t_philo	philos;
	t_data	data;
	if (argc < 5 || argc > 6)
		ft_print_error("Numbers of arguments invaled");
	
	ft_parse(&data, argc, argv);
	ft_malloc_struct_data(&data);
	return (0);	
}