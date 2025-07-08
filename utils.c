/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levincen <levincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:16:21 by levincen          #+#    #+#             */
/*   Updated: 2025/07/08 12:39:21 by levincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	smart_sleep(int duration, t_philo *philo)
{
	long	start;

	start = get_time();
	while (get_time() - start < duration)
	{
		if (death_check(philo))
			break ;
		usleep(1000);
	}
}

void	print_action(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->is_dead_mtx);
	if (philo->rules->is_dead)
	{
		pthread_mutex_unlock(&philo->rules->is_dead_mtx);
		return ;
	}
	pthread_mutex_unlock(&philo->rules->is_dead_mtx);
	pthread_mutex_lock(&philo->rules->start_time_mtx);
	printf("%lld %i %s\n", timestamp(philo->rules->start_time), philo->id, str);
	pthread_mutex_unlock(&philo->rules->start_time_mtx);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	signe;
	int	result;

	i = 0;
	signe = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (result * signe);
}

long	get_time(void)
{
	struct	timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

long long timestamp(long long start_time)
{
	return (get_time() - start_time);
}
