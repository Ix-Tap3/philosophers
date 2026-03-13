/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 14:49:47 by pcaplat           #+#    #+#             */
/*   Updated: 2026/03/13 17:54:21 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

static int	ft_isspace(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

static int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/* This atoi doesn't handle value < 0 and this atoi is overflow safe */
int	safe_atoi(char *str)
{
	long	res;
	int		i;

	res = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		return (-1);
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		res = (res * 10) + str[i] - '0';
		i++;
	}
	if (res > 2147483647)
		return (-1);
	return ((int)res);
}

void	ft_putstr_fd(int fd, char *s)
{
	int	len;

	if (!s)
		return ;
	len = 0;
	while (s[len])
		len++;
	write(fd, s, len);
}

long long	get_actual_time()
{
	struct timeval	tv;
	long long		time;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}
