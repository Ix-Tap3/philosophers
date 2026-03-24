/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 18:25:14 by pcaplat           #+#    #+#             */
/*   Updated: 2026/03/20 15:27:16 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"
#include "includes/utils.h"
#include <pthread.h>
#include <stdlib.h>

static void	destroy_mutexs(t_data *data)
{
	int	i;

	if (pthread_mutex_destroy(&data->text_lock) != 0)
		ft_putstr_fd(2, "Error: Impossible to destroy text mutex.\n");
	if (pthread_mutex_destroy(&data->die_lock) != 0)
		ft_putstr_fd(2, "Error: Impossible to destroy dead mutex.\n");
	i = 0;
	while (data->forks && i < data->nb_philosophers)
	{
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
			ft_putstr_fd(2, "Error: Impossible to destroy fork mutex.\n");
		i++;
	}
}

static void	clean_all(t_data *data, t_philo *philo_arr)
{
	destroy_mutexs(data);
	if (philo_arr)
		free(philo_arr);
	if (data->forks)
		free(data->forks);
	if (data->tids)
		free(data->tids);
	free(data);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo_arr;

	if (ac != 5 && ac != 6)
	{
		ft_putstr_fd(2, "Error: invalid number of arguments.\n");
		return (1);
	}
	data = parse(ac, av);
	philo_arr = init_philo_arr(data);
	if (!data || !philo_arr)
	{
		clean_all(data, NULL);
		return (1);
	}
	if (!create_threads(data, philo_arr))
	{
 		ft_putstr_fd(2, "Error while creating philosophers threads.\n");
		clean_all(data, philo_arr);
		return (1);
	}
	start_monitor(philo_arr);
	wait_all_threads(data);
	clean_all(data, philo_arr);
	return (0);
}
