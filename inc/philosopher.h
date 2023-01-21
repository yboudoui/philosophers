/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:52:04 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/21 18:22:14 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdint.h>
# include <stdbool.h>
# include "memory.h"
# include <pthread.h>
# include <sys/time.h>

/* ************************************************************************** */

typedef enum e_hands {
	LEFT,
	RIGHT,
	MAX_HANDS,
}	t_hands;

typedef struct s_philo_data {
	pthread_mutex_t	mutex;
	uint64_t		id;
	unsigned long	last_eat;
	void			*shared_data;
}	t_philo_data;

typedef struct s_philosopher		*t_philosopher;
struct s_philosopher {
	t_philo_data	data;
	pthread_t		thread;
};

unsigned long		time_now_millisecond(void);
void				update_last_eat(t_philo_data *philo);

t_philosopher		create_philosopher(uint64_t id, void *shared_data);
void				destroy_philosopher(void *data);

/* ************************************************************************** */

typedef struct s_philosopher_array	*t_philosopher_array;
struct s_philosopher_array {
	size_t			size;
	t_philosopher	*array;
};

t_philosopher_array	create_philosopher_array(size_t size, void *shared_data);
void				destroy_philosopher_array(void *data);

/* ************************************************************************** */
#endif
