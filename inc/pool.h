/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:35:00 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/21 14:09:21 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POOL_H
# define POOL_H

# include "memory.h"
# include "fork.h"
# include "parser.h"
# include "philosopher.h"
# include <stdbool.h>
# include <pthread.h>

#include <sys/time.h>

/* ************************************************************************** */


typedef struct s_pool_data	*t_pool_data;
struct s_pool_data {
	struct timeval	*start_time;

	pthread_mutex_t	dead_mutex;
	bool			dead;

	pthread_mutex_t	print_mutex;

	pthread_mutex_t	mutex_start;
	bool			*start;

	t_input			arg;

	size_t			size;
	pthread_mutex_t	*forks_mutex;
	bool			*forks;
};

unsigned long	time_now_millisecond(void);
unsigned long	elapse(struct timeval a, struct timeval b);

unsigned long	elapse_time(t_philo_data *philo);
unsigned long		diff(t_pool_data data);
t_pool_data	create_pool_data(t_input arg);
void		destroy_pool_data(void *data);

/* ************************************************************************** */

typedef struct s_pool {
	t_pool_data			shared_data;
	t_philosopher_array	philosophers;
}	t_pool;

typedef void	*(t_fp_routine)(void *);
int			pool(t_input arg, t_fp_routine routine);

/* ************************************************************************** */

#endif
