/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levincen <levincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:09:10 by levincen          #+#    #+#             */
/*   Updated: 2025/07/03 16:20:01 by levincen         ###   ########.fr       */
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
	usleep(philo->rules->time_to_eat * 1000);
	pthread_mutex_lock(&philo->last_meal_mtx);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->last_meal_mtx);
}
