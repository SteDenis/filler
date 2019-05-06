/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdenis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 12:55:37 by stdenis           #+#    #+#             */
/*   Updated: 2018/11/11 13:31:44 by stdenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static char	*ft_strcat(char *s1, const char *s2)
{
	size_t	i;
	size_t	ls1;

	i = 0;
	ls1 = ft_strlen(s1);
	while (s2[i])
	{
		s1[ls1 + i] = s2[i];
		i++;
	}
	s1[ls1 + i] = '\0';
	return (s1);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	ls1;
	size_t	ls2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	if (!(new = ft_strnew(ls1 + ls2)))
		return (NULL);
	new = ft_strcpy(new, s1);
	new = ft_strcat(new, s2);
	return (new);
}
