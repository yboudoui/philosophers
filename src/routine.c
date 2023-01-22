/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:50:48 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/22 20:25:26 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

bool	wait_start(t_philo_data *philo)
{
	bool			wait;

	if (philo == NULL)
		return (false);
	wait = true;
	while (wait)
	{
		pthread_mutex_lock(&philo->pool->mutex_start);
		wait = !(*philo->pool->start);
		pthread_mutex_unlock(&philo->pool->mutex_start);
		usleep(5);
	}
	philo->last_eat = time_now_millisecond();
	return (true);
}

void	mutex_fork(bool lock, t_philo_data *philo, t_hands hand)
{
	static int	(*func[MAX_HANDS])(pthread_mutex_t *) = {
		pthread_mutex_unlock,
		pthread_mutex_lock,
	};

	if (philo->pool->size == 1 && hand == RIGHT)
		return ;
	func[lock](&philo->pool->forks_mutex[philo->fork[hand]]);
}

bool	take_fork(t_philo_data *philo)
{
	if (philo == NULL)
		return (false);
	mutex_fork(true, philo, LEFT);
	mutex_fork(true, philo, RIGHT);
	if (philo->pool->forks[philo->fork[LEFT]] == false)
	{
		philo->pool->forks[philo->fork[LEFT]] = true;
		print(philo, HAS_TAKE_FORK);
		if (philo->pool->size == 1)
			print(philo, MUST_WAIT_TO_DIE);
	}
	if (philo->pool->forks[philo->fork[RIGHT]] == false)
	{
		philo->pool->forks[philo->fork[RIGHT]] = true;
		print(philo, HAS_TAKE_FORK);
	}
	mutex_fork(false, philo, RIGHT);
	mutex_fork(false, philo, LEFT);
	return (true);
}

bool	is_eating(t_philo_data *philo)
{
	bool		out;

	out = true;
	if (philo == NULL)
		return (false);
	mutex_fork(true, philo, LEFT);
	mutex_fork(true, philo, RIGHT);
	if (philo->pool->forks[philo->fork[LEFT]]
		&& philo->pool->forks[philo->fork[RIGHT]])
	{
		out = print(philo, IS_EATING);
		philo->last_eat = time_now_millisecond();
		philo->pool->forks[philo->fork[LEFT]] = false;
		philo->pool->forks[philo->fork[RIGHT]] = false;
	}
	mutex_fork(false, philo, RIGHT);
	mutex_fork(false, philo, LEFT);
	return (out);
}

bool	is_sleeping(t_philo_data *philo)
{
	if (philo == NULL)
		return (false);
	return (print(philo, IS_SLEEPING));
}

bool	is_thinking(t_philo_data *philo)
{
	if (philo == NULL)
		return (false);
	return (print(philo, IS_THINKING));
}
