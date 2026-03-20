/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 12:02:00 by pcaplat           #+#    #+#             */
/*   Updated: 2026/03/20 14:41:44 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/utils.h"
#include <stdio.h>
#include <unistd.h>

int	is_dead(t_philo *philo)
{
	long long	actual_time;
	long long	past_time;

	actual_time = get_actual_time() - philo->data->start_time;
	past_time = actual_time - philo->last_meal;
	if (past_time >= philo->data->time_to_die)
	{
		if (pthread_mutex_lock(&philo->data->text_lock) != 0)
			return (-1);
		printf("%lld %d died\n", actual_time, philo->id);
		if (pthread_mutex_unlock(&philo->data->text_lock) != 0)
			return (-1);
		return (1);
	}
	return (0);
}

static int	get_left_fork(int id)
{
	return (id - 1);
}

static int	get_right_fork(t_philo *philo)
{
	return (philo->id % philo->data->nb_philosophers);
}

static void	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[get_left_fork(philo->id)]);
		print_msg(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[get_right_fork(philo)]);
		print_msg(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[get_right_fork(philo)]);
		print_msg(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[get_left_fork(philo->id)]);
		print_msg(philo, "has taken a fork");
	}
	print_msg(philo, "is eating");
	pthread_mutex_lock(&data->die_lock);
	philo->last_meal = get_actual_time() - data->start_time;
	pthread_mutex_unlock(&data->die_lock);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->forks[get_left_fork(philo->id)]);
	pthread_mutex_unlock(&philo->data->forks[get_right_fork(philo)]);
	usleep(1000);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philosophers == 1)
	{
		print_msg(philo, "has taken a fork");
		usleep(philo->data->time_to_die * 1000);
		return (NULL);
	}
	while (1)
	{
		usleep(100);
		pthread_mutex_lock(&philo->data->die_lock);
		if (philo->data->one_is_dead == 1)
		{
			pthread_mutex_unlock(&philo->data->die_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->die_lock);
		philo_eat(philo);
		print_msg(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		print_msg(philo, "is thinking");
	}
	return (philo);
}
