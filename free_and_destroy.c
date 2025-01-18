/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:30:21 by tmontani          #+#    #+#             */
/*   Updated: 2025/01/18 17:26:20 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "philo.h"

void	free_and_destroy(t_philo **philo, t_data *data)
{
	int	i;

	i = 0;
	if (data->fork_tab != NULL)
	{
		while (i < data->nb_philo)
		{
			pthread_mutex_destroy(&(data->fork_tab[i]));
			i++;
		}
		free(data->fork_tab);
		data->fork_tab = NULL;
	}
	if (*philo != NULL)
	{
		free(*philo);
		*philo = NULL;
	}
}
