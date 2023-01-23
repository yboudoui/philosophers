/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_eating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:04:43 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/23 18:11:10 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static bool	lock_forks(t_philo_data *philo)
{
	bool	all_fork;

	if (should_die(philo))
		return (false);
	all_fork = true;
	pthread_mutex_lock(&philo->pool->forks_mutex[philo->fork[0]]);
	all_fork &= !philo->pool->forks[philo->fork[0]]--;
	if (all_fork)
		print(philo, HAS_TAKE_FORK);
	if (philo->pool->size == 1)
		return (print(philo, MUST_WAIT_TO_DIE));
	pthread_mutex_lock(&philo->pool->forks_mutex[philo->fork[1]]);
	all_fork &= !philo->pool->forks[philo->fork[1]]--;
	if (all_fork)
		print(philo, HAS_TAKE_FORK);
	return (all_fork);
}

static void	unlock_forks(t_philo_data *philo)
{
	if (philo->pool->size > 1)
	{
		philo->pool->forks[philo->fork[1]]--;
		pthread_mutex_unlock(&philo->pool->forks_mutex[philo->fork[1]]);
	}
	philo->pool->forks[philo->fork[0]]--;
	pthread_mutex_unlock(&philo->pool->forks_mutex[philo->fork[0]]);
}

bool	is_eating(t_philo_data *philo)
{
	bool		out;

	if (philo == NULL)
		return (false);
	if (philo->status != IS_EATING)
		return (true);
	out = lock_forks(philo);
	if (out)
	{
		if (philo->pool->arg.eat && philo->pool->nb_eat == 0)
		{
			pthread_mutex_lock(&philo->pool->print_mutex);
			philo->pool->dead = true;
			out = false;
			pthread_mutex_unlock(&philo->pool->print_mutex);
		}
		else
		{
			out = print(philo, IS_EATING);
			philo->last_eat = time_now_millisecond();
			philo->status = IS_SLEEPING;
			philo->pool->nb_eat -= (philo->pool->arg.meal == philo->nb_eat++);
		}
	}
	return (unlock_forks(philo), out);
}
