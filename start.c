/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:35:44 by tmontani          #+#    #+#             */
/*   Updated: 2024/11/29 16:14:17 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_message(t_philo *philo, char *str)
{
    printf("philo %d: %s\n", philo->id, str);
}

void *start(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (1) // Boucle infinie pour la simulation
    {
        ft_message(philo, "is thinking");

        // Synchronisation pour pairs et impairs
        pthread_mutex_lock(&philo->data_ptr->turn_mutex);
        while ((philo->id % 2 == 0 && philo->data_ptr->pair_turn == 0) ||
               (philo->id % 2 != 0 && philo->data_ptr->pair_turn == 1))
        {
            pthread_mutex_unlock(&philo->data_ptr->turn_mutex);
            usleep(100); // Petite pause avant de revérifier
            pthread_mutex_lock(&philo->data_ptr->turn_mutex);
        }
        pthread_mutex_unlock(&philo->data_ptr->turn_mutex);

        // Prendre les fourchettes et manger
        pthread_mutex_lock(philo->l_fork);
        ft_message(philo, "has taken a fork");
        pthread_mutex_lock(philo->r_fork);
        ft_message(philo, "has taken a fork");

        ft_message(philo, "is eating");
        philo->last_meal = current_time();
        philo->meals_eaten++;
        usleep(philo->data_ptr->eat * 1000); // Manger

        // Libérer les fourchettes
        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(philo->r_fork);

        // Alterner les tours (pairs/impairs)
        pthread_mutex_lock(&philo->data_ptr->turn_mutex);
        philo->data_ptr->pair_turn = !philo->data_ptr->pair_turn;
        pthread_mutex_unlock(&philo->data_ptr->turn_mutex);

        ft_message(philo, "is sleeping");
        usleep(philo->data_ptr->sleep * 1000); // Dormir
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
