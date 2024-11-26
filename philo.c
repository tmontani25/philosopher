/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmontani <tmontani@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:54:00 by tmontani          #+#    #+#             */
/*   Updated: 2024/11/14 21:12:51 by tmontani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

// fonction qui initialise les structures philo
void	create_philo(t_data *data, t_philo **philo)
{
	int i;

	i = -1;
	while (++i < data->nb_philo)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].data_ptr = data;
		(*philo)[i].l_fork = &data->fork_tab[i];
		(*philo)[i].r_fork = &data->fork_tab[(i + 1) % data->nb_philo];
	}
	return ;
	//une structure philo a ete cree par philo
	//assigner chaque structure philo a un thread
	
}

void init_philos(t_philo **philo, int nb_philo)
{
    *philo = malloc(sizeof(t_philo) * nb_philo);
    if (*philo == NULL)
    {
        perror("Error malloc");
        exit(1);
    }
}

void	init_data(t_data *data, char **argv)
{
	int i;

	i = 0;
	data->nb_philo = atoi(argv[1]);
	data->die = atoi(argv[2]);
	data->eat = atoi(argv[3]);
	data->sleep = atoi(argv[4]);
	data->nb_meal = atoi(argv[5]);
	printf("%d\n", data->nb_philo);
	data->fork_tab = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	while (i < data->nb_philo)
    {
        pthread_mutex_init(&(data->fork_tab[i]), NULL);  // Initialisation de chaque mutex
		i++;
    }
	i = 0;
	return ;
}

int main(int argc, char *argv[])
{
	t_data data;
	t_philo *philo;

	philo = NULL;
	if (argc != 6)
	{
		write(1, "wrong nb of arguments\n", 22);
		return (0);
	}
	init_data(&data, argv);
	init_philos(&philo, data.nb_philo);
	create_philo(&data, &philo);
	create_threads(&philo, &data);
	//initialiser chaque thread
	//initialiser la structure pour chaque thread
	//assigner les fourchettes de data a chaque thread
	// commencer la simulation
	
}
