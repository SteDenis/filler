/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:10:21 by stdenis           #+#    #+#             */
/*   Updated: 2018/11/15 15:10:24 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "filler.h"

char	*ft_strdup(const char *src)
{
	size_t	l;
	size_t	i;
	char	*res;

	i = 0;
	l = ft_strlen((char*)src);
	if (!(res = (char *)malloc(sizeof(char) * (l + 1))))
		return (0);
	while (src[i] != '\0')
	{
		res[i] = src[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
