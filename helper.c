/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timo <timo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:30:24 by teichelm          #+#    #+#             */
/*   Updated: 2024/03/12 00:45:46 by timo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *p)
{
	int	i;
	int	result;
	int	sign;

	sign = 1;
	result = 0;
	i = 0;
	while (p[i] == ' ' || p[i] == '\f' || p[i] == '\n' || p[i] == '\r'
		|| p[i] == '\t' || p[i] == '\v')
		i++;
	if (p[i + 1] >= '0' && p[i + 1] <= '9' && (p[i] == '-' || p[i] == '+'))
	{
		if (p[i] == '-')
			sign = -1;
		i++;
	}
	else if ((p[i] == '-' || p[i] == '+') && !(p[i + 1] >= '0' && p[i] <= '9'))
		return (0);
	while (p[i] >= '0' && p[i] <= '9')
	{
		result = result * 10 + (p[i] - '0');
		i++;
	}
	return (result * sign);
}

int	check_meals(int *count, int philo_count)
{
	int	i;
	int	done;

	i = 0;
	done = 0;
	while (i < philo_count)
	{
		if (count[i] == '1')
			done++;
		i++;
	}
	if (done == philo_count)
		return (0);
	else
		return (1);
}

void	detach(pthread_t *th, int philo_count, int *count)
{
	int	j;

	j = 0;
	while (j < philo_count)
	{
		pthread_detach(th[j]);
		j++;
	}
	free(count);
}

void	dead(t_philo *p)
{
	pthread_mutex_lock(p->dead_trap);
	*p->dead = 1;
	printf("%d %d died\n", timestamp(p->start), p->num);
}

void	take_forks(t_philo *p)
{
	if (p->num % 2 == 0)
	{
		if (p->mealcount > 0)
			usleep((p->t_die - (timestamp(p->start) - p->last_meal)));
		pthread_mutex_lock(&p->next->fork);
		printf_message(p, 0);
		pthread_mutex_lock(&p->fork);
		printf_message(p, 0);
	}
	if (p->num % 2 == 1)
	{
		if (p->mealcount > 0)
			usleep((p->t_die - (timestamp(p->start) - p->last_meal)));
		pthread_mutex_lock(&p->fork);
		printf_message(p, 0);
		pthread_mutex_lock(&p->next->fork);
		printf_message(p, 0);
	}
}
