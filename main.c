/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:27:15 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/21 17:47:32 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "pool.h"
#include <stdio.h>
#include <unistd.h>

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
//	printf("[%lu] now %lu - last eat %lu = %lu\n", philo->id + 1, now, philo->last_eat, now - philo->last_eat);
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
/*
		pthread_mutex_lock(&pool->print_mutex);
		if (philo->id + 1 == 7)
			printf("[%lu] wait %lu, elapse %lu \n", philo->id + 1, ms, now - start);
		pthread_mutex_unlock(&pool->print_mutex);
*/
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
	if (pool->forks[l] == false)
	{
		pool->forks[l] = true;
		print("has taken a fork", philo);
	}
	pthread_mutex_unlock(&pool->forks_mutex[l]);
	pthread_mutex_lock(&pool->forks_mutex[r]);
	if (pool->forks[r] == false)
	{
		pool->forks[r] = true;
		print("has taken a fork", philo);
	}
	pthread_mutex_unlock(&pool->forks_mutex[r]);
}

bool	is_eating(t_philo_data *philo)
{
	int	l;
	int	r;
	t_pool_data	pool;

	if (philo == NULL)
		return (false);
	pool = philo->shared_data;
	init_l_r(philo->id, pool, &l, &r);
	pthread_mutex_lock(&pool->forks_mutex[l]);
	pthread_mutex_lock(&pool->forks_mutex[r]);
	if (pool->forks[l] && pool->forks[r])
	{
		print("is eating", philo);
		philo->last_eat = time_now_millisecond();
		pool->forks[l] = false;
		pool->forks[r] = false;
	}
	pthread_mutex_unlock(&pool->forks_mutex[r]);
	pthread_mutex_unlock(&pool->forks_mutex[l]);
	return (try_wait(pool->arg.time_to_eat, philo));
}

void	is_thinking(t_philo_data *philo)
{
	if (philo == NULL)
		return ;
	print("is thinking", philo);
}

bool	is_sleeping(t_philo_data *philo)
{
	t_pool_data	pool;

	if (philo == NULL)
		return (false);
	pool = philo->shared_data;
	print("is sleeping", philo);
	return (try_wait(pool->arg.time_to_sleep, philo));
}

bool	wait_to_start(t_philo_data *philo)
{
	t_pool_data		pool;
	bool			continu;

	continu = true;
	pool = philo->shared_data;
	pthread_mutex_lock(&pool->mutex_start);
	continu = !(*pool->start);
	pthread_mutex_unlock(&pool->mutex_start);
	return (continu);
}

void	*routine(void *ptr)
{
	t_philo_data	*philo;
	t_pool_data		pool;

	if (ptr == NULL)
		return (NULL);
	philo = ptr;
	pool = philo->shared_data;
	while (wait_to_start(ptr))
		usleep(5);
	philo->last_eat = time_now_millisecond();
	while (42)
	{
		if (must_die(ptr))
			break ;
		take_fork(ptr);
		if (!is_eating(ptr))
			break ;
		is_thinking(ptr);
		if (!is_sleeping(ptr))
			break ;
	}
	return (NULL);
}

int	main(int ac, char *av[])
{
	t_input	out;
	int		nb_arg;

	nb_arg =  parse_arg(ac, av, &out);
	if (!nb_arg)
		return (-1);
	pool(out, routine);
	return (0);
}
