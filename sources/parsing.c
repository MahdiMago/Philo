/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:09:18 by mamagoma          #+#    #+#             */
/*   Updated: 2025/08/20 20:55:14 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	only_digits(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j])
	{
		while (str[j][i])
			if (str[j][i] < '0' && str[j][i++] > '9')
				return (false);
		j++;
	}
	return (true);
}

bool	check_argument(int ac, char **av)
{
	if (ac < 5)
		return (false);
	else if (!only_digits)
		return (false);
	else return (true);
}

int	error_return(void)
{
	printf("Error");
	return (0);
}
