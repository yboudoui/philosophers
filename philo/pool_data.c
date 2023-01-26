/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 07:36:50 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/23 18:01:48 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

unsigned long	time_now_millisecond(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (((now.tv_sec * 1e6) + now.tv_usec) / 1e3);
}

unsigned long	elapse_time(t_philo_data *philo)
{
	unsigned long	a;
	unsigned long	b;
	struct timeval	old;
	struct timeval	new;

	old = (*philo->pool->start_time);
	gettimeofday(&new, NULL);
	a = (new.tv_sec * 1e6) + new.tv_usec;
	b = (old.tv_sec * 1e6) + old.tv_usec;
	return ((a - b) / 1e3);
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
	out->start = ft_calloc(1, sizeof(bool));
	out->start_time = ft_calloc(1, sizeof(struct timeval));
	out->forks = ft_calloc(size, sizeof(bool));
	out->forks_mutex = ft_calloc(size, sizeof(pthread_mutex_t));
	if (!out->start || ! out->start_time || !out->forks || !out->forks_mutex)
		return (destroy_pool_data(out), NULL);
	index = 0;
	while (index < size)
		pthread_mutex_init(&(out->forks_mutex[index++]), NULL);
	pthread_mutex_init(&out->dead_mutex, NULL);
	pthread_mutex_init(&out->print_mutex, NULL);
	pthread_mutex_init(&out->mutex_start, NULL);
	out->size = size;
	out->arg = arg;
	out->nb_eat = size;
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
	free(input->start);
	free(input->start_time);
	free(input->forks_mutex);
	free(input->forks);
	pthread_mutex_destroy(&input->dead_mutex);
	pthread_mutex_destroy(&input->mutex_start);
	free(input);
}
