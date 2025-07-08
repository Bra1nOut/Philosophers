/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bra1nout <bra1nout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:06:18 by levincen          #+#    #+#             */
/*   Updated: 2025/07/05 17:49:42 by bra1nout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*test(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *)ptr;
	sleeping(philo);
	thinking(philo);
	eating(philo);
	printf("HERE at : %lld\n", timestamp(philo->rules->start_time));
	return (NULL);
}

int main(int argc, char **argv)
{
	t_rules	rules;
	pthread_t	monitoring;

	monitoring = 0;
	memset(&rules, 0, sizeof(t_rules));
	rules.is_running = true;
	init_all(&rules, monitoring, argc, argv);
	printf("nb_philo : %i\n", rules.nb_philo);
	printf("time_to_die : %i\n", rules.time_to_die);
	printf("time_to_eat : %i\n", rules.time_to_eat);
	printf("time_to_sleep : %i\n", rules.time_to_sleep);
	printf("start_time : %lli\n", rules.start_time);
	printf("eat_count : %i\n", rules.eat_count);
	printf("\n");
	printf("/////////////////////////////////////\n");
	printf("\n");
	shutdown_all(&rules);
	return (0);
}
