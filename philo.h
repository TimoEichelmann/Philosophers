/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timo <timo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:17:10 by teichelm          #+#    #+#             */
/*   Updated: 2024/03/12 00:49:48 by timo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_philosopher {
	struct s_philosopher	*prior;
	int						*dead;
	pthread_mutex_t			*dead_trap;
	int						last_meal;
	int						mealcount;
	int						num;
	int						thinking;
	int						t_die;
	int						t_eat;
	int						t_sleep;
	int						t_must_eat;
	int						start;
	int						total;
	pthread_mutex_t			fork;
	struct s_philosopher	*next;
}t_philo;

typedef struct s_times {
	int	die;
	int	eat;
	int	sleep;
	int	must_eat;
}t_times;

int		ft_atoi(const char *p);
int		check_meals(int *count, int philo_count);
void	detach(pthread_t *th, int philo_count, int *count);
void	dead(t_philo *p);
void	take_forks(t_philo *p);
void	start_time(t_philo *p, int philo_count);
t_philo	*philos_init(char **argv, int argc, int *d, pthread_mutex_t *death);
void	insert_mutexes(t_philo *result, int *d, pthread_mutex_t *death);
void	insert(t_philo *result, char **argv, int argc, int i);
int		input(int argc, char **argv);
void	*routine(void *arg);
int		observation(t_philo *p, int philo_count, pthread_t *th);
int		threads(t_philo *philos, int philo_count);
void	free_list(t_philo *p);
void	printf_message(t_philo *p, int code);
int		timestamp(int start);

#endif