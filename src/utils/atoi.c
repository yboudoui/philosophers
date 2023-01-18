/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:44:40 by yboudoui          #+#    #+#             */
/*   Updated: 2023/01/16 14:21:10 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

bool	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

bool	ft_isspace(int c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}

void	ft_skip(char **str, t_pf_is_charset charset)
{
	while (**str && charset(**str))
		(*str)++;
}

bool	ft_atoi_to(char **str, int *result)
{
	long long int	out;

	if (!result)
		return (false);
	ft_skip(str, ft_isspace);
	if (!ft_isdigit(**str))
		return (false);
	out = 0;
	while (ft_isdigit(**str))
		out = (out * 10) + (*(*str)++ - '0');
	if ((**str) || out < INT_MIN || out > INT_MAX)
		return (false);
	return (*result = out, true);
}
