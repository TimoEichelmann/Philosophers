/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:15:44 by teichelm          #+#    #+#             */
/*   Updated: 2024/02/05 13:48:05 by teichelm         ###   ########.fr       */
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

int	last(t_philosopher *p)
{
	int	i;

	i = 0;
	while (p[i].dead != -1)
		i++;
	return (i);
}

//philo routine : try to eat, if not possible, sleep, think, repeat;
void	*routine(void *arg)
{
	t_philosopher 	*p;
	int				mealcount;

	p = (t_philosophr *)arg;
	usleep(50);
	while (*p->dead != 1)
	{
		//implement something to track whether philo has eaten in order to sleep and timer for t_die count and mealcount
		//mutexes for trying to eat;
		printf("philosopher %d is sleeping.", p->num);
		usleep(p->t_sleep);
		printf("philsopher %d is thinking", p->num);
	}
}

int	threads(t_philosopher *philos, t_times *times, int philo_count)
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
		pthread_create(th[i], NULL, routine, (void *)philos);
		philos = philos->next;
		i++;
	}
	i = 0;
	while (*dead != 1)

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

	*d = 0;
	if (input(argc, argv) == -1)
		return (0);
	philos = philos_init(argv, argc, d);
	free_list(philos);
	// threads(philos, times, ft_atoi(argv[1]));
	free(philos);
}