/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:15:44 by teichelm          #+#    #+#             */
/*   Updated: 2024/02/13 16:10:54 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	input(int	argc, char **argv)
{
	t_times *result;
	
	if (!(argc >= 5 && argc < 7))
		return (-1);
	result = malloc(sizeof(t_times));
	result->die = ft_atoi(argv[2]);
	result->eat = ft_atoi(argv[3]);
	result->sleep = ft_atoi(argv[4]);
	result->must_eat = -1;
	if (argc == 6)
		result->must_eat = ft_atoi(argv[5]);
	if (result->die < 1 || result->eat < 1 || result->sleep < 1
			|| argv[1][0] < '1' || result->must_eat < 1 || ft_atoi(argv[1]) > 200)
	{
		printf("Wrong input.\n");
		free(result);
		return (-1);
	}
	free(result);
	return (0);
}

void	insert(t_philosopher *result, char **argv, int argc, int i)
{
	result->fork = 1;
	result->dead = 0;
	result->num = i;
	result->t_die = ft_atoi(argv[2]);
	result->t_eat = ft_atoi(argv[3]);
	result->t_sleep = ft_atoi(argv[4]);
	result->t_must_eat = -1;
	result->thinking = 0;
	if (argc == 6)
		result->t_must_eat = ft_atoi(argv[5]);
	result->total = ft_atoi(argv[1]);
}

t_philosopher	*philos_init(char **argv, int argc, int *d)
{
	t_philosopher	*result;
	t_philosopher	*p;
	t_philosopher	*start;
	int				i;
	
	p = NULL;
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		result = malloc(sizeof(t_philosopher));
		if (p)
		{
			result->prior = p;
			p->next = result;
		}
		if (p == NULL)
			start = result;
		insert(result, argv, argc, i + 1);
		result->dead = d;
		p = result;
		i++;
	}
	p->next = start;
	start->prior = p;
	return (start);
}

int	take_forks(t_philosopher *p)
{
	int	ind;

	pthread_mutex_lock(&p->mutex);
	printf("philosopher %d has taken his fork in state %d\n", p->num, p->fork);
	p->fork = 0;
	if (p->prior->fork == 1)
	{
		p->prior->fork = 0;
		ind = 0;
	}
	else
	{
		p->next->fork = 0;
		ind = 1;
	}
	if (ind == 0)
		printf("philosopher %d has taken a fork of %d\n", p->num, p->prior->num);
	if (ind == 1)
		printf("philosopher %d has taken a fork of %d\n", p->num, p->next->num);
	pthread_mutex_unlock(&p->mutex);
	return (ind);
}

void	drop_forks(t_philosopher *p, int ind)
{
	
	pthread_mutex_lock(&p->mutex);
	p->fork = 1;
	if (ind == 0)
		p->prior->fork = 1;
	else
		p->next->fork = 1;
	printf("philosopher %d has dropped forks\n", p->num);
	pthread_mutex_unlock(&p->mutex);
}

void	*routine(void *arg)
{
	t_philosopher 	*p;
	int				mealcount;
	int				ind;
	int				i;

	i = 0;
	p = (t_philosopher *)arg;
	usleep(20);
	while (i < 5)
	{
		if ((p->prior->fork == 1 || p->next->fork == 1) && p->fork == 1)
		{
			p->thinking = 0;
			ind = take_forks(p);
			printf("philosopher %d is eating\n", p->num);
			usleep(p->t_eat);
			drop_forks(p, ind);
			printf("philosopher %d is sleeping.\n", p->num);
			usleep(p->t_sleep);
		}
		if (p->thinking == 0)
		{
			p->thinking = 1;
			printf("philsopher %d is thinking\n", p->num);
		}
		i++;
	}
	return (NULL);
}

int	threads(t_philosopher *philos, int philo_count)
{
	int			i;
	pthread_t	*th;
	int			*dead;

	dead = philos->dead;
	th = malloc(sizeof(pthread_t) * philo_count);
	if (!th)
		return (-1);
	i = 0;
	while (i < philo_count)
	{
		pthread_mutex_init(&philos->mutex, NULL);
		pthread_create(&th[i], NULL, routine, (void *)philos);
		philos = philos->next;
		i++;
	}
	i = 0;
	while (i < philo_count)
	{
		pthread_join(th[i], NULL);
		i++;
	}
	return (0);
}

void	free_list(t_philosopher *p)
{
	t_philosopher *p2;
	int				i;
	int				total;

	total = p->total;
	i = 0;
	while (i < total)
	{
		p2 = p->next;
		free(p);
		p = p2;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philosopher	*philos;
	int				*d;

	d = malloc(sizeof(int));
	*d = 0;
	if (input(argc, argv) == -1)
		return (0);
	philos = philos_init(argv, argc, d);
	threads(philos, ft_atoi(argv[1]));
	free_list(philos);
}