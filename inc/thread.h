/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 06:52:05 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/17 07:53:43 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include "memory.h"
# include <pthread.h>

typedef struct s_mutex	t_mutex;
struct s_mutex {
	void			*data
	pthread_mutex_t	lock;
};

t_mutex	create_mutex(void *data);
void	destroy_mutex(void *data);

#endif
