/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levincen <levincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:32:28 by levincen          #+#    #+#             */
/*   Updated: 2025/07/03 16:21:37 by levincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mutexes(t_rules *rules)
{
	free(rules->forks);
	if (rules->philo)
	{
		free(rules->philo);
		rules->philo = NULL;
	}
}

void	free_thread(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_join(rules->philo[i].thread, NULL);
		i++;
	}
}

void	shutdown_all(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_join(rules->philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&rules->print_mutex);
	pthread_mutex_destroy(&rules->start_time_mtx);

	if (rules->forks)
	{
		free(rules->forks);
		rules->forks = NULL;
	}
	if (rules->philo)
	{
		free(rules->philo);
		rules->philo = NULL;
	}
}

