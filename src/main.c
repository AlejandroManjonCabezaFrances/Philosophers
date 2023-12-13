
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






// void	ft_init_philo(char **argv, t_data *data, int i)
// {
// 	data->time_to_die = ft_atoi_philo(argv[2]);
// 	data->time_to_eat = ft_atoi_philo(argv[3]);
// 	data->time_to_sleep = ft_atoi_philo(argv[4]);
// 	if (argv[5])
// 		data->n_times_to_eat = ft_atoi_philo(argv[5]);
// 	else
// 		data->n_times_to_eat = -1;
// 	data->philos[i].id = i + 1;
// 	data->philos[i].last_meal = 0;
// 	data->philos[i].data = data;
// 	data->philos[i].left_fork = 0;
// 	data->philos[i].right_fork = NULL;
// 	// data->philos[i].r_fork = NULL;
// 	data->finish_program = 0;
// 	data->start_time = ft_get_time();
// }

// void	ft_take_forks(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->l_fork);			// prueba Ángel
// 	if (philo->left_fork == TABLE)
// 	{
// 		philo->left_fork = LEFT_HAND;
// 		ft_print_status(philo, TAKE_LEFT_FORK);
// 	}
// 	// pthread_mutex_lock(philo->r_fork);			// prueba Ángel
// 	if (*philo->right_fork == /* (int *) */TABLE)
// 	{
// 		*philo->right_fork = RIGHT_HAND;
// 		ft_print_status(philo, TAKE_RIGHT_FORK);
// 	}
// }

// void	ft_drop_forks(t_philo *philo)
// {
// 	pthread_mutex_unlock(&philo->l_fork);		// prueba Ángel
// 	pthread_mutex_unlock(philo->r_fork);		// prueba Ángel
// 	ft_print_status(philo, SLEEP);
// 	ft_usleep(philo->data->time_to_sleep);
// }

// void	ft_eating(t_philo *philo)
// {
// 	if (philo->left_fork == LEFT_HAND && *philo->right_fork == RIGHT_HAND)
// 	{
// 		philo->last_meal = ft_get_time() - philo->data->start_time;
// 		ft_print_status(philo, EAT);
// 	}
// }

// void	ft_philo_eat(t_philo *philo)
// {
// 	while (philo->data->finish_program == 0)
// 	{
// 		//pthread_mutex_unlock(philo->data->print_mutex);	// 1 -> entrada función
// 		ft_take_forks(philo);
// 		pthread_mutex_lock(philo->data->lock);
// 		ft_eating(philo);
// 		/* philo->last_meal = ft_get_time() - philo->data->start_time;
// 		ft_print_status(philo, EAT); */
// 		pthread_mutex_unlock(philo->data->lock);
// 		ft_usleep(philo->data->time_to_eat);
// 		ft_drop_forks(philo);
// 		ft_print_status(philo, THINK);
// 		//pthread_mutex_lock(philo->data->print_mutex);	// 2 -> salida función
// 	}
// }

// void	*ft_routine(void *philo_struct)
// {
// 	t_philo *philo;

// 	philo = (t_philo *)philo_struct;
// 	if (philo->id % 2 == 0)
// 		ft_usleep(50);		// 200
// 	//pthread_mutex_lock(philo->data->print_mutex);		// 1 -> entrada función
// 	ft_philo_eat(philo);
// 	//pthread_mutex_unlock(philo->data->print_mutex);	// 2 -> salida función
// 	return (NULL);
// }








void	*ft_routine(void *philo_struct)
{
	t_philo *philo;

	philo = (t_philo *)philo_struct;
	
	// ft_philo_eat(philo);
	return (0);
}

/**
 * int pthread_create(pthread_t *thread, const pthread_attr_t *attr,void *(*start_routine) (void *), void *arg);
 * This function 
 * @param	void
 * @return	void
*/
void	ft_init_threads(t_philo *philo, int i)
{
	i = 0;
	while (i < philo->data->n_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, &ft_routine, &philo[i]) != 0)
			ft_print_error("error creating thread\n");
		i++;
	}
}

/**
 * int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
 * This function initialize the mutexes and ensures that the last philosopher `s
 * left fork assignment is correctly connected to the first fork in the table.
 * @param	void
 * @return	void
*/
int	ft_init_mutex(t_data *data, t_philo *philo, int i)
{
	i = 0;
	if (pthread_mutex_init(&data->lock, NULL) != 0)
	{
		printf("error init mutex: lock");
		return (1);
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		printf("error init mutex: print_mutex");
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

/**
 * The pointers of the right fork and the right fork mutex are initialized
 * in a loop for each thread, the right fork = memory address of the left
 * fork of the next thread
 * @param	t_data *data
 * @return	void
*/
void	ft_init_forks_right(int n_philos, t_philo *philo, int i)
{
	int pos_philo;

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

void	ft_init_mutex_philos_forks_threads(t_philo *philo, t_data *data, int i)
{
	ft_init_mutex(data, philo, START_I);
	while (i < data->n_philos)
	{
		philo[i].id = i + 1;
		philo[i].last_meal = 0;
		philo[i].data = data;
		philo[i].left_fork = 0;
		philo[i].right_fork = NULL;
		philo[i].r_fork = NULL;
		i++;
	}
	ft_init_forks_right(data->n_philos, philo, START_I);
	i = START_I;
	ft_init_threads(philo, START_I);
}

void	ft_parse_and_init_struct_data(int argc, char **argv, t_data *data)
{
	argc = 0;

	data->n_philos = ft_atoi_philo(argv[1]);
	data->time_to_die = ft_atoi_philo(argv[2]);
	data->time_to_eat = ft_atoi_philo(argv[3]);
	data->time_to_sleep = ft_atoi_philo(argv[4]);
	if (argv[5])
		data->n_times_to_eat = ft_atoi_philo(argv[5]);
	else
		data->n_times_to_eat = -1;
	data->finish_program = 0;
	data->start_time = ft_get_time();
}

int main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;
	int i;

	if (argc < 5 || argc > 6)
		ft_print_error("Numbers of arguments invaled");
	ft_parse_and_init_struct_data(argc, argv, &data);
	philo = NULL;
	philo = (t_philo *)malloc(sizeof(t_philo) * data.n_philos);
	if (philo == NULL)
	{
		ft_print_error("error malloc");
		return (1);
	}
	if (data.n_philos >= 1 && data.n_philos <= 200)
		ft_init_mutex_philos_forks_threads(philo, &data, START_I);
	else	
		printf("Number of philosopher's is too many or 0");
	// pthread_join(*data.thread, NULL);
	i = 0;
	while (i < data.n_philos)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
		// printf("data.n_philos = %d\n", data.n_philos);
		// printf("i = %d\n", i);
	}
	
	// if (pthread_mutex_destroy(&data.lock) != 0)
	// {
    //     perror("Error al destruir el mutex");
    //     return 1; // Manejo de error
	// }
	// if (pthread_mutex_destroy(&data.print_mutex) != 0)
	// {
    // 	perror("Error al destruir el mutex");
    //     return 1; // Manejo de error
	// }
	// i = 0;
	// while (i < data.n_philos)
	// {
	// 	if (pthread_mutex_destroy(&data.philos[i].l_fork) != 0)
	//   	{
    // 		perror("Error al destruir el mutex");
    // 		return 1; // Manejo de error
	//   	}
	// 	i++;
	// }
	printf("fin programa\n");
	return (0);
}
