/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:35:44 by tmontani          #+#    #+#             */
/*   Updated: 2025/01/21 15:06:41 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_philo *philo)
{
	ft_message(philo, "is sleeping");
	ft_usleep(philo->data_ptr->sleep);
	ft_message(philo, "is thinking");
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	ft_message(philo, "has taken left fork");
	if (philo->data_ptr->simulation_active == 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(&philo->data_ptr->turn_mutex);
		return ;
	}
	if (philo->data_ptr->nb_philo == 1)
	{
		ft_message(philo, "has died");
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(&philo->data_ptr->turn_mutex);
		philo->data_ptr->simulation_active = 0;
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	ft_message(philo, "has taken right fork");
	ft_message(philo, "is eating");
	philo->last_meal = ft_current_time();
	philo->meals_eaten++;
	ft_usleep(philo->data_ptr->eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	ft_message(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data_ptr->turn_mutex);
	if (philo->data_ptr->simulation_active == 0)
	{
		pthread_mutex_unlock(&philo->data_ptr->turn_mutex);
		return ;
	}
	printf("%ld %ld %s\n", ft_current_time()
		- philo->data_ptr->time_start, philo->id, str);
	pthread_mutex_unlock(&philo->data_ptr->turn_mutex);
}

void	*start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id & 1)
		ft_usleep(philo->data_ptr->sleep);
	while (1)
	{
		if (philo->data_ptr->simulation_active == 0)
		{
			if (philo->l_fork)
				pthread_mutex_unlock(philo->l_fork);
			pthread_mutex_unlock(&philo->data_ptr->turn_mutex);
			return (NULL);
		}
		ft_eat(philo);
		ft_sleep(philo);
		pthread_mutex_unlock(&philo->data_ptr->turn_mutex);
	}
	return (NULL);
}

void	create_threads(t_philo **philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&(*philo)[i].thread, NULL, start, &(*philo)[i]) != 0)
		{
			perror("Error creating philosopher thread");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	create_monitor_thread(philo);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join((*philo)[i].thread, NULL) != 0)
			perror("Error joining philosopher thread");
		i++;
	}
	free_and_destroy(philo, data);
}
