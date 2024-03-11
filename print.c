/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timo <timo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 00:41:38 by timo              #+#    #+#             */
/*   Updated: 2024/03/12 00:42:28 by timo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	timestamp(int start)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec * 1000 + current.tv_usec / 1000) - start);
}

void	printf_message(t_philo *p, int code)
{
	pthread_mutex_lock(p->dead_trap);
	if (code == 0)
		printf("%d %d has taken a fork\n", timestamp(p->start), p->num);
	if (code == 1)
		printf("%d %d is eating\n", timestamp(p->start), p->num);
	if (code == 2)
		printf("%d %d is sleeping\n", timestamp(p->start), p->num);
	if (code == 3)
		printf("%d %d is thinking\n", timestamp(p->start), p->num);
	pthread_mutex_unlock(p->dead_trap);
	return ;
}
