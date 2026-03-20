/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 14:27:09 by pcaplat           #+#    #+#             */
/*   Updated: 2026/03/19 19:38:36 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>

typedef struct s_data
{
	int				nb_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	int				one_is_dead;
	long long		start_time;
	pthread_t		monitor_tid;
	pthread_t		*tids;
	pthread_mutex_t	*forks;
	pthread_mutex_t	text_lock;
	pthread_mutex_t	die_lock;
}					t_data;

typedef struct s_philo
{
	int				id;
	long long		last_meal;
	int				nb_meals;
	t_data			*data;
}					t_philo;

/* Parser */
t_data	*parse(int ac, char **av);
t_philo	*init_philo_arr(t_data *data);

/* Monitor */
int		start_monitor(t_philo *philo_arr);
void	print_msg(t_philo *philo, char *msg);

/* Threads Handler */
int		create_threads(t_data *data, t_philo *philo_arr);
int		wait_all_threads(t_data *data);

/* Philo routine */
void	*philo_routine(void *arg);
int		is_dead(t_philo *philo);

#endif
