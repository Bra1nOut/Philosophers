/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bra1nout <bra1nout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:50:50 by bra1nout          #+#    #+#             */
/*   Updated: 2025/08/06 23:13:15 by bra1nout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	diff_time(long long past, long long present)
{
	return (present - past);
}

void	sleep_precise(long long time)
{
	long long	start;

	start = timestamp();
	while (diff_time(start, timestamp()) < time)
		usleep(500);
}
