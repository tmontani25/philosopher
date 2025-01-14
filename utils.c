/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:53:14 by tmontani          #+#    #+#             */
/*   Updated: 2025/01/14 16:21:03 by tmontani         ###   ########.fr       */
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

int check_death(t_philo **philo)
{
    int i;

    i = 0;
    while (i < (*philo)->data_ptr->nb_philo) // Assurez-vous que vous parcourez le tableau correctement
    {
        if (ft_current_time() - (*philo)[i].last_meal > (*philo)[i].data_ptr->die)
            return (1); // Vérifier si le philosophe est mort (temps écoulé depuis son dernier repas >= temps limite)
        i++; // N'oubliez pas d'incrémenter `i` pour avancer dans le tableau
    }
    return (0); // Aucun philosophe n'est mort
}

void *monitoring(t_philo **philo)
{
    int i;

    i = 0;
    while ((*philo)->data_ptr->simulation_active)
    {
        if (check_death(philo))
        {
            ft_message((*philo), "has died\n");
            (*philo)->data_ptr->simulation_active = 0;
            return (NULL);
        }
        if ((*philo)->data_ptr->nb_meal != -1)
        {
            while (i < (*philo)->data_ptr->nb_philo)
            {
                if ((*philo)[i].meals_eaten < (*philo)->data_ptr->nb_meal)
                    break;
                i++;
            }
        }
        if (i == (*philo)->data_ptr->nb_philo)
        {
            (*philo)->data_ptr->simulation_active = 0; // Arrêter la simulation
            return (NULL);
        }
    }
    return (NULL);
}




