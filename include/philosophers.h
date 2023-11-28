/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:29:49 by amanjon-          #+#    #+#             */
/*   Updated: 2023/11/28 08:02:38 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* --- LIBRARIES --- */
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <limits.h>
//# include <sys/wait.h> 
# include <sys/time.h>

/* -- TO FILES DESCRIPTOR -- */
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>

/* ---------- NEW ---------- */
# include <pthread.h>
# include <stdint.h> //para linux

/* ---------------- PATH ---------------- */
# include "../libft/Libft/include/libft.h"
# include "../libft/ft_printf/include/ft_printf.h"
# include "../libft/Gnl/include/get_next_line.h"

/* ------- MACROS ------- */
# define PATH_FD		"/Users/amanjon-/Desktop/philosophers_github/file.txt"
/* # define FALSE 		0
# define TRUE		1 */

/* ------- EMOJIS ------- */
# define	EAT			"is eating 🍉"
# define	SLEEP		"is sleeping 😴💤"
# define	DIE			"is died 💀"
# define	THINK		"is thinking 🤔⏳"
# define	TAKE_LEFT_FORK	"⭕ 🍽️🍴has taken a left fork🍽️🍴"
# define	TAKE_RIGHT_FORK	"🍴🍽️has taken a right fork🍴🍽️  ⭕"

/* ------- eNum ------- */
enum	e_bool	
{
	FALSE,
	TRUE
};

/* ------- PROTOTYPES ------- */
typedef struct s_philo t_philo;
typedef struct s_data t_data;

/* ------ STRUCT ------ */
typedef struct s_philo
{
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					finish_program;
	int					n_times_to_eat;
	int					id;
	uint64_t			last_meal;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*print_mutex;
	pthread_mutex_t		*lock;
	t_data				*data;
}	t_philo;

typedef struct s_data
{
	int					n_philos;
	uint64_t			start_time;
	pthread_t			*thread;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*print_mutex;
	pthread_mutex_t		*lock;
	t_philo				*philos;			//check por si puedo quitarlo
}	t_data;

/*---------- OPERATORS ----------*/

/* ----------------- FUNCTION MINISHELL----------------- */
int					main(int argc, char **argv);
int					ft_atoi_philo(const char *str);
int					ft_print_error(char *str);
void				ft_malloc_init_struct_data(char **argv, t_data *data);
void				ft_init_elems_and_create_threads(int argc, char **argv, t_data *data);
void				ft_init_mutex(t_data *data, int i);
void				ft_init_philo(int argc, char **argv, t_data *data, int i);
void				ft_print_status(t_philo *philo, char *action);
uint64_t			ft_get_time(void);
void				*ft_routine(void *philo_struct);
int					ft_usleep(unsigned int our_time);
void				ft_take_forks(t_philo *philo);
void				ft_drop_forks(t_philo *philo);

#endif