/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:35:44 by tmontani          #+#    #+#             */
/*   Updated: 2025/01/09 17:04:53 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_philo *philo)
{
	ft_message(philo, "is sleeping");
	ft_usleep(philo->data_ptr->sleep);
	ft_message(philo, "is thinking");
}
void    ft_eat(t_philo *philo)
{
		// Prendre les fourchettes et manger
	pthread_mutex_lock(philo->l_fork);
	ft_message(philo, "has taken left fork");
	if (philo->data_ptr->simulation_active == 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(&philo->data_ptr->turn_mutex);
		return ;
	}
	if (philo->data_ptr->nb_philo == 1) // si il y a qu'un philo r_fork et l_fork sont les memes
	{
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
	ft_usleep(philo->data_ptr->eat); // Manger

	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
void    ft_message(t_philo *philo, char *str)
{
    pthread_mutex_lock(&philo->data_ptr->turn_mutex);
	if (philo->data_ptr->simulation_active == 0)
	{ 
		pthread_mutex_unlock(&philo->data_ptr->turn_mutex);
		return ;
	}
	printf("%ld %ld %s\n", ft_current_time() - philo->data_ptr->time_start, philo->id, str);
	pthread_mutex_unlock(&philo->data_ptr->turn_mutex);
}

void *start(void *arg)
{
	t_philo *philo = (t_philo *)arg;
		// Synchronisation pour pairs et impairs
		// pthread_mutex_lock(&philo->data_ptr->turn_mutex);
	if (philo->id & 1)
		ft_usleep(philo->data_ptr->sleep);
		// pthread_mutex_unlock(&philo->data_ptr->turn_mutex);
	while (1) // Boucle infinie pour la simulation
	{
		// pthread_mutex_lock(&philo->data_ptr->turn_mutex);
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

void create_threads(t_philo **philo, t_data *data)
{
    int i;
	pthread_t monitor_thread;
	
    i = 0;
    while (i < data->nb_philo)
    {
        if (pthread_create(&(*philo)[i].thread, NULL, start, &(*philo)[i]) != 0)
        {
            perror("Error creating philosopher thread");
            exit(EXIT_FAILURE); // Arrêt en cas d'erreur critique
        }
        usleep(100); // Petite pause pour synchroniser
        i++;
    }
    if (pthread_create(&monitor_thread, NULL, (void *(*)(void *))monitoring, philo) != 0)
    {
        perror("Error creating monitor thread");
        exit(EXIT_FAILURE); // Arrêt en cas d'erreur critique
    }
    i = 0;
    while (i < data->nb_philo)
    {
        if (pthread_join((*philo)[i].thread, NULL) != 0)
            perror("Error joining philosopher thread");
        i++;
    }
    if (pthread_join(monitor_thread, NULL) != 0)
        perror("Error joining monitor thread");
}

