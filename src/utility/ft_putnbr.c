/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 17:11:22 by stdenis           #+#    #+#             */
/*   Updated: 2018/11/13 17:27:23 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	ft_putnbr(int n)
{
	long int	res;

	res = n;
	if (n < 0)
		ft_putchar('-');
	res = (n < 0) ? (res * -1) : n;
	if (res > 9)
	{
		ft_putnbr(res / 10);
		ft_putchar((res % 10) + '0');
	}
	else
		ft_putchar(res + '0');
}
