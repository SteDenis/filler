/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnappend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstadelw <fstadelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 14:33:19 by fstadelw          #+#    #+#             */
/*   Updated: 2018/12/19 14:34:08 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnappend(char **str, char *end, size_t n)
{
	char	*rtn;
	size_t	str_len;

	str_len = ft_strlen(*str);
	rtn = ft_strnew(str_len + ft_strlen(end));
	if (rtn == NULL)
		return (NULL);
	ft_strcpy(rtn, *str);
	ft_strncpy(&rtn[str_len], end, n);
	ft_strdel(str);
	*str = rtn;
	return (rtn);
}
