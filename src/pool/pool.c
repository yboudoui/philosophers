/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:33:11 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/25 11:57:36 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	create_thread(t_philosopher_array philo, t_fp_routine routine)
{
	size_t	index;

	index = 0;
	while (index < philo->size)
	{
		pthread_create(
			&philo->array[index]->thread,
			NULL, routine,
			&philo->array[index]->data);
		index += 1;
	}
}

static void	launch_start(t_pool_data data)
{
	pthread_mutex_lock(&data->mutex_start);
	(*data->start) = true;
	gettimeofday(data->start_time, NULL);
	pthread_mutex_unlock(&data->mutex_start);
	while (42)
	{
		usleep(100);
		pthread_mutex_lock(&data->mutex_start);
		if (data->is_all_started == data->size)
			return ((void)pthread_mutex_unlock(&data->mutex_start));
		pthread_mutex_unlock(&data->mutex_start);
	}
}

/*static*/ void	silent_kill(t_pool_data data)
{
	size_t			index;
	t_philosopher	philo;
	unsigned long	now;

	while (true)
	{
		index = 0;
		usleep(100);
		while (index < (*data->philosophers)->size)
		{
			philo = (*data->philosophers)->array[index];
			pthread_mutex_lock(&data->mutex_eat);
			now = time_now_millisecond();
			if ((now - philo->data.last_eat) >= data->arg.time_to_die)
			{
				should_die(&philo->data);
				return ((void)pthread_mutex_unlock(&data->mutex_eat));
			}
			pthread_mutex_unlock(&data->mutex_eat);
			index++;
		}
	}
}

static void	wait(t_philosopher_array philo)
{
	size_t	index;

	index = 0;
	while (index < philo->size)
	{
		pthread_join(philo->array[index]->thread, NULL);
		index += 1;
	}
}

int	pool(t_input arg, t_fp_routine routine)
{
	t_pool_data			data;
	t_philosopher_array	philo;

	data = create_pool_data(arg);
	if (data == NULL)
		return (-1);
	philo = create_philosopher_array(arg.number_of_philosophers, data);
	if (philo == NULL)
		return (destroy_pool_data(data), -2);
	data->philosophers = &philo;
	create_thread(philo, routine);
	launch_start(data);
	silent_kill(data);
	wait(philo);
	destroy_philosopher_array(philo);
	destroy_pool_data(data);
	return (true);
}
