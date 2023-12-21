/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:29:49 by amanjon-          #+#    #+#             */
/*   Updated: 2023/12/21 10:55:43 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* --- LIBRARIES --- */
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdint.h>
# include <pthread.h>
# include <sys/time.h>

/* ------- MACROS ------- */
# define PATH_FD		"/Users/amanjon-/Desktop/philosophers_github/file.txt"

/* ------- EMOJIS ------- */
# define EAT			"is eating 🍉"
# define SLEEP		"is sleeping 😴💤"
# define DIE			"is died 💀"
# define THINK		"is thinking 🤔⏳"
# define TAKE_RIGHT_FORK	"🍴🍽️ has taken a right fork 🍴🍽️  ⭕⭕"
# define TAKE_LEFT_FORK	" 🍽️🍴 has taken a left fork 🍽️🍴  ⭕"

// # define EAT			"is eating "
// # define SLEEP		"is sleeping "
// # define DIE			"is died "
// # define THINK		"is thinking "
// # define TAKE_RIGHT_FORK	"has taken a right fork "
// # define TAKE_LEFT_FORK	" has taken a left fork "

/* ------- eNum ------- */
enum e_status
{
	EATTING,
	SLEEPING,
	THINKING,
	DYING
};

enum	e_bool
{
	FALSE,
	TRUE
};

enum	e_status_table
{
	TABLE,
	LEFT_HAND,
	RIGHT_HAND
};

/* ------- PROTOTYPES ------- */
typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

/* ------ STRUCT ------ */
typedef struct s_philo
{
	int					id;
	int					count_meals;
	int					status;
	int					status_changed;
	int					left_fork;
	int					*right_fork;
	uint64_t			last_meal;
	pthread_mutex_t		l_fork;
	pthread_mutex_t		*r_fork;
	pthread_t			thread;
	t_data				*data;
}	t_philo;

typedef struct s_data
{
	int					n_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					n_times_to_eat;
	int					finish_program;
	int					pause;
	int					min_pause;
	uint64_t			start_time;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		aux_mutex;
	t_philo				*philos;
}	t_data;

/* ----------------- FUNCTION PHILO----------------- */
uint64_t	ft_get_time(void);
int			ft_print_error(char *str);
int			main(int argc, char **argv);
int			ft_stop_routine(t_data *data);
int			ft_atoi_philo(const char *str);
int			ft_init_threads(t_philo *philo);
int			ft_init_mutex(t_data *data, t_philo *philo);
void		ft_death(t_philo *philo);
void		ft_drop_forks(t_philo *philo);
void		*ft_routine(void *philo_struct);
void		ft_synchronization(t_philo *philo);
void		ft_sleep_and_think(t_philo *philo);
void		ft_join_threads(t_data *data, t_philo *philo);
void		ft_destroy_threads(t_data *data, t_philo *philo);
void		ft_init_forks_right(t_data *data, t_philo *philo);
void		ft_init_table(int argc, t_philo *philo, t_data *data);
void		ft_take_forks_and_eat(t_philo *philo, u_int64_t time);
void		ft_init_philos(int argc, t_data *data, t_philo *philo);
void		ft_parse_and_init_data_struct(char **argv, t_data *data);
void		ft_print_status(t_philo *philo, char *action, uint64_t time);

#endif
