/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:52:04 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/25 11:09:28 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include "memory.h"
# include "fork.h"
# include "parser.h"
# include "philosopher.h"

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>

/* ************************************************************************** */
typedef struct s_pool_data			*t_pool_data;
typedef struct s_philosopher		*t_philosopher;
typedef struct s_philosopher_array	*t_philosopher_array;
typedef void						*(t_fp_routine)(void *);

typedef enum e_status {
	HAS_TAKE_FORK,
	IS_THINKING,
	IS_EATING,
	IS_SLEEPING,
	DIED,
	NO_MORE_MEAL,
	MAX_STATUS,
	MUST_WAIT_TO_DIE,
}	t_status;

/* ************************************************************************** */

typedef enum e_hands {
	RIGHT = false,
	LEFT = true,
	MAX_HANDS,
}	t_hands;

typedef struct s_philo_data {
	uint64_t		id;
	uint64_t		fork[MAX_HANDS];
	uint64_t		nb_eat;
	t_status		status;
	unsigned long	last_eat;
	t_pool_data		pool;
}	t_philo_data;

struct s_philosopher {
	t_philo_data	data;
	pthread_t		thread;
};

t_philosopher		create_philosopher(uint64_t id, t_pool_data pool);
void				destroy_philosopher(void *data);

/* ************************************************************************** */

struct s_philosopher_array {
	size_t			size;
	t_philosopher	*array;
};

t_philosopher_array	create_philosopher_array(size_t size, t_pool_data pool);
void				destroy_philosopher_array(void *data);

/* ************************************************************************** */

struct s_pool_data {
	bool				*start;
	size_t				is_all_started;
	struct timeval		*start_time;
	pthread_mutex_t		mutex_start;
	bool				dead;
	pthread_mutex_t		dead_mutex;
	bool				print;
	pthread_mutex_t		print_mutex;
	t_input				arg;
	size_t				nb_eat;
	pthread_mutex_t		mutex_eat;
	size_t				size;
	pthread_mutex_t		*forks_mutex;
	bool				*forks;
	t_philosopher_array	*philosophers;
};

t_pool_data			create_pool_data(t_input arg);
void				destroy_pool_data(void *data);

unsigned long		time_now_millisecond(void);
unsigned long		elapse_time(t_philo_data *philo);

/* ************************************************************************** */

typedef struct s_pool {
	t_pool_data			shared_data;
	t_philosopher_array	philosophers;
}	t_pool;

void				update_last_eat(t_philo_data *philo);
bool				should_die(t_philo_data *philo);
bool				try_wait_status(t_philo_data *philo, t_status status);
int					pool(t_input arg, t_fp_routine routine);
void				print(t_philo_data *philo, t_status status);

/* ************************************************************************** */
bool				wait_start(t_philo_data *philo);
bool				take_fork(t_philo_data *philo);
bool				is_eating(t_philo_data *philo);
bool				is_sleeping(t_philo_data *philo);
bool				is_thinking(t_philo_data *philo);
/* ************************************************************************** */
#endif
