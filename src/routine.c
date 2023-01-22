/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:50:48 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/22 18:23:55 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "routine.h"

void	take_fork(t_philo_data *philo)
{
	int			l;
	int			r;
	t_pool_data	pool;

	if (philo == NULL)
		return ;
	pool = philo->shared_data;
	init_l_r(philo->id, pool, &l, &r);
	pthread_mutex_lock(&pool->forks_mutex[l]);
	pthread_mutex_lock(&pool->forks_mutex[r]);
	if (pool->forks[l] == false)
	{
		pool->forks[l] = true;
		print("has taken a fork", philo);
	}
	if (pool->forks[r] == false)
	{
		pool->forks[r] = true;
		print("has taken a fork", philo);
	}
	pthread_mutex_unlock(&pool->forks_mutex[r]);
	pthread_mutex_unlock(&pool->forks_mutex[l]);
}

bool	is_sleeping(t_philo_data *philo)
{
	t_pool_data		pool;

	if (philo == NULL)
		return (false);
	pool = philo->shared_data;
	print("is sleeping", philo);
	return (try_wait(pool->arg.time_to_sleep, philo));
}

bool	is_eating(t_philo_data *philo)
{
	int			l;
	int			r;
	t_pool_data	pool;
	bool		out;

	out = true;
	if (philo == NULL)
		return (false);
	take_fork(philo);
	pool = philo->shared_data;
	init_l_r(philo->id, pool, &l, &r);
	pthread_mutex_lock(&pool->forks_mutex[l]);
	pthread_mutex_lock(&pool->forks_mutex[r]);
	if (pool->forks[l] && pool->forks[r])
	{
		print("is eating", philo);
		pool->forks[l] = false;
		pool->forks[r] = false;
		out = try_wait(pool->arg.time_to_eat, philo);
		philo->last_eat = time_now_millisecond();
	}
	pthread_mutex_unlock(&pool->forks_mutex[r]);
	pthread_mutex_unlock(&pool->forks_mutex[l]);
	return (is_sleeping(philo));
}

bool	is_thinking(t_philo_data *philo)
{
	unsigned long	now;

	if (philo == NULL)
		return (false);
	now = time_now_millisecond();
	print("is thinking", philo);
	return (try_wait(((now - philo->last_eat) / 10) * 8, philo));
}

void	*routine(void *ptr)
{
	t_philo_data	*philo;
	t_pool_data		pool;
	bool			wait;

	if (ptr == NULL)
		return (NULL);
	wait = true;
	philo = ptr;
	pool = philo->shared_data;
	while (wait)
	{
		pthread_mutex_lock(&pool->mutex_start);
		wait = !(*pool->start);
		pthread_mutex_unlock(&pool->mutex_start);
		usleep(5);
	}
	philo->last_eat = time_now_millisecond();
	while (42)
		if (must_die(ptr) || !is_thinking(ptr) || !is_eating(ptr)) //|| !is_sleeping(ptr))
			break ;
	return (NULL);
}
