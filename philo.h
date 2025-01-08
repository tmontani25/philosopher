/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:33:08 by tmontani          #+#    #+#             */
/*   Updated: 2025/01/08 16:12:54 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>

typedef struct s_philo t_philo;
typedef struct s_data t_data;

typedef struct s_data
{  
	long nb_philo;
	long die;
	long eat;
	long sleep;
	long nb_meal;
	long	pair_turn;
	int	simulation_active;
	long time_start;
	pthread_mutex_t sim_mutex;
	pthread_mutex_t	turn_mutex;
	pthread_mutex_t *fork_tab;
	t_philo	**philos;
}           t_data;

typedef struct s_philo
{
	pthread_t	thread;
	long id;
	t_data *data_ptr;
	pthread_mutex_t *l_fork;
	pthread_mutex_t *r_fork;
	long meals_eaten;
	long	last_meal;
}               t_philo;



//philo.c
void	init_data(t_data *data, char **argv);
void init_philos(t_philo **philo, int nb_philo);

//utils.c
long ft_current_time(void);
void *monitoring(t_philo **philo);
void ft_usleep(long time);

//start
void    create_threads(t_philo **philo, t_data *data);
void    ft_message(t_philo *philo, char *str);
void	ft_sleep(t_philo *philo);
void    ft_eat(t_philo *philo);

// assigner chaque fourchette de data
// aux fourchettes de la strucuture philo

#endif