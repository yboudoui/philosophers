/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:56:30 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/21 17:59:23 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTINE_H
# define ROUTINE_H

# include "parser.h"
# include "pool.h"
# include <stdio.h>
# include <unistd.h>

void	init_l_r(uint64_t id, t_pool_data pool, int *l, int *r);
bool	anyone_died(t_philo_data *philo);
bool	must_die(t_philo_data *philo);
bool	try_wait(unsigned long ms, t_philo_data *philo);
void	print(char *str, t_philo_data *philo);
void	*routine(void *ptr);

#endif
