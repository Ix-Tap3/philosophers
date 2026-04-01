/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 16:09:54 by pcaplat           #+#    #+#             */
/*   Updated: 2026/03/30 16:11:23 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/utils.h"
#include <stdlib.h>
#include <unistd.h>

int	create_threads(t_data *data, t_philo *p_arr)
{
	int		i;

	data->tids = malloc(sizeof(pthread_t) * data->nb_philosophers);
	if (!data->tids)
		return (0);
	data->one_is_dead = 0;
	data->start_time = get_actual_time();
	pthread_mutex_init(&data->text_lock, NULL);
	pthread_mutex_init(&data->die_lock, NULL);
	i = 0;
	while (i < data->nb_philosophers)
	{
		if (pthread_create(&data->tids[i], NULL, philo_routine, &p_arr[i]) != 0)
			return (0);
		i += 2;
	}
	usleep(50);
	i = 1;
	while (i < data->nb_philosophers)
	{
		if (pthread_create(&data->tids[i], NULL, philo_routine, &p_arr[i]) != 0)
			return (0);
		i += 2;
	}
	return (1);
}

int	wait_all_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philosophers)
	{
		if (pthread_join(data->tids[i], NULL) != 0)
		{
			ft_putstr_fd(2, "Error while joinning a thread.\n");
			return (0);
		}
		i++;
	}
	return (1);
}
