/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstadelw <fstadelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:22:01 by fstadelw          #+#    #+#             */
/*   Updated: 2018/12/30 18:48:53 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle,
					size_t len)
{
	size_t	i;
	size_t	j;

	if (needle[0] == '\0')
		return ((char *)haystack);
	if (haystack[0] == '\0')
		return ((char *)NULL);
	j = 0;
	i = 0;
	while (haystack[i] != '\0' && needle[j] != '\0' && i < len)
	{
		j = 0;
		while (needle[j] == haystack[i + j]
			&& needle[j] != '\0' && i + j < len)
			j++;
		i++;
	}
	i--;
	if (needle[j] == '\0')
		return ((char *)&haystack[i]);
	return ((char *)NULL);
}
