/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bra1nout <bra1nout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:49:20 by bra1nout          #+#    #+#             */
/*   Updated: 2025/08/06 23:14:01 by bra1nout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules	rules;
	int		i;

	if (init_all(&rules, argc, argv) != 0)
		return (1);
	i = 0;
	while (i < rules.nb_philo)
	{
		pthread_create(&rules.philos[i].thread, NULL,
			routine, &rules.philos[i]);
		i++;
	}
	monitor(&rules);
	free_all(rules);
	return (0);
}
