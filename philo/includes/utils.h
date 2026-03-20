/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:03:34 by pcaplat           #+#    #+#             */
/*   Updated: 2026/03/19 19:45:24 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "philo.h"

long long	get_actual_time(void);
int			safe_atoi(char *str);
void		ft_putstr_fd(int fd, char *str);
void		display_time(t_philo *philo, long long actual_time, long long past_time);

#endif
