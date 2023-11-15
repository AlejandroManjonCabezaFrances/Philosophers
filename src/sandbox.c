/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 06:50:27 by amanjon-          #+#    #+#             */
/*   Updated: 2023/11/14 11:18:23 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/* ##############################  1  ############################## */
/* #######################  INICIALIZAR 1 HILO  ####################### */
// ejecutar : con make re

// O_APPEND = Al abrirse archivo añade nueva línea.
// Comprobar file descriptor diferente de -1 para escribir.
// void	*ft_thread_routine(void *arg)
// {
// 	int i;
// 	int n_lines;
// 	int fd;

// 	i = 0;
// 	n_lines = *((int *)arg);
// 	while (i < n_lines)
// 	{
// 		fd = open(PATH_FD, O_WRONLY | O_APPEND);
// 		write(fd, "nueva linea\n", 12);
// 		close(fd);
// 		i++;
// 	}
// 	return (NULL);
// }

// // pthread_create(identificador, atributos "por defecto", rutina del hilo,
// // argumento de entrada "numero de lineas pasado por argumentos") --> value = argv[1] --> n_lines

// // pthread_join(identificador, NULL "valor de retorno"); --> esta función evita que el programa acabe
// // sin que acabe el hilo de ejecutarse
// int main(int argc, char **argv)
// {
// 	(void) argc;
// 	(void) argv;

// 	pthread_t	thread1;
// 	int 		value;

// 	value = atoi(argv[1]);
// 	if (pthread_create(&thread1, NULL, ft_thread_routine, &value) != 0)
// 	{
// 		printf("pthread not created!!\n");
// 		return (-1);
// 	}
	
// 	pthread_join(thread1, NULL);
	
// 	return (0);
// }


/* ##############################  2  ############################## */
/* ############################  MUTEX  ############################ */
// ejecutar :  gcc sandbox.c -lpthread -o philosophers

static int count = 10;
pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;

void	*ft_thread1_routine(void *unused)
{
	int i;

	i = 0;
	while (i < 10000)
	{
		pthread_mutex_lock(&my_mutex);
		count++;
		pthread_mutex_unlock(&my_mutex);
		i++;
	}
	printf("count funcion 1 = %d\n", count);
	return (NULL);
}

void	*ft_thread2_routine(void *unused)
{
	int i;

	i = 0;
	while (i < 10000)
	{
		pthread_mutex_lock(&my_mutex);
		count--;
		pthread_mutex_unlock(&my_mutex);
		i++;
	}
	printf("count funcion 2 = %d\n", count);
	return (NULL);
}

void	ft_error_exit(char *error)
{
	perror(error);
	exit(1);
}

int main(int argc, char **argv)
{
	pthread_mutex_t my_mutex;
	pthread_t		thread1;
	pthread_t		thread2;
	
	if (pthread_create(&thread1, NULL, ft_thread1_routine, NULL) != 0)
	{
		ft_error_exit("thread1 cannnot be created!!\n");
	}
	if (pthread_create(&thread2, NULL, ft_thread2_routine, NULL) != 0)
	{
		ft_error_exit("thread1 cannnot be created!!\n");
	}
	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	printf("count value %d\n", count); // en el viceo solo muestra este printf, los demás son por check
	
	return (0);
}