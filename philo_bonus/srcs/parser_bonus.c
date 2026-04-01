/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 14:30:40 by pcaplat           #+#    #+#             */
/*   Updated: 2026/03/31 13:05:48 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include "../includes/utils_bonus.h"
#include <fcntl.h>
#include <stdlib.h>

static int	check_data(int ac, t_data *data)
{
	int	ret;

	ret = 1;
	if (data->nb_philosophers <= 0)
		ret = 0;
	if (data->time_to_die <= 0)
		ret = 0;
	if (data->time_to_eat <= 0)
		ret = 0;
	if (data->time_to_sleep <= 0)
		ret = 0;
	if (ac == 6)
	{
		if (data->max_meals <= 0)
			ret = 0;
	}
	if (ret == 0)
	{
		free(data);
		ft_putstr_fd(2, "Error: invalid argument(s).\n");
	}
	return (ret);
}

static void	parse_args(t_data *data, int ac, char **av)
{
	data->nb_philosophers = safe_atoi(av[1]);
	data->time_to_die = safe_atoi(av[2]);
	data->time_to_eat = safe_atoi(av[3]);
	data->time_to_sleep = safe_atoi(av[4]);
	data->one_is_dead = 0;
	if (ac == 6)
		data->max_meals = safe_atoi(av[5]);
	else
		data->max_meals = -1;
}

static int	init_locks(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/meal");
	sem_unlink("/text");
	sem_unlink("/end");
	data->forks = sem_open("/forks", O_CREAT, 0644, data->nb_philosophers);
	if (data->forks == SEM_FAILED)
		return (-1);
	data->meal_lock = sem_open("/meal", O_CREAT, 0644, 1);
	if (data->meal_lock == SEM_FAILED)
		return (-1);
	data->text_lock = sem_open("/text", O_CREAT, 0644, 1);
	if (data->text_lock == SEM_FAILED)
		return (-1);
	data->end_lock = sem_open("/end", O_CREAT, 0644, 0);
	if (data->end_lock == SEM_FAILED)
		return (-1);
	return (0);
}

t_data	*parse(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		ft_putstr_fd(2, "Error: malloc failed !\n");
		return (NULL);
	}
	parse_args(data, ac, av);
	if (!check_data(ac, data))
		return (NULL);
	if (init_locks(data) == -1)
	{
		clean_all(data);
		ft_putstr_fd(2, "Error: impossible to init semaphore(s).");
		return (NULL);
	}
	return (data);
}
