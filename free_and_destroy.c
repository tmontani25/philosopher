/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:30:21 by tmontani          #+#    #+#             */
/*   Updated: 2025/01/16 15:02:43 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_and_destroy(t_philo **philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&(data->fork_tab[i]));
		i++;
	}
	free(data->fork_tab);
	pthread_mutex_destroy(&data->turn_mutex);
	i = 0;
	while (i < data->nb_philo)
	{
		free(philo[i]);
		i++;
	}
	free(data->philos);
}
