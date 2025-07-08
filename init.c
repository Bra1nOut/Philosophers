/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bra1nout <bra1nout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:38:29 by bra1nout          #+#    #+#             */
/*   Updated: 2025/07/05 17:38:57 by bra1nout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_rules *rules)
{
	int i;

	i = 0;
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
	if (!rules->forks)
		return(1);
	while (i < rules->nb_philo)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
			return (1);
		printf("fork[%i]\n", i);
		i++;
	}
	if (pthread_mutex_init(&rules->print_mutex, NULL) != 0)
		return (1);
	return (0);
}

void	init_philo(t_rules *rules, pthread_t monitoring_t)
{
	int i;

	i = 0;
	rules->philo = malloc(sizeof(t_philo) * rules->nb_philo);
	while (i < rules->nb_philo)
	{
		rules->philo[i].id = i;
		rules->philo[i].left_fork = rules->forks[i];
		rules->philo[i].right_fork = rules->forks[(i + 1) % rules->nb_philo];
		rules->philo[i].last_meal = rules->start_time;
		rules->philo[i].meal_eated = 0;
		rules->philo[i].rules = rules;
		if (pthread_create(&rules->philo[i].thread, NULL, test, &rules->philo[i]) != 0)
			return ;
		i++;
	}
	if (pthread_create(&monitoring_t, NULL, monitoring, rules) != 0)
		return ;
}

int	init_all(t_rules *rules, pthread_t	monitoring, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (printf("Usage : ./philo nb_philo time_to_die time_to_eat time_to_sleep (eat_count)\n"));
	rules->nb_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->is_dead = false;
	if (argc == 6)
		rules->eat_count = ft_atoi(argv[5]);
	if (rules->time_to_die < 0 || rules->time_to_eat < 0 || rules->time_to_sleep < 0 || rules->eat_count < 0)
	{
		rules->is_running = false;
		return (printf("Error : Make sure every parameters are above 0 and are nums\n"));
	}
	rules->start_time = get_time();
	if (rules->nb_philo < 1)
		return (printf("At least 1 philosopher is needed\n"));
	init_mutexes(rules);
	init_philo(rules, monitoring);
	return (0);
}
