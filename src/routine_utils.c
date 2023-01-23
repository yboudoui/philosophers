/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:51:28 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/23 18:09:05 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

bool	try_wait(uint64_t ms, t_philo_data *philo)
{
	unsigned long	start;
	unsigned long	now;

	start = time_now_millisecond();
	now = start;
	while ((now - start) < ms)
	{
		now = time_now_millisecond();
		if ((now - start) >= philo->pool->arg.time_to_die)
			return (false);
		usleep(500);
	}
	return (true);
}

bool	try_wait_status(t_philo_data *philo, t_status status)
{
	unsigned long	start;
	unsigned long	now;
	uint64_t		ms;

	start = time_now_millisecond();
	now = start;
	if ((now - philo->last_eat) >= philo->pool->arg.time_to_die)
		return (false);
	if (status == HAS_TAKE_FORK)
		return (true);
	ms = ((philo->pool->arg.time_to_die - (now - philo->last_eat)) / 10) * 7;
	if (status == MUST_WAIT_TO_DIE)
		ms = now - philo->last_eat + philo->pool->arg.time_to_die;
	if (status == IS_EATING)
		ms = philo->pool->arg.time_to_eat;
	else if (status == IS_SLEEPING)
		ms = philo->pool->arg.time_to_sleep;
	return (try_wait(ms, philo));
}

const char	*g_status_message[MAX_STATUS] = {
[IS_EATING] = "is eating",
[IS_SLEEPING] = "is sleeping",
[IS_THINKING] = "is thinking",
[HAS_TAKE_FORK] = "has taken a fork",
};

bool	should_die(t_philo_data *philo)
{
	bool	death;

	pthread_mutex_lock(&philo->pool->print_mutex);
	death = philo->pool->dead;
	pthread_mutex_unlock(&philo->pool->print_mutex);
	return (death);
}

bool	must_die(t_philo_data *philo)
{
	pthread_mutex_lock(&philo->pool->print_mutex);
	philo->pool->dead = true;
	pthread_mutex_unlock(&philo->pool->print_mutex);
	return (false);
}

bool	print(t_philo_data *philo, t_status status)
{
	unsigned long	now;

	if (philo == NULL)
		return (false);
	if (should_die(philo))
		return (false);
	pthread_mutex_lock(&philo->pool->print_mutex);
	now = time_now_millisecond();
	if (status == MUST_WAIT_TO_DIE
		|| (now - philo->last_eat) >= philo->pool->arg.time_to_die)
	{
		philo->pool->dead = true;
		try_wait_status(philo, status);
		printf("%ld %lu died\n", elapse_time(philo), philo->id + 1);
		return (pthread_mutex_unlock(&philo->pool->print_mutex), false);
	}
	if (philo->status < MAX_STATUS)
		printf("%ld %lu %s\n",
			elapse_time(philo), philo->id + 1,
			g_status_message[status]);
	pthread_mutex_unlock(&philo->pool->print_mutex);
	return (try_wait_status(philo, status));
}
