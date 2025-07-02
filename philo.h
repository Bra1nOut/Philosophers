/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levincen <levincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:10:00 by levincen          #+#    #+#             */
/*   Updated: 2025/07/02 16:02:19 by levincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdbool.h>

typedef struct s_philo
{
	int				id;
	pthread_mutex_t left_fork;
	pthread_mutex_t right_fork;
	long			last_meal;
	int				meal_eated;
	pthread_t		thread;
	struct s_rules	*rules;
	bool			is_dead;
}					t_philo;

typedef struct s_rules
{
	int				nb_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				eat_count;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	t_philo			*philo;
}					t_rules;


// Utils
int		ft_atoi(const char *str);
long	get_time(void);
void	free_mutexes(t_rules *rules);

#endif
