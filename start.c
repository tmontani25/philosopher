/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:35:44 by tmontani          #+#    #+#             */
/*   Updated: 2024/11/26 15:37:37 by tmontani         ###   ########.fr       */
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

    while (1) // Une boucle infinie pour simuler la vie du philosophe
    {
        ft_message(philo, "is thinking");
        if (philo->id % 2 == 0) // Philosophes pairs prennent les fourchettes dans cet ordre
        {
            pthread_mutex_lock(philo->l_fork);
            ft_message(philo, "has taken a fork");
            pthread_mutex_lock(philo->r_fork);
            ft_message(philo, "has taken a fork");
        }
        else // Philosophes impairs prennent les fourchettes dans l'ordre inverse
        {
            pthread_mutex_lock(philo->r_fork);
            ft_message(philo, "has taken a fork");
            pthread_mutex_lock(philo->l_fork);
            ft_message(philo, "has taken a fork");
        }
        ft_message(philo, "is eating");
        usleep(philo->data_ptr->eat * 1000); // Convertir le temps en millisecondes

        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(philo->r_fork);
        ft_message(philo, "is sleeping");
        usleep(philo->data_ptr->sleep * 1000);
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
