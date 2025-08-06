/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bra1nout <bra1nout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:50:04 by bra1nout          #+#    #+#             */
/*   Updated: 2025/08/06 23:19:57 by bra1nout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parse_args(t_rules *rules, int argc, char **argv)
{
	rules->nb_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->eat_limit = -1;
	if (argc == 6)
		rules->eat_limit = ft_atoi(argv[5]);
	if (rules->nb_philo <= 0 || rules->time_to_die < 0
		|| rules->time_to_eat < 0 || rules->time_to_sleep < 0
		|| (argc == 6 && rules->eat_limit <= 0))
		return (1);
	rules->all_alive = 1;
	rules->start_time = timestamp();
	return (0);
}

static void	init_mutexes(t_rules *rules)
{
	int	i;

	i = 0;
	pthread_mutex_init(&rules->write_mutex, NULL);
	pthread_mutex_init(&rules->meal_check, NULL);
	while (i < rules->nb_philo)
	{
		pthread_mutex_init(&rules->forks[i], NULL);
		i++;
	}
}

static void	init_philos(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		rules->philos[i].id = i + 1;
		rules->philos[i].eat_count = 0;
		rules->philos[i].last_meal = timestamp();
		rules->philos[i].left_fork = &rules->forks[i];
		rules->philos[i].right_fork = &rules->forks[(i + 1) % rules->nb_philo];
		rules->philos[i].rules = rules;
		i++;
	}
}

int	init_all(t_rules *rules, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (printf("Error: wrong number of arguments\n"), 1);
	if (parse_args(rules, argc, argv))
		return (printf("Error: invalid arguments\n"), 1);
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
	rules->philos = malloc(sizeof(t_philo) * rules->nb_philo);
	if (!rules->forks || !rules->philos)
		return (1);
	init_mutexes(rules);
	init_philos(rules);
	return (0);
}
