/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:17:10 by teichelm          #+#    #+#             */
/*   Updated: 2024/02/05 13:15:56 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_philosopher {
	struct s_philosopher *prior;
	int	fork;
	int	dead;
	int	num;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	t_must_eat;
	int	total;
	struct s_philosopher *next;
}t_philosopher;

typedef	struct s_monitor {
	int	death;
}

typedef struct s_times {
	int	die;
	int	eat;
	int	sleep;
	int	must_eat;
}t_times;

int	ft_atoi(const char *p);


#endif