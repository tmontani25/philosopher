/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:35:44 by tmontani          #+#    #+#             */
/*   Updated: 2024/11/14 21:39:18 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_message(t_philo *philo, char *str)
{
    
    printf("philo %d: %s\n", philo->id, str);
}
void    *start(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    usleep(100);
    printf("philo id: %d\n", philo->id);
    if (philo->id % 2 == 0)
    {
        ft_message(philo, "has taken a fork");
        pthread_mutex_lock(philo->l_fork);
        ft_message(philo, "has taken a fork");
        pthread_mutex_lock(philo->r_fork);

        ft_message(philo, "is eating");
        usleep(philo->data_ptr->eat);
    }
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
    usleep(100);
      if (philo->id % 2 != 0)
    {
        // printf("philo impaires id: %d\n", philo->id);
        puts("");
    }
    return (NULL);
}

void create_threads(t_philo **philo, t_data *data)
{
    int i;

    i = 0;
    while (i < data->nb_philo)
    {
        // Création de chaque thread avec une pause pour observer les IDs dans l’ordre
        if (pthread_create(&(*philo)[i].thread, NULL, start, &(*philo)[i]) != 0)
        {
            perror("Error creating thread");
        }
        usleep(50); // Pause pour laisser chaque thread démarrer
        i++;
    }

    i = 0;
    while (i < data->nb_philo)
    {
        if (pthread_join((*philo)[i].thread, NULL) != 0)
        {
            perror("Error joining thread");
        }
        i++;
    }
}
