/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 18:25:14 by pcaplat           #+#    #+#             */
/*   Updated: 2026/03/13 19:59:48 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"
#include "includes/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	free_all(t_data *data)
{
	if (data->tids)
		free(data->tids);
	free(data);
}

// static void	print_data_struct(t_data *data)
// {
// 	printf("Number of philosophers: %d\n", data->nb_philosophers);
// 	printf("Time to die: %dms\n", data->time_to_die);
// 	printf("Time to eat: %dms\n", data->time_to_eat);
// 	printf("Time to sleep: %dms\n", data->time_to_sleep);
// 	printf("Number of meals: %d\n", data->max_meals);
// }

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 5 && ac != 6)
	{
		ft_putstr_fd(2, "Error: invalid number of arguments.\n");
		return (1);
	}
	data = parse(ac, av);
	if (!data)
		return (1);
	if (!create_threads(data))
	{
		ft_putstr_fd(2, "Error while creating philosophers threads.\n");
		free_all(data);
		return (1);
	}
	wait_all_threads(data);
	return (0);
}
