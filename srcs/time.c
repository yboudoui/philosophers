/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:50:19 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/18 17:54:52 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long	current_time(void)
{
	struct timeval	new;

	gettimeofday(&new, NULL);
	return ((new.tv_sec / 1e6) + new.tv_usec);
}

long	time_diff(long past, long present)
{
	return (present - past);
}

long	elapse_time(long val)
{
	return (val - current_time());
}
