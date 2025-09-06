/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagoma <mamagoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:31:55 by mamagoma          #+#    #+#             */
/*   Updated: 2025/08/20 13:31:56 by mamagoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

unsigned long get_time(void)
{
	struct timeval	v;

	gettimeofday(&v, NULL);
	return ((unsigned long)(v.tv_sec * 1000UL) + (unsigned long)(v.tv_usec / 1000UL));
}
