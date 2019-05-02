/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstadelw <fstadelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:22:01 by fstadelw          #+#    #+#             */
/*   Updated: 2018/11/09 21:56:00 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr_fd(int n, int fd)
{
	int		tmp;
	int		size;

	size = 0;
	if (n >= 0)
		n = n * -1;
	else
		ft_putchar_fd('-', fd);
	tmp = n;
	while (tmp <= -10)
	{
		tmp /= 10;
		size++;
	}
	while (size >= 0)
	{
		size--;
		tmp = n / ft_pow(10, size) % 10;
		if (tmp < 0)
			tmp *= -1;
		ft_putchar_fd(tmp % 10 + '0', fd);
	}
}
