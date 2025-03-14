/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:45:22 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/16 15:47:01 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include <stddef.h>
# include <limits.h>
# include "memory.h"

bool	ft_isdigit(int c);
bool	ft_isspace(int c);

typedef bool	(*t_pf_is_charset)(int);

void	ft_skip(char **str, t_pf_is_charset charset);
bool	ft_atoi_to(char **str, int *result);

#endif
