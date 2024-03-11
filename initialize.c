/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timo <timo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 00:38:46 by timo              #+#    #+#             */
/*   Updated: 2024/03/12 00:43:32 by timo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	input(int argc, char **argv)
{
	t_times	*result;

	if (!(argc >= 5 && argc < 7))
		return (-1);
	result = malloc(sizeof(t_times));
	result->die = ft_atoi(argv[2]);
	result->eat = ft_atoi(argv[3]);
	result->sleep = ft_atoi(argv[4]);
	result->must_eat = 0;
	if (argc == 6)
		result->must_eat = ft_atoi(argv[5]);
	if (result->die < 1 || result->eat < 1 || result->sleep < 1
		|| argv[1][0] < '1' || result->must_eat <= -1 || ft_atoi(argv[1]) > 200)
	{
		printf("Wrong input.\n");
		free(result);
		return (-1);
	}
	free(result);
	return (0);
}

void	insert(t_philo *result, char **argv, int argc, int i)
{
	result->dead = 0;
	result->num = i;
	result->mealcount = 0;
	result->t_die = ft_atoi(argv[2]);
	result->t_eat = ft_atoi(argv[3]);
	result->t_sleep = ft_atoi(argv[4]);
	result->t_must_eat = 100000;
	result->thinking = 0;
	if (argc == 6)
		result->t_must_eat = ft_atoi(argv[5]);
	result->total = ft_atoi(argv[1]);
}

void	insert_mutexes(t_philo *result, int *d, pthread_mutex_t *death)
{
	result->dead_trap = death;
	result->dead = d;
}

t_philo	*philos_init(char **argv, int argc, int *d, pthread_mutex_t *death)
{
	t_philo	*result;
	t_philo	*p;
	t_philo	*start;
	int		i;

	p = NULL;
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		result = malloc(sizeof(t_philo));
		if (p)
		{
			result->prior = p;
			p->next = result;
		}
		if (p == NULL)
			start = result;
		insert(result, argv, argc, i + 1);
		insert_mutexes(result, d, death);
		p = result;
		i++;
	}
	p->next = start;
	start->prior = p;
	return (start);
}

void	start_time(t_philo *p, int philo_count)
{
	int				i;
	struct timeval	time;
	int				start;

	i = 0;
	gettimeofday(&time, NULL);
	start = time.tv_sec * 1000 + time.tv_usec / 1000;
	while (i < philo_count)
	{
		p->start = start;
		p = p->next;
		i++;
	}
}
