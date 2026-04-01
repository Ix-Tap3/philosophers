/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 16:36:07 by pcaplat           #+#    #+#             */
/*   Updated: 2026/03/28 17:38:03 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include "../includes/utils_bonus.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <pthread.h>

void	kill_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philosophers)
	{
		kill(data->pids[i], SIGKILL);
		i++;
	}
}

int	wait_all(void)
{
	int	status;
	int	ret;

	ret = waitpid(-1, &status, 0);
	if (ret == -1)
	{
		ft_putstr_fd(2, "Error: Impossible to wait processes.\n");
		return (ret);
	}
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	return (ret);
}

static void	philo_process(t_data *data, int id)
{
	t_philo		philo;
	pthread_t	tid;

	philo.id = id + 1;
	philo.data = data;
	philo.last_meal = 0;
	philo.nb_meals = 0;
	if (pthread_create(&tid, NULL, monitor_routine, &philo) == -1)
	{
		printf("Error while creating philo %d monitor thread\n", philo.id);
		clean_all(data);
		exit(1);
	}
	if (pthread_detach(tid) == -1)
	{
		printf("Error while detaching philo %d monitor thread\n", philo.id);
		clean_all(data);
		exit(1);
	}
	philo_routine((void *)&philo);
	clean_all(data);
	exit(0);
}

int	create_philos(t_data *data)
{
	int		i;

	data->pids = malloc(sizeof(pid_t) * data->nb_philosophers);
	if (!data->pids)
		return (0);
	i = 0;
	data->start_time = get_actual_time();
	while (i < data->nb_philosophers)
	{
		data->pids[i] = fork();
		if (data->pids[i] == -1)
		{
			free(data->pids);
			return (0);
		}
		if (data->pids[i] == 0)
			philo_process(data, i);
		i++;
	}
	return (1);
}
