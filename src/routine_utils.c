/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:51:28 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/22 18:32:45 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

bool	try_wait(t_philo_data *philo)
{
	unsigned long	start;
	unsigned long	now;
	uint64_t		ms;

	start = time_now_millisecond();
	now = start;
	ms = ((now - philo->last_eat) / 10) * 9;
	if (philo->status == HAS_TAKE_FORK)
		return (true);
	if (philo->status == IS_EATING)
		ms = philo->pool->arg.time_to_eat;
	else if (philo->status == IS_SLEEPING)
		ms = philo->pool->arg.time_to_sleep;
	while ((now - start) < ms)
	{
		now = time_now_millisecond();
		if ((now - start) >= philo->pool->arg.time_to_die)
			return (false);
		usleep(500);
	}
	return (true);
}

const char	*g_status_message[MAX_STATUS] = {
[IS_EATING] = "is eating",
[IS_SLEEPING] = "is sleeping",
[IS_THINKING] = "is thinking",
[HAS_TAKE_FORK] = "has taken a fork",
};

bool	print(t_philo_data *philo)
{
	unsigned long	now;

	if (philo == NULL)
		return (false);
	pthread_mutex_lock(&philo->pool->print_mutex);
	if (philo->pool->dead)
		return (pthread_mutex_unlock(&philo->pool->print_mutex), false);
	now = time_now_millisecond();
	if ((now - philo->last_eat) >= philo->pool->arg.time_to_die)
	{
		philo->pool->dead = true;
		printf("%ld %lu died\n", elapse_time(philo), philo->id + 1);
		return (pthread_mutex_unlock(&philo->pool->print_mutex), false);
	}
	printf("%ld %lu %s\n",
			elapse_time(philo), philo->id + 1,
			g_status_message[philo->status]);
	return (pthread_mutex_unlock(&philo->pool->print_mutex), try_wait(philo));
}
