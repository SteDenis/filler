/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstadelw <fstadelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:22:01 by fstadelw          #+#    #+#             */
/*   Updated: 2018/11/10 19:31:50 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	itoa_size(int n)
{
	size_t		rtn;

	rtn = 1;
	if (n < 0)
	{
		n *= -1;
		rtn++;
	}
	while (n >= 10)
	{
		n /= 10;
		rtn++;
	}
	return (rtn);
}

char			*ft_itoa(int n)
{
	char		*rtn;
	int			i;
	int			tmp;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	rtn = ft_strnew(itoa_size(n));
	if (rtn == (char *)NULL)
		return ((char *)NULL);
	i = 0;
	if (n < 0)
		rtn[i++] = '-';
	n = n < 0 ? -n : n;
	tmp = 1;
	while (tmp * 10 <= 1000000000 && tmp * 10 < n)
		tmp *= 10;
	while (tmp >= 1)
	{
		rtn[i++] = (char)(n / tmp) + '0';
		n %= tmp;
		tmp /= 10;
	}
	rtn[i] = '\0';
	return (rtn);
}
