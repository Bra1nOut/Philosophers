/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levincen <levincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:10:00 by levincen          #+#    #+#             */
/*   Updated: 2025/07/03 16:18:40 by levincen         ###   ########.fr       */
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
	pthread_mutex_t	last_meal_mtx;
	int				meal_eated;
	pthread_t		thread;
	struct s_rules	*rules;
	bool			is_dead;
}					t_philo;

typedef struct s_rules
{
	bool			is_running;
	int				nb_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				eat_count;
	long long		start_time;
	pthread_mutex_t	start_time_mtx;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	t_philo			*philo;
}					t_rules;


// Utils
int					ft_atoi(const char *str);
long				get_time(void);
long long 			timestamp(long long start_time);
void				print_action(char *str, t_philo *philo);

// Free
void				free_mutexes(t_rules *rules);
void				free_thread(t_rules *rules);

// Routines
void				sleeping(t_philo *philo);
void				thinking(t_philo *philo);
void				eating(t_philo *philo);

// A SUPPR
void	*test(void *ptr);
void	shutdown_all(t_rules *rules);


#endif
