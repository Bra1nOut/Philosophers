/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bra1nout <bra1nout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:50:12 by bra1nout          #+#    #+#             */
/*   Updated: 2025/08/06 23:18:56 by bra1nout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_rules	t_rules;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_rules			*rules;
}	t_philo;

typedef struct s_rules
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_limit;
	int				all_alive;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	meal_check;
	t_philo			*philos;
}	t_rules;

// init.c
int			init_all(t_rules *rules, int argc, char **argv);

// routine.c
void		*routine(void *arg);

// time.c
long long	timestamp(void);
void		sleep_precise(long long time);
long long	diff_time(long long past, long long present);

// utils.c
int			ft_atoi(const char *str);
void		print_action(t_rules *rules, int id, char *msg);
int			death_check(t_rules *rules);
void		free_all(t_rules rules);

// monitor.c
void		monitor(t_rules *rules);

#endif
