/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 14:30:40 by pcaplat           #+#    #+#             */
/*   Updated: 2026/03/19 19:40:20 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "../includes/utils.h"
#include <stdlib.h>

static pthread_mutex_t	*init_forks_arr(int	nb_forks)
{
	pthread_mutex_t	*arr;
	int				i;

	arr = malloc(sizeof(pthread_mutex_t) * nb_forks);
	if (!arr)
	{
		ft_putstr_fd(2, "Error: malloc failed !\n");
		return (NULL);
	}
	i = 0;
	while (i < nb_forks)
	{
		pthread_mutex_init(&arr[i], NULL);
		i++;
	}
	return (arr);
}

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

t_philo	*init_philo_arr(t_data *data)
{
	t_philo	*philo_arr;
	int		i;

	if (!data)
		return (NULL);
	philo_arr = malloc(sizeof(t_philo) * data->nb_philosophers);
	if (!philo_arr)
	{
		ft_putstr_fd(2, "Error: malloc failed !\n");
		return (NULL);
	}
	i = 0;
	while (i < data->nb_philosophers)
	{
		philo_arr[i].id = i + 1;
		philo_arr[i].last_meal = 0;
		philo_arr[i].nb_meals = 0;
		philo_arr[i].data = data;
		i++;
	}
	return (philo_arr);
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
	data->nb_philosophers = safe_atoi(av[1]);
	data->time_to_die = safe_atoi(av[2]);
	data->time_to_eat = safe_atoi(av[3]);
	data->time_to_sleep = safe_atoi(av[4]);
	if (ac == 6)
		data->max_meals = safe_atoi(av[5]);
	else
		data->max_meals = -1;
	if (!check_data(ac, data))
		return (NULL);
	data->forks = init_forks_arr(data->nb_philosophers);
	if (!data->forks)
	{
		free(data);
		return (NULL);
	}
	return (data);
}
