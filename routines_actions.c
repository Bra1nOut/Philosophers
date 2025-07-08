/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_actions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levincen <levincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:09:10 by levincen          #+#    #+#             */
/*   Updated: 2025/07/08 13:52:43 by levincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *philo)
{
	print_action("is sleeping", philo);
	usleep(philo->rules->time_to_sleep * 1000);
}

void	thinking(t_philo *philo)
{
	print_action("is thinking", philo);
	usleep(5000);
}

void	eating(t_philo *philo)
{
	print_action("has taken a fork", philo);
	print_action("has taken a fork", philo);
	print_action("is eating", philo);
	pthread_mutex_lock(&philo->last_meal_mtx);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->last_meal_mtx);
	usleep(philo->rules->time_to_eat * 1000);
	pthread_mutex_lock(&philo->meal_eated_mtx);
	philo->meal_eated++;
	pthread_mutex_unlock(&philo->meal_eated_mtx);
}

void	eat_priority(t_philo *philo, int i)
{
	if (i % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork);
		pthread_mutex_lock(&philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork);
		pthread_mutex_lock(&philo->left_fork);
	}
	if (death_check(philo) == false)
		eating(philo);
	if (i % 2 == 0)
	{
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
	}
}
