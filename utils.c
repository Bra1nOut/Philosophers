/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bra1nout <bra1nout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:50:35 by bra1nout          #+#    #+#             */
/*   Updated: 2025/08/06 23:16:04 by bra1nout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	print_action(t_rules *rules, int id, char *msg)
{
	pthread_mutex_lock(&rules->write_mutex);
	if (rules->all_alive)
		printf("%lld %d %s\n", timestamp() - rules->start_time, id, msg);
	pthread_mutex_unlock(&rules->write_mutex);
}

int	death_check(t_rules *rules)
{
	int	alive;

	pthread_mutex_lock(&rules->meal_check);
	alive = rules->all_alive;
	pthread_mutex_unlock(&rules->meal_check);
	return (alive);
}
