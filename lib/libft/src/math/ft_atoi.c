/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstadelw <fstadelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:22:01 by fstadelw          #+#    #+#             */
/*   Updated: 2018/12/28 14:35:24 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	long	i;
	long	rtn;
	char	is_neg;

	i = 0;
	rtn = 0;
	is_neg = '+';
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		is_neg = str[i++];
	if (str[i] == '+' && is_neg == '-')
		return (0);
	i += (str[i] == '+');
	while (str[i] >= '0' && str[i] <= '9')
	{
		rtn *= 10;
		rtn += str[i] - '0';
		i++;
	}
	if (rtn < 0)
		return ((is_neg != '-') * -1);
	if (is_neg == '-')
		rtn *= -1;
	return ((int)rtn);
}
