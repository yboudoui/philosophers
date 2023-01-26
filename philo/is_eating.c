/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_eating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:04:43 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/26 18:49:31 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static bool	lock_forks(t_philo_data *philo)
{
	pthread_mutex_lock(&philo->pool->forks_mutex[philo->fork[0]]);
	if (philo->pool->forks[philo->fork[0]] == false)
	{
		philo->pool->forks[philo->fork[0]] = true;
		print(philo, HAS_TAKE_FORK);
	}
	if (philo->pool->size == 1)
		return (try_wait_status(philo, MUST_WAIT_TO_DIE));
	pthread_mutex_lock(&philo->pool->forks_mutex[philo->fork[1]]);
	if (philo->pool->forks[philo->fork[1]] == false)
	{
		philo->pool->forks[philo->fork[1]] = true;
		print(philo, HAS_TAKE_FORK);
	}
	return (true
		&& philo->pool->forks[philo->fork[0]]
		&& philo->pool->forks[philo->fork[1]]);
}

static void	unlock_forks(t_philo_data *philo)
{
	if (philo->pool->size > 1)
	{
		if (philo->pool->forks[philo->fork[1]])
		{
			philo->pool->forks[philo->fork[1]] = false;
			pthread_mutex_unlock(&philo->pool->forks_mutex[philo->fork[1]]);
		}
	}
	if (philo->pool->forks[philo->fork[0]])
	{
		philo->pool->forks[philo->fork[0]] = false;
		pthread_mutex_unlock(&philo->pool->forks_mutex[philo->fork[0]]);
	}
}

void	update_last_eat(t_philo_data *philo)
{
	pthread_mutex_lock(&philo->pool->mutex_eat);
	philo->last_eat = time_now_millisecond();
	pthread_mutex_unlock(&philo->pool->mutex_eat);
}

bool	is_eating(t_philo_data *philo)
{
	bool	out;

	if (philo == NULL || should_die(philo))
		return (false);
	if (philo->status != IS_EATING)
		return (true);
	out = lock_forks(philo);
	if (out)
	{
		print(philo, IS_EATING);
		update_last_eat(philo);
		out = try_wait_status(philo, IS_EATING);
		philo->status = IS_SLEEPING;
		pthread_mutex_lock(&philo->pool->dead_mutex);
		philo->pool->nb_eat -= (philo->pool->arg.meal == ++philo->nb_eat);
		pthread_mutex_unlock(&philo->pool->dead_mutex);
	}
	return (unlock_forks(philo), out);
}
