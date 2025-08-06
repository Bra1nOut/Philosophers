/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bra1nout <bra1nout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 22:48:22 by bra1nout          #+#    #+#             */
/*   Updated: 2025/08/06 22:49:42 by bra1nout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_rules rules)
{
	int	i;

	i = 0;
	while (i < rules.nb_philo)
	{
		pthread_join(rules.philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < rules.nb_philo)
	{
		pthread_mutex_destroy(&rules.forks[i]);
		i++;
	}
	pthread_mutex_destroy(&rules.write_mutex);
	pthread_mutex_destroy(&rules.meal_check);
	free(rules.forks);
	free(rules.philos);
}
