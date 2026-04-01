/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:26:44 by pcaplat           #+#    #+#             */
/*   Updated: 2026/03/30 11:17:35 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include "../includes/utils_bonus.h"
#include <stdlib.h>
#include <unistd.h>

static void	philo_eat(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_msg(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	print_msg(philo, "has taken a fork");
	print_msg(philo, "is eating");
	sem_wait(philo->data->meal_lock);
	philo->last_meal = get_actual_time() - philo->data->start_time;
	philo->nb_meals++;
	if (philo->nb_meals == philo->data->max_meals)
		sem_post(philo->data->end_lock);
	sem_post(philo->data->meal_lock);
	usleep(philo->data->time_to_eat * 1000);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	usleep(1000);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philosophers == 1)
	{
		print_msg(philo, "has taken a fork");
		usleep(philo->data->time_to_die * 1000);
		clean_all(philo->data);
		exit(1);
	}
	while (1)
	{
		philo_eat(philo);
		print_msg(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		print_msg(philo, "is thinking");
	}
	return (NULL);
}
