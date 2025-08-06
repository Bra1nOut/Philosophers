/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bra1nout <bra1nout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:51:21 by bra1nout          #+#    #+#             */
/*   Updated: 2025/08/06 23:16:32 by bra1nout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_one_philo(t_philo *philo)
{
	print_action(philo->rules, philo->id, "has taken a fork");
	sleep_precise(philo->rules->time_to_die);
	pthread_mutex_lock(&philo->rules->write_mutex);
	printf("%lld %d died\n", timestamp() - philo->rules->start_time, philo->id);
	pthread_mutex_unlock(&philo->rules->write_mutex);
	pthread_mutex_lock(&philo->rules->meal_check);
	philo->rules->all_alive = 0;
	pthread_mutex_unlock(&philo->rules->meal_check);
}

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo->rules, philo->id, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_action(philo->rules, philo->id, "has taken a fork");
	pthread_mutex_lock(&philo->rules->meal_check);
	print_action(philo->rules, philo->id, "is eating");
	philo->last_meal = timestamp();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->rules->meal_check);
	sleep_precise(philo->rules->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	philo_sleep(t_philo *philo)
{
	print_action(philo->rules, philo->id, "is sleeping");
	sleep_precise(philo->rules->time_to_sleep);
}

static void	philo_think(t_philo *philo)
{
	print_action(philo->rules, philo->id, "is thinking");
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->rules->nb_philo == 1)
	{
		handle_one_philo(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (death_check(philo->rules))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
