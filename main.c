/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levincen <levincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:06:18 by levincen          #+#    #+#             */
/*   Updated: 2025/07/02 16:30:42 by levincen         ###   ########.fr       */
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

int	init_philo(t_rules *rules)
{
	int i;

	i = 0;
	rules->philo = malloc(sizeof(t_philo) * rules->nb_philo);
	if (!rules->philo)
		return (1);
	while (i < rules->nb_philo)
	{
		rules->philo[i].id = i;
		rules->philo[i].left_fork = rules->forks[i];
		rules->philo[i].right_fork = rules->forks[(i + 1) % rules->nb_philo];
		rules->philo[i].last_meal = rules->start_time;
		rules->philo[i].meal_eated = 0;
		rules->philo[i].is_dead = false;
		rules->philo[i].rules = rules;
		i++;
	}
	return (0);
}

int	init_all(t_rules *rules, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (printf("Usage : ./philo nb_philo time_to_die time_to_eat time_to_sleep (eat_count)\n"));
	rules->nb_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules->eat_count = ft_atoi(argv[5]);
	if (rules->time_to_die < 0 || rules->time_to_eat < 0 || rules->time_to_sleep < 0 || rules->eat_count < 0)
		return (printf("Error : Make sure every parameters are above 0 and are nums\n"));
	rules->start_time = get_time();
	if (rules->nb_philo < 1)
		return (printf("At least 1 philosopher is needed\n"));
	init_mutexes(rules);
	init_philo(rules);
	return (0);
}

int main(int argc, char **argv)
{
	t_rules	rules;
	init_all(&rules, argc, argv);
	printf("nb_philo : %i\n", rules.nb_philo);
	printf("time_to_die : %i\n", rules.time_to_die);
	printf("time_to_eat : %i\n", rules.time_to_eat);
	printf("time_to_sleep : %i\n", rules.time_to_sleep);
	printf("start_time : %lli\n", rules.start_time);
	printf("eat_count : %i\n", rules.eat_count);
	printf("\n");
	printf("/////////////////////////////////////\n");
	printf("\n");
	
	// int i = 0;
	// int num = ((i + 1) % rules.nb_philo);
	// while(i < rules.nb_philo)
	// {
	// 	printf("Philo n[%i] ID : %i\n", i, rules.philo[i].id);
	// 	printf("Philo n[%i] left_fork_num : %i\n", i, i);
	// 	printf("Philo n[%i] right_fork_num : %i\n", i, num);
	// 	printf("Philo n[%i] last_meal : %li\n", i, rules.philo[i].last_meal);
	// 	printf("Philo n[%i] meal_eated : %i\n", i, rules.philo[i].meal_eated);
	// 	i++;
	// 	num = ((i + 1) % rules.nb_philo);
	// }
	free_mutexes(&rules);
	return (0);
}
