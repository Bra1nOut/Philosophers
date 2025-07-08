/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levincen <levincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 09:48:45 by levincen          #+#    #+#             */
/*   Updated: 2025/07/08 13:43:23 by levincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	limited_routine(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->meal_eated_mtx);
		pthread_mutex_lock(&philo->rules->eat_count_mtx);
		if (philo->meal_eated == philo->rules->eat_count)
		{
			pthread_mutex_unlock(&philo->rules->eat_count_mtx);
			pthread_mutex_unlock(&philo->meal_eated_mtx);
			break ;
		}
		pthread_mutex_unlock(&philo->rules->eat_count_mtx);
		pthread_mutex_unlock(&philo->meal_eated_mtx);
		if (death_check(philo))
			return ;
		thinking(philo);
		if (death_check(philo))
			return ;
		eat_priority(philo, philo->id);
		if (death_check(philo))
			return ;
		sleeping(philo);
		if (death_check(philo))
			return ;
	}
}

void	routine_no_meal(t_philo *philo)
{
	while (death_check(philo) == false)
	{
		thinking(philo);
		if (death_check(philo))
			return ;
		eat_priority(philo, philo->id);
		if (death_check(philo))
			return ;
		sleeping(philo);
		if (death_check(philo))
			return ;
	}
}

void	*solo(void *ptr)
{
	t_rules	*rules;

	rules = (t_rules *)ptr;
	printf("%lld %i is thinking\n", timestamp(rules->start_time), rules->philo->id);
	usleep(5000);
	printf("%lld %i take a fork\n", timestamp(rules->start_time), rules->philo->id);
	usleep(rules->time_to_die * 1000);
	printf("%lld %i died\n", timestamp(rules->start_time), rules->philo->id);
	return (NULL);
}

void	one_philo(t_rules *rules)
{
	rules->philo = malloc(sizeof(t_philo));
	init_mutexes(rules);
	if (!rules->philo)
		return ;
	rules->start_time = get_time();
	rules->philo->id = 1;
	rules->philo->rules = rules;
	rules->philo->left_fork = rules->forks[0];
	rules->philo->last_meal = rules->start_time;
	rules->philo->meal_eated = 0;
	if (pthread_create(&rules->philo->thread, NULL, solo, rules) != 0)
		return ;
}

void	*routine_choose(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(&philo->rules->eat_count_mtx);
	if (philo->rules->eat_count == 0)
	{
		pthread_mutex_unlock(&philo->rules->eat_count_mtx);
		routine_no_meal(philo);
	}
	else
	{
		pthread_mutex_unlock(&philo->rules->eat_count_mtx);
		limited_routine(philo);
	}
	return (NULL);
}
