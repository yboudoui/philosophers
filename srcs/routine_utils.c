/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:51:28 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/21 17:52:09 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "routine.h"

void	init_l_r(uint64_t id, t_pool_data pool, int *l, int *r)
{
	if (id % 2)
	{
		(*l) = id;
		(*r) = (id + 1) % pool->size;
	}
	else
	{
		(*r) = id;
		(*l) = (id + 1) % pool->size;
	}
}

bool	anyone_died(t_philo_data *philo)
{
	t_pool_data		pool;
	bool			death;

	death = false;
	pool = philo->shared_data;
	pthread_mutex_lock(&pool->dead_mutex);
	death = pool->dead;
	pthread_mutex_unlock(&pool->dead_mutex);
	return (death);
}

bool	must_die(t_philo_data *philo)
{
	unsigned long	now;
	bool			die;
	t_pool_data		pool;

	die = false;
	pool = philo->shared_data;
	pthread_mutex_lock(&pool->print_mutex);
	pthread_mutex_lock(&pool->dead_mutex);
	now = time_now_millisecond();
	if (pool->dead)
		die = true;
	else if ((now - philo->last_eat) >= (unsigned long)pool->arg.time_to_die)
	{
		pool->dead = true;
		printf("%ld %lu died\n", elapse_time(philo), philo->id + 1);
		die = true;
	}
	pthread_mutex_unlock(&pool->dead_mutex);
	pthread_mutex_unlock(&pool->print_mutex);
	return (die);
}

bool	try_wait(unsigned long ms, t_philo_data *philo)
{
	unsigned long	start;
	unsigned long	now;
	t_pool_data		pool;

	pool = philo->shared_data;
	start = time_now_millisecond();
	now = start;
	ms /= 1000;
	while (!must_die(philo) && (now - start) < ms)
	{
		now = time_now_millisecond();
		if ((now - start) >= (unsigned long)pool->arg.time_to_die)
			return (false);
		if (must_die(philo) || anyone_died(philo))
			return (false);
		usleep(500);
	}
	return (true);
}

void	print(char *str, t_philo_data *philo)
{
	t_pool_data	pool;

	if (str == NULL || philo == NULL)
		return ;
	pool = philo->shared_data;
	pthread_mutex_lock(&pool->print_mutex);
	pthread_mutex_lock(&pool->dead_mutex);
	if (pool->dead == false)
		printf("%ld %lu %s\n", elapse_time(philo), philo->id + 1, str);
	pthread_mutex_unlock(&pool->dead_mutex);
	pthread_mutex_unlock(&pool->print_mutex);
}
