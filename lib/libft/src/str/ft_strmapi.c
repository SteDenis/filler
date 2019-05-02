/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstadelw <fstadelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:22:01 by fstadelw          #+#    #+#             */
/*   Updated: 2018/12/28 14:19:55 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*rtn;

	if (s == (char *)NULL || !f)
		return (NULL);
	rtn = ft_strnew(ft_strlen(s));
	if (rtn == (char *)NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		rtn[i] = f((unsigned int)i, s[i]);
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}
