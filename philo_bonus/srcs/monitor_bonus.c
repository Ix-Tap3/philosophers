/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:28:04 by pcaplat           #+#    #+#             */
/*   Updated: 2026/03/30 11:16:32 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include "../includes/utils_bonus.h"
#include <stdio.h>
#include <unistd.h>

void	print_msg(t_philo *philo, char *msg)
{
	t_data		*data;
	long long	time;

	if (!msg)
		return ;
	data = philo->data;
	time = get_actual_time() - data->start_time;
	sem_wait(data->text_lock);
	printf("%lld %d %s\n", time, philo->id, msg);
	sem_post(data->text_lock);
}

void	*monitor_routine(void *arg)
{
	t_philo		*philo;
	t_data		*data;
	long long	time;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		time = get_actual_time() - data->start_time;
		sem_wait(data->meal_lock);
		if ((time - philo->last_meal) >= data->time_to_die)
		{
			sem_post(data->meal_lock);
			print_msg(philo, "died");
			kill_all(data);
			break ;
		}
		sem_post(data->meal_lock);
		usleep(1000);
	}
	return (NULL);
}
