/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timo <timo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:15:44 by teichelm          #+#    #+#             */
/*   Updated: 2024/03/12 00:42:54 by timo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (*p->dead != 1 && p->mealcount != p->t_must_eat)
	{
		printf_message(p, 3);
		take_forks(p);
		p->mealcount++;
		p->last_meal = timestamp(p->start);
		printf_message(p, 1);
		usleep(p->t_eat * 1000);
		pthread_mutex_unlock(&p->fork);
		pthread_mutex_unlock(&p->next->fork);
		printf_message(p, 2);
		usleep(p->t_sleep * 1000);
		if (p->mealcount == p->t_must_eat)
			return (NULL);
	}
	return (NULL);
}

int	observation(t_philo *p, int philo_count, pthread_t *th)
{
	int	i;
	int	*count;

	count = malloc(sizeof(int) * philo_count);
	memset(count, '0', philo_count);
	i = 0;
	while (*p->dead != 1)
	{
		while (i < philo_count && *p->dead != 1)
		{
			if (p->mealcount < p->t_must_eat
				&& timestamp(p->start) - p->last_meal >= p->t_die)
				dead(p);
			if (p->mealcount == p->t_must_eat)
				count[i] = '1';
			if (!check_meals(count, philo_count))
				*p->dead = 1;
			i++;
			p = p->next;
		}
		i = 0;
	}
	usleep(10);
	detach(th, philo_count, count);
	return (1);
}

int	threads(t_philo *philos, int philo_count)
{
	int			i;
	pthread_t	*th;

	th = malloc(sizeof(pthread_t) * philo_count);
	if (!th)
		return (-1);
	i = 0;
	while (i < philo_count)
	{
		pthread_mutex_init(&philos->fork, NULL);
		start_time(philos, philo_count);
		pthread_create(&th[i], NULL, routine, (void *)philos);
		philos = philos->next;
		i++;
	}
	observation(philos, philo_count, th);
	free(th);
	i = 0;
	return (1);
}

void	free_list(t_philo *p)
{
	t_philo			*p2;
	int				i;
	int				total;

	total = p->total;
	i = 0;
	while (i < total)
	{
		pthread_mutex_destroy(&p->fork);
		p2 = p->next;
		free(p);
		p = p2;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo			*philos;
	pthread_mutex_t	death;
	int				*d;

	if (input(argc, argv) == -1)
		return (0);
	d = malloc(sizeof(int));
	*d = 0;
	pthread_mutex_init(&death, NULL);
	philos = philos_init(argv, argc, d, &death);
	threads(philos, ft_atoi(argv[1]));
	free(d);
	pthread_mutex_destroy(&death);
	free_list(philos);
}
