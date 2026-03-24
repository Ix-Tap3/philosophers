/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:38:34 by pcaplat           #+#    #+#             */
/*   Updated: 2026/03/20 15:40:40 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("Invalid number of arguments\n");
		return (1);
	}
	printf("%s\n", av[1]);
	return (0);
}
