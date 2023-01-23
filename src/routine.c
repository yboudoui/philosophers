/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:50:48 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/23 18:00:25 by yboudoui         ###   ########.fr       */
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

bool	is_sleeping(t_philo_data *philo)
{
	if (philo == NULL)
		return (false);
	if (should_die(philo))
		return (false);
	if (philo->status != IS_SLEEPING)
		return (true);
	return (philo->status = IS_THINKING, print(philo, IS_SLEEPING));
}

bool	is_thinking(t_philo_data *philo)
{
	if (philo == NULL)
		return (false);
	if (should_die(philo))
		return (false);
	if (philo->status != IS_THINKING)
		return (true);
	return (philo->status = IS_EATING, print(philo, IS_THINKING));
}
