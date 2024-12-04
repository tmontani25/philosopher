/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:53:14 by tmontani          #+#    #+#             */
/*   Updated: 2024/12/04 15:56:04 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_usleep(long time)
{
    long start;
    
    start = ft_current_time();
    while (ft_current_time() - start < time)
    {
        usleep(100);
    }
}
long ft_current_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000); // Convertir en millisecondes
}


void *monitoring(t_philo *philo)
{
    puts("salut");
    while (philo->data_ptr->simulation_active)
    {
        puts("inside\n");
        for (int i = 0; i < philo->data_ptr->nb_philo; i++) {
            pthread_mutex_lock(&philo->data_ptr->turn_mutex);
            if (ft_current_time() - philo->data_ptr->philos[i]->last_meal > philo->data_ptr->die) {
                ft_message(philo->data_ptr->philos[i], "died");
                philo->data_ptr->simulation_active = 0;
                pthread_mutex_unlock(&philo->data_ptr->turn_mutex);
                return (NULL);
            }
            pthread_mutex_unlock(&philo->data_ptr->turn_mutex);
        }
    }
    return (NULL);
}


