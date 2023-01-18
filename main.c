/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:27:15 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/18 18:15:11 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "pool.h"
#include <stdio.h>
#include <unistd.h>

void	print(char *str, t_philo_data *philo)
{
	t_pool_data	pool;

	if (str == NULL || philo == NULL)
		return ;
	pool = philo->shared_data;
	pthread_mutex_lock(&pool->print_mutex);
	printf("%ld %lu %s\n", diff(pool), philo->id + 1, str);
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

void	is_eating(t_philo_data *philo)
{
	int	l;
	int	r;
	t_pool_data	pool;

	if (philo == NULL)
		return ;
	pool = philo->shared_data;
	init_l_r(philo->id, pool, &l, &r);
	pthread_mutex_lock(&pool->forks_mutex[l]);
	pthread_mutex_lock(&pool->forks_mutex[r]);
	if (pool->forks[l] && pool->forks[r])
	{
		print("is eating", philo);
		update_last_eat(philo);
		usleep(pool->arg.time_to_eat);
		pool->forks[l] = false;
		pool->forks[r] = false;
	}
	pthread_mutex_unlock(&pool->forks_mutex[r]);
	pthread_mutex_unlock(&pool->forks_mutex[l]);
}

void	is_thinking(t_philo_data *philo)
{
	if (philo == NULL)
		return ;
	print("is thinking", philo);
}

void	is_sleeping(t_philo_data *philo)
{
	t_pool_data	pool;

	if (philo == NULL)
		return ;
	pool = philo->shared_data;
	print("is sleeping", philo);
	usleep(pool->arg.time_to_sleep);
}

void	*routine(void *ptr)
{
	t_philo_data	*philo;
	t_pool_data		pool;

	if (ptr == NULL)
		return (NULL);
	philo = ptr;
	pool = philo->shared_data;
	unsigned long	a;
	unsigned long	b;
	while (42)
	{
		a = elapse_time(ptr);
		b = pool->arg.time_to_die;
//		if (a > b)
		{
			pthread_mutex_lock(&pool->print_mutex);
			printf("============%lu %lu\n", a, b);
			pthread_mutex_unlock(&pool->print_mutex);
		}
		take_fork(ptr);
		is_eating(ptr);
		is_thinking(ptr);
		is_sleeping(ptr);
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
