/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstadelw <fstadelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:22:01 by fstadelw          #+#    #+#             */
/*   Updated: 2018/11/10 00:00:27 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*rtn;

	if (s == (char *)NULL || ft_strlen(s) < (size_t)start + len)
		return ((char *)NULL);
	rtn = ft_strnew(len);
	if (rtn == (char *)NULL)
		return ((char *)NULL);
	ft_strncpy(rtn, &s[start], len);
	return (rtn);
}
