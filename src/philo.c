
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

int	ft_stop_routine(t_data *data)
{
	int stop;

	pthread_mutex_lock(&data->aux_mutex);
	stop = data->finish_program;
	pthread_mutex_unlock(&data->aux_mutex);
	return (stop);
}

void	ft_parse_and_init_struct_data(char **argv, t_data *data)
{
	data->n_philos = ft_atoi_philo(argv[1]);
	data->time_to_die = ft_atoi_philo(argv[2]);
	data->time_to_eat = ft_atoi_philo(argv[3]);
	data->time_to_sleep = ft_atoi_philo(argv[4]);
	if (argv[5])
		data->n_times_to_eat = ft_atoi_philo(argv[5]);
	data->finish_program = 0;
	data->start_time = ft_get_time();
}

int main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	if (argc < 5 || argc > 6)
	{
		printf("Numbers of arguments invaled");
		return (1);
	}
	ft_parse_and_init_struct_data(argv, &data);
	philo = NULL;
	philo = (t_philo *)malloc(sizeof(t_philo) * data.n_philos);
	if (philo == NULL)
	{
		printf("error malloc");
		return (1);
	}
	if (data.n_philos >= 1 && data.n_philos <= 200)
		ft_init_table(argc, philo, &data);
	else
	{	
		printf("Number of philosopher's is too many or 0");
		return (1);
	}
	return (0);
}
