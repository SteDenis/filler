/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:04:00 by stdenis           #+#    #+#             */
/*   Updated: 2018/11/09 14:01:22 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_tabset(char **arr, void *val, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{
		arr[i] = val;
		i++;
	}
}

void	*ft_memset(void *b, int c, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{
		((unsigned char*)b)[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
