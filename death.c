/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bra1nout <bra1nout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:39:21 by bra1nout          #+#    #+#             */
/*   Updated: 2025/07/05 17:45:48 by bra1nout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	death_check(t_philo *philo)
{
	long	time;
	time = get_time();
	pthread_mutex_lock(&philo->last_meal_mtx);
	if ((time - philo->last_meal) >= philo->rules->time_to_die)
	{
		pthread_mutex_unlock(&philo->last_meal_mtx);
		pthread_mutex_lock(&philo->rules->is_dead_mtx);
		if (philo->rules->is_dead == 0)
		{
			philo->rules->is_dead = 1;
			print_action("died", philo);
		}
		pthread_mutex_unlock(&philo->rules->is_dead_mtx);
		return (true);
	}
	pthread_mutex_unlock(&philo->last_meal_mtx);
	return (false);
}

void	*monitoring(void *arg)
{
	t_rules	*rules = (t_rules *)arg;
	int		i;

	while (1)
	{
		i = 0;
		while (i < rules->nb_philo)
		{
			pthread_mutex_lock(&rules->philo[i].meal_eated_mtx);
			pthread_mutex_lock(&rules->eat_count_mtx);

			if (death_check(&rules->philo[i]) == true ||
			    (rules->eat_count != 0 && rules->philo[i].meal_eated >= rules->eat_count))
			{
				pthread_mutex_unlock(&rules->philo[i].meal_eated_mtx);
				pthread_mutex_unlock(&rules->eat_count_mtx);
				return (NULL);
			}

			pthread_mutex_unlock(&rules->philo[i].meal_eated_mtx);
			pthread_mutex_unlock(&rules->eat_count_mtx);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

