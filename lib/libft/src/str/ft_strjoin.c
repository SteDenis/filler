/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstadelw <fstadelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:22:01 by fstadelw          #+#    #+#             */
/*   Updated: 2018/12/19 11:04:18 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*rtn;
	size_t	s1_len;

	s1_len = ft_strlen(s1);
	rtn = ft_strnew(s1_len + ft_strlen(s2));
	if (rtn == (char *)NULL)
		return ((char *)NULL);
	ft_strcpy(rtn, s1);
	ft_strcpy(&rtn[s1_len], s2);
	return (rtn);
}
