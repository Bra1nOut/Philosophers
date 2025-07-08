/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levincen <levincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:06:18 by levincen          #+#    #+#             */
/*   Updated: 2025/07/08 12:55:47 by levincen         ###   ########.fr       */
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
	t_philo philo;
	pthread_t	monitoring;

	monitoring = 0;
	memset(&philo, 0, sizeof(t_philo));
	memset(&rules, 0, sizeof(t_rules));
	rules.is_running = true;
	if (init_all(&rules, &monitoring, argc, argv) != 0)
		return (1);
	pthread_join(monitoring, NULL);
	free_thread(&rules);
	shutdown_all(&rules);
	return (0);
}
