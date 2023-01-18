/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 07:36:50 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/18 18:14:52 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pool.h"

unsigned long	diff(t_pool_data data)
{
	struct timeval	new;

	gettimeofday(&new, NULL);
	new.tv_sec -= data->start_time.tv_sec;
	new.tv_usec -= data->start_time.tv_usec;
	unsigned long out = (new.tv_sec * 1e6) + new.tv_usec;
	return (out / 1000);
}

unsigned long	elapse_time(t_philo_data *philo)
{
	t_pool_data		pool;
	struct timeval	new;

	pool = philo->shared_data;
	gettimeofday(&new, NULL);
	new.tv_sec -= pool->start_time.tv_sec - philo->last_eat.tv_sec;
	new.tv_usec -= pool->start_time.tv_usec - philo->last_eat.tv_usec;
	unsigned long out = (new.tv_sec * 1e6) + new.tv_usec;
	return (out / 1000);
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
	//pthread_mutex_init(&out->dead_mutex, NULL);
	pthread_mutex_init(&out->print_mutex, NULL);
	out->size = size;
	out->arg = arg;
	gettimeofday(&out->start_time, NULL);
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
	//pthread_mutex_destroy(&input->dead_mutex);
	free(input);
}
