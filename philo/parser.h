/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:47:36 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/25 11:26:49 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "utils.h"
# include <stdint.h>

typedef struct s_input {
	uint64_t	number_of_philosophers;
	uint64_t	time_to_die;
	uint64_t	time_to_eat;
	uint64_t	time_to_sleep;
	uint64_t	meal;
	bool		eat;
	uint64_t	time_to_think;
}	t_input;

int	parse_arg(int ac, char *av[], t_input *out);

#endif
