/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levincen <levincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:39:21 by bra1nout          #+#    #+#             */
/*   Updated: 2025/07/08 14:08:51 by levincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	death_check(t_philo *philo)
{
	long	time;

	time = get_time();
	if (!philo || !philo->rules)
		return false;
	pthread_mutex_lock(&philo->rules->is_dead_mtx);
	if (philo->rules->is_dead == true)
	{
		pthread_mutex_unlock(&philo->rules->is_dead_mtx);
		printf("%lld %i died\n", timestamp(philo->rules->start_time), philo->id);
		return (true);
	}
	pthread_mutex_unlock(&philo->rules->is_dead_mtx);
	return (false);
}

bool	death_calc(t_philo *philo)
{
	// pthread_mutex_lock(&philo->last_meal_mtx);
	// long diff = get_time() - philo->last_meal;
	// pthread_mutex_unlock(&philo->last_meal_mtx);

	// printf("Philo %d time since last meal: %ld ms (die if > %d)\n", philo->id, diff, philo->rules->time_to_die);
	pthread_mutex_lock(&philo->rules->is_dead_mtx);
	pthread_mutex_lock(&philo->last_meal_mtx);
	if ((get_time() - philo->last_meal) > philo->rules->time_to_die)
	{
		philo->rules->is_dead = true;
		pthread_mutex_unlock(&philo->rules->is_dead_mtx);
		pthread_mutex_unlock(&philo->last_meal_mtx);
		return (true);
	}
	pthread_mutex_unlock(&philo->last_meal_mtx);
	pthread_mutex_unlock(&philo->rules->is_dead_mtx);
	return (false);
}

void *monitoring(void *arg)
{
	t_rules *rules = (t_rules *)arg;
		int	i;
		int	finished;

	while (1)
	{
		i = 0;
		finished = 0;
		while (i < rules->nb_philo)
		{
			t_philo *philo = &rules->philo[i];
			pthread_mutex_lock(&philo->meal_eated_mtx);
			pthread_mutex_lock(&rules->eat_count_mtx);

			if (death_calc(philo) ||
				(rules->eat_count != 0 && philo->meal_eated >= rules->eat_count))
			{
				pthread_mutex_unlock(&philo->meal_eated_mtx);
				pthread_mutex_unlock(&rules->eat_count_mtx);
				return (NULL);
			}
			if (rules->eat_count > 0 && philo->meal_eated >= rules->eat_count)
				finished++;
			pthread_mutex_unlock(&philo->meal_eated_mtx);
			pthread_mutex_unlock(&rules->eat_count_mtx);
			i++;
		}
		if (rules->eat_count != -1 && finished == rules->nb_philo)
			return (NULL);
	}
	return (NULL);
}

