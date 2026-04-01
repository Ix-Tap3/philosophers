/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:03:34 by pcaplat           #+#    #+#             */
/*   Updated: 2026/03/28 16:30:36 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "philo.h"

long long	get_actual_time(void);
int			safe_atoi(char *str);
void		ft_putstr_fd(int fd, char *str);
void		display_time(t_philo *philo, long long a_time, long long p_time);

#endif
