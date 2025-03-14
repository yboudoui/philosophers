/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:34:23 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/21 18:22:37 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORK_H
# define FORK_H

# include "memory.h"
# include <stdbool.h>
# include <pthread.h>

/* ************************************************************************** */

typedef struct s_fork		*t_fork;
struct s_fork {
	pthread_mutex_t	mutex;
	bool			is_taken;
};

t_fork			create_fork(void);
void			destroy_fork(void *data);

/* ************************************************************************** */

typedef struct s_fork_array	*t_fork_array;
struct s_fork_array {
	size_t	size;
	t_fork	*array;
};

t_fork_array	create_fork_array(size_t size);
void			destroy_fork_array(void *data);

/* ************************************************************************** */

#endif
