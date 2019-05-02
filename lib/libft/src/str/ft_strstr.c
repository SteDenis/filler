/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstadelw <fstadelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:22:01 by fstadelw          #+#    #+#             */
/*   Updated: 2018/11/09 16:02:37 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;

	if (needle[0] == '\0')
		return ((char *)haystack);
	if (haystack[0] == '\0')
		return ((char *)NULL);
	j = 0;
	i = 0;
	while (haystack[i] != '\0' && needle[j] != '\0')
	{
		j = 0;
		while (needle[j] == haystack[i + j] && needle[j] != '\0')
			j++;
		i++;
	}
	i--;
	if (needle[j] == '\0')
		return ((char *)&haystack[i]);
	return ((char *)NULL);
}
