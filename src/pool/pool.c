/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:33:11 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/21 14:19:39 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pool.h"

static void	run(t_philosopher_array philo, t_fp_routine routine)
{
	size_t	index;

	index = 0;
	while(index < philo->size)
	{
		pthread_create(
			&philo->array[index]->thread,
			NULL, routine,
			&philo->array[index]->data);
		index += 1;
	}
}

static void	wait(t_philosopher_array philo)
{
	size_t	index;

	index = 0;
	while(index < philo->size)
	{
		pthread_join(philo->array[index]->thread, NULL);
		index += 1;
	}
}

int	pool(t_input arg, t_fp_routine routine)
{
	t_pool_data			data;
	t_philosopher_array	philo;
	bool				*start;
	struct timeval		*start_time;

	start_time = ft_calloc(1, sizeof(struct timeval));
	start = ft_calloc(1, sizeof(bool));
	if (start == NULL)
		return (-21);
	data = create_pool_data(arg);
	if (data == NULL)
		return (-1);
	(*start) = false;
	data->start = start;
	data->start_time = start_time;
	philo = create_philosopher_array(arg.number_of_philosophers, data);
	if (philo == NULL)
		return (destroy_pool_data(data), -2);

	run(philo, routine);

	pthread_mutex_lock(&data->mutex_start);
	(*start) = true;
	gettimeofday(start_time, NULL);
	pthread_mutex_unlock(&data->mutex_start);

	wait(philo);

	destroy_philosopher_array(philo);
	destroy_pool_data(data);
	return (free(start), true);
}
