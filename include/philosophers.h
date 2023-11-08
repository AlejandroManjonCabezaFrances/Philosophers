/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:29:49 by amanjon-          #+#    #+#             */
/*   Updated: 2023/11/08 15:05:42 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* --- LIBRARIES --- */
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h> 
# include <errno.h>
/* -- TO FILES DESCRIPTOR -- */
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
/* ---------- NEW ---------- */
#include <pthread.h>

/* ---------------- PATH ---------------- */
# include "../libft/Libft/include/libft.h"
# include "../libft/ft_printf/include/ft_printf.h"
# include "../libft/Gnl/include/get_next_line.h"

/* ------- MACROS ------- */
#define PATH_FD		"/Users/amanjon-/Desktop/philosophers_github/file.txt"

/* ------- EMOJIS ------- */
#define	EAT			"Going to eat 🍉"
#define	SLEEP		"Going to sleep 😴💤"
#define DIE			"Going to die 💀"
#define	THINK		"Going to think 👀"
#define FORK_LEFT	"🍽️🍴---left---"
#define FORK_RIGHT	"---right---🍴🍽️"

/* ------ STRUCT ------ */


/*---------- OPERATORS ----------*/



/* ----------------- FUNCTION MINISHELL----------------- */
int main(int argc, char **argv);

#endif