/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 14:27:09 by pcaplat           #+#    #+#             */
/*   Updated: 2026/03/28 17:37:39 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <semaphore.h>

typedef struct s_data
{
	int			nb_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			max_meals;
	int			one_is_dead;
	pid_t		*pids;
	sem_t		*forks;
	sem_t		*text_lock;
	sem_t		*meal_lock;
	sem_t		*end_lock;
	long long	start_time;
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
int		create_philos(t_data *data);
int		wait_all(void);

/* Philo management */
void	kill_all(t_data *data);
void	*philo_routine(void *arg);

/* Monitor */
void	print_msg(t_philo *philo, char *msg);
void	*monitor_routine(void *arg);

#endif
