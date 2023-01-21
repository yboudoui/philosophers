/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 07:36:50 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/21 14:24:17 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pool.h"

unsigned long	time_now_millisecond(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (((now.tv_sec * 1e6) + now.tv_usec) / 1e3);
}

unsigned long	elapse(struct timeval new, struct timeval old)
{
	unsigned long	a;
	unsigned long	b;

	a = (new.tv_sec * 1e6) + new.tv_usec;
	b = (old.tv_sec * 1e6) + old.tv_usec;
	return ((a - b) / 1e3);
}

unsigned long	elapse_time(t_philo_data *philo)
{
	struct timeval	new;
	t_pool_data		pool;

	pool = philo->shared_data;
	gettimeofday(&new, NULL);
	return (elapse(new, (*pool->start_time)));
}

t_pool_data	create_pool_data(t_input arg)
{
	size_t		size;
	size_t		index;
	t_pool_data	out;

	size = arg.number_of_philosophers;
	out = ft_calloc(1, sizeof(struct s_pool_data));
	if (out == NULL)
		return (NULL);
	out->forks = ft_calloc(size, sizeof(bool));
	out->forks_mutex = ft_calloc(size, sizeof(pthread_mutex_t));
	if (out->forks == NULL || out->forks_mutex == NULL)
		return (destroy_pool_data(out), NULL);
	index = 0;
	while (index < size)
		pthread_mutex_init(&(out->forks_mutex[index++]), NULL);
	pthread_mutex_init(&out->dead_mutex, NULL);
	pthread_mutex_init(&out->print_mutex, NULL);
	pthread_mutex_init(&out->mutex_start, NULL);
	out->size = size;
	out->arg = arg;
	return (out);
}

void	destroy_pool_data(void *data)
{
	size_t		index;
	t_pool_data	input;

	input = data;
	if (input == NULL)
		return ;
	index = 0;
	while (index < input->size)
		pthread_mutex_destroy(&input->forks_mutex[index++]);
	free(input->forks_mutex);
	free(input->forks);
	pthread_mutex_destroy(&input->dead_mutex);
	pthread_mutex_destroy(&input->mutex_start);
	free(input);
}
