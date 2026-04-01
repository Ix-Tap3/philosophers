/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:38:34 by pcaplat           #+#    #+#             */
/*   Updated: 2026/03/30 16:20:51 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_bonus.h"
#include "includes/utils_bonus.h"
#include <stdlib.h>

void	clean_all(t_data *data)
{
	if (data->pids)
		free(data->pids);
	sem_unlink("/forks");
	sem_unlink("/meal");
	sem_unlink("/text");
	sem_unlink("/died");
	sem_close(data->forks);
	sem_close(data->meal_lock);
	sem_close(data->text_lock);
	sem_close(data->end_lock);
	free(data);
}

static void	check_meals(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philosophers)
	{
		sem_wait(data->end_lock);
		i++;
	}
	kill_all(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 5 && ac != 6)
	{
		ft_putstr_fd(2, "Error: Invalid number of arguments.\n");
		return (1);
	}
	data = parse(ac, av);
	if (!data)
		return (1);
	if (!create_philos(data))
	{
		ft_putstr_fd(2, "Error: Impossible to create philosopher's process.\n");
		clean_all(data);
		return (1);
	}
	check_meals(data);
	wait_all();
	clean_all(data);
	return (0);
}
