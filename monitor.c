/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bra1nout <bra1nout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:51:58 by bra1nout          #+#    #+#             */
/*   Updated: 2025/08/06 23:17:44 by bra1nout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_deaths(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_lock(&rules->meal_check);
		if (diff_time(rules->philos[i].last_meal,
				timestamp()) > rules->time_to_die && rules->all_alive)
		{
			rules->all_alive = 0;
			pthread_mutex_lock(&rules->write_mutex);
			printf("%lld %d died\n",
				timestamp() - rules->start_time, rules->philos[i].id);
			pthread_mutex_unlock(&rules->write_mutex);
		}
		pthread_mutex_unlock(&rules->meal_check);
		usleep(1000);
		i++;
	}
}

static int	check_all_ate(t_rules *rules)
{
	int	i;
	int	done;

	i = 0;
	done = 1;
	while (i < rules->nb_philo)
	{
		pthread_mutex_lock(&rules->meal_check);
		if (rules->philos[i].eat_count < rules->eat_limit)
			done = 0;
		pthread_mutex_unlock(&rules->meal_check);
		i++;
	}
	return (done);
}

void	monitor(t_rules *rules)
{
	while (rules->all_alive)
	{
		check_deaths(rules);
		if (rules->eat_limit > 0 && check_all_ate(rules))
		{
			rules->all_alive = 0;
			break ;
		}
	}
}
