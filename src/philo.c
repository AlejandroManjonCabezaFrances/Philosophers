
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

void	ft_sleep_and_think(t_philo *philo)
{
	philo->status = THINKING;
	ft_print_status(philo, THINK, philo->last_meal + philo->data->time_to_eat + philo->data->time_to_sleep);
	if (philo->count_meals > 0)
		philo->count_meals--;
}

void	ft_death(t_philo *philo)
{
	u_int64_t	time;

	pthread_mutex_lock(&philo->data->aux_mutex);
	if (philo->data->finish_program == 0)
	{
		philo->data->finish_program = 1;
		pthread_mutex_lock(&philo->data->print_mutex);
		time = philo->last_meal + philo->data->time_to_die;
		printf("time:%llums | philo:%d | action: %s\n", time - philo->data->start_time, philo->id, DIE);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	pthread_mutex_unlock(&philo->data->aux_mutex);
}

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

/**
 * int pthread_create(pthread_t *thread, const pthread_attr_t *attr,void *(*start_routine) (void *), void *arg);
 * This function 
 * @param	void
 * @return	void
*/
void	ft_init_threads(t_philo *philo/* , int i */)
{
	int i;

	i = 0;
	while (i < philo->data->n_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, &ft_routine, &philo[i]) != 0)
			ft_print_error("error creating even thread\n");
		i = i + 2;
	}
	usleep(25);
	i = 1;
	while (i < philo->data->n_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, &ft_routine, &philo[i]) != 0)
			ft_print_error("error creating odd thread\n");
		i = i + 2;
	}
}

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
/**
 * int pthread_mutex_destroy(pthread_mutex_t *mutex);
 * @param	t_philo *philo, t_data *data
 * @return	void
*/
void	ft_join_threads(t_data *data ,t_philo *philo)
{
	int i;

	i = -1;
	while (++i < data->n_philos)
		pthread_join(philo[i].thread, NULL);
	i = -1;
	while (++i < data->n_philos)
		pthread_mutex_destroy(&philo[i].l_fork);
}

void	ft_destroy_threads(t_data *data ,t_philo *philo)
{
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->aux_mutex);
	free (philo);
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

void	ft_init_table(int argc, t_philo *philo, t_data *data)
{
	ft_init_mutex(data, philo);
	ft_init_philos(argc, data, philo);
	ft_init_forks_right(data->n_philos, philo);
	ft_init_threads(philo);
	ft_join_threads(data, philo);
	ft_destroy_threads(data, philo);
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
