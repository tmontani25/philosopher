/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:53:14 by tmontani          #+#    #+#             */
/*   Updated: 2025/01/21 16:11:15 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_monitor_thread(t_philo **philo)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL,
			(void *(*)(void *))monitoring, philo) != 0)
	{
		perror("Error creating monitor thread");
		exit(EXIT_FAILURE);
	}
	if (pthread_join(monitor_thread, NULL) != 0)
		perror("Error joining monitor thread");
}

void	ft_usleep(long time)
{
	long	start;

	start = ft_current_time();
	while (ft_current_time() - start < time)
	{
		usleep(100);
	}
}

long	ft_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	check_death(t_philo **philo)
{
	int	i;

	i = 0;
	while (i < (*philo)->data_ptr->nb_philo)
	{
		if (ft_current_time() - (*philo)[i].last_meal >
				(*philo)[i].data_ptr->die)
			return (i);
		i++;
	}
	return (-1);
}

void	*monitoring(t_philo **philo)
{
	int	i;
	int	dead_philo;

	i = 0;
	while ((*philo)->data_ptr->simulation_active)
	{
		dead_philo = check_death(philo);
		if (dead_philo != -1)
		{
			ft_message(&(*philo)[dead_philo], "has died");
			return ((*philo)->data_ptr->simulation_active = 0, NULL);
		}
		if ((*philo)->data_ptr->nb_meal != -1)
		{
			while (i < (*philo)->data_ptr->nb_philo)
			{
				if ((*philo)[i].meals_eaten < (*philo)->data_ptr->nb_meal)
					break ;
				i++;
			}
		}
		if (i == (*philo)->data_ptr->nb_philo)
			return ((*philo)->data_ptr->simulation_active = 0, NULL);
	}
	return (NULL);
}
