/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:06:23 by amanjon-          #+#    #+#             */
/*   Updated: 2023/12/21 08:11:42 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/**
 * This function checks the exit of the loop "routine" when a thread dies
 * @param	t_data *data
 * @return	int
*/
int	ft_stop_routine(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->aux_mutex);
	stop = data->finish_program;
	pthread_mutex_unlock(&data->aux_mutex);
	return (stop);
}

/**
 * Parses arguments with ft_stoi_philo and initializes data struct
 * @param	char **argv, t_data *data
 * @return	void
*/
void	ft_parse_and_init_data_struct(char **argv, t_data *data)
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

/**
 * Parse, reserve dynamic memory for the philosophers array
 * and initialize the program
 * @param	int argc, char **argv
 * @return	int
*/
int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	if (argc < 5 || argc > 6)
	{
		printf("Numbers of arguments invaled");
		return (1);
	}
	ft_parse_and_init_data_struct(argv, &data);
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
