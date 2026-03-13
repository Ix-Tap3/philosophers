/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 16:09:54 by pcaplat           #+#    #+#             */
/*   Updated: 2026/03/13 20:34:28 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/utils.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;

	pthread_mutex_lock(&philo->data->text_lock);
	printf("%d: I'm alive !!!\n", philo->id);
	pthread_mutex_unlock(&philo->data->text_lock);
	return (NULL);
}

static t_philo	init_philo(int i, t_data *data)
{
	t_philo	philo;

	philo.id = i + 1;
	philo.last_meal = 0;
	philo.nb_meals = 0;
	philo.data = data;
	return (philo);
}

int	create_threads(t_data *data)
{
	int		i;
	t_philo	philo;

	data->tids = malloc(sizeof(pthread_t) * data->nb_philosophers);
	if (!data->tids)
		return (0);
	data->start_time = get_actual_time();
	pthread_mutex_init(&data->text_lock, NULL);
	pthread_mutex_init(&data->die_lock, NULL);
	i = 0;
	while (i < data->nb_philosophers)
	{
		philo = init_philo(i, data);
		if (pthread_create(&data->tids[i], NULL, philo_routine, &philo) != 0)
			return (0);
		i++;
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
