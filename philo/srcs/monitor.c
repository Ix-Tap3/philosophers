/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 11:07:51 by pcaplat           #+#    #+#             */
/*   Updated: 2026/03/28 16:34:59 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/utils.h"
#include <unistd.h>
#include <stdio.h>

void	print_msg(t_philo *philo, char *msg)
{
	t_data		*data;
	long long	time;

	data = philo->data;
	pthread_mutex_lock(&philo->data->die_lock);
	if (philo->data->one_is_dead == 1)
	{
		pthread_mutex_unlock(&philo->data->die_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->data->die_lock);
	time = get_actual_time() - data->start_time;
	pthread_mutex_lock(&data->text_lock);
	printf("%lld %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&data->text_lock);
}

static int	check_philo_meals(t_philo *philo_arr)
{
	t_data	*data;
	int		i;
	int		all_eat;

	data = philo_arr[0].data;
	i = 0;
	all_eat = 1;
	while (i < data->nb_philosophers)
	{
		if (philo_arr[i].nb_meals != data->max_meals)
			all_eat = 0;
		i++;
	}
	return (all_eat);
}

static void	*monitor_process(void *arg)
{
	t_philo	*philo_arr;
	t_data	*data;
	int		i;
	int		stop;

	philo_arr = (t_philo *)arg;
	data = (t_data *)philo_arr[0].data;
	stop = 0;
	while (!stop)
	{
		i = 0;
		pthread_mutex_lock(&data->die_lock);
		while (i < data->nb_philosophers)
		{
			if (check_philo_meals(philo_arr) || is_dead(&philo_arr[i++]) == 1)
			{
				data->one_is_dead = 1;
				stop = 1;
				break ;
			}
		}
		pthread_mutex_unlock(&data->die_lock);
		usleep(1000);
	}
	return (NULL);
}

int	start_monitor(t_philo *p_arr)
{
	t_data	*data;

	data = p_arr[0].data;
	data->monitor_tid = 0;
	if (pthread_create(&data->monitor_tid, NULL, monitor_process, p_arr) != 0)
		return (0);
	if (pthread_join(data->monitor_tid, NULL) != 0)
		return (0);
	return (1);
}
