/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: levincen <levincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:10:00 by levincen          #+#    #+#             */
/*   Updated: 2025/07/08 12:34:05 by levincen         ###   ########.fr       */
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
	pthread_mutex_t	meal_eated_mtx;
	pthread_t		thread;
	struct s_rules	*rules;

}					t_philo;

typedef struct s_rules
{
	bool			is_dead;
	pthread_mutex_t	is_dead_mtx;
	bool			is_running;
	int				nb_philo;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				eat_count;
	pthread_mutex_t	eat_count_mtx;
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
void				smart_sleep(int duration, t_philo *philo);

// Free
void				free_mutexes(t_rules *rules);
void				free_thread(t_rules *rules);

// Routines
void				sleeping(t_philo *philo);
void				thinking(t_philo *philo);
void				eating(t_philo *philo);
void				routine_no_meal(t_philo *philo);
void				*routine_choose(void *ptr);
void				one_philo(t_rules *rules);
void				eat_priority(t_philo *philo, int i);

// Init
int					init_mutexes(t_rules *rules);
void				init_philo(t_rules *rules, pthread_t *monitoring_t);
int					init_all(t_rules *rules, pthread_t	*monitoring, int argc, char **argv);
void				*monitoring(void *arg);
bool				death_check(t_philo *philo);

// A SUPPR
void	*test(void *ptr);
void	shutdown_all(t_rules *rules);


#endif
