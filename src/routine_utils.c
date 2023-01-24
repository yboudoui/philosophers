/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:51:28 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/24 18:18:25 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	death(bool lock, t_philo_data *philo)
{
	static int	(*func[MAX_HANDS])(pthread_mutex_t *) = {
		pthread_mutex_unlock, pthread_mutex_lock};

	func[lock](&philo->pool->dead_mutex);
}

inline bool	should_die(t_philo_data *philo)
{
	unsigned long	now;

	death(true, philo);
	now = time_now_millisecond();
	if (philo->pool->dead)
		return (death(false, philo), true);
	if ((now - philo->last_eat) >= philo->pool->arg.time_to_die)
		philo->pool->dead = true;
	else if (philo->pool->arg.eat && philo->pool->nb_eat == 0)
	{
		philo->pool->dead = true;
		print(philo, NO_MORE_MEAL);
		return (death(false, philo), true);
	}
	if (!philo->pool->dead)
		return (death(false, philo), false);
	print(philo, DIED);
	return (death(false, philo), true);
}

bool	try_wait_status(t_philo_data *philo, t_status status)
{
	unsigned long	start;
	unsigned long	now;
	uint64_t		ms;

	ms = 0;
	if (should_die(philo))
		return (false);
	if (status == HAS_TAKE_FORK)
		return (true);
	start = time_now_millisecond();
	now = start;
	if (status == MUST_WAIT_TO_DIE)
		ms = now - philo->last_eat + philo->pool->arg.time_to_die;
	else if (status == IS_EATING)
		ms = philo->pool->arg.time_to_eat;
	else if (status == IS_SLEEPING)
		ms = philo->pool->arg.time_to_sleep;
	while (ms && (now - start) < ms)
	{
		now = time_now_millisecond();
		if (should_die(philo))
			return (false);
		usleep(500);
	}
	return (true);
}

inline void	print(t_philo_data *philo, t_status status)
{
	const char	*message[MAX_STATUS] = {[IS_EATING] = "is eating",
	[IS_SLEEPING] = "is sleeping", [IS_THINKING] = "is thinking",
	[HAS_TAKE_FORK] = "has taken a fork", [DIED] = "died"};

	pthread_mutex_lock(&philo->pool->print_mutex);
	if (!philo->pool->print)
	{
		if (status != NO_MORE_MEAL)
		{
			printf("%ld %lu %s\n",
				elapse_time(philo), philo->id + 1, message[status]);
		}
		philo->pool->print = (status == DIED);
	}
	pthread_mutex_unlock(&philo->pool->print_mutex);
}
