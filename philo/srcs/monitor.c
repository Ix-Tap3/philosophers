/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 11:07:51 by pcaplat           #+#    #+#             */
/*   Updated: 2026/03/19 18:31:44 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <unistd.h>

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
			if (is_dead(&philo_arr[i]) == 1)
			{
				data->one_is_dead = 1;
				stop = 1;
				break;
			}
			i++;
		}
		pthread_mutex_unlock(&data->die_lock);
		usleep(1000);
	}
	return (NULL);
}

int	start_monitor(t_philo *philo_arr)
{
	philo_arr[0].data->monitor_tid = 0;
	if (pthread_create(&philo_arr[0].data->monitor_tid, NULL, monitor_process, philo_arr) != 0)
		return (0);
	if (pthread_join(philo_arr[0].data->monitor_tid, NULL) != 0)
		return (0);
	return (1);
}
