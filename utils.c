/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:53:14 by tmontani          #+#    #+#             */
/*   Updated: 2024/11/28 19:14:51 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long current_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000); // Convertir en millisecondes
}

void *monitoring(void *arg)
{
    t_data *data = (t_data *)arg;

    while (data->simulation_active)
    {
        for (int i = 0; i < data->nb_philo; i++) {
            pthread_mutex_lock(&data->turn_mutex);
            if (current_time() - data->philos[i]->last_meal > data->die) {
                ft_message(data->philos[i], "died");
                data->simulation_active = 0;
                pthread_mutex_unlock(&data->turn_mutex);
                return (NULL);
            }
            pthread_mutex_unlock(&data->turn_mutex);
        }
        usleep(1000); // Vérification périodique
    }
    return (NULL);
}


