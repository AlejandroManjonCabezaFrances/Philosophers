/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:29:49 by amanjon-          #+#    #+#             */
/*   Updated: 2023/12/19 14:59:51 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* --- LIBRARIES --- */
# include <errno.h>
# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdint.h> //para linux

/* ---------------- PATH ---------------- */
# include "../libft/Libft/include/libft.h"
# include "../libft/ft_printf/include/ft_printf.h"
# include "../libft/Gnl/include/get_next_line.h"

/* ------- MACROS ------- */
# define PATH_FD		"/Users/amanjon-/Desktop/philosophers_github/file.txt"
# define START_I 		0

/* ------- EMOJIS ------- */
# define	EAT			"is eating 🍉"
# define	SLEEP		"is sleeping 😴💤"
# define	DIE			"is died 💀"
# define	THINK		"is thinking 🤔⏳"
# define	TAKE_RIGHT_FORK	"🍴🍽️ has taken a right fork 🍴🍽️  ⭕⭕"
# define	TAKE_LEFT_FORK	" 🍽️🍴 has taken a left fork 🍽️🍴  ⭕"

/* ------- eNum ------- */
enum e_status{
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
typedef struct s_philo t_philo;
typedef struct s_data t_data;

/* ------ STRUCT ------ */
typedef struct s_philo
{
	int					id;
	uint64_t			last_meal;
	int					count_meals;
	int					left_fork;
	int					*right_fork;
	int					status;
	int					status_changed;
	pthread_mutex_t		l_fork;			// se inicializa
	pthread_mutex_t		*r_fork;		// no se inicializa
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
	t_philo				*philos;			//check por si puedo quitarlo
}	t_data;

/*---------- OPERATORS ----------*/

/* ----------------- FUNCTION PHILO----------------- */
int					main(int argc, char **argv);
void				ft_parse_and_init_struct_data(char **argv, t_data *data);
void				ft_init_table(int argc, t_philo *philo, t_data *data);
int					ft_init_mutex(t_data *data, t_philo *philo);
void				ft_init_forks_right(int n_philos, t_philo *philo);
int					ft_init_threads(t_philo *philo);
void				*ft_routine(void *philo_struct);
void				ft_take_forks_and_eat(t_philo *philo, u_int64_t time);
void				ft_drop_forks(t_philo *philo);
void				ft_sleep_and_think(t_philo *philo);
void				ft_join_threads(t_data *data ,t_philo *philo);
void				ft_destroy_threads(t_data *data ,t_philo *philo);
void				ft_death(t_philo *philo);
int					ft_stop_routine(t_data *data);
// void				ft_synchronization(t_philo *philo);
void				ft_init_philos(int argc, t_data *data, t_philo *philo);

/*---------- NO CHECKS ----------*/
// int					ft_print_error(char *str);
int					ft_atoi_philo(const char *str);
void				ft_print_status(t_philo *philo, char *action, uint64_t time);
uint64_t			ft_get_time(void);
int					ft_usleep(unsigned int our_time);

#endif
