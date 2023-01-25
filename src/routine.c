/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:50:48 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/25 12:29:01 by yboudoui         ###   ########.fr       */
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
		wait = !(*philo->pool->start);// && (philo->id % 2);
		pthread_mutex_unlock(&philo->pool->mutex_start);
		usleep(5);
	}
	pthread_mutex_lock(&philo->pool->mutex_start);
	philo->pool->is_all_started += 1;
	pthread_mutex_unlock(&philo->pool->mutex_start);
	update_last_eat(philo);
	if (philo->id % 2)
		usleep(500);
	return (true);
}

bool	is_sleeping(t_philo_data *philo)
{
	if (philo == NULL && should_die(philo))
		return (false);
	philo->status = IS_THINKING;
	print(philo, IS_SLEEPING);
	return (try_wait_status(philo, IS_SLEEPING));
}

bool	is_thinking(t_philo_data *philo)
{
	if (philo == NULL && should_die(philo))
		return (false);
//	if (philo->status != IS_THINKING)
//		return (true);
	philo->status = IS_EATING;
	print(philo, IS_THINKING);
	return (try_wait_status(philo, IS_THINKING));
}
