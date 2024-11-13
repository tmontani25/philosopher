/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:33:08 by tmontani          #+#    #+#             */
/*   Updated: 2024/11/13 16:11:55 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>


typedef struct s_data
{  
	int nb_philo;
	int die;
	int eat;
	int sleep;
	int nb_meal;
	pthread_mutex_t *fork_tab;
}           t_data;

typedef struct s_philo
{
	pthread_t	thread;
	int id;
	t_data *data_ptr;
	pthread_mutex_t *l_fork;
	pthread_mutex_t *r_fork;
}               t_philo;

//philo.c
void	init_data(t_data *data, char **argv);
void init_philos(t_philo **philo, int nb_philo);

//utils.c
void	*ft_memset(void *b, int c, size_t len);

//start
void    create_threads(t_philo **philo, t_data *data);

// assigner chaque fourchette de data
// aux fourchettes de la strucuture philo

#endif